#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建action
    createAction();
    //创建目录
    createMenu();
    //创建状态栏
    createStatusBar();
    //设置窗口属性
    setGameWindow();
    //背景音乐
    m_music = new QSound(":/resource/music2.wav");
    m_music->play();
//    m_music->setLoops(10);



//    QSound::play(":/resource/music1.wav");

}

MainWindow::~MainWindow()
{
    delete m_menuGame;
    delete m_menuSet;
    delete m_menuHelp;
    delete m_widget;
    delete m_music;

}

/** *******************创建菜单栏，动作，状态栏******************** */

void MainWindow::createAction()
{
    m_actionNewGame = new QAction("新游戏(&New)",this);
    m_actionNewGame->setShortcuts(QKeySequence::New);
    m_actionNewGame->setStatusTip(tr("开始新游戏"));
    connect(m_actionNewGame, SIGNAL(triggered()), this, SLOT(slotNewGame()));
    m_actionTop = new QAction("排行榜(&Top)",this);
    m_actionTop->setStatusTip(tr("成绩排行榜"));
    connect(m_actionTop, SIGNAL(triggered()), this, SLOT(slotTop()));

    m_actionMusic = new QAction("游戏音效(&Music)",this);
    m_actionMusic->setStatusTip(tr("打开或关闭背景音乐"));
    connect(m_actionMusic, SIGNAL(triggered()), this, SLOT(slotMusic()));

    m_actionExit = new QAction("退出(&Exit)",this);
    m_actionExit->setShortcuts(QKeySequence::Close);
    m_actionExit->setStatusTip(tr("退出游戏"));
    connect(m_actionExit, SIGNAL(triggered()), this, SLOT(close()));

    m_actionLevelEasy = new QAction("简单(&Easy)",this);
    m_actionLevelEasy->setStatusTip(tr("设置简单难度"));
    connect(m_actionLevelEasy, SIGNAL(triggered()), this, SLOT(slotLevelEasy()));

    m_actionLevelMiddle = new QAction("中等(&Middle)",this);
    m_actionLevelMiddle->setStatusTip(tr("设置中等难度"));
    connect(m_actionLevelMiddle, SIGNAL(triggered()), this, SLOT(slotLevelMiddle()));

    m_actionLevelHard = new QAction("困难(&Hard)",this);
    m_actionLevelHard->setStatusTip(tr("设置困难难度"));
    connect(m_actionLevelHard, SIGNAL(triggered()), this, SLOT(slotLevelHard()));

    m_actionLevelDiy = new QAction("自定义(&Diy)",this);
    m_actionLevelDiy->setStatusTip(tr("自定义游戏难度"));
    connect(m_actionLevelDiy, SIGNAL(triggered()), this, SLOT(slotLevelDiy()));

    m_actionHelp = new QAction("帮助(&Help)",this);
    m_actionHelp->setStatusTip(tr("帮助"));
    connect(m_actionHelp, SIGNAL(triggered()), this, SLOT(slotHelp()));

    m_actionAbout = new QAction("关于(&About)",this);
    m_actionAbout->setStatusTip(tr("查看游戏的来历"));
    connect(m_actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));

}


void MainWindow::createMenu()
{
    menuBar()->addMenu(m_menuGame = new QMenu("游戏(&G)"));
    m_menuGame->addAction(m_actionNewGame);
    m_menuGame->addAction(m_actionTop);
    m_menuGame->addAction(m_actionMusic);
    m_menuGame->addAction(m_actionExit);

    menuBar()->addMenu(m_menuSet = new QMenu("设置(&S)"));
    m_menuSet->addAction(m_actionLevelEasy);
    m_menuSet->addAction(m_actionLevelMiddle);
    m_menuSet->addAction(m_actionLevelHard);
    m_menuSet->addAction(m_actionLevelDiy);

    menuBar()->addMenu(m_menuHelp = new QMenu("帮助(&H)"));
    m_menuHelp->addAction(m_actionHelp);
    m_menuHelp->addAction(m_actionAbout);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("点击方块开始游戏"));
}

