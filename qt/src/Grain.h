
#ifndef GRAIN_MODEL
#define GRAIN_MODEL

class Grain {

private:
    float h; 
    float t;
    float b;
    float grey;
    Grain* relativeGrains[7];
public:
    float getHp(float gh);
    float getH_sum();
    float getHp_sum();
    float getD_k(float gh);

public:
    Grain();
    void init(Grain* al, Grain* au, Grain* alu,   // i前缀表示副高度，a前缀表示主高度
              Grain* ir, Grain* ib, Grain* irb);  // 在使用Grain前必须初始化Grian左，下，左下三个方向的突起高度
    void updateH(float gh); 
    void updateT(float gt);
    void setB_v(float bv);

    float getH();
    float getH_max();
    float getH_min();
    float getHp_max();
    float getHp_min();
    float getT_v(float f_v);
    float getL_k(float f_v);
    float getB_k(float m, float p, float f_v);
    float getT_k();

    float getB_v() {return b;}

};

#endif
