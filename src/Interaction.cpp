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
 
Interaction::Interaction(Paper p, Pencil pen) {

    d_l = 0;
    e_k = 0;
    x   = 0;
    y   = 0;

    paper(p);
    pencil(pen);

}


void Interaction::setXY(int coordx, int coordy) {
    
    x = coordx;
    y = coordy;

}


void Interaction::calD_l() {

    set<Elem>::iterator iter = pencil.getAllPoints.begin();

    for (; iter != pencil.getAllPoints.end(); ++iter) {

        int tempx = x + iter->x;
        int tempy = y + iter->y;
        float hmax = p.getH_max(tempx, tempy);
        float hmin = p.getH_min(tempx, tempy);
        
        float d_l = hmax - hmax * p.getAvgPressure();
        if (d_l < hmin)
            d_l = hmin;
        
        float B_v = 0;
        if (p.getH(tempx, tempy) >= B_v)
            B_v = p.getT_v(tempx, tempy);
        else {

            float h_m = (p.getHp_max(tempx, tempy) - d_l) /
                        (p.getHp_max(tempx, tempy) - p.getHp_min(tempx, tempy));
            B_v = p.getT_v(tempx, tempy);
        }

        pencil.BVAdjuster(B_v);
        
        float B_k = B_v * d_l;        



    
    }
}

