#include <limits.h>

#include "HeatWidget.h"



HeatWidget::HeatWidget(int width, int height,
                       float a, float tao, float step,
                       BoundaryCondition g1, BoundaryCondition g2, InitialCondition phi)
    : heatConduction(width, height, a, tao, step, g1, g2, phi)
{
    heat = nullptr;
    this->width = width;
    this->height = height;
    heatConduction.calc();
    init();
}

void HeatWidget::draw()
{
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
    for(int i = 0; i < width - 1; i++)
    {
        float heatValleft = heat[i];
        float heatValright = heat[i + 1];
        glColor3f(0, 0, heatValleft);

        float begin = i - float(width / 2);
        float yLen = 1.0;

        glVertex3f(begin, -yLen, 0);
        glVertex3f(begin, yLen, 0);

        glColor3f(0, 0, heatValright);


        glVertex3f(begin + 1.0, yLen, 0);
        glVertex3f(begin + 1.0, - yLen, 0);
    }
    glEnd();
}


void HeatWidget::animate()
{
    heat = heatConduction.getHeatData();
}

void HeatWidget::init()
{
    heat = heatConduction.getHeatData();
}
