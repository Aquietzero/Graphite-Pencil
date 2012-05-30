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


void Interaction::calPencilB_v() {

    set<Elem>::iterator iter = pencil.getAllPoints.begin();

    for (; iter != pencil.getAllPoints.end(); ++iter) {

        int tempx = x + iter->x;
        int tempy = y + iter->y;
        float hmax = paper.getH_max(tempx, tempy);
        float hmin = paper.getH_min(tempx, tempy);
        
        // 计算d_l
        float d_l = hmax - hmax * pencil.getAvgPressure();
        if (d_l < hmin)
            d_l = hmin;

        // 更新突起高度
        float E = d_l * pencil.da() * paper.getW();
        float h = paper.getH(tempx, tempy) - E;
        paper.update(h, tempx, tempy);
         
        // 计算突起对应铅笔位置上的损耗 
        if (paper.getH(tempx, tempy) >= d_l)
            iter->b = paper.getT_v(tempx, tempy);
        else {

            float h_m = (paper.getHp_max(tempx, tempy) - d_l) /
                        (paper.getHp_max(tempx, tempy) - paper.getHp_min(tempx, tempy));
            iter->b = paper.getT_v(tempx, tempy) * h_m;
        }
        
        // 调整B_v
        pencil.BVAdjuster(iter->b);

    }


    iter = pencil.getAllPoints.begin();
    // 计算4个位置
    float B = 0;
    for (; iter != pencil.getAllPoints.end(); ++iter) {
        int tempx = x + iter->x;   
        int tempy = y + iter->y;

        Grain* G = relativeGrains(tempx, tempy);
        float currentH = paper.getH(tempx, tempy);
        for (int i = 0; i < 4; ++i, ++G)
            B += G->getB_v() * G->calD_k(currentH);

        if (paper.getT_v(tempx, tempy) >= paper.getL_k(tempx, tempy))   
            B = B * pow(paper.getM(), pencil.getAvgPressure());

        float G = pencil.getGP() * B;
        float C = pencil.getCP() * B;
        float W = pencil.getWP() * B;

        float T = G + C + W;
        paper.updateT_k(tempx, tempy, T);

    }

    

             



    
    }
}

