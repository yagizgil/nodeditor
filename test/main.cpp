#include <QtWidgets>
#include "NodeEditor.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *w = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    w->setLayout(layout);

    NodeEditor *ne = new NodeEditor();

    layout->addWidget(ne);

    w->show();

    return app.exec();
}
