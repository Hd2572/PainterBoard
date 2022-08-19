#include "mypaint.h"

MyPaint::MyPaint(QWidget* parent) : QMainWindow(parent)
{
    cont._begin = pos();

    this->setGeometry(400, 150, 900, 680);  //设置主窗口位置、大小、背景色
    this->setStyleSheet("background-color:white;");

    setMouseTracking(true);  //开始鼠标追踪

    QToolBar* tbar = addToolBar(tr("工具栏"));                 //工具栏设置
    tbar->setMovable(false);                                   //固定
    tbar->setIconSize(QSize(30, 30));                          //图标大小
    tbar->setStyleSheet("background-color:rgb(201,163,201)");  //颜色

    //添加工具栏选项
    QAction* openAction = new QAction("打开", this);  //打开文件
    openAction->setIcon(QIcon(":/images/open.png"));  //设置图标
    openAction->setShortcut(QKeySequence("Ctrl+O"));  //快捷键
    tbar->addAction(openAction);                      //添加到工具栏，以下各项同

    QAction* newAction = new QAction("新建", this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    tbar->addAction(newAction);

    QAction* saveAction = new QAction("保存", this);  //保存文件
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    tbar->addAction(saveAction);

    QAction* lineAction = new QAction("直线", this);  //直线
    lineAction->setIcon(QIcon(":/images/line.png"));
    lineAction->setShortcut(QKeySequence(tr("Ctrl+L")));
    tbar->addAction(lineAction);
    lineAction->setCheckable(true);  //设置按钮可按下，以下各项同

    QAction* linesAction = new QAction("铅笔", this);  //铅笔
    linesAction->setIcon(QIcon(":/images/pen.png"));
    linesAction->setShortcut(QKeySequence("Ctrl+P"));
    tbar->addAction(linesAction);
    linesAction->setCheckable(true);

    QAction* eraserAction = new QAction("橡皮擦", this);  //橡皮
    eraserAction->setIcon(QIcon(":/images/eraser.png"));
    eraserAction->setShortcut(QKeySequence("Ctrl+A"));
    tbar->addAction(eraserAction);
    eraserAction->setCheckable(true);

    QAction* rectAction = new QAction("矩形", this);  //矩形动作
    rectAction->setIcon(QIcon(":/images/rect.png"));
    rectAction->setShortcut(QKeySequence("Ctrl+R"));
    tbar->addAction(rectAction);
    rectAction->setCheckable(true);

    QAction* ellipseAction = new QAction("椭圆", this);  //椭圆动作
    ellipseAction->setIcon(QIcon(":/images/ellipse.png"));
    ellipseAction->setShortcut(QKeySequence("Ctrl+E"));
    tbar->addAction(ellipseAction);
    ellipseAction->setCheckable(true);

    QAction* colorAction = new QAction("颜色", this);  //画笔颜色
    colorAction->setIcon(QIcon(":/images/color.png"));
    colorAction->setShortcut(QKeySequence("Ctrl+C"));
    tbar->addAction(colorAction);

    QAction* fillAction = new QAction("颜色", this);  //填充颜色
    fillAction->setIcon(QIcon(":/images/spray.png"));
    fillAction->setShortcut(QKeySequence("Ctrl+F"));
    tbar->addAction(fillAction);

    QAction* widthAction = new QAction("线宽", this);  //线宽
    widthAction->setIcon(QIcon(":/images/size.png"));
    widthAction->setShortcut(QKeySequence("Ctrl+W"));
    tbar->addAction(widthAction);

    QActionGroup* groupAction = new QActionGroup(this);  //设置可按下按钮互斥
    groupAction->addAction(lineAction);
    groupAction->addAction(linesAction);
    groupAction->addAction(rectAction);
    groupAction->addAction(ellipseAction);
    groupAction->addAction(eraserAction);

    //连接信号与槽函数
    connect(linesAction, &QAction::triggered, this, &MyPaint::Lines);
    connect(rectAction, &QAction::triggered, this, &MyPaint::Rects);
    connect(ellipseAction, &QAction::triggered, this, &MyPaint::Ellipses);
    connect(lineAction, &QAction::triggered, this, &MyPaint::Line);
    connect(saveAction, &QAction::triggered, this, &MyPaint::SavePic);
    connect(openAction, &QAction::triggered, this, &MyPaint::OpenPic);
    connect(newAction, &QAction::triggered, this, &MyPaint::NewPaint);
    connect(eraserAction, &QAction::triggered, this, &MyPaint::Eraser);
    connect(colorAction, &QAction::triggered, this, &MyPaint::ChoseClr);
    connect(widthAction, &QAction::triggered, this, &MyPaint::ChoseWid);
    connect(fillAction, &QAction::triggered, this, &MyPaint::ChosefilClr);

    QMenu* Style = new QMenu(this);  //设置线型菜单
    Style->addAction("Qt::NoPen", [=]() { cont._style = 0; });
    Style->addAction("Qt::SolidLine", [=]() { cont._style = 1; });
    Style->addAction("Qt::DashLine", [=]() { cont._style = 2; });
    Style->addAction("Qt::DotLine", [=]() { cont._style = 3; });
    Style->addAction("Qt::DashDotLine", [=]() { cont._style = 4; });
    Style->addAction("Qt::DashDotDotLine", [=]() { cont._style = 5; });
    Style->addAction("Qt::CustomDashLine", [=]() { cont._style = 6; });

    QAction* styleAction = new QAction("线型", this);  //添加线型选项
    styleAction->setMenu(Style);
    styleAction->setIcon(QIcon(":/images/style.png"));
    tbar->addAction(styleAction);

    cont._Help = new QMenu(this);  //设置帮助菜单
    cont._Help->addAction("打开  \tCtrl+O", this, &MyPaint::OpenPic);
    cont._Help->addAction("新建  \tCtrl+N", this, &MyPaint::NewPaint);
    cont._Help->addAction("保存  \tCtrl+S", this, &MyPaint::SavePic);
    cont._Help->addSeparator();
    cont._Help->addAction("直线  \tCtrl+L", this, &MyPaint::Line);
    cont._Help->addAction("铅笔  \tCtrl+P", this, &MyPaint::Lines);
    cont._Help->addAction("橡皮  \tCtrl+A", this, &MyPaint::Eraser);
    cont._Help->addAction("矩形  \tCtrl+R", this, &MyPaint::Rects);
    cont._Help->addAction("椭圆  \tCtrl+E", this, &MyPaint::Ellipses);
    cont._Help->addSeparator();
    cont._Help->addAction("选择画笔颜色  \tCtrl+C", this, &MyPaint::ChoseClr);
    cont._Help->addAction("选择图形填充色  \tCtrl+F", this, &MyPaint::ChosefilClr);
    cont._Help->addAction("选择透明填充色  \tCtrl+U", this, &MyPaint::Unfill);
    cont._Help->addAction("选择画笔粗细  \tCtrl+W", this, &MyPaint::ChoseWid);

    cont._Help->addSeparator();
    cont._Help->addAction("退出  \tALT+F4", this, &MyPaint::close);
    cont._Help->addAction("撤销  \tCtrl+Z", this, &MyPaint::Rescind);
    cont._Help->setStyleSheet("background-color:rgb(255,235,205);selection-color:blue");  //设置菜单颜色

    QAction* helpAction = new QAction("帮助", this);  //添加帮助选项
    helpAction->setMenu(cont._Help);
    helpAction->setIcon(QIcon(":/images/help.png"));  //图标
    tbar->addAction(helpAction);
}

void MyPaint::paintEvent(QPaintEvent*)  //重绘
{
    if (cont._openflag == 0)  //未打开图片则新建空白的画布
    {
        cont._pixmap = QPixmap(size());
        cont._pixmap.fill(Qt::white);
    }
    QPixmap pix = cont._pixmap;  //新建另一画布,双缓存去闪
    QPainter p(&pix);

    int ipen = 0, irect = 0, iellipse = 0, iline = 0, iera = 0;  //工具索引

    for (int c = 0; c < cont._shape.size(); ++c)  //循环重绘容器内所有项
    {
        QPen pen(QColor(cont._colors.at(c)));  //每次循环设置画笔
        pen.setWidth(cont._widths.at(c));      //线宽
        if (cont._isfills.at(c))               //填充
        {
            QBrush brush(QColor(cont._fillcolors.at(c)));
            p.setBrush(brush);
        }
        else
        {
            p.setBrush(QBrush(Qt::NoBrush));
        }
        switch (cont._styles.at(c))  //线型
        {
            case 0: pen.setStyle(Qt::NoPen); break;
            case 1: pen.setStyle(Qt::SolidLine); break;
            case 2: pen.setStyle(Qt::DashLine); break;
            case 3: pen.setStyle(Qt::DotLine); break;
            case 4: pen.setStyle(Qt::DashDotLine); break;
            case 5: pen.setStyle(Qt::DashDotDotLine); break;
            case 6: pen.setStyle(Qt::CustomDashLine); break;
        }
        p.setPen(pen);

        if (cont._shape.at(c) == 1)  //铅笔线
        {
            const QVector<QPoint>& line = cont._pen.at(ipen++);  //分段绘制铅笔线
            for (int j = 0; j < line.size() - 1; ++j) { p.drawLine(line.at(j), line.at(j + 1)); }
        }
        else if (cont._shape.at(c) == 2)  //矩形
        {
            p.drawRect(cont._rects.at(irect++));
        }
        else if (cont._shape.at(c) == 3)  //椭圆
        {
            p.drawEllipse(cont._ellipse.at(iellipse++));
        }
        else if (cont._shape.at(c) == 4)  //直线
        {
            p.drawLine(cont._line.at(iline).topLeft(), cont._line.at(iline).bottomRight());
            iline++;
        }
        else if (cont._shape.at(c) == 5)  //橡皮
        {
            const QVector<QPoint>& eraser = cont._eraser.at(iera++);
            for (int j = 0; j < eraser.size() - 1; ++j)  //同铅笔线
            {
                p.drawLine(eraser.at(j), eraser.at(j + 1));
            }
            // p.setPen(pen);
        }
    }
    p.end();
    p.begin(this);
    p.drawPixmap(0, 0, pix);  //将临时画布画到窗体
}

void MyPaint::mousePressEvent(QMouseEvent* e)  //鼠标按下
{
    if (e->button() == Qt::LeftButton)  //左键按下
    {
        if (cont._drawType == 1)  //添加铅笔，下同
        {
            cont._lpress = true;  //按下标志为真

            QVector<QPoint> line;  //新铅笔线写入容器
            cont._pen.append(line);
            QVector<QPoint>& lastLine = cont._pen.last();

            lastLine.append(e->pos());  //新线条的开始坐标

            cont._colors.append(cont._color);  //记录各种状态
            cont._fillcolors.append(Qt::black);
            cont._isfills.append(0);
            cont._widths.append(cont._width);
            cont._styles.append(cont._style);
            cont._shape.append(1);
        }
        else if (cont._drawType == 2)  //矩形
        {
            cont._lpress = true;
            if (!cont._drag)  //非拖拽
            {
                QRect rect;
                cont._rects.append(rect);
                QRect& lastRect = cont._rects.last();

                lastRect.setTopLeft(e->pos());

                cont._colors.append(cont._color);
                cont._fillcolors.append(cont._fillcolor);
                cont._isfills.append(cont._isfill);
                cont._styles.append(cont._style);
                cont._widths.append(cont._width);
                cont._shape.append(2);
            }
            else if (cont._rects.last().contains(e->pos()))  //拖拽，鼠标在图形内部，下同
            {
                cont._begin = e->pos();  //记录起始的坐标
            }
        }
        else if (cont._drawType == 3)  //椭圆
        {
            cont._lpress = true;
            if (!cont._drag)
            {
                QRect rect;
                cont._ellipse.append(rect);
                QRect& lastEllipse = cont._ellipse.last();
                lastEllipse.setTopLeft(e->pos());
                cont._colors.append(cont._color);
                cont._fillcolors.append(cont._fillcolor);
                cont._isfills.append(cont._isfill);
                cont._styles.append(cont._style);
                cont._widths.append(cont._width);
                cont._shape.append(3);
            }
            else if (cont._ellipse.last().contains(e->pos()))
            {
                cont._begin = e->pos();
            }
        }
        else if (cont._drawType == 4)  //直线
        {
            cont._lpress = true;
            QRect rect;
            cont._line.append(rect);
            QRect& lastLine = cont._line.last();

            lastLine.setTopLeft(e->pos());

            cont._colors.append(cont._color);
            cont._fillcolors.append(Qt::black);
            cont._isfills.append(0);
            cont._styles.append(cont._style);
            cont._widths.append(cont._width);
            cont._shape.append(4);
        }
        else if (cont._drawType == 5)  //橡皮
        {
            cont._lpress = true;
            QVector<QPoint> eraser;
            cont._eraser.append(eraser);
            QVector<QPoint>& lasteraser = cont._eraser.last();

            lasteraser.append(e->pos());

            cont._colors.append(QColor(Qt::white));  //橡皮颜色线型线宽为定值
            cont._fillcolors.append(Qt::white);
            cont._isfills.append(0);
            cont._widths.append(25);
            cont._styles.append(1);
            cont._shape.append(5);
            cont._eraing = 1;
        }
    }
}

void MyPaint::mouseMoveEvent(QMouseEvent* e)  //鼠标移动
{
    if (cont._drag && ((cont._drawType == 2 && cont._rects.last().contains(e->pos())) ||
                       (cont._drawType == 3 && cont._ellipse.last().contains(e->pos()))))  //拖拽中
    {
        setCursor(Qt::SizeAllCursor);  //设置十字光标
    }
    else if (cont._eraing)
    {
        setCursor(Qt::ForbiddenCursor);  //橡皮时设置红圈光标
    }
    else
    {
        setCursor(Qt::ArrowCursor);  //恢复原始光标形状
        cont._eraing = 0;            //标志置0
        cont._drag = 0;
    }

    if (cont._lpress)
    {
        if (cont._drawType == 1)  //铅笔画线，下同
        {
            if (cont._pen.size() <= 0)  //容器非空
                return;

            QVector<QPoint>& lastLine = cont._pen.last();  //取得新线条
            lastLine.append(e->pos());                     //容器内存入线条轨迹
            update();                                      //更新画板
        }
        else if (cont._drawType == 2)  //矩形
        {
            if (cont._drag == 0)  //非拖拽
            {
                QRect& lastRect = cont._rects.last();
                lastRect.setBottomRight(e->pos());  //更新右下角坐标
            }
            else  //拖拽
            {
                QRect& lastRect = cont._rects.last();
                if (lastRect.contains(e->pos()))  //在矩形的内部
                {
                    int dx = e->pos().x() - cont._begin.x();  //移动
                    int dy = e->pos().y() - cont._begin.y();
                    lastRect = lastRect.adjusted(dx, dy, dx, dy);  //更新位置
                    cont._begin = e->pos();                        //刷新拖拽点起始坐标
                }
            }
            update();
        }
        else if (cont._drawType == 3)
        {
            if (cont._drag == 0)
            {
                QRect& lastEllipse = cont._ellipse.last();  //拿到椭圆
                lastEllipse.setBottomRight(e->pos());       //更新椭圆右下角坐标
            }
            else
            {
                QRect& lastEllipse = cont._ellipse.last();
                if (lastEllipse.contains(e->pos()))
                {
                    int dx = e->pos().x() - cont._begin.x();  //移动
                    int dy = e->pos().y() - cont._begin.y();
                    lastEllipse = lastEllipse.adjusted(dx, dy, dx, dy);
                    cont._begin = e->pos();
                }
            }
            update();
        }
        else if (cont._drawType == 4)  //直线
        {
            QRect& lastLine = cont._line.last();
            lastLine.setBottomRight(e->pos());
            update();
        }
        else if (cont._drawType == 5)  //橡皮
        {
            if (cont._eraser.size() <= 0)
                return;
            QVector<QPoint>& lasteraser = cont._eraser.last();
            lasteraser.append(e->pos());
            update();
        }
    }
}

void MyPaint::mouseReleaseEvent(QMouseEvent* e)  //鼠标松开
{
    if (cont._lpress)
    {
        if (cont._drawType == 1)  //铅笔线
        {
            QVector<QPoint>& lastLine = cont._pen.last();
            lastLine.append(e->pos());  //记录线条的结束坐标
            cont._lpress = false;       //标志左键释放
        }
        else if (cont._drawType == 2)  //矩形
        {
            QRect& lastRect = cont._rects.last();
            if (!cont._drag)  //非拖拽
            {
                lastRect.setBottomRight(e->pos());  //更新右下角坐标

                this->cursor().setPos(this->cursor().pos().x() - lastRect.width() / 2,
                                      this->cursor().pos().y() - lastRect.height() / 2);  //光标置图形中心
                cont._drag = 1;                                                           //拖拽标志
            }
            cont._lpress = false;  //松开标志
        }
        else if (cont._drawType == 3)  //椭圆
        {
            QRect& lastEllipse = cont._ellipse.last();
            if (!cont._drag)
            {
                lastEllipse.setBottomRight(e->pos());

                this->cursor().setPos(this->cursor().pos().x() - lastEllipse.width() / 2,
                                      this->cursor().pos().y() - lastEllipse.height() / 2);
                cont._drag = 1;
            }
            cont._lpress = false;
        }
        else if (cont._drawType == 4)  //直线
        {
            QRect& lastLine = cont._line.last();
            lastLine.setBottomRight(e->pos());
            cont._lpress = false;
        }
        else if (cont._drawType == 5)  //橡皮
        {
            QVector<QPoint>& lasteraser = cont._eraser.last();
            lasteraser.append(e->pos());
            cont._lpress = false;
            cont._eraing = 0;  //橡皮结束
        }
    }
}

void MyPaint::keyPressEvent(QKeyEvent* e)  //快捷键
{
    if (e->key() == Qt::Key_Z && e->modifiers() == Qt::ControlModifier)  // 撤销
    {
        this->Rescind();
    }
    if (e->key() == Qt::Key_U && e->modifiers() == Qt::ControlModifier)  // 透明填充
    {
        this->Unfill();
    }
}

void MyPaint::Lines()
{
    cont._drawType = 1;  //铅笔
    cont._eraing = 0;
}
void MyPaint::Eraser()
{
    cont._drawType = 5;  //橡皮
    cont._eraing = 1;
    cont._drag = 0;
}
void MyPaint::Line()
{
    cont._drawType = 4;  //直线
    cont._eraing = 0;
}

void MyPaint::Rects()
{
    cont._drawType = 2;  //矩形
    cont._drag = 0;
    cont._eraing = 0;
}

void MyPaint::Ellipses()
{
    cont._drawType = 3;  //椭圆
    cont._drag = 0;
    cont._eraing = 0;
}

void MyPaint::SavePic()  //保存
{
    //弹出文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, "保存", "Paint.jpg", "Image (*.jpg *.png *.bmp)");

    if (fileName.length() > 0)
    {
        QPixmap pixmap(size());  //将画布渲染到新建画布，双缓存去闪
        QPainter painter(&pixmap);
        painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);
        this->render(&painter);

        pixmap.copy(QRect(0, 42, size().width(), size().height() - 42)).save(fileName);  //保存（去掉工具栏）
    }
}

