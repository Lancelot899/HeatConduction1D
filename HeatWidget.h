#ifndef HEATWIDGET_H
#define HEATWIDGET_H

#include <QGLViewer/qglviewer.h>

#include "HeatConduction.h"

class HeatWidget : public QGLViewer
{
public:
    HeatWidget(int width, int height,
               float a, float tao, float step,
               BoundaryCondition g1, BoundaryCondition g2,
               InitialCondition phi);
    virtual void draw();
    virtual void animate();
    virtual void init();

private:
    HeatConduction heatConduction;
    int width;
    int height;
    const float *heat;
};

#endif // HEATWIDGET_H
