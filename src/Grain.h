#ifndef GRAIN_MODEL
#define GRAIN_MODEL

#include "const.h"

class Grain {

private:
    float h;      // 高度
    float h_min;
    float h_max;
    float hp;     // 高度的补
    float hp_min;
    float hp_max;

    float d_k;    // D_k, 各高度比率
    float v_g;    // 突起体积
    float t_v;    // 突起最大笔屑容量
    float l_k;    // 各高度的最大笔屑容量

    Grain* minor_right;     // 表示该高度所持有的另外三个副高度
    Grain* minor_bottom;
    Grain* minor_rightBottom;

    Grain* major_left;     // 表示该突起高度所相关的另外三个突起主高度
    Grain* major_top;
    Grain* major_leftTop;

   float getH()      { return h; }
   float getHp()     { return hp; }
/* float getH_sum();
   float getHp_sum();*/
   float calL_k(float gh); // 计算某高度分属各个突起所能容纳的最大笔屑数量
   void update(float f_v); // 更新突起所有其他有关属性以及相关突起高度的属性

public:
    Grain();
    void init(Grain* ir, Grain* ib, Grain* irb,   // i前缀表示副高度，a前缀表示主高度
              Grain* ar, Grain* ab, Grain* arb);  // 在使用Grain前必须初始化Grian左，下，左下三个方向的突起高度
    void update(float newH, float f_v);           // 更新突起主高度

    float getH_max()  { return h_max; }
    float getH_min()  { return h_min; }
    float getHp_max() { return hp_max; }
    float getHp_min() { return hp_min; }

    float getD_k()    { return d_k; }    
    float getT_v()    { return t_v; }    
    float getL_k()    { return l_k; }    
};

#endif