void MyPaint::Rescind()  //撤回函数
{
    if (cont._shape.size() > 0)
    {
        switch (cont._shape.last())  //总容器弹出
        {
            case 1: cont._pen.pop_back(); break;  //个体容器弹出
            case 2: cont._rects.pop_back(); break;
            case 3: cont._ellipse.pop_back(); break;
            case 4: cont._line.pop_back(); break;
            case 5: cont._eraser.pop_back(); break;
        }
        cont._shape.pop_back();  //各种设置容器弹出
        cont._colors.pop_back();
        cont._widths.pop_back();
        cont._fillcolors.pop_back();
        cont._isfills.pop_back();
        cont._styles.pop_back();

        cont._drag = 0;  //各种标志置0
        cont._eraing = 0;
        update();  //更新
    }
}

void MyPaint::NewPaint()  //新建
{
    MyPaint* w = new MyPaint();  // 新建一个画图窗口
    w->setWindowIcon(QIcon(":/images/1.png"));
    w->show();
    //    this->close();
    //去掉注释后，新建后删除原有窗口
}

void MyPaint::OpenPic()  //打开文件
{
    QString picPath = QFileDialog::getOpenFileName(this, "打开", "/", "Image Files(*.jpg *.png *.bmp)");  //文件路径
    if (!picPath.isEmpty())  //非空则双缓存载入
    {
        QPixmap pix;
        pix.load(picPath);
        QPainter p(&cont._pixmap);
        p.drawPixmap(0, 42, pix);  //避开工具栏空间
        cont._openflag = 1;        //文件打开标志
        update();                  //更新
    }
}

void MyPaint::ChoseClr()  //选颜色
{
    QColorDialog* colDig = new QColorDialog(this);  //颜色对话框
    colDig->setWindowTitle(QString("画笔颜色选择"));
    colDig->setGeometry(500, 300, 556, 428);
    cont._color = colDig->getColor();  //当前颜色
}

void MyPaint::ChosefilClr()  //选填充色
{
    QColorDialog* colDig = new QColorDialog(this);  //颜色对话框
    colDig->setWindowTitle(QString("填充颜色选择"));
    colDig->setGeometry(500, 300, 556, 428);
    cont._fillcolor = colDig->getColor();  //当前填充色
    cont._isfill = 1;                      //填充标志
}

void MyPaint::ChoseWid()  //选线宽
{
    QInputDialog* inPut = new QInputDialog(this);
    cont._width = inPut->getInt(this, "输入线宽", "请输入线宽(1-50)", cont._width, 1, 50);
    //线宽对话框，1-50
}

void MyPaint::Unfill() { cont._isfill = 0; }  //设为非填充

void MyPaint::contextMenuEvent(QContextMenuEvent*)  //右键
{
    cont._Help->exec(cursor().pos());  //鼠标处显示模态菜单
}
