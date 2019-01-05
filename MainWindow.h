#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextCodec>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>

#include "ui_dlgGameDiyLevel.h"
#include "ui_dlgGameWin.h"

#include "GameWidget.h"
#include "MySql.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


signals:


public slots:
    void    slotNewGame();       //新游戏
    void    slotTop();           //成绩排行榜
    void    slotMusic();         //开启或关闭音效

    void    slotLevelEasy();     //简单水平
    void    slotLevelMiddle();   //中等水平
    void    slotLevelHard();     //困难水平
    void    slotLevelDiy();      //自定义水平

    void    slotHelp();          //帮助
    void    slotAbout();         //关于游戏

    void    slotGameWin(int timeNum);       //游戏成功


private:
    /** ****私有成员变量******* */
    //菜单栏
    QMenu *m_menuGame;              //菜单_游戏
    QMenu *m_menuSet;               //菜单_设置
    QMenu *m_menuHelp;              //菜单_帮助

    QAction *m_actionNewGame;       //新游戏
    QAction *m_actionTop;           //成绩排行榜
    QAction *m_actionMusic;         //音效
    QAction *m_actionExit;          //退出游戏

    QAction *m_actionLevelEasy;     //简单水平
    QAction *m_actionLevelMiddle;   //中等水平
    QAction *m_actionLevelHard;     //困难水平
    QAction *m_actionLevelDiy;      //自定义水平

    QAction *m_actionHelp;          //帮助
    QAction *m_actionAbout;         //关于游戏

    QSound  *m_music;               //背景音乐

    //游戏界面
    MyWidget *m_widget;

    //dialog
    QDialog m_dialog;

    /** *****私有成员函数******* */
    //创建action
    void createAction();
    //创建目录
    void createMenu();
    //创建状态栏
    void createStatusBar();
    //设置窗口属性
    void setGameWindow();





};

#endif // MAINWINDOW_H
