#include <QtWidgets>
#include "connection.h"

#include "iostream"
using namespace std;

Connection::Connection(QGraphicsScene *scene, Socket *start, Socket *end, qreal type)
{
    this->scene = scene;
    this->start = start;
    this->end = end;
    this->type = type;

    pen.setWidthF(2.0);
    penSelected.setWidthF(2.0);

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setZValue(-1);

    this->setSource(start->scenePos());
    this->setDestination(end->scenePos());

    this->updatePath();
}

void Connection::addScene()
{
    this->scene->addItem(this);
}

Connection::~Connection()
{
    scene->removeItem(this);
    /*delete color;
    delete colorSelected;
    delete pen;
    delete penSelected;
    delete brush;*/
    // delete path;
}

void Connection::setSource(qreal x, qreal y)
{
    this->posSource[0] = x;
    this->posSource[1] = y;
}
void Connection::setSource(QPointF point)
{
    this->posSource[0] = point.x();
    this->posSource[1] = point.y();
}

void Connection::setDestination(qreal x, qreal y)
{
    this->posDestination[0] = x;
    this->posDestination[1] = y;
}
void Connection::setDestination(QPointF point)
{
    this->posDestination[0] = point.x();
    this->posDestination[1] = point.y();
}

void Connection::loadSource()
{
    this->setSource(start->scenePos());
}
void Connection::loadDestination()
{
    this->setDestination(end->scenePos());
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // loadSource();
    // loadDestination();

    // cout << static_cast<double>(start->parentItem()->scenePos().x()) <<endl;

    this->updatePath();
    if (this->isSelected())
        painter->setPen(penSelected);
    else
        painter->setPen(pen);

    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);

    // QGraphicsPathItem::paint(painter, option, widget);
}

/*QRectF Connection::boundingRect() const {
    //return path.boundingRect();
    return QGraphicsPathItem::boundingRect().adjusted(-2, -2, 2, 2);
}*/

void Connection::updatePath()
{

    if (type == nconnection::DIRECT)
    {
        this->path = QPainterPath(QPointF(this->posSource[0], this->posSource[1]));
        this->path.lineTo(this->posDestination[0], this->posDestination[1]);
        this->setPath((this->path));
    }
    else
    {
        /*qreal dist = (posDestination[0] + posSource[0]) * 0.5;
        if (posSource[0] > posDestination[0])
        {
            dist += -1;
        }

        this->path = new QPainterPath(QPointF(this->posSource[0], this->posSource[1]));
        this->path->cubicTo(posSource[0] + dist, posSource[1], posDestination[0] - dist, posDestination[1], posDestination[0], posDestination[1]);
        this->setPath(*(this->path));*/

        qreal dist = qAbs(posDestination[0] - posSource[0]) * 0.5;
        qreal controlPointOffset = qMin(dist, 100.0); // Bezier eğrisinin kontrol noktaları arasındaki uzaklık için bir sınırlama ekleyebilirsiniz

        QPointF controlPoint1(posSource[0] + controlPointOffset, posSource[1]);
        QPointF controlPoint2(posDestination[0] - controlPointOffset, posDestination[1]);

        this->path = QPainterPath(QPointF(posSource[0], posSource[1]));
        this->path.cubicTo(controlPoint1, controlPoint2, QPointF(posDestination[0], posDestination[1]));
        this->setPath(path);
    }
}

Socket *Connection::getStart() const
{
    return start;
}
Socket *Connection::getEnd() const
{
    return end;
}

ConnectionGuide::ConnectionGuide(QGraphicsScene *scene, Socket *start, qreal type)
{
    this->scene = scene;
    this->start = start;
    this->type = type;

    pen.setWidthF(3.0);
    pen.setStyle(Qt::DotLine);
    penSelected.setWidthF(2.0);

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setZValue(-1);

    this->setSource(start->scenePos());
    this->setDestination(start->scenePos());

    this->updatePath();
}

void ConnectionGuide::addScene()
{
    this->scene->addItem(this);
}

