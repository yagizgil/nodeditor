#ifndef _N_CONTENT_
#define _N_CONTENT_
#include <QtWidgets>

class Content : public QGraphicsProxyWidget
{
private:
    QWidget *widget;
public:
    Content(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~Content();

    void setGeo(int ax, int ay, int aw, int ah);
};

#endif
