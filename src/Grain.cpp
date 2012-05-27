
#include "const.h"

Grain::Grain() {

    h = hp = 0;
    h_max = h_min = hp_max = hp_min = 0;
    d_k = v_g = t_v = l_k = 0;

    minor_right = minor_bottom = minor_rightBottom = NULL; 
    major_left  = major_top    = major_leftTop     = NULL; 

}

void Grain::init(Grain* ir, Grain* ib, Grain* irb,
                 Grain* ar, Grain* ab, Grain* arb) {

    minor_right       = ir;
    minor_bottom      = ib;
    minor_rightBottom = irb;

    major_left        = ar;
    major_top         = ab;
    major_leftTop     = arb;

}

void Grain::update(float newH, float f_v) {

    if (fabs(h - newH) < 0.001)
        return;

    h = newH;
    update(f_v);
    major_left->update(f_v);
    major_top->update(f_v);
    major_leftTop->update(f_v);

}

void Grain::update(float f_v) {

    float h_ir   = minor_right->getH();
    float h_ib   = minor_bottom->getH();
    float h_irb  = minor_rightBottom->getH();
    h_max = MAX4(h, h_ir, h_ib, h_irb);
    h_min = MIN4(h, h_ir, h_ib, h_irb);
    hp = h_max - h;

    float hp_ir  = minor_right->getHp();
    float hp_ib  = minor_bottom->getHp();
    float hp_irb = minor_rightBottom->getHp();
    hp_max = MAX4(hp, hp_ir, hp_ib, hp_irb);
    hp_min = MIN4(hp, hp_ir, hp_ib, hp_irb);

    d_k = h / (h + h_ir + h_ib + h_irb);
    v_g = (hp + hp_ir + hp_ib + hp_irb) / 4;
    t_v = f_v * v_g;
    l_k = d_k * t_v    // = this->calL_k(h)
        + major_left->calL_k(h)
        + major_top->calL_k(h)
        + major_leftTop->calL_k(h);

}

/* 
float Grain::getH_sum() {

    return h 
         + minor_right->getH()
         + minor_bottom->getH()
         + minor_rightBottom->getH();

}

float Grain::getHp_sum() {

    return hp 
         + minor_right->getHp()
         + minor_bottom->getHp()
         + minor_rightBottom->getHp();

}*/

float Grain::calL_k(float gh) {

    return gh 
         / (h + minor_right->getH() + minor_bottom->getH() + minor_rightBottom->getH())
         * t_v;
    
}
