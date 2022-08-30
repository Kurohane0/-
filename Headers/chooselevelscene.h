#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //绘图事件
    void paintEvent(QPaintEvent *);

    //维护关卡场景的指针
    PlayScene * pScene;

signals:
    //自定义点击返回按钮的信号
    void ChooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
