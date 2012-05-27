/*
 * =====================================================================================
 *
 *       Filename:  Element.h
 *
 *    Description:  Element.h defines the basic class of points
 *
 *        Version:  1.0
 *        Created:  2012年05月19日 23时13分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yveschen
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_
//#pragma once

struct Elem {

    Elem(float vx, float vy, float vc=0, float vp=0);
    Elem(const Elem& e);
    Elem();
    Elem& operator =  (const Elem& e);
    bool  operator == (const Elem& e) const ;
    bool  operator != (const Elem& e) const ;
    bool  operator >= (const Elem& e) const ;
    bool  operator <= (const Elem& e) const ;
    bool  operator >  (const Elem& e) const ;
    bool  operator <  (const Elem& e) const ;

    float x;
    float y; // 定点坐标 (x, y)
    float c; // 压力系数 [0, 1]
    float p; // 压力

};

#endif

