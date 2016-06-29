#include <math.h>

#include <QApplication>

#include "HeatWidget.h"

float f(float)
{
    return 0.0;
}

int main(int argc, char*argv[])
{
    QApplication app(argc, argv);

    HeatWidget w(20, 20, 1.0, 0.001, 0.001, cos, sin, f);
    w.setWindowTitle("heat simulation");
    w.show();

    return app.exec();
}


