#include "chooselevelscene.h"
#include <qpainter.h>
#include "mypushbutton.h"
#include <qlabel.h>
#include <qtimer.h>
#include <qsound.h>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
//    //关卡音效
//    QSound * chooseSound = new QSound(":/TapButtonSound.wav",this);
//    //返回按钮音效
//    QSound * backSound = new QSound(":/BackButtonSound.wav",this);


    //设置固定尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置图标
    this->setWindowIcon(QPixmap(":/Coin0001.png"));

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/BackButton.png",":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width()-5,this->height() - backBtn->height()-10);

    connect(backBtn,&MyPushButton::clicked,this,[=](){

//        backSound->play();  //播放音效

        //发送点击返回的信号
        emit this->ChooseSceneBack();
    });

    pScene = NULL;

    //创建关卡按钮
    for(int i = 0; i < 20; i++){
        MyPushButton * menuBtn = new MyPushButton(":/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move( 25 + (i % 4)*70, 150 + (i/4)*70 );

        connect(menuBtn, &MyPushButton::clicked,this,[=]{

//            chooseSound->play();    //播放音效

            this->pScene = new PlayScene(i+1);
            this->pScene->setGeometry(this->geometry());   //同步场景位置
            this->pScene->show();       //显示关卡场景
            this->hide();

            //监听关卡场景中返回按钮的信号
            connect(this->pScene,&PlayScene::ChooseSceneBack,this,[=]{
                QTimer::singleShot(100,this,[=]{
                    this->setGeometry(this->pScene->geometry());   //同步场景位置
                    this->pScene->hide();  //关卡场景隐藏
                    this->show();   //选关界面显示

                    delete this->pScene;
                    this->pScene = NULL;
                });
            });

        });

        //显示关卡数字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->move( 25 + (i % 4)*70, 150 + (i/4)*70 );
        //设置尺寸
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        //设置文本
        label->setText(QString::number(i+1));
        //设置对齐方式
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置鼠标穿透属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

//设置背景
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //创建画家对象
    QPainter painter(this);

    //创建QPixmap对象
    QPixmap pix;
    pix.load(":/OtherSceneBg.png");

    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题资源
    pix.load(":/Title.png");

    //绘制标题
    painter.drawPixmap((this->width() - pix.width())*0.5,30,pix);
}















































