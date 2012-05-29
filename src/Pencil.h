
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
    void setPointsByRasterize(const Elem& e1, const Elem& e2, const Elem& e3);
    void setElemByLinearInterpolation(const Elem& e1, Elem& e2, const Elem& e3);
    void setElemByTriangleInterpolation(const Elem& e1, const Elem& e2, const Elem& e3, Elem& e0);
    void setIntersectionElem(const Elem& e0, const Elem& e1, const Elem& e2, const Elem& e3, Elem& e4);
    void setBorder(float& left, float& right, float& up, float& down, const Elem& e1, const Elem& e2, const Elem& e3);
    bool isInner(const Elem& e1, const Elem& e2, const Elem& e3, const Elem& e0);
    const float getGP();
    const float getCP();
    const float getWP();

public:
    Pencil(float p, float d, float gp, float cp, float wp, 
           Elem* first, Elem* last);
    Pencil(Pencil pen);
    set<Elem>& getAllPoints() { return points; }
    void update(set<Elem>::iterator it, float bv);
    void update(float bv);
    float getAvgPressure();// 计算所有点的平均压力

};

#endif
