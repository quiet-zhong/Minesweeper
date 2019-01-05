#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QTextCodec>
#include <QWidget>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include "GameBlock.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    QPushButton *m_buttonStart; //开始按钮

    //设置游戏参数，行，列，雷数
    void setGameLevel(int wide,int high,int mineTotalNum,bool flagInit);
    //自动扩散
    void blockAutoSpread (int x,int y);

    int calculateMines(int x,int y);

    bool    m_flagInit;     //初始化标志
    bool    m_flagGameOver; //游戏结束标志

    QTimer  *m_timer;       //时间定时器

    /** **********获取变量的函数******** */
    int wide() const;
    int high() const;
    int mineTotalNum() const;

signals:
    void sigGameOver();     //游戏结束信号
    void sigNewGame();      //新游戏的信号
    void sigGameWin(int timeNum);      //游戏胜利信号

public slots:

    void slotIsMine(bool t_bl);
    void slotMark(bool t_bl);
    void slotGameOver();
    void slotNewGame();
    void slotTimeUpdate();

private:
    QVBoxLayout *m_VboxLayout;      //垂直布局
    QHBoxLayout *m_HboxLayout;      //水平布局
    QGridLayout *m_GridLayout;      //栅格布局


    QLCDNumber  *m_lcdTimer;        //时间显示器
    QLCDNumber  *m_lcdMineNum;      //剩余雷数显示器

    Block       *m_block;           //方块

    int     m_wide;             //横向个量
    int     m_high;             //纵向个数
    int     m_mineTotalNum;     //雷的总数
    int     m_blockTotalNum;    //总的方块
    int     m_turnOverNum;      //已经翻开的方块数
    int     m_clickCount;       //统计点击次数

    int     m_timeNum;          //所用时间数（第一个LCD数字）
    int     m_mineLcdNum;       //还剩下的雷数(第二个LCD数字)
};

#endif // MYWIDGET_H
