#include "mycoin.h"
#include <qdebug.h>


MyCoin::MyCoin(QString img)
{
    QPixmap pix;
    bool ret = pix.load(img);
    if(!ret){
        QString str = QString("图标加载失败，失败路径为：%1").arg(img);
        qDebug() << str;
        return;
    }

    //设置按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

    //创建定时器
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    //监听金币翻银币的定时器
    connect(this->timer1,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str = QString(":/Coin000%1.png").arg(this->min++);
        bool ret = pix.load(str);
        if(!ret){
            QString str1 = QString("图标加载失败，失败路径为：%1").arg(str);
            qDebug() << str1;
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min > this->max){
            this->min = 1;
            this->timer1->stop();
            isAnimation = false;
        }
    });

    //监听银币翻金币的定时器
    connect(this->timer2,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str = QString(":/Coin000%1.png").arg(this->max--);
        bool ret = pix.load(str);
        if(!ret){
            QString str1 = QString("图标加载失败，失败路径为：%1").arg(str);
            qDebug() << str1;
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min){
            this->max = 8;
            this->timer2->stop();
            isAnimation = false;
        }
    });
}

//点击金币 翻转
void MyCoin::changeFlag()
{
    if(this->flag){
        this->timer1->start(30);    //金币翻银币
        this->flag = false;
    }
    else{
        this->timer2->start(30);    //金币翻银币
        this->flag = true;
    }

    isAnimation = true;
}

//动画期间 或游戏通关 禁用鼠标点击
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin ){
        return;
    }
    else{
        QPushButton::mousePressEvent(e);
    }
}




























