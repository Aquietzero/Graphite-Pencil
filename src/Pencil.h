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
 *         Author:  xxspc
 *        Company:  XXSpace && NullSpace
 *
 * =====================================================================================
 */

#ifndef GRAPHITE_PENCIL_PENCIL_MODEL
#define GRAPHITE_PENCIL_PENCIL_MODEL

class Pencil {
    
private:
    set<Elem> vertices;       // 多边形顶点
    set<Elem> points;         // 多边形所有点

    float pressure;     // 铅笔中心所受压力
    const float degree;       // 铅笔硬度
    const float g_p;
    const float c_p;
    const float w_p;
   
    float da() { return 0.5; }// 返回值域[0, 1],暂定返回0.5
    float BVAdjuster(float bv);//根据突起对应铅笔位置上的损耗调整该损耗对铅笔形状进行调整

    void setPoints();         // 光栅话从而得到铅笔多边形所包含的所有点

    void rasterize(const Elem& e1, const Elem& e2, const Elem& e3);
    void cInterpolation(const Elem& e1, Elem& e2, const Elem& e3);

public:
    Pencil(float p, float d, float gp, float cp, float wp, 
           Elem* first, Elem* last);
    void update(set<Elem>::iterator it, float bv);
    void update(float bv);
    float getAvgPressure();// 计算所有点的平均压力

};

#endif
