#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <qtimer.h>
#include <qsound.h>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

//    //准备音效
//    QSound * startSound = new QSound(":/TapButtonSound.wav",this);

    //设置固定尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币");
    //设置图标
    this->setWindowIcon(QPixmap(":/Coin0001.png"));

    //创建第二个选关场景
    this->chooseScene = new ChooseLevelScene;

    //创建开始按钮
    MyPushButton *startBtn = new MyPushButton(":/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.7);
    connect(startBtn,&MyPushButton::clicked,this,[=](){

//        //播放音效
//        startSound->play();

        startBtn->zoom1();  //向下跳跃
        startBtn->zoom2();  //向上跳跃

        //延时进入第二个场景
        QTimer::singleShot(200,this,[=]{
            this->chooseScene->setGeometry(this->geometry());   //同步场景位置
            this->chooseScene->show();  //选关场景显示
            this->hide();   //开始界面隐藏
        });
    });

    //监听选关场景中返回按钮的信号
    connect(this->chooseScene,&ChooseLevelScene::ChooseSceneBack,this,[=]{
        QTimer::singleShot(100,this,[=]{
            this->setGeometry(this->chooseScene->geometry());   //同步场景位置
            this->chooseScene->hide();  //选关场景隐藏
            this->show();   //开始界面显示
        });
    });
}

//绘图事件
void MainScene::paintEvent(QPaintEvent *){
    //创建画家对象
    QPainter painter(this);

    //创建QPixmap对象
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");

    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题资源
    pix.load(":/Title.png");

    //绘制标题
    painter.drawPixmap(26,40,pix);

}

MainScene::~MainScene()
{
    delete ui;
}



















