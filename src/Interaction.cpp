/*
 * =====================================================================================
 *
 *       Filename:  Interaction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月22日 11时01分26秒
 *       Revision:  implement Interaction.h
 *       Compiler:  gcc
 *
 *         Author:  yveschen 
 *        Company:  
 *
 * =====================================================================================
 */

#include "const.h"
  
Interaction::Interaction(Paper& pp, Pencil& pn): paper(pp), pencil(pn) {

    x   = 0;
    y   = 0;

}

void Interaction::setXY(float ox, float oy, float offsetX, float offsetY) {
    
    x = ox + offsetX;
    y = oy + offsetY;

}

float Interaction::calD_l() {

    float h_max = paper.getH_max(x, y);
    float h_min = paper.getH_min(x, y);
    float p_a   = pencil.getAvgPressure();
    float d_l = h_max - h_max * p_a;
    return d_l < h_min ? h_min : d_l;
    
}

float Interaction::calH_k(float d_l) {

    return paper.getH(x, y) - d_l * pencil.da();

}

float Interaction::calB_v(float d_l) {

   if (paper.getH(x, y) > d_l)
       return paper.getT_v(x, y);

    float hp_max = paper.getHp_max(x, y);
    float hp_min = paper.getHp_min(x, y);
    float b_v =  paper.getT_v(x, y) * (hp_max - d_l) / (hp_max - hp_min);
    return b_v * pencil.ba();

}


float Interaction::calT_k(float b_k) {

    return (pencil.getGP()
          + pencil.getCP()
          + pencil.getWP())
          * b_k;
}

void Interaction::act(float mx, float my) {

    set<Elem>& points = pencil.getAllPoints();
    set<Elem>::iterator it;

    for (it = points.begin(); it != points.end(); ++it) {
        setXY(it->x, it->y, x, y);
        float d_l = calD_l();
        float h_k = calH_k(d_l);
        float b_v = calB_v(d_l);
        paper.setB_v(x, y, b_v);
        paper.updateH(x, y, h_k);

    }

    for (it = points.begin(); it != points.end(); ++it) {
        setXY(it->x, it->y, x, y);
        float d_l = calD_l();
        float h_k = calH_k(d_l);
        float b_k = paper.getB_k(pencil.getAvgPressure(), x, y);
        float t_k = calT_k(b_k);
        paper.updateH(x, y, h_k);
        paper.updateT(x, y, t_k);

    }
}













