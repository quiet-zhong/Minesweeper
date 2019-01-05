#include "GameWidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent),
      m_flagInit(true),
      m_flagGameOver(false),
      m_clickCount(0)
{

    m_VboxLayout = new QVBoxLayout;
    m_GridLayout = new QGridLayout;
    m_GridLayout->setHorizontalSpacing(0);
    m_GridLayout->setVerticalSpacing(0);
    m_HboxLayout = new QHBoxLayout;

    //添加水平布局
    m_HboxLayout->addStretch();
    m_lcdTimer = new QLCDNumber;

    //创建一个定时器
    m_timer = new QTimer;

    m_HboxLayout->addWidget(m_lcdTimer);
    m_HboxLayout->addStretch();
    m_buttonStart = new QPushButton(QIcon(QPixmap(":/resource/start.png")),"",this);
    connect(m_buttonStart,SIGNAL(clicked()),this,SLOT(slotNewGame()));
    m_buttonStart->setIconSize(QSize(40,40));
    m_buttonStart->setFlat(true);
    m_HboxLayout->addWidget(m_buttonStart);
    m_HboxLayout->addStretch();
    m_lcdMineNum= new QLCDNumber;
    m_HboxLayout->addWidget(m_lcdMineNum);
    m_HboxLayout->addStretch();

    m_VboxLayout->addLayout(m_HboxLayout);
    m_VboxLayout->addLayout(m_GridLayout);



    this->setLayout(m_VboxLayout);

    //初始化游戏难度等级
    setGameLevel(9,9,10,m_flagInit);

    connect(this,SIGNAL(sigGameOver()),this,SLOT(slotGameOver()));
}

MyWidget::~MyWidget()
{
    for(int i=0;i<m_wide;i++)
    {
        for(int j=0;j<m_high;j++)
        {
            delete static_cast<Block*>(m_GridLayout->itemAtPosition(i,j)->widget());
        }
    }

    delete m_timer;
    delete m_lcdTimer;     //计时器
    delete m_lcdMineNum;   //计量剩余雷数
    delete m_buttonStart;

    delete m_HboxLayout;
    delete m_GridLayout;
    delete m_VboxLayout;
}

int MyWidget::mineTotalNum() const
{
    return m_mineTotalNum;
}

int MyWidget::high() const
{
    return m_high;
}

int MyWidget::wide() const
{
    return m_wide;
}

//设置游戏难度等级
void MyWidget::setGameLevel(int wide,int high,int mineTotalNum,bool flagInit)
{
    //如果不是第一次玩，删除所有标签类
    if(!flagInit)
    {
        for(int i=0;i<m_wide;i++)
        {
            for(int j=0;j<m_high;j++)
            {
                delete static_cast<Block*>(m_GridLayout->itemAtPosition(i,j)->widget());
            }
        }
    }
    //所有变量初始化
    m_wide = wide;
    m_high = high;
    m_mineTotalNum = mineTotalNum;
    m_blockTotalNum = m_wide*m_high;
    m_turnOverNum = 0;
    m_flagGameOver = false;
    m_timeNum = 0;
    m_mineLcdNum = m_mineTotalNum;
    m_clickCount = 0;

    //设置鼠标形状
    this->setCursor(Qt::ClosedHandCursor);

    //LCD显示时间
    m_lcdTimer->display(m_timeNum);
    //设置定时器每个多少毫秒发送一个timeout()信号
    m_timer->setInterval(1000);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimeUpdate()));

    //LCD 显示雷的总数
    m_lcdMineNum->display(m_mineLcdNum);

    bool blockAry[m_blockTotalNum];
    //创建总雷数的true
    for(int i=0; i<m_mineTotalNum; i++)
        blockAry[i] = true;
    //创建剩余数的false
    for(int i=m_mineTotalNum; i<m_blockTotalNum; i++)
        blockAry[i] = false;

    //产生随机数布置雷的分布
    QTime t_time;
    t_time = QTime::currentTime();
    qsrand(t_time.msec() + t_time.second()*1000);
    //将数组放入随机容器
    std::random_shuffle(blockAry,blockAry + m_blockTotalNum);

    for(int i=0;i<m_wide;i++)
    {
        for(int j=0;j<m_high;j++)
        {
            m_block = new Block;
            m_block->m_flagIsMine = blockAry[i * m_high + j];
            m_GridLayout->addWidget(m_block,i,j);
        }
    }
    //统计每一个方格周围的雷数,并关联左键点击和右键点击的信号
    for(int i=0;i<m_wide;i++)
    {
        for(int j=0;j<m_high;j++)
        {
            Block* current_block = static_cast<Block*>(m_GridLayout->itemAtPosition(i,j)->widget());
            current_block->setNumber(calculateMines(i,j));
            connect(current_block,SIGNAL(sigIsMine(bool)),this,SLOT(slotIsMine(bool)));
            connect(current_block,SIGNAL(sigMark(bool)),this,SLOT(slotMark(bool)));
            current_block->installEventFilter(this);
        }
    }

    setFixedSize(sizeHint());
}


