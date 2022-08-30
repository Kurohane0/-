#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:

    //参数1 正常显示图片路径 参数2按下后切换图片路径
    MyPushButton(QString normalimg,QString pressimg = "");

    QString normalPath;     //默认显示图片路径
    QString pressPath;      //按下后显示图片路径

    //向下跳跃
    void zoom1();

    //向上跳跃
    void zoom2();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYPUSHBUTTON_H


















































