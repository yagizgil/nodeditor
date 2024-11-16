#include <QtWidgets>
#include "NodeEditor.h"

#include <cmath>
#include <list>

#include "iostream"

using namespace std;

NodeEditor::NodeEditor(/* args */)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    // this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setCacheMode(QGraphicsView::CacheBackground);

    this->setDragMode(QGraphicsView::RubberBandDrag);

    GraphicsScene *scene = new GraphicsScene();
    setScene(scene);
    this->setSceneRect(scene->itemsBoundingRect());

    for (int i = 1; i < 3; i++)
    {
        Node *n = new Node(scene, "abcd", i * 100, i * 100);
        Node *n1 = new Node(scene, "abc", i * 300, i * 400);

        n->addScene();
        n1->addScene();

        // Connection *c = new Connection(scene, n->getOutputs()[0].data(), n1->getInputs()[0].data(), nconnection::BEZIER);
    }
}

NodeEditor::~NodeEditor()
{
}

void NodeEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->leftMouseButtonPress(event);
    }
    else if (event->button() == Qt::RightButton)
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
    else if (event->button() == Qt::MiddleButton)
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void NodeEditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->leftMouseButtonRelease(event);
    }
    else if (event->button() == Qt::RightButton)
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
    else if (event->button() == Qt::MiddleButton)
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void NodeEditor::leftMouseButtonPress(QMouseEvent *event)
{

    /*static bool isClickInProgress = false; // Ardışık tıklamaları engellemek için flag

    if (isClickInProgress)
    {
        // Ardışık tıklama işlemi devam ediyorsa, bu tıklamayı işleme alma
        return;
    }*/

    QGraphicsItem *pressedItem = itemAt(event->pos());
    QList<QGraphicsItem *> selectedItems = scene()->selectedItems();

    if (!pressedItem)
    {
        if (event->modifiers() == Qt::AltModifier)
        {
            QMouseEvent *releaseEvent = new QMouseEvent(QEvent::MouseButtonRelease, event->pos(), event->pos(), Qt::LeftButton, Qt::NoButton, event->modifiers());
            QGraphicsView::mouseReleaseEvent(releaseEvent);

            this->setDragMode(QGraphicsView::RubberBandDrag);

            QMouseEvent *fakeEvent = new QMouseEvent(event->type(), event->pos(), event->pos(), Qt::LeftButton, event->button() | Qt::LeftButton, event->modifiers());
            QGraphicsView::mousePressEvent(fakeEvent);
        }
        else if (event->modifiers() == Qt::ShiftModifier)
        {
            if (mode == smode::NOOP)
            {
                mode = smode::CUT;
                cut = new ConnectionCut(scene(), mapToScene(event->pos()));
                cut->addScene();
                QApplication::setOverrideCursor(Qt::CrossCursor);
            }
        }
        else
        {
            QMouseEvent *releaseEvent = new QMouseEvent(QEvent::MouseButtonRelease, event->pos(), event->pos(), Qt::LeftButton, Qt::NoButton, event->modifiers());
            QGraphicsView::mouseReleaseEvent(releaseEvent);

            this->setDragMode(QGraphicsView::ScrollHandDrag);

            QMouseEvent *fakeEvent = new QMouseEvent(event->type(), event->pos(), event->pos(), Qt::LeftButton, event->button() | Qt::LeftButton, event->modifiers());
            QGraphicsView::mousePressEvent(fakeEvent);
        }
    }
    else
    {
        Socket *socket = dynamic_cast<Socket *>(pressedItem);
        if (socket)
        {
            if (mode == smode::NOOP)
            {
                mode = smode::DRAG;
                socketOutletType = socket->getType();
                dragSocketStart = socket;
                cout << "Start dragging mode" << endl;
                cout << "   assign Start Socket" << endl;
                guide = new ConnectionGuide(scene(), socket, nconnection::BEZIER);
                guide->addScene();
            }

            /*// Ardışık tıklamaları engellemek için bir süre boyunca işlemi engelle
            isClickInProgress = true;
            QTimer::singleShot(500, this, [this]()
                               { isClickInProgress = false; });*/

            return;
        }

        /*Node *node = dynamic_cast<Node *>(pressedItem);
        if (node) {
            if (event->modifiers() and Qt::ShiftModifier) {
                cout<<"lmb + shift on" << endl;
                event->ignore();
                QMouseEvent *fakeEvent = new QMouseEvent(QEvent::MouseButtonPress, event->pos(), event->pos(), Qt::LeftButton, event->button() | Qt::LeftButton, event->modifiers() | Qt::ControlModifier);
                QGraphicsView::mousePressEvent(fakeEvent);
                return;
            }
        }*/

        QGraphicsView::mousePressEvent(event);
    }
}

