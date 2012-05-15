/*
 * =====================================================================================
 *
 *       Filename:  Pencil.h
 *
 *    Description:  Pencil.h defines the basic model of the graphite pencil.
 *
 *        Version:  1.0
 *        Created:  05/15/2012 10:35:30 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef GRAPHITE_PENCIL_PENCIL_MODEL
#define GRAPHITE_PENCIL_PENCIL_MODEL

#include "const.h"

class element {

    element(); // 初始化各个参数为0
    float x;
    float y;
    float c_i; // 压力系数 (0, 1)
    float p_i; // 压力 (0, 1)

};


class Pencil {
    
private:

    vector<element> vertices; // 多边形顶点
    vector<element> points;   // 多边形所有点
    int num_vertices;         // 多边形顶点数量
    int num_points;           // 多边形所有点数量
    float avg_pressure;       // 平均压力
    float pencil_degree;      // 铅笔硬度
    float da();               // 返回值域[0, 1]

    calAllpoints();           // 广搜算法算出所有点
    calCoefficient();         // 全局插值法求所有点压力系数
    calPressures();           // 计算各点承受的压力
    calAvgPressures();        // 计算所有点的平均压力

    const int GRAPHITE_PERCENT;
    const int CLAY_PERCENT;
    const int WAX_PERCENT;

public:

    Pencil();                 // 中心及边界坐标和对应压力系数，调用以下四个函数
                              // calAllpoints(); calCoefficient(); 
                              // calPressures(); calAvgPressures();     
                              
};

#endif
