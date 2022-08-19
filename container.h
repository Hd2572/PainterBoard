#ifndef CONTAINER_H
#define CONTAINER_H

#include <QAction>
#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMouseEvent>
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QPoint>
#include <QToolBar>
#include <QToolButton>
#include <QVector>
/*
    容器类
*/
class Container : public QObject
{
    Q_OBJECT
  public:
    explicit Container(QObject* parent = nullptr);

  public:
    QColor _color;                      //当前画笔颜色
    QColor _fillcolor;                  //当前填充颜色
    QMenu* _Help;                       //右键帮助菜单
    int _isfill;                        //填充标志
    int _width;                         //线宽
    int _lpress;                        //鼠标按下标志
    int _drag;                          //拖拽标志
    int _eraing;                        //橡皮标志
    int _drawType;                      //当前绘画类型标志
    int _style;                         //线型
    int _openflag;                      //是否打开文件
    QPixmap _pixmap;                    //当前画布图片
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
    QPoint _begin;                      //开始坐标
  public slots:
};

#endif  // CONTAINER_H
