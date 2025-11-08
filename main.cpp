#include "Qt_OpenGL.h"
#include <QtWidgets/QApplication>
#include <qimagewriter.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Qt_OpenGL window;
    window.show();
    return app.exec();
}
