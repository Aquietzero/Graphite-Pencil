
#ifndef GRAPHITE_PENCIL_PENCIL_MODEL
#define GRAPHITE_PENCIL_PENCIL_MODEL

class Pencil {
    
private:
    vector<Elem> vertices;       // 多边形顶点
    set<Elem> points;         // 多边形所有点

    float pressure;     // 铅笔中心所受压力
    float degree;       // 铅笔硬度
    float g_p;
    float c_p;
    float w_p;
   
    float BVAdjuster(float bv);//根据突起对应铅笔位置上的损耗调整该损耗对铅笔形状进行调整

    void setPoints();         // 光栅话从而得到铅笔多边形所包含的所有点
    bool setLineEquation(const Elem& e1, const Elem& e2, float& a, float& b, float& c);
    void setPointsByRasterize(const Elem& e1, const Elem& e2, const Elem& e3);
    bool setElemByLinearInterpolation(const Elem& e1, Elem& e2, const Elem& e3);
    bool setElemByTriangleInterpolation(const Elem& e1, const Elem& e2, const Elem& e3, Elem& e0);
    bool setIntersectionElem(const Elem& e0, const Elem& e1, const Elem& e2, const Elem& e3, Elem& e4);
    void setBorder(float& left, float& right, float& up, float& down, const Elem& e1, const Elem& e2, const Elem& e3);
    bool isInner(const Elem& e1, const Elem& e2, const Elem& e3, const Elem& e0);

public:
    Pencil();
    void init(float p, float d, float gp, float cp, float wp, 
              Elem* first, Elem* last);

    float getGP() { return g_p; }
    float getCP() { return c_p; }
    float getWP() { return w_p; }
    float getAvgPressure();

    void update(set<Elem>::iterator it, float bv);
    void update(float bv);
    float da() { return 0.1; }// 返回值域[0, 1],暂定返回0.5
    float ba() { return 0.5; }// 返回值域[0, 1],暂定返回0.5

    set<Elem>& getAllPoints() { return points; }

};

#endif
