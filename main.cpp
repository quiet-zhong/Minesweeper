#include "MainWindow.h"
#include <QApplication>
#include <QFinalState>
#include <QTextCodec>

#if 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#endif


#if 0
#include <QApplication>
#include <QPushButton>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    QPushButton *button = new QPushButton("“Animated Button”");
    button->show();
    QStateMachine *machine = new QStateMachine;
    //QState *state1 = new QState(machine->rootState());
    QState *state1 = new QState(machine);
    state1->assignProperty(button, "“geometry”", QRect(0, 0, 150, 30));
    machine->setInitialState(state1);
    //QState *state2 = new QState(machine->rootState());
    QState *state2 = new QState(machine);
    state2->assignProperty(button, "“geometry”", QRect(250, 250, 150, 30));
    QSignalTransition *transition1 = state1->addTransition(button,
                                                           SIGNAL(clicked()), state2);
    transition1->addAnimation(new QPropertyAnimation(button, "“geometry”"));
    QSignalTransition *transition2 = state2->addTransition(button,
                                                           SIGNAL(clicked()), state1);
    transition2->addAnimation(new QPropertyAnimation(button, "“geometry”"));
    machine->start();
    app.exec();
}

#endif


#if 0
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    QWidget *w=new QWidget();
    w->resize(300,400);

    QPixmap birdimg=QPixmap("../aaa.png").scaled(40,40);

    QLabel *bird_1=new QLabel(w);
    bird_1->setPixmap(birdimg);

    QPropertyAnimation *anim1=new QPropertyAnimation(bird_1, "pos");
    anim1->setDuration(2000);
    anim1->setStartValue(QPoint(0, 360));
    anim1->setEndValue(QPoint(110, 180));
//    anim1->setEasingCurve(QEasingCurve::OutBounce);
//    anim1->start();


    QLabel *bird_2=new QLabel(w);
    bird_2->setPixmap(QPixmap("../start.png"));

    QPropertyAnimation *anim2=new QPropertyAnimation(bird_2, "pos");
    anim2->setDuration(2000);
    anim2->setStartValue(QPoint(0, 0));
    anim2->setEndValue(QPoint(150, 180));
//    anim2->setEasingCurve(QEasingCurve::OutBounce);
    anim2->setEasingCurve(QEasingCurve::CosineCurve);

    /*
        Linear,
        InQuad, OutQuad, InOutQuad, OutInQuad,
        InCubic, OutCubic, InOutCubic, OutInCubic,
        InQuart, OutQuart, InOutQuart, OutInQuart,
        InQuint, OutQuint, InOutQuint, OutInQuint,
        InSine, OutSine, InOutSine, OutInSine,
        InExpo, OutExpo, InOutExpo, OutInExpo,
        InCirc, OutCirc, InOutCirc, OutInCirc,
        InElastic, OutElastic, InOutElastic, OutInElastic,
        InBack, OutBack, InOutBack, OutInBack,
        InBounce, OutBounce, InOutBounce, OutInBounce,
        InCurve, OutCurve, SineCurve, CosineCurve,
        BezierSpline, TCBSpline, Custom, NCurveTypes

    */

    QSequentialAnimationGroup group;
//    QParallelAnimationGroup group;
    group.addAnimation(anim1);
    group.addAnimation(anim2);
    group.start();

    bird_1->move(-40,-40);
    bird_2->move(-40,-40);



    w->show();
    return app.exec();
}

#endif
