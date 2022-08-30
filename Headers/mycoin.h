#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <qtimer.h>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString img);

    int posX;   //x坐标
    int posY;   //y坐标
    bool flag;  //正反标志

    void changeFlag();  //翻转金币
    QTimer *timer1;     //金币翻银币 定时器
    QTimer *timer2;     //银币翻金币 定时器
    int min = 1;    //最小图片
    int max = 8;    //最大图片

    bool isAnimation = false;   //翻转动画标志

    //重写鼠标按下事件，实现禁用鼠标点击
    void mousePressEvent(QMouseEvent *e);

    bool isWin = false; //通关标识

signals:

};

#endif // MYCOIN_H






















