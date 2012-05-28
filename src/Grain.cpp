
#include "const.h"

Grain::Grain() {

    h = hp = 0;
    h_max = h_min = hp_max = hp_min = 0;
    d_k = t_v = l_k = 0;

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

void Grain::updateH(float newH) {

    h = newH;

}

void Grain::updateH_max() {

    h_max = MAX4(h,
                 minor_right->getH(),
                 minor_bottom->getH(),
                 minor_rightBottom->getH());

}

void Grain::updateH_min() {

    h_min = MIN4(h,
                 minor_right->getH(),
                 minor_bottom->getH(),
                 minor_rightBottom->getH());

}

void Grain::updateHp() {

    hp = h_max - h;

}

void Grain::updateHp_max() {

    h_max = MAX4(h,
                 minor_right->getHp(),
                 minor_bottom->getHp(),
                 minor_rightBottom->getHp());

}

void Grain::updateHp_min() {

    h_min = MIN4(h,
                 minor_right->getHp(),
                 minor_bottom->getHp(),
                 minor_rightBottom->getHp());

}

void Grain::updateD_k() {
 
    d_k = h / getH_sum();

}

void Grain::updateT_v(float f_v) {

    t_v = f_v * getHp_sum() / 4;

}

void Grain::updateL_k() {

    l_k = this->calL_k(h)
        + major_left->calL_k(h)
        + major_top->calL_k(h)
        + major_leftTop->calL_k(h);

}

void Grain::update(float newH, float f_v) {

    updateH(newH);

    this->updateByH(f_v);
    major_left->updateByH(f_v);
    major_top->updateByH(f_v);
    major_leftTop->updateByH(f_v);

}

void Grain::updateByH(float f_v) {

    updateH_max();
    updateH_min();
    updateHp();
    updateHp_max();
    updateHp_min();

    updateD_k();
    updateT_v(f_v);
    updateL_k();

}

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

}

float Grain::calL_k(float gh) {

    return gh / getH_sum() * t_v;
    
}
