#include <QtWidgets>
#include "node/socket.h"

#include "iostream"
using namespace std;

Socket::Socket(qreal position, QGraphicsItem *parent) : QGraphicsItem(parent) {
    position = position;

    pen = new QPen(*outlineColor);
    pen->setWidthF(outlineWidth);

    brush = new QBrush(*backgroundColor);

    if (position == nsock::LEFT_BOTTOM or position == nsock::LEFT_TOP) {
        type = nsock::INPUT;
    }
    else {
        type = nsock::OUTPUT;
    }

    setAcceptHoverEvents(true);
}

Socket::~Socket() {
    delete backgroundColor;
    delete outlineColor;
    delete pen;
    delete brush;
}

qreal Socket::getPosition() const{
    return position;
}

qreal Socket::getType() const {
    return type;
}

QRectF Socket::boundingRect() const
{
    return QRectF(-radius - outlineWidth, -radius - outlineWidth, 2 * (radius + outlineWidth), 2 * (radius + outlineWidth)).normalized();
}

void Socket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(*brush);
    painter->setPen(*pen);
    painter->drawEllipse(-radius, -radius, 2 * radius, 2 * radius);
}

void Socket::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    radius = 8.0;
    QGraphicsItem::hoverEnterEvent(event);
}

void Socket::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    radius = 6.0;
    QGraphicsItem::hoverLeaveEvent(event);
}

/*void Socket::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    cout << "soclet"<<endl;
}*/