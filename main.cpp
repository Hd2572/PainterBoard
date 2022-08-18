#include <QApplication>

#include "mypaint.h"
/*
    程序设计实践大作业：Qt画图板
    2022/8/15
*/

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QApplication::setDoubleClickInterval(500);  //设置鼠标点击间隔，连击触发画图

    MyPaint* w = new MyPaint();
    w->setWindowIcon(QIcon(":/images/1.png"));  //窗口图标
    w->show();

    return a.exec();
}
