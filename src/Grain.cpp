
#include "const.h"

Grain::Grain() {
    
    h = t = 0;

}

void Grain::init(Grain* ir, Grain* ib, Grain* irb,
                 Grain* ar, Grain* ab, Grain* arb) {

   relativeGrains[0] = ar;
   relativeGrains[1] = ab;
   relativeGrains[2] = arb;

   relativeGrains[3] = this;
   
   relativeGrains[4] = ib;
   relativeGrains[5] = irb;
   relativeGrains[6] = irb;

}

void Grain::updateH(float gh) { h = gh; }

void Grain::updateT(float gt) { t += gt; }

float Grain::getH() { return h; }
float Grain::getT() { return t; }

float Grain::getH_max() {

    return MAX4(relativeGrains[BELOWER_FIRST + 0]->h,
                relativeGrains[BELOWER_FIRST + 1]->h,
                relativeGrains[BELOWER_FIRST + 2]->h,
                relativeGrains[BELOWER_FIRST + 3]->h);

}

float Grain::getH_min() {

    return MIN4(relativeGrains[BELOWER_FIRST + 0]->h,
                relativeGrains[BELOWER_FIRST + 1]->h,
                relativeGrains[BELOWER_FIRST + 2]->h,
                relativeGrains[BELOWER_FIRST + 3]->h);

}

float Grain::getHp() { return getH_max() - h; }

float Grain::getHp_max() {

    return MAX4(relativeGrains[UPPER_FIRST + 0]->getHp(),
                relativeGrains[UPPER_FIRST + 1]->getHp(),
                relativeGrains[UPPER_FIRST + 2]->getHp(),
                relativeGrains[UPPER_FIRST + 3]->getHp());

}

float Grain::getHp_min() {

    return MIN4(relativeGrains[UPPER_FIRST + 0]->getHp(),
                relativeGrains[UPPER_FIRST + 1]->getHp(),
                relativeGrains[UPPER_FIRST + 2]->getHp(),
                relativeGrains[UPPER_FIRST + 3]->getHp());

}

float Grain::getH_sum() {

    int h_sum = 0;
    for (int i = BELOWER_FIRST; i != BELOWER_LAST; ++i)
         h_sum += relativeGrains[i]->h;
    return h_sum;

}

float Grain::getHp_sum() {

    int hp_sum = 0;
    for (int i = BELOWER_FIRST; i != BELOWER_LAST; ++i)
         hp_sum += relativeGrains[i]->getHp();
    return hp_sum;

}

float Grain::getD_k(float gh) { return gh / getH_sum(); }

float Grain::getT_v(float f_v) {return f_v * getHp_sum() / 4; }

float Grain::getL_k(float f_v) {

    float l_k = 0;
    for (int i = UPPER_FIRST; i < UPPER_LAST; ++i)
        l_k += relativeGrains[i]->getD_k(h) * relativeGrains[i]->getT_v(f_v);
    return l_k;
}

void Grain::setB_v(float bv) { b = bv; }

float Grain::getB_k(float m, float p, float f_v) {
 
    float b_k = 0;
    for (int i = UPPER_FIRST; i < UPPER_LAST; ++i)
        b_k += relativeGrains[i]->getD_k(h) * relativeGrains[i]->b;
    if (t >= getL_k(f_v))
        b_k *= pow(m, p);
    return b_k;

}