ConnectionGuide::~ConnectionGuide()
{
    scene->removeItem(this);
    /*delete color;
    delete colorSelected;
    delete pen;
    delete penSelected;
    delete brush;*/
    // delete path;
}

void ConnectionGuide::setSource(qreal x, qreal y)
{
    this->posSource[0] = x;
    this->posSource[1] = y;
}
void ConnectionGuide::setSource(QPointF point)
{
    this->posSource[0] = point.x();
    this->posSource[1] = point.y();
}

void ConnectionGuide::setDestination(qreal x, qreal y)
{
    this->posDestination[0] = x;
    this->posDestination[1] = y;
}
void ConnectionGuide::setDestination(QPointF point)
{
    this->posDestination[0] = point.x();
    this->posDestination[1] = point.y();
}

void ConnectionGuide::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // loadSource();
    // loadDestination();

    // cout << static_cast<double>(start->parentItem()->scenePos().x()) <<endl;
    this->updatePath();
    if (this->isSelected())
        painter->setPen(penSelected);
    else
        painter->setPen(pen);

    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);

    // QGraphicsPathItem::paint(painter, option, widget);
}

/*QRectF Connection::boundingRect() const {
    //return path.boundingRect();
    return QGraphicsPathItem::boundingRect().adjusted(-2, -2, 2, 2);
}*/

void ConnectionGuide::updatePath()
{

    if (type == nconnection::DIRECT)
    {
        this->path = QPainterPath(QPointF(this->posSource[0], this->posSource[1]));
        this->path.lineTo(this->posDestination[0], this->posDestination[1]);
        this->setPath((this->path));
    }
    else
    {
        /*qreal dist = (posDestination[0] + posSource[0]) * 0.5;
        if (posSource[0] > posDestination[0])
        {
            dist += -1;
        }

        this->path = new QPainterPath(QPointF(this->posSource[0], this->posSource[1]));
        this->path->cubicTo(posSource[0] + dist, posSource[1], posDestination[0] - dist, posDestination[1], posDestination[0], posDestination[1]);
        this->setPath(*(this->path));*/

        qreal dist = qAbs(posDestination[0] - posSource[0]) * 0.5;
        qreal controlPointOffset = qMin(dist, 100.0); // Bezier eğrisinin kontrol noktaları arasındaki uzaklık için bir sınırlama ekleyebilirsiniz

        QPointF controlPoint1(posSource[0] + controlPointOffset, posSource[1]);
        QPointF controlPoint2(posDestination[0] - controlPointOffset, posDestination[1]);

        this->path = QPainterPath(QPointF(posSource[0], posSource[1]));
        this->path.cubicTo(controlPoint1, controlPoint2, QPointF(posDestination[0], posDestination[1]));
        this->setPath(path);
    }
}































ConnectionCut::ConnectionCut(QGraphicsScene *scene, QPointF p)
{
    this->scene = scene;

    pen.setWidthF(3.0);
    pen.setStyle(Qt::DotLine);

    this->setZValue(2);
    addPoint(p);
}

void ConnectionCut::addScene()
{
    this->scene->addItem(this);
}

ConnectionCut::~ConnectionCut()
{
    scene->removeItem(this);
    /*delete color;
    delete colorSelected;
    delete pen;
    delete penSelected;
    delete brush;*/
    // delete path;
}


void ConnectionCut::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // loadSource();
    // loadDestination();
    cout<<"paint"<<endl;
    // cout << static_cast<double>(start->parentItem()->scenePos().x()) <<endl;
    updatePath();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);

    // QGraphicsPathItem::paint(painter, option, widget);
}

void ConnectionCut::updatePath()
{
    this->path = QPainterPath();
    path.addPolygon(QPolygonF(points));
    this->setPath(path);
}
void ConnectionCut::addPoint(QPointF p) {
    cout<<p.x() << "  " << p.y() <<endl;
    points.push_back(p);
    updatePath();
}

/*QRectF ConnectionCut::boundingRect() const {
    //return path.boundingRect();
    //return QGraphicsPathItem::boundingRect().adjusted(-2, -2, 2, 2);
    return QRectF(0,0,1,1);
}*/
