
#ifndef GRAIN_MODEL
#define GRAIN_MODEL

class Grain {

private:
    enum {BELOWER_FIRST=3, BELOWER_LAST=7, UPPER_FIRST=0, UPPER_LAST=4};
    float h;      // 高度
    float t;
    float b;
    Grain* relativeGrains[BELOWER_LAST];

    float getHp();
    float getH_sum();
    float getHp_sum();
    float getD_k(float gh);

public:
    Grain();
    void init(Grain* ir, Grain* ib, Grain* irb,   // i前缀表示副高度，a前缀表示主高度
              Grain* ar, Grain* ab, Grain* arb);  // 在使用Grain前必须初始化Grian左，下，左下三个方向的突起高度
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
    float getT();

};

#endif
