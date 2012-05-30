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
 
Interaction::Interaction() {

    d_l = 0;
    e_k = 0;
    x   = 0;
    y   = 0;

}


void Interaction::initPencil(float p, float d, float gp, float cp, float wp,
                             Elem* first, Elem* last) {

    pencil.init(p, d, gp, cp, wp, first, last);

}


void initPaper() {

    paper.init();

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
        float hmax = paper.getH_max(tempx, tempy);
        float hmin = paper.getH_min(tempx, tempy);
        
        float d_l = hmax - hmax * pencil.getAvgPressure();
        if (d_l < hmin)
            d_l = hmin;
        
        if (paper.getH(tempx, tempy) >= d_l)
            iter->B_v = paper.getT_v(tempx, tempy);
        else {

            float h_m = (paper.getHp_max(tempx, tempy) - d_l) /
                        (paper.getHp_max(tempx, tempy) - paper.getHp_min(tempx, tempy));
            iter->B_v = paper.getT_v(tempx, tempy) * h_m;
        }

        pencil.BVAdjuster(B_v);
        ////////////////////////////////////////////
        float B_k = B_v * paper.getTop(tempx, tempy);       
        float g_k, G_k = 0;

        for (int i = 0; i < 4; ++i) {
            g_k = pencil.getGP() * B_k;



    
    }
}

