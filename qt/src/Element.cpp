
#include "const.h"

void Elem::set(float vx, float vy, float vc, float vp) {
    
    x = vx;
    y = vy;
    c = vc;
    p = vp;
 
}

Elem::Elem(float vx, float vy, float vc, float vp) {
 
    set(vx, vy, vc, vp);
   
}

Elem::Elem(const Elem& e) {

    set(e.x, e.y, e.c, e.p);

}

Elem::Elem() {

    set(0, 0, 0, 0);

}

Elem& Elem::operator = (const Elem& e) {

    Elem(e.x, e.y, e.c, e.p);

}


bool Elem::operator  < (const Elem& e) const {

    float d1 = sqrt(x*x + y*y);
    float d2 = sqrt(e.x*e.x + e.y*e.y);
    if (d1 - d2 <= -DIFF)
        return true;
    else if (fabs(d1 - d2) < DIFF) {
        if (x - e.x <= -DIFF)
            return true;
        else if (fabs(x - e.x) < DIFF && y - e.y <= -DIFF)
            return true;
    }
    return false;

}