void NodeEditor::leftMouseButtonRelease(QMouseEvent *event)
{
    QGraphicsItem *pressedItem = itemAt(event->pos());
    if (!pressedItem)
    {
        if (mode == smode::DRAG)
        {
            mode = smode::NOOP;
            cout << "End dragging mode" << endl;
            scene()->removeItem(guide);
            delete guide;
        }
        else if (mode == smode::CUT)
        {
            mode = smode::NOOP;
            scene()->removeItem(cut);
            delete cut;

            QApplication::setOverrideCursor(Qt::ArrowCursor);
        }
        this->setDragMode(QGraphicsView::NoDrag);
        QMouseEvent *fakeEvent = new QMouseEvent(event->type(), event->pos(), event->pos(), Qt::LeftButton, event->buttons() & Qt::LeftButton, event->modifiers());
        QGraphicsView::mouseReleaseEvent(fakeEvent);
    }
    else
    {
        Socket *socket = dynamic_cast<Socket *>(pressedItem);
        if (mode == smode::DRAG)
        {
            mode = smode::NOOP;
            if (socket)
            {
                if (socketOutletType != socket->getType() and dragSocketStart->parentItem() != socket->parentItem())
                {
                    cout << "   assign End Socket" << endl;
                    if (dragSocketStart->getType() == nsock::OUTPUT)
                    {
                        Connection *c = new Connection(scene(), dragSocketStart, socket, nconnection::BEZIER);
                        c->addScene();
                    }
                    else
                    {
                        Connection *c = new Connection(scene(), socket, dragSocketStart, nconnection::BEZIER);
                        c->addScene();
                    }
                    dragSocketStart = nullptr;
                }
            }
            cout << "End dragging mode" << endl;
            scene()->removeItem(guide);
            delete guide;
            return;
        }

        else if (mode == smode::CUT)
        {
            mode = smode::NOOP;
            scene()->removeItem(cut);
            delete cut;

            QApplication::setOverrideCursor(Qt::ArrowCursor);
            return;
        }

        /*Node *node = dynamic_cast<Node *>(pressedItem);
        if (node) {
            if (event->modifiers() and Qt::ShiftModifier) {
                cout<<"lmb + shift reles" << endl;
                event->ignore();
                QMouseEvent *fakeEvent = new QMouseEvent(event->type(), event->pos(), event->pos(), Qt::LeftButton, Qt::NoButton, event->modifiers() | Qt::ControlModifier);
                QGraphicsView::mouseReleaseEvent(fakeEvent);
                return;
            }
        }*/

        QGraphicsView::mouseReleaseEvent(event);
    }
}

void NodeEditor::wheelEvent(QWheelEvent *event)
{
    float zoomOutFactor = 1 / zoomInFactor;
    QPointF oldPos = this->mapToScene(event->position().x(), event->position().y());

    float zoomFactor;

    if (event->angleDelta().y() > 0)
    {
        zoomFactor = zoomInFactor;
        zoom += zoomStep;
    }
    else
    {
        zoomFactor = zoomOutFactor;
        zoom -= zoomStep;
    }

    bool clamped = false;
    if (zoom < (float)zoomRange[0])
    {
        zoom = (float)zoomRange[0];
        clamped = true;
    }
    if (zoom > (float)zoomRange[0])
    {
        zoom = (float)zoomRange[1];
        clamped = true;
    }

    if (!clamped or !zoomClamp)
    {
        this->scale(zoomFactor, zoomFactor);
    }

    QPointF newPos = this->mapToScene(event->position().x(), event->position().y());

    QPointF delta = newPos - oldPos;
    this->translate(delta.x(), delta.y());
}

void NodeEditor::middleMouseButtonPress(QMouseEvent *event)
{
}

void NodeEditor::middleMouseButtonRelease(QMouseEvent *event)
{
}

void NodeEditor::keyPressEvent(QKeyEvent *event)
{
    // Seçili QGraphicsItem'ların alınması
    QList<QGraphicsItem *> selectedItems = scene()->selectedItems();

    if (!selectedItems.isEmpty())
    {

        QList<QGraphicsItem *> filteredItems;
        foreach (QGraphicsItem *item, selectedItems)
        {
            if (qgraphicsitem_cast<QGraphicsPathItem *>(item) == nullptr)
            {
                // QGraphicsPathItem değilse listeye ekle
                filteredItems.append(item);
            }
        }
        // Seçili QGraphicsItem'ların hareket ettirilmesi
        qreal dx = 0, dy = 0;
        const qreal stepSize = 10; // Hareket adımı (isteğe bağlı olarak ayarlanabilir)

        switch (event->key())
        {
        case Qt::Key_Left:
            dx -= stepSize;
            break;
        case Qt::Key_Right:
            dx += stepSize;
            break;
        case Qt::Key_Up:
            dy -= stepSize;
            break;
        case Qt::Key_Down:
            dy += stepSize;
            break;
        case Qt::Key_Delete:
            foreach (QGraphicsItem *item, selectedItems)
            {
                foreach (QGraphicsItem *conn, scene()->items())
                {
                    Connection *connection = qgraphicsitem_cast<Connection *>(conn);
                    if (connection && (connection->getStart()->parentItem() == item || connection->getEnd()->parentItem() == item))
                    {
                        scene()->removeItem(connection);
                        delete connection;
                    }
                }
                scene()->removeItem(item);
                delete item;
            }
            break;
        default:
            QGraphicsView::keyPressEvent(event);
            return;
        }

        foreach (QGraphicsItem *item, filteredItems)
        {
            item->moveBy(dx, dy);

            Node *node = qgraphicsitem_cast<Node *>(item);
            if (node)
            {
                node->connectionRePos();
            }
        }
    }
    else
    {
        // Sahnenin hareket ettirilmesi
        int dx = 0, dy = 0;
        const int stepSize = 20; // Hareket adımı (isteğe bağlı olarak ayarlanabilir)

        switch (event->key())
        {
        case Qt::Key_Left:
            dx -= stepSize;
            break;
        case Qt::Key_Right:
            dx += stepSize;
            break;
        case Qt::Key_Up:
            dy -= stepSize;
            break;
        case Qt::Key_Down:
            dy += stepSize;
            break;
        default:
            QGraphicsView::keyPressEvent(event);
            return;
        }

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + dx);
        verticalScrollBar()->setValue(verticalScrollBar()->value() + dy);
    }
}

