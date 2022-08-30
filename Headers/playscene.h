#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);   //参数为当前关卡号

    int levelIndex;     //记录当前关卡号

    void paintEvent(QPaintEvent *);     //绘制背景

    //二维数组数据 初始化关卡
    int gameArray[4][4];

    //所有硬币的二维数组，用来找周围的硬币
    MyCoin * coinBtn[4][4];

    bool isWin = true;  //是否通关

signals:
    //自定义点击返回按钮的信号
    void ChooseSceneBack();
};

#endif // PLAYSCENE_H
