#ifndef GAMEBLOCK_H
#define GAMEBLOCK_H

#include <QTextCodec>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

#include <QDebug>
#include <QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QQueue>
#include <QStateMachine>
#include <QFinalState>


class Block : public QLabel
{
    Q_OBJECT

public:
    explicit Block(QWidget* parent = 0);

    ~Block();

    //重写鼠标事件
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *e);
    //设置周围雷数
    void setNumber(const int & number);

    bool m_flagIsMine;  //是否是雷

    //是不是已经被翻开
    bool isTurnOver();
    //将图片翻开
    void turnOver();



signals:
    void sigIsMine(bool);
    void sigMark(bool);

private:

    bool m_flagLeft;    //是否被左键点击
    bool m_flagRight;   //是否被右键标记
    int  m_number;      //周围雷的数量


};

#endif // BLOCK_H
