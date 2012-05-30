
#ifndef GRAIN_MODEL
#define GRAIN_MODEL

class Grain {

private:
    float h;      // 高度
    float h_min;
    float h_max;
    float hp;     // 高度的补
    float hp_min;
    float hp_max;

    float d_k;    // D_k, 各高度比率
    float t_v;    // 突起最大笔屑容量
    float l_k;    // 各高度的最大笔屑容量
    float t_k;

    Grain* minor_right;     // 表示该高度所持有的另外三个副高度
    Grain* minor_bottom;
    Grain* minor_rightBottom;

    Grain* major_left;     // 表示该突起高度所相关的另外三个突起主高度
    Grain* major_top;
    Grain* major_leftTop;

    float getHp()     { return hp; }
    float getH_sum();
    float getHp_sum();

    float calL_k(float gh); // 计算某高度分属各个突起所能容纳的最大笔屑数量

    void updateByH(float f_v); // 更新突起所有其他有关属性以及相关突起高度的属性
    void updateH(float newH);
    void updateH_max();
    void updateH_min();
    void updateHp();
    void updateHp_max();
    void updateHp_min();

    void updateD_k();
    void updateT_v(float f_v);
    void updateL_k();
    void updateT_k(float tk);

public:
    Grain();
    void init(Grain* ir, Grain* ib, Grain* irb,   // i前缀表示副高度，a前缀表示主高度
              Grain* ar, Grain* ab, Grain* arb);  // 在使用Grain前必须初始化Grian左，下，左下三个方向的突起高度
    void update(float newH, float f_v, float tk);   

    float getH()      { return h; }
    float getH_max()  { return h_max; }
    float getH_min()  { return h_min; }
    float getHp_max() { return hp_max; }
    float getHp_min() { return hp_min; }

    float getD_k()    { return d_k; }    
    float getT_v()    { return t_v; }    
    float getL_k()    { return l_k; }    
    float getT_k()    { return t_k; }

    Grain& getLeft()        { return *major_left; }
    Grain& getTop()         { return *major_top; }
    Grain& getLeftTop()     { return *major_leftTop; }
    Grain& getRight()       { return *minor_right; }
    Grain& getBottom()      { return *minor_bottom; }
    Grain& getRightBottom() { return *minor_rightBottom; }

};

#endif
