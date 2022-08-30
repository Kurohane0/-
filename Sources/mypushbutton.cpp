#include "mypushbutton.h"
#include <qdebug.h>
#include "QPropertyAnimation"

//参数1 正常显示图片路径 参数2按下后切换图片路径
MyPushButton::MyPushButton(QString normalimg,QString pressimg){

    this->normalPath = normalimg;
    this->pressPath = pressimg;

    //创建QPixmap对象
    QPixmap pix;
    bool ret = pix.load(this->normalPath);
    if(!ret){
        QString str = QString("图标加载失败，失败路径为：%1").arg(this->normalPath);
        qDebug() << str;
    }

    //设置按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

//向下跳跃
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置动画间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);    //参数：执行后删除对象

}

//向上跳跃
void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置动画间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

//鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //路径不为空，切换图片
    if(this->pressPath != ""){

        //创建QPixmap对象
        QPixmap pix;
        bool ret = pix.load(this->pressPath);
        if(!ret){
            QString str = QString("图标加载失败，失败路径为：%1").arg(this->pressPath);
            qDebug() << str;
        }

        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //父类处理其余事件
    QPushButton::mousePressEvent(e);

}

//鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //路径不为空，还原图片
    if(this->pressPath != ""){

        //创建QPixmap对象
        QPixmap pix;
        bool ret = pix.load(this->normalPath);
        if(!ret){
            QString str = QString("图标加载失败，失败路径为：%1").arg(this->normalPath);
            qDebug() << str;
        }

        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //父类处理其余事件
    QPushButton::mouseReleaseEvent(e);

}































