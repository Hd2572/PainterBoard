#ifndef MYPAINT_H
#define MYPAINT_H

#include <QAction>
#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QPoint>
#include <QToolBar>
#include <QToolButton>
#include <QVector>
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
  public:
  private:
    QColor _color;      //当前画笔颜色
    QColor _fillcolor;  //当前填充颜色
    QMenu* _Help;       //右键帮助菜单
    QPixmap _pixmap;    //当前画布图片

    int _isfill;    //填充标志
    int _width;     //线宽
    int _lpress;    //鼠标按下标志
    int _drag;      //拖拽标志
    int _eraing;    //橡皮标志
    int _drawType;  //当前绘画类型标志
    int _style;     //线型
    int _openflag;  //是否打开文件

  public:
    QVector<QVector<QPoint> > _pen;     //铅笔线容器
    QVector<QVector<QPoint> > _eraser;  //橡皮线容器
    QVector<QColor> _colors;            //颜色容器
    QVector<QColor> _fillcolors;        //填充色容器
    QVector<QRect> _rects;              //矩形容器
    QVector<QRect> _ellipse;            //椭圆容器
    QVector<QRect> _line;               //直线容器
    QVector<int> _widths;               //宽度容器
    QVector<int> _isfills;              //填充色容器
    QVector<int> _styles;               //线型容器
    QVector<int> _shape;                //全部容器
    QPoint _begin;                      //动作开始坐标
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