//计算点(x,y)周围的雷数
int MyWidget::calculateMines(int x, int y)
{
    int number = 0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if( (x+i-1>=0) && (x+i-1<m_wide) && (y+j-1>=0) && (y+j-1<m_high) )
                if(static_cast<Block*>(m_GridLayout->itemAtPosition(x+i-1,y+j-1)->widget())->m_flagIsMine )
                    ++number;
    return number;
}

/** **********************************************/
//自动翻周围无雷标记的块
void MyWidget::blockAutoSpread(int x,int y)
{
    QQueue<QPair<int,int> > queue;
    QPair<int,int> pair;
    queue.enqueue(qMakePair(x,y));
    while(!queue.isEmpty())
    {
        pair=queue.head();
        queue.dequeue();
        if(calculateMines(pair.first,pair.second) == 0)
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    if( (pair.first-1+i >= 0) && (pair.first-1+i < m_wide) && (pair.second-1+j >= 0) && (pair.second-1+j < m_high) )
                    {
                        if(!static_cast<Block*>(m_GridLayout->itemAtPosition(pair.first-1+i,pair.second-1+j)->widget())->isTurnOver())
                        {
                            static_cast<Block*>(m_GridLayout->itemAtPosition(pair.first-1+i,pair.second-1+j)->widget())->turnOver();
                            ++m_turnOverNum;
                            qDebug() << "翻开的数量"<< m_turnOverNum;
                            queue.enqueue(qMakePair(pair.first-1+i,pair.second-1+j));
                        }
                    }
                }
            }
        }
    }
    //如果翻开的数量等于总数量减去总的雷数，发送游戏成功信号
    if(m_turnOverNum == m_blockTotalNum - m_mineTotalNum)
    {
        m_flagGameOver = true;

        //发送游胜利的信号
        qDebug() << "GameWidget send  sigGameWin  signal";
        sigGameWin(m_timeNum);
        m_timer->stop();
    }
}



void MyWidget::slotIsMine(bool t_bl)
{
    qDebug() << "GameWidget slotIsMine recived signal"<< t_bl;

    m_clickCount++;
    qDebug()<<" click count " << m_clickCount << endl;
    //如果是第一次点击,启动定时器
    if(m_clickCount == 1)
    {
        qDebug()<< "第一次点击左键启动定时器";
        //启动定时器
        m_timer->start();
    }
    if(!t_bl)
    {
        for(int i=0;i<m_wide;i++)
        {
            for(int j=0;j<m_high;j++)
            {
                Block* current_block = static_cast<Block*>(m_GridLayout->itemAtPosition(i,j)->widget());
                if(current_block == this->sender())
                {
                    qDebug() << "i = "<< i << " j = "<< j;
                    m_turnOverNum++;
                    blockAutoSpread(i,j);
                }
            }
        }
    }
    else
    {
        qDebug() << "游戏结束";
        m_flagGameOver = true;
        qDebug() << "GameWidget send  sigGameOver  signal";
        this->sigGameOver();
    }
}

void MyWidget::slotMark(bool t_bl)
{
    qDebug() << "GameWidget slotMark recived signal";
    m_clickCount++;
    //如果是第一次点击,启动定时器
    if(m_clickCount == 1)
    {
        qDebug()<< "第一次点击右键启动定时器" << endl;
        //启动定时器
        m_timer->start();
    }
    //被标记
    if(t_bl && m_mineLcdNum > 0)
    {
        m_mineLcdNum--;
    }
    //取消标记
    else if(!t_bl && m_mineLcdNum<m_mineTotalNum)
    {
        m_mineLcdNum++;
    }
    m_lcdMineNum->display(m_mineLcdNum);
}

void MyWidget::slotGameOver()
{
    qDebug() << "GameWidget slotGameOver  recived signal";
    if(m_flagGameOver)
    {
        m_timer->stop();
        m_timer->disconnect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimeUpdate()));
        //将所有的雷翻开
        for(int i=0;i<m_wide;i++)
        {
            for(int j=0;j<m_high;j++)
            {
                Block* current_block = static_cast<Block*>(m_GridLayout->itemAtPosition(i,j)->widget());
                if(current_block->m_flagIsMine)
                {
                    current_block->setPixmap(QPixmap(":/resource/mine.png"));
                }
            }
        }
        QMessageBox::information(this,tr("游戏结果"),"<center>真  的  很  遗  憾!     "
                                                    "<br>你 踩 到 了     "
                                                    "<br>雷               "
                                                    "<br>不 要 灰 心                    "
                                                    "<br>再接再厉!                      "
                                                    "<br>^_^</center>");
        slotNewGame();
    }

}

void MyWidget::slotNewGame()
{
    qDebug() << "Gamewidget slotNewGame  recived signal";
    m_timer->stop();
    disconnect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimeUpdate()));
    qDebug() << "GameWidget send  sigNewGame  signal";
    this->sigNewGame();
    setGameLevel(m_wide,m_high,m_mineTotalNum,false);
}


void MyWidget::slotTimeUpdate()
{
//    qDebug() << "GameWidget slotTimeUpdate  recived signal";
    m_timeNum++;
    m_lcdTimer->display(m_timeNum);
}

