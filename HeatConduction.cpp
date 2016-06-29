#include <memory.h>
#include <stdio.h>

#include <opencv2/core/core.hpp>

#include "HeatConduction.h"

HeatConduction::HeatConduction(int width, int height,
                                   float a, float tao, float step,
                                   BoundaryCondition g1, BoundaryCondition g2,
                                   InitialCondition phi)
{
    this->r = a * tao / step / step;
    this->step = step;
    this->tao = tao;
    this->width = width;
    this->height = height;
    this->g1 = g1;
    this->g2 = g2;
    this->phi = phi;
    heat = new float[width * height];
    heatShow = heat;
    memset(heat, 0, sizeof(float) * width * height);
}

void HeatConduction::calc()
{
    for(int i = 0; i < width; ++i)
        heat[i] = phi(i * step);
    for(int j = 0; j < height; ++j)
        heat[j * width] = g1(j * tao);
    for(int j = 1; j < height + 1; ++j)
        heat[j * width - 1] = g2((j-1) * tao);

    solve();

    minHeat = 9999.0;
    maxHeat = -9999.0;

    for(int i = 0; i < width * height; ++i )
    {
        if(minHeat > heat[i])
            minHeat = heat[i];
        if(maxHeat < heat[i])
            maxHeat = heat[i];
        printf("heat[%d] = %f\n", i, heat[i]);
    }
}

void HeatConduction::solve()
{
    cv::Mat A(height, height, CV_32F);
    for(int i = 1; i < height - 1; ++i)
    {
        A.at<float>(i, i + 1) = -r;
        A.at<float>(i, i) = 1.0 + 2 * r;
        A.at<float>(i, i - 1) = -r;
    }
    A.at<float>(0, 0) = 1.0 + 2 * r;
    A.at<float>(0, 1) = -r;
    A.at<float>(height - 1, height - 1) = 1.0 + 2 * r;
    A.at<float>(height - 1, height - 2) = -r;

    cv::Mat B = A.inv();
    for(int j = 0; j < width - 1; ++j)
    {
        for(int i = 1; i < height - 1; i++)
        {
            for(int k = 2; k < height - 1; ++k)
            {
                heat[j * width + i] += B.at<float>(i, k - 1) * heat[j * width + k];
            }
            heat[j * width + i] += B.at<float>(i, 0) * (heat[j * width + 1] + r *heat[(j + 1) * width]);
            heat[j * width + i] += B.at<float>(i, height - 1) * (heat[j * width + height - 1] + r *heat[(j + 1) * width + height - 1]);
        }
    }

}
