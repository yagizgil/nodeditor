#ifndef _N_SOCKET_
#define _N_SOCKET_
#include <QtWidgets>

namespace nsock {
    static qreal LEFT_TOP = 1;
    static qreal LEFT_BOTTOM = 2;
    static qreal RIGHT_TOP = 3;
    static qreal RIGHT_BOTTOM = 4;

    static qreal INPUT = 1;
    static qreal OUTPUT = 2;
}

class Socket : public QGraphicsItem
{
private:
    qreal index;
    qreal position;

    qreal radius = 6.0;
    qreal outlineWidth = 1.0;

    QColor *backgroundColor = new QColor(QString("#FFFF7700"));
    QColor *outlineColor = new QColor(QString("#FF000000"));

    QPen *pen;
    QBrush *brush;

    qreal type;

public:
    Socket(qreal position=nsock::LEFT_TOP, QGraphicsItem *parent = nullptr);
    ~Socket();

    qreal getPosition() const;
    qreal getType() const;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif
