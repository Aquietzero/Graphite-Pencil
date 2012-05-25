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
class Element {

public:
    Element(float X, float Y, float C_I, float P_I);
    float x;
    float y;
    float c_i; // 压力系数 (0, 1)
    float p_i; // 压力 (0, 1)

};

#endif

