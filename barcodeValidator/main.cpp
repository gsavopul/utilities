#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    a.setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles);
    w.show();

    return a.exec();
}
