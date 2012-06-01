
#include "const.h"

Grain::Grain() {
    
    h = t = 0;

}

void Grain::init(Grain* al, Grain* au, Grain* alu,
                 Grain* ir, Grain* ib, Grain* irb) {

    relativeGrains[0] = al;
    relativeGrains[1] = au;
    relativeGrains[2] = alu;

    relativeGrains[3] = this;

    relativeGrains[4] = ir;
    relativeGrains[5] = ib;
    relativeGrains[6] = irb;

}

void Grain::updateH(float gh) {

    h = gh; 
}

void Grain::updateT(float gt) { 
    
    t += gt; 

}

float Grain::getH() { 
    
    return h; 

}

float Grain::getT_k() { 
    
    return t; 

}

float Grain::getH_max() {

    return MAX4(relativeGrains[3]->h,
                relativeGrains[4]->h,
                relativeGrains[5]->h,
                relativeGrains[6]->h);

}

float Grain::getH_min() {

    return MIN4(relativeGrains[3]->h,
                relativeGrains[4]->h,
                relativeGrains[5]->h,
                relativeGrains[6]->h);

}

float Grain::getH_sum() {

    return relativeGrains[3]->h 
         + relativeGrains[4]->h
         + relativeGrains[5]->h
         + relativeGrains[6]->h;
}

float Grain::getHp_max() {

    return getH_max() - getH_min();
/*  float h_max = getH_max();
    return MAX4(h_max - relativeGrains[3]->h,
                h_max - relativeGrains[4]->h,
                h_max - relativeGrains[5]->h,
                h_max - relativeGrains[6]->h);
*/
}

float Grain::getHp_min() {

    return 0;
/*  float h_max = getH_max();
    return MIN4(h_max - relativeGrains[3]->h,
                h_max - relativeGrains[4]->h,
                h_max - relativeGrains[5]->h,
                h_max - relativeGrains[6]->h);
*/
}

float Grain::getHp_sum() {

    float h_max = getH_max();
    return h_max - relativeGrains[3]->h
         + h_max - relativeGrains[4]->h
         + h_max - relativeGrains[5]->h
         + h_max - relativeGrains[6]->h;
}

float Grain::getD_k(float gh) { 

    float h_sum = getH_sum();
    if (h_sum < DIFF)
        return 0;
    return gh / getH_sum(); 
}

float Grain::getT_v(float f_v) {

    return f_v * getHp_sum() / 4; 

}

float Grain::getL_k(float f_v) {

    return relativeGrains[0]->getD_k(h) * relativeGrains[0]->getT_v(f_v) 
         + relativeGrains[1]->getD_k(h) * relativeGrains[1]->getT_v(f_v)
         + relativeGrains[2]->getD_k(h) * relativeGrains[2]->getT_v(f_v)
         + relativeGrains[3]->getD_k(h) * relativeGrains[3]->getT_v(f_v);
}

void Grain::setB_v(float bv) { 

    b = bv; 

}

float Grain::getB_k(float m, float p, float f_v) {
 
    float b_k = relativeGrains[0]->getD_k(h) * relativeGrains[0]->b 
              + relativeGrains[1]->getD_k(h) * relativeGrains[1]->b
              + relativeGrains[2]->getD_k(h) * relativeGrains[2]->b
              + relativeGrains[3]->getD_k(h) * relativeGrains[3]->b;
    return t >= getL_k(f_v) ? b_k * pow(m, p) : b_k;
}

