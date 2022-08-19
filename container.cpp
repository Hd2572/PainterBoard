#include "container.h"

Container::Container(QObject* parent) : QObject(parent)
{
    _lpress = false;  //各成员初始化
    _drawType = 0;
    _drag = 0;
    _eraing = 0;
    _openflag = 0;
    _width = 1;
    _style = 1;
    _isfill = 0;
    _color = QColor(Qt::black);
    _fillcolor = QColor(Qt::white);
}
