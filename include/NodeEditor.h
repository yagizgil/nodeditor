#ifndef _NODE_
#define _NODE_
#include <QtWidgets>

#include "node/node.h"
#include "node/socket.h"
#include "connection.h"

namespace smode
{
    static qreal NOOP = 1;
    static qreal DRAG = 2;
    static qreal CUT = 3;
};

class NodeEditor : public QGraphicsView
{
private:
    float zoomInFactor = 1.25;
    float zoom = 10;
    float zoomStep = 1;
    bool zoomClamp = false;
    QList<int> zoomRange = {1, 10};

    qreal mode = smode::NOOP;
    qreal socketOutletType;

    Socket *dragSocketStart;
    // Socket *dragSocketEnd;

    ConnectionGuide *guide;
    ConnectionCut *cut;

    void wheelEvent(QWheelEvent *event);

    void leftMouseButtonPress(QMouseEvent *event);
    void leftMouseButtonRelease(QMouseEvent *event);

    void rightMouseButtonPress(QMouseEvent *event);
    void rightMouseButtonRelease(QMouseEvent *event);

    void middleMouseButtonPress(QMouseEvent *event);
    void middleMouseButtonRelease(QMouseEvent *event);

public:
    NodeEditor(/* args */);
    ~NodeEditor();

    // void createConnection(Socket *start, Socket *end);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event) override;
};

class GraphicsScene : public QGraphicsScene
{
private:
    typedef QGraphicsScene super;
    QPen *lpen;
    QPen *dpen;
    void setGrid(QPainter *painter, const QRectF &rect);

public:
    GraphicsScene(/* args */);
    ~GraphicsScene();
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif
