#include <QtWidgets>
#include "node/node.h"
#include "node/content.h"
#include "connection.h"

#include "iostream"
#include "string"

using namespace std;

Node::Node(QGraphicsScene *scene, QString title, qreal x, qreal y)
{
    this->scene = scene;
    this->title = title;
    this->setPos(x, y);

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);

    this->initTitle();

    this->initContent();
    this->initSockets();
}

Node::~Node()
{
    scene->removeItem(this);
    delete content;
    //delete title;
    //delete titleColor;
    //delete titleBrush;
    //delete titleFont;
    delete titleItem;
    //delete backgroundBrush;
    delete penDefault;
    delete penSelected;
}

void Node::addScene()
{
    this->scene->addItem(this);
}



void Node::initSockets()
{
    for (qreal i = 0; i < 3; i++)
    {
        QSharedPointer<Socket> socket(new Socket(nsock::LEFT_BOTTOM, this));
        socket->setPos(getSocketPosition(i,nsock::LEFT_BOTTOM));
        inputs.insert(QString::number(i), socket);
    }
    
    /*for (auto it = inputs.begin(); it != inputs.end(); ++it) {
        qDebug() << it.key() << ":" << &(it.value());
    }*/

    for (qreal i = 0; i < 1; i++)
    {
        QSharedPointer<Socket> socket(new Socket(nsock::RIGHT_TOP, this));
        socket->setPos(getSocketPosition(i,nsock::RIGHT_TOP));
        outputs.insert(QString::number(i), socket);
    }
    
}

QPointF Node::getSocketPosition(qreal index, qreal position) {
    qreal x;
    qreal y;
    if (position == nsock::LEFT_BOTTOM or position == nsock::LEFT_TOP) {
        x =0;
    }
    else {
        x = this->getWidth();
    }

    if (position == nsock::LEFT_BOTTOM or position == nsock::RIGHT_BOTTOM) {
        y = this->getHeight() - this->getEdgeSize() - this->getPadding()  - index * socketSpacing;
    } 
    else {
        y = this->getTitleHeight() + this->getPadding() + this->getEdgeSize() + index*socketSpacing;
    }

    return QPointF(x,y);
}

QList<QSharedPointer<Socket>> Node::getInputs() const {
    return inputs.values();
}
QList<QSharedPointer<Socket>> Node::getOutputs() const {
    return outputs.values();
}


void Node::initTitle()
{
    this->titleItem = new QGraphicsTextItem(this);
    this->titleItem->setDefaultTextColor((this->titleColor));
    this->titleItem->setFont((this->titleFont));
    this->titleItem->setPos(padding, 0);
    this->titleItem->setPlainText((this->title));
    // this->titleItem->setTextWidth(width - 2 * padding);
    // this->titleItem->textWidth();

    width = this->titleItem->boundingRect().width();
    if (width < min_width)
    {
        width = min_width;
    }
}

void Node::initContent()
{
    content = new Content(this);
    content->setGeo(edgeSize, titleHeight + edgeSize, width - 2 * edgeSize, height - 2 * edgeSize - titleHeight);
}

QRectF Node::boundingRect() const
{
    return QRectF(0, 0, /*2 * edgeSize +*/ width, /*2 * edgeSize +*/ height).normalized();
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // std::cout << static_cast<double>(width) << std::endl;
    //  title
    QPainterPath *pathTitle = new QPainterPath();
    pathTitle->setFillRule(Qt::WindingFill);
    pathTitle->addRoundedRect(0, 0, width, titleHeight, edgeSize, edgeSize);
    pathTitle->addRect(0, titleHeight - edgeSize, edgeSize, edgeSize);
    pathTitle->addRect(width - edgeSize, titleHeight - edgeSize, edgeSize, edgeSize);
    painter->setPen(Qt::NoPen);
    painter->setBrush(titleBrush);
    painter->drawPath(pathTitle->simplified());
    delete pathTitle;

    // content
    QPainterPath *pathContent = new QPainterPath();
    pathContent->setFillRule(Qt::WindingFill);
    pathContent->addRoundedRect(0, titleHeight, width, height - titleHeight, edgeSize, edgeSize);
    pathContent->addRect(0, titleHeight, edgeSize, edgeSize);
    pathContent->addRect(width - edgeSize, titleHeight, edgeSize, edgeSize);
    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundBrush);
    painter->drawPath(pathContent->simplified());
    delete pathContent;

    // outline
    QPainterPath *pathOutline = new QPainterPath();
    pathOutline->addRoundedRect(0, 0, width, height, edgeSize, edgeSize);

    if (this->isSelected())
    {
        painter->setPen(*(this->penSelected));
    }
    else
    {
        painter->setPen(*(this->penDefault));
    }

    painter->setBrush(Qt::NoBrush);
    painter->drawPath(pathOutline->simplified());
    delete pathOutline;
}

qreal Node::getWidth() const{
    return width;
}
qreal Node::getHeight() const{
    return height;
}
qreal Node::getMinWidth() const{
    return min_width;
}
qreal Node::getMinHeight() const{
    return min_height;
}
qreal Node::getEdgeSize() const{
    return edgeSize;
}
qreal Node::getTitleHeight() const{
    return titleHeight;
}
qreal Node::getPadding() const{
    return padding;
}


void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {    
    connectionRePos();
    this->super::mouseMoveEvent(event);
}

void Node::connectionRePos() {
    QList<Connection *> connectionsToUpdate;
    foreach (QGraphicsItem *item, this->scene->items()) {
        Connection *connection = qgraphicsitem_cast<Connection *>(item);
        if (connection && (connection->getStart()->parentItem() == this || connection->getEnd()->parentItem() == this)) {
            connectionsToUpdate.append(connection);
        }
    }
    
    foreach (Connection *connection, connectionsToUpdate) {
        connection->loadSource();
        connection->loadDestination();
        connection->update();
    }
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->super::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->super::mouseReleaseEvent(event);
}
