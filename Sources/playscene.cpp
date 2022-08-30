#include "playscene.h"
#include <qpainter.h>
#include "mypushbutton.h"
#include <qlabel.h>
#include "mycoin.h"
#include "dataconfig.h"
#include "qpropertyanimation.h"
#include <qsound.h>

PlayScene::PlayScene(int index)
{
    this->levelIndex = index;

//    //返回按钮音效
//    QSound * backSound = new QSound(":/BackButtonSound.wav",this);
//    //翻金币音效
//    QSound * flipSound = new QSound(":/ConFlipSound.wav",this);
//    //胜利音效
//    QSound * winSound = new QSound(":/LevelWinSound.wav",this);

    //设置固定尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币");
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

    //显示当前关卡号
    QLabel * label = new QLabel;
    label->setParent(this);
    QString str = QString("Level: %1").arg(this->levelIndex);
    label->setText(str);
    QFont font("华文新魏",15);
    label->setFont(font);
    //设置标签大小、位置
    label->setGeometry(QRect(20,this->height() - 50,this->width(),50));
    //设置鼠标穿透属性
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

    //胜利图片
    QLabel * winLabel = new QLabel;
    winLabel->setParent(this);
    QPixmap pix;
    pix.load(":/LevelCompletedDialogBg.png");
    winLabel->setPixmap(pix);
    winLabel->setGeometry(0,0,pix.width(),pix.height());
    winLabel->move(this->width()*0.5 - pix.width()*0.5, -pix.height());

    //初始化关卡的二维数组
    dataConfig config;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }


    //创建金币的背景图片
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){

            QLabel * label = new QLabel;
            QPixmap pix;
            pix.load(":/BoardNode.png");
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i*pix.width(),200 + j*pix.height());

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1){
                str = ":/Coin0001.png";
            }
            else{
                str = ":/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*pix.width(),204 + j*pix.height());

            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];

            this->coinBtn[i][j] = coin;

            //点击硬币 调用changeFlag
            connect(coin,&MyCoin::clicked,this,[=](){

                //flipSound->play();  //播放音效

                //禁用所有金币点击
                for(int i = 0; i < 4; i++){
                    for(int j = 0;j < 4; j++){
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();

                //翻转周围硬币
                QTimer::singleShot(100,this,[=]{
                    //右侧
                    if(coin->posX + 1 <= 3){
                        this->coinBtn[coin->posX+1][coin->posY]->changeFlag();
                    }
                    //左侧
                    if(coin->posX - 1 >= 0){
                        this->coinBtn[coin->posX-1][coin->posY]->changeFlag();
                    }
                    //上侧
                    if(coin->posY - 1 >= 0){
                        this->coinBtn[coin->posX][coin->posY-1]->changeFlag();
                    }
                    //下侧
                    if(coin->posY + 1 <= 3){
                        this->coinBtn[coin->posX][coin->posY+1]->changeFlag();
                    }

                    //检测是否通关
                    this->isWin = true;
                    for(int i=0; i<4; i++){
                        for(int j=0; j<4; j++){
                            if(this->coinBtn[i][j]->flag == false){
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(isWin == true){
                        //设置游戏胜利标识
                        for(int i=0; i<4; i++){
                            for(int j=0; j<4; j++){
                                this->coinBtn[i][j]->isWin = true;
                            }
                        }

                        //winSound->play();  //播放音效

                        //显示胜利图片
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),
                                                       winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y() + 175,
                                                     winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start(QAbstractAnimation::DeleteWhenStopped);
                    }
                    else{
                        //解除所有金币点击禁用
                        for(int i = 0; i < 4; i++){
                            for(int j = 0;j < 4; j++){
                                this->coinBtn[i][j]->isWin = false;
                            }
                        }
                    }
                });


            });

        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
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
    pix = pix.scaled(pix.width()*0.6,pix.height()*0.6);
    painter.drawPixmap(15,20,pix);

}