void MainWindow::setGameWindow()
{
    //设置窗口标题
    setWindowTitle("扫雷小游戏_聂世忠制作");
    setWindowIcon(QIcon(QPixmap(":/resource/gameicon.png")));
    //设置背景颜色为纯白色
    setStyleSheet("background-color:white;");
//    setStyleSheet("background-color:lightblue;");
//    setStyleSheet("background-color:rgb(0, 170, 255);");

    //游戏界面
    m_widget = new MyWidget(this);
    //开始按钮
    connect(m_widget,SIGNAL(sigNewGame()),this,SLOT(slotNewGame()));
    //游戏胜利
    connect(m_widget,SIGNAL(sigGameWin(int)),this,SLOT(slotGameWin(int)));
    //设置中心组件
    this->setCentralWidget(m_widget);

}

/** *******************槽函数******************** */
void MainWindow::slotNewGame()
{
    qDebug() << "MainWindow slotNewGame recived signal";
    m_widget->m_timer->stop();
//    m_widget->m_timer->disconnect(m_widget->m_timer,SIGNAL(timeout()),m_widget,SLOT(slotTimeUpdate()));

    m_widget->setGameLevel(m_widget->wide(),m_widget->high(),m_widget->mineTotalNum(),false);
}

//查看排行榜(总分)
void MainWindow::slotTop()
{
    qDebug() << "查看排行榜 slot";
    QWidget *t_widget = new QWidget;
    TopWidget *t_wgt = new TopWidget(t_widget,
        "select name 姓名,easyscores 简单,middlescores 中等,"
        "hardscores 困难 from Minesweeper order by  "
        "ifnull(easyscores,0) + "
        "ifnull(middlescores,0) + "
        "ifnull(hardscores,0) desc");
    t_widget->setWindowTitle("扫雷英雄榜");
    t_widget->show();
}

void MainWindow::slotMusic()
{
    static int i = 0;
    i++;
    qDebug() << "music signal" << i;
    if( i%2 == 0)
        m_music->play();
    else
        m_music->stop();
}

//简单难度
void MainWindow::slotLevelEasy()
{
    qDebug() << "简单难度 slot";
    delete m_widget;
    m_widget = new MyWidget(this);
    //    设置中心组件
    this->setCentralWidget(m_widget);
    m_widget->m_flagInit = false;
    m_widget->setGameLevel(9,9,10,false);
}

//中等难度
void MainWindow::slotLevelMiddle()
{
    qDebug() << "中等难度 slot";
    delete m_widget;
    m_widget = new MyWidget(this);
    //    设置中心组件
    this->setCentralWidget(m_widget);
    m_widget->m_flagInit = false;
    m_widget->setGameLevel(16,16,40,false);
}

//困难水平
void MainWindow::slotLevelHard()
{
    qDebug() << "困难水平 slot";
    delete m_widget;
    m_widget = new MyWidget(this);
    //    设置中心组件
    this->setCentralWidget(m_widget);

    m_widget->m_flagInit = false;
    m_widget->setGameLevel(16,30,99,false);
}

//自定义游戏难度
void MainWindow::slotLevelDiy()
{
    qDebug() << "自定义游戏 slot";
    Ui::dlgGameLevel t_dlg;
    t_dlg.setupUi(&m_dialog);

    int ret = m_dialog.exec();

    int  t_high = t_dlg.spinBox_col->value();
    int  t_wide = t_dlg.spinBox_row->value();
    int t_mineNum = t_dlg.spinBox_MineNum->value();

    if(ret == QDialog::Accepted)
    {
        qDebug() << t_wide << t_high <<  t_mineNum;
        delete m_widget;
        m_widget = new MyWidget(this);
        //设置中心组件
        this->setCentralWidget(m_widget);

        m_widget->m_flagInit = false;
        m_widget->m_timer->stop();
        m_widget->m_timer->disconnect(m_widget->m_timer,SIGNAL(timeout()),m_widget,SLOT(slotTimeUpdate()));

        m_widget->setGameLevel(t_wide,t_high,t_mineNum,false);
    }
}


