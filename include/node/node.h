#ifndef _G_NODE_
#define _G_NODE_
#include <QtWidgets>

#include "node/content.h"
#include "node/socket.h"

class Node : public QGraphicsItem
{
private:
    typedef QGraphicsItem super;
    QGraphicsScene *scene;

    Content *content;

    QMap<QString,QSharedPointer<Socket>> inputs;
    QMap<QString,QSharedPointer<Socket>> outputs;

    qreal socketSpacing = 22;

    QString title;
    //QColor *titleColor = new QColor(QString("#ffffff"));
    //QFont *titleFont = new QFont(QString("Ubuntu"), 10);
    //QBrush *titleBrush = new QBrush(QColor(QString("#FF313131")));
    QColor titleColor = QColor("#ffffff");
    QFont titleFont = QFont("Ubuntu", 10);
    QBrush titleBrush = QBrush(QColor("#FF313131"));
    QGraphicsTextItem *titleItem;

    //QBrush *backgroundBrush = new QBrush(QColor(QString("#e3212121")));
    QBrush backgroundBrush = QBrush(QColor("#e3212121"));

    qreal width = 180;
    qreal height = 240;
    qreal min_width = 180;
    qreal min_height = 240;

    qreal edgeSize = 10.0;
    qreal titleHeight = 24.0;
    qreal padding = 0.5;

    QPen *penDefault = new QPen(QColor(QString("#7F000000")));
    QPen *penSelected = new QPen(QColor(QString("#FFFFA637")));

    void initTitle();
    void initContent();
    void initSockets();

public:
    Node(QGraphicsScene *scene, QString title, qreal x = 0, qreal y = 0);
    ~Node();

    void addScene();
    
    QPointF getSocketPosition(qreal index, qreal position);

    QList<QSharedPointer<Socket>> getInputs() const;
    QList<QSharedPointer<Socket>> getOutputs() const;

    qreal getWidth() const;
    qreal getHeight() const;
    qreal getMinWidth() const;
    qreal getMinHeight() const;
    qreal getEdgeSize() const;
    qreal getTitleHeight() const;
    qreal getPadding() const;

    void connectionRePos();


    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif
