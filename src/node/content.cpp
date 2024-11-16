#include <QtWidgets>
#include "node/content.h"


Content::Content(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsProxyWidget(parent,wFlags)
{
    widget = new QWidget();

    widget->setStyleSheet(QString("QWidget {background: transparent;} QPushButton {color: red; font-size:21px;}"));
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);

    QPushButton *b = new QPushButton(QString("sdf"));
    b->setCursor(QCursor(Qt::PointingHandCursor));
    layout->addWidget(b);

    //this->setWidget(widget);
}


Content::~Content()
{
    delete widget;
}

void Content::setGeo(int ax, int ay, int aw, int ah) {
    widget->setGeometry(ax,ay,aw,ah);
}