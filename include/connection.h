#ifndef _N_EDGE_
#define _N_EDGE_
#include <QtWidgets>

#include "node/socket.h"

namespace nconnection
{
    static qreal DIRECT = 1;
    static qreal BEZIER = 2;
}

class Connection : public QGraphicsPathItem
{
private:
    QGraphicsScene *scene;

    Socket *start;
    Socket *end;

    qreal type;

    QColor color = QColor(QString("#001000"));
    QColor colorSelected = QColor(QString("#00ff00"));
    QPen pen = QPen(color);
    QPen penSelected = QPen(colorSelected);
    QBrush brush = QBrush(color);

protected:
    QList<qreal> posSource = {200.0, 200.0};
    QList<qreal> posDestination = {800, 500};

    QPainterPath path;

public:
    Connection(QGraphicsScene *scene, Socket *start, Socket *end, qreal type = nconnection::DIRECT);
    ~Connection();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void updatePath();
    // QRectF boundingRect() const override;

    void setSource(qreal x, qreal y);
    void setSource(QPointF point);

    void setDestination(qreal x, qreal y);
    void setDestination(QPointF point);

    void loadSource();
    void loadDestination();

    Socket *getStart() const;
    Socket *getEnd() const;

    void addScene();
};

class ConnectionGuide : public QGraphicsPathItem
{
private:
    QGraphicsScene *scene;

    Socket *start;

    qreal type;

    QColor color = QColor(QString("#001000"));
    QColor colorSelected = QColor(QString("#00ff00"));
    QPen pen = QPen(color);
    QPen penSelected = QPen(colorSelected);
    QBrush brush = QBrush(color);

protected:
    QList<qreal> posSource = {200.0, 200.0};
    QList<qreal> posDestination = {800, 500};

    QPainterPath path;

public:
    ConnectionGuide(QGraphicsScene *scene, Socket *start, qreal type = nconnection::DIRECT);
    ~ConnectionGuide();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void updatePath();
    // QRectF boundingRect() const override;

    void setSource(qreal x, qreal y);
    void setSource(QPointF point);

    void setDestination(qreal x, qreal y);
    void setDestination(QPointF point);

    Socket *getStart() const;
    Socket *getEnd() const;

    void addScene();
};


class ConnectionCut : public QGraphicsPathItem {
private:
    QGraphicsScene *scene;

    QColor color = QColor(QString("#ffffff"));
    QPen pen = QPen(color);
    QBrush brush = QBrush(color);

protected:
    QList<QPointF> points;

    QPainterPath path;

public:
    ConnectionCut(QGraphicsScene *scene, QPointF p);
    ~ConnectionCut();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void updatePath();
    //QRectF boundingRect() const override;

    void addPoint(QPointF p);

    void addScene();
};

#endif