void MainWindow::slotHelp()
{
    qDebug() << "MainWindow recived  slotHelp  signal";

    QMessageBox::information(this,"先说两句","<center>"
                                       "^~^     <br>"
                                       "连个扫雷都不会玩         <br>"
                                       "这个让我很无语          <br>"
                                       "因为你浪费了我的劳动成果          <br>"
                                       "如果想获取帮助           <br>"
                                       "联系我             <br>"
                                       "记得请我吃饭哦          </center>");
    QMessageBox::information(this,"帮助","<center> 雷决八条："
                             "第一条：基本定式不要忘，现场推理真够呛。<br>"
                             "第二条：鼠标点击不要快，稳定节奏把空开。<br>"
                             "第三条：顺手标雷不要惯，积累下来记录悬。<br>"
                             "第四条：无从下手不要愣，就近猜雷把心横。<br>"
                             "第五条：遇到猜雷不要怕，爆了脸上不留疤。<br>"
                             "第六条：猜雷猜错不要悔，哭天抢地也白费。<br>"
                             "第七条：碰上好局不要慌，紧盯局部慢扩张。<br>"
                             "第八条：痛失好局不要恨，既然有缘定有份。<br>""</center>");
}


void MainWindow::slotAbout()
{
    qDebug() << "MainWindow recived  slotAbout  signal";
    QMessageBox::information(this,"关于","<center>"
                                       "本游戏            <br>"
                                       "是由一个新手     <br>"
                                       "夜以继日             <br>"
                                       "瘦了70斤             <br>"
                                       "才完成的              <br>"
                                       "很多功能不完善         <br>"
                                       "如果不满意            <br>"
                                       "你打我啊！       </center>");
}


void MainWindow::slotGameWin(int timeNum)
{
    qDebug() << "MainWindow recived  slotGameWin  signal";
    Ui::DialogGameWin t_dlg;
    t_dlg.setupUi(&m_dialog);

    int t_score = 0;//将时间转化为成绩
    qDebug() << "success time: " << timeNum;
    //显示时间成绩
    QString t_strScore = "Time : " + QString("%4").arg(timeNum) +"  S ";
    t_dlg.label_score->setText(t_strScore);

    int ret = m_dialog.exec();


    if(ret == QDialog::Accepted)
    {
        QString t_name =  t_dlg.lineEdit->text();

        //判断游戏难度等级 ,拼接sql语句
        QString t_str;
        if(m_widget->wide() == 9 && m_widget->high() == 9)
        {
            t_score = 1000 - timeNum;//将时间转化为成绩
            t_str = "insert into Minesweeper(name,easyscores) values('"
                                    + t_name
                                    + "',"
                                    + QString("%3").arg(t_score)
                                    +")" ;
        }
        else if(m_widget->wide() == 16 && m_widget->high() == 16)
        {
            t_score = 2000 - timeNum;//将时间转化为成绩
            t_str = "insert into Minesweeper(name,middlescores) values('"
                                    + t_name
                                    + "',"
                                    + QString("%4").arg(t_score)
                                    +")" ;
        }

        else if(m_widget->wide() == 16 && m_widget->high() == 30)
        {
            t_score = 3000 - timeNum;//将时间转化为成绩
            t_str = "insert into Minesweeper(name,hardscores) values('"
                                + t_name
                                + "',"
                                + QString("%4").arg(t_score)
                                +")" ;
        }
        qDebug() << t_str ;

        //链接数据库插入数据
        TopWidget t_wgt(this,t_str);
        qDebug()<< "数据库插入数据";
    }
    //开始新游戏
    slotNewGame();
    qDebug() << "MainWindow recived  slotNewGame  signal";

}
/**
  SQL语句
  创建
create table Minesweeper(
name varchar(20),
easyscores int,
middlescores int,
hardscores int
);

插入
insert into Minesweeper(
name,easyscores,
middlescores,hardscores)
 values('zhao',776,
1704,2032);

排序查询
select name,easyscores,middlescores,
hardscores from Minesweeper order by
ifnull(easyscores,0) + ifnull(middlescores,0) + ifnull(hardscores,0) desc
*/






