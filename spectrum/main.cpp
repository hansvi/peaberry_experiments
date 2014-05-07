#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FFTWidget w;
    w.show();
    
    return a.exec();
}
