#ifndef HeatConduction_H
#define HeatConduction_H

#include <functional>

typedef std::function<float(float)> BoundaryCondition;
typedef std::function<float(float)> InitialCondition;


class HeatConduction
{
public:
    HeatConduction(int width, int height,
                     float a, float tao, float step,
                     BoundaryCondition g1, BoundaryCondition g2,
                     InitialCondition phi);

    const float* getHeatData()
    {
        if(heatShow + width < heat + width * height)
            return (heatShow+=width);
        else
            return heatShow = heat;
    }

    float getMaxHeat()
    {
        return maxHeat;
    }

    float getMinHeat()
    {
        return minHeat;
    }

    void calc();

private:
    void solve();

private:
    float r;          //r = \frac{a * tao }{step^2}
    float step;
    float tao;
    float *heat;
    float *heatShow;
    int    width;
    int    height;
    float  minHeat;
    float  maxHeat;
    BoundaryCondition g1;
    BoundaryCondition g2;
    InitialCondition  phi;
};

#endif // HeatConduction_H
