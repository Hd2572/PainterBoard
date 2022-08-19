#ifndef MYPAINT_H
#define MYPAINT_H

#include "container.h"
/*

    画图板类

*/
class MyPaint : public QMainWindow
{
    Q_OBJECT
  public:
    explicit MyPaint(QWidget* parent = nullptr);

  protected:
    void mousePressEvent(QMouseEvent*);         //重载鼠标按下函数
    void mouseReleaseEvent(QMouseEvent*);       //重载鼠标松开函数
    void mouseMoveEvent(QMouseEvent*);          //重载鼠标移动函数
    void contextMenuEvent(QContextMenuEvent*);  //重载鼠标右键
    void paintEvent(QPaintEvent*);              //重载重绘函数
    void keyPressEvent(QKeyEvent* e);           //重载快捷键设置

  private:
    Container cont;  //容器

  signals:

  public slots:
    void OpenPic();   //打开图片
    void SavePic();   //保存图片
    void NewPaint();  //新建画板
    void Rescind();   //撤销
    void Lines();     //铅笔画线
    void Line();      //画直线
    void Eraser();    //橡皮
    void Rects();     //画矩形
    void Ellipses();  //画椭圆

    void ChoseClr();     //选画笔颜色
    void ChosefilClr();  //选填充颜色
    void Unfill();       //设置无填充
    void ChoseWid();     //选线宽
};

#endif  // MYPAINT_H