void NodeEditor::mouseMoveEvent(QMouseEvent *event)
{

    if (mode == smode::DRAG)
    {
        guide->setDestination(mapToScene(event->pos()));
        guide->updatePath();
    }
    else if (mode == smode::CUT){
        cut->addPoint(mapToScene(event->pos()));
    }
    else
    {
        QList<QGraphicsItem *> selectedItems = scene()->selectedItems();

        QList<QGraphicsItem *> filteredItems;
        foreach (QGraphicsItem *item, selectedItems)
        {
            if (qgraphicsitem_cast<QGraphicsPathItem *>(item) == nullptr)
            {
                // QGraphicsPathItem değilse listeye ekle
                filteredItems.append(item);
            }
        }

        foreach (QGraphicsItem *item, filteredItems)
        {
            Node *node = qgraphicsitem_cast<Node *>(item);
            if (node)
            {
                node->connectionRePos();
            }
        }
    }

    QGraphicsView::mouseMoveEvent(event);
}

GraphicsScene::GraphicsScene(/* args */)
{
    this->setBackgroundBrush(QColor(QString("#393935")));
    this->setSceneRect(0, 0, 2000, 2000);

    this->lpen = new QPen(QColor(QString("#2f2f2f")));
    this->lpen->setWidth(1);

    this->dpen = new QPen(QColor(QString("#292929")));
    this->dpen->setWidth(2);
}

GraphicsScene::~GraphicsScene()
{
    delete lpen;
    delete dpen;
}

void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    this->super::drawBackground(painter, rect);
    // painter->fillRect(rect, QColor(40, 40, 40));
    this->setGrid(painter, rect);
}

void GraphicsScene::setGrid(QPainter *painter, const QRectF &rect)
{
    int gridSize = 5;
    int left = (int)(floor(rect.left()));
    int right = (int)(ceil(rect.right()));
    int top = (int)(floor(rect.top()));
    int bottom = (int)(ceil(rect.bottom()));

    int fleft = left - (left % gridSize);
    int ftop = top - (top % gridSize);

    QList<QLine> *lines_light = new QList<QLine>;
    QList<QLine> *lines_dark = new QList<QLine>;

    list<int> numbers;
    for (int i = fleft; i < right; i = i + gridSize)
    {
        numbers.push_back(i);
    }

    for (int n : numbers)
    {
        if ((n % 100) != 0)
        {
            lines_light->append(QLine(n, top, n, bottom));
        }
        else
        {
            lines_dark->append(QLine(n, top, n, bottom));
        }
    }

    list<int> numbers2;
    for (int i = ftop; i < bottom; i = i + gridSize)
    {
        numbers2.push_back(i);
    }

    for (int n : numbers2)
    {
        if ((n % 100) != 0)
        {
            lines_light->append(QLine(left, n, right, n));
        }
        else
        {
            lines_dark->append(QLine(left, n, right, n));
        }
    }

    painter->setPen(*(this->lpen));
    painter->drawLines(*lines_light);

    painter->setPen(*(this->dpen));
    painter->drawLines(*lines_dark);

    delete lines_light;
    delete lines_dark;
    /*QRectF area = sceneRect();
    int gridSize = 20;

    int left = int(area.left()) - (int(area.left()) % gridSize);
    int top = int(area.top()) - (int(area.top()) % gridSize);

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x < area.right(); x += gridSize)
        lines.append(QLineF(x, area.top(), x, area.bottom()));
    for (qreal y = top; y < area.bottom(); y += gridSize)
        lines.append(QLineF(area.left(), y, area.right(), y));

    painter->setPen(*dpen);
    painter->drawLines(lines.data(), lines.size());

    lines.clear();
    for (qreal x = left; x < area.right(); x += gridSize * 4)
        lines.append(QLineF(x, area.top(), x, area.bottom()));
    for (qreal y = top; y < area.bottom(); y += gridSize * 4)
        lines.append(QLineF(area.left(), y, area.right(), y));

    painter->setPen(*lpen);
    painter->drawLines(lines.data(), lines.size());*/
}
