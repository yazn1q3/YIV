#include <QApplication>
#include "ImageViewer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ImageViewer viewer;
    viewer.resize(1200, 800);
    viewer.show();
    return app.exec();
}
