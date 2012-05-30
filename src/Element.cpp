
#include "const.h"

void Elem::set(float vx, float vy, float vc, float vp, float vb) {
    
    x = vx;
    y = vy;
    c = vc;
    p = vp;
    b = vb;
 
}

Elem::Elem(float vx, float vy, float vc, float vp, float vb) {
 
    set(vx, vy, vc, vp, vb);
   
}

Elem::Elem(const Elem& e) {

    set(e.x, e.y, e.c, e.p, e.b);

}

Elem::Elem() {

    set(0, 0, 0, 0, 0);

}

Elem& Elem::operator = (const Elem& e) {

    Elem(e.x, e.y, e.c, e.p);

}

bool Elem::operator == (const Elem& e) const {

    return fabs((x - e.x) * (x - e.x) + (y - e.y) * (y - e.y)) <= DIFF;

}

bool Elem::operator != (const Elem& e) const {

    return fabs((x - e.x) * (x - e.x) + (y - e.y) * (y - e.y)) > DIFF;

}

bool Elem::operator > (const Elem& e) const {

    return (x*x + y*y) - (e.x*e.x + e.y*e.y) > DIFF;
}

bool Elem::operator <= (const Elem& e) const {

    return (x*x + y*y) - (e.x*e.x + e.y*e.y) <= DIFF;

}

bool Elem::operator < (const Elem& e) const {

    return (x*x + y*y) - (e.x*e.x + e.y*e.y) < -DIFF;

}

bool Elem::operator >= (const Elem& e) const  {

    return (x*x + y*y) - (e.x*e.x + e.y*e.y) >= -DIFF;

}

