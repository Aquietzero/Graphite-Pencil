
#ifndef ELEMENT_H_
#define ELEMENT_H_

struct Elem {

    void set(float vx, float vy, float vc, float vp);

    Elem(float vx, float vy, float vc=0, float vp=0);
    Elem(const Elem& e);
    Elem();
    Elem& operator =  (const Elem& e);
    bool  operator <  (const Elem& e) const ;

    float x;
    float y; // 定点坐标 (x, y)
    float c; // 压力系数 [0, 1]
    float p; // 压力

};

#endif

