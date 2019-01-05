#include "GameBlock.h"

Block::Block(QWidget* parent)
    : QLabel(parent),
      m_flagIsMine(false),  //初始化为不是雷
      m_flagLeft(false),    //初始化为左键未点击状态
      m_flagRight(false),   //初始化为右键未点击状态
      m_number(0)         //初始化周围累数为0
{
    //设置初始状态显示图片
    setPixmap(QPixmap(":/resource/normal.png"));
    //设置鼠标移动时不需要按下就可触发mouseMoveEvent，即鼠标跟踪
//    this->setMouseTracking(true);


}

Block::~Block()
{

}

//鼠标点击事件
void Block::mousePressEvent(QMouseEvent *ev)
{
    //如果点击的是左键,左右键都没被点
    if(ev->button() == Qt::LeftButton && !m_flagRight && !m_flagLeft)
    {
         qDebug() <<"左键 m_flagIsMine = " << m_flagIsMine;
        //如果是雷
        if(m_flagIsMine)
        {
            setPixmap(QPixmap(":/resource/mine.png"));
            QSound::play(":/resource/boom.wav");
        }
        else
        {
            //设置成和雷数匹配的图片
            setPixmap(QPixmap(":/resource/img_mine_" + QString("%1").arg(m_number) + ".png") );
        }

        //更改左键的flag为true
        m_flagLeft = true;

        sigIsMine(m_flagIsMine);
        QSound::play(":/resource/clicked.wav");
     }

    //如果点击的是右键,并且左键未点击
    if(ev->button() == Qt::RightButton && !m_flagLeft)
    {
        //如果右键没有点击
        if( !m_flagRight)
        {
            //设置成旗帜标记图片
            setPixmap(QPixmap(":/resource/flag.png"));
            qDebug() <<"右键标记";
            m_flagRight = true;
        }
        //如果右键被点击
        else
        {
            //设置成初始图片
            setPixmap(QPixmap(":/resource/normal.png"));
            qDebug() <<"右键取消标记";
            m_flagRight = false;
        }
        //发送信号
        sigMark(m_flagRight);
        qDebug()<< " 发送信号 m_flag = " << m_flagRight;
    }
}

void Block::mouseMoveEvent(QMouseEvent *e)
{
    e->accept();
//     if(enterBtn(e->pos(),ui->SystemSetButton))
     {
//       ui->SystemSetButton->setSizeIncrement(163,91);
//       QIcon *MouseOnIcon = new QIcon(":/new/prefix1/back/系统设置2.png");
//       ui->SystemSetButton->setIcon(*MouseOnIcon);
     }
}

void Block::setNumber(const int &t_number)
{
    m_number = t_number;
}

bool Block::isTurnOver()
{
    if(m_flagLeft)
        return true;
    else
        return false;
}

void Block::turnOver()
{
    if(!m_flagIsMine)
    {
        //设置成和雷数匹配的图片
        setPixmap(QPixmap(":/resource/img_mine_" + QString("%1").arg(m_number) + ".png") );
    }
    m_flagLeft = true;
}



