/*
 * =====================================================================================
 *
 *       Filename:  Element.cpp
 *
 *    Description:  implement Element.h
 *
 *        Version:  1.0
 *        Created:  2012年05月21日 18时39分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yveschen 
 *        Company:  
 *
 * =====================================================================================
 */

#include "const.h"

Elem::Elem() {

    Elem(0, 0, 0, 0);

}


Elem::Elem(float vx, float vy, float vc, float vp) {
    
    x = vx;
    y = vy;
    c = vc;
    p = vp;
    
}


Elem::Elem(const Elem& e) {

    Elem(e.x, e.y, e.c, e.p);
}


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

