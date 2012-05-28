
#include "const.h"

<<<<<<< HEAD
void Elem::set(float vx, float vy, float vc, float vp) {
=======
Elem::Elem() {

    Elem(0, 0, 0, 0);

}


Elem::Elem(float vx, float vy, float vc, float vp) {
>>>>>>> 9abcdac29314434d58d162c267808fc7da6b8258
    
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

<<<<<<< HEAD
Elem::Elem() {

    set(0, 0, 0, 0);

}
=======
>>>>>>> 9abcdac29314434d58d162c267808fc7da6b8258

Elem& Elem::operator = (const Elem& e) {

    x = vx;
    y = vy;
    c = vc;
    p = vp;

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

