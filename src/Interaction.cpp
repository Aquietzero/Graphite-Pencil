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
#include <iomanip>
  
Interaction::Interaction(Paper& pp, Pencil& pn): paper(pp), pencil(pn) {

    x = y = 0;

}

void Interaction::setPosition(float ox, float oy, float offsetX, float offsetY) {
    
    x = ox + offsetX;
    y = oy + offsetY;
    paper.setPosition(x, y);
    /*
    cout << "(" << ox << "," << oy << ")"
         << "(" << offsetX << "," << offsetY << ")"
         << "(" << x << "," << y << ")";
    */

}

float Interaction::calD_l() {

//    return paper.getHp_max() * pencil.getAvgPressure();
    float h_max = paper.getH_max();
    float h_min = paper.getH_min();
    float p_a   = pencil.getAvgPressure();
    float d_l = h_max - h_max * p_a;
    d_l =  d_l < h_min ? h_min : d_l;
    return d_l;
   
}

float Interaction::calH_k(float d_l) {

//    return paper.getH() * d_l * pencil.da();
    float h_k = paper.getH() - d_l * pencil.da() * paper.getW();
    h_k = h_k < 0 ? 0 : h_k;
    return h_k;

}

float Interaction::calB_v(float d_l) {

//    return  paper.getT_v() * d_l * pencil.ba();
    if (paper.getH() > d_l)
       return paper.getT_v();

    float hp_max = paper.getHp_max();
    float hp_min = paper.getHp_min();
    float b_v =  pencil.ba() * paper.getT_v() * (hp_max - d_l) / (hp_max - hp_min);
    b_v = b_v < 0 ? 0 : b_v;
    return b_v;

}


float Interaction::calT_k(float b_k) {

  float t_k = (pencil.getGP()
          + pencil.getCP()
          + pencil.getWP())
          * b_k;
    return t_k;

}

void Interaction::act(float mx, float my) {

    set<Elem>& points = pencil.getAllPoints();
    set<Elem>::iterator it;
    
    for (it = points.begin(); it != points.end(); ++it) {
        setPosition(it->x, it->y, mx, my);
        float d_l = calD_l();
        float b_v = calB_v(d_l);
        paper.setB_v(b_v);
    }

    for (it = points.begin(); it != points.end(); ++it) {
        setPosition(it->x, it->y, mx, my);
        float d_l = calD_l();
        float h_k = calH_k(d_l);
        float b_k = paper.getB_k(pencil.getAvgPressure());
        float t_k = calT_k(b_k);
       
                
        
/*
        cout << setw(15) << 1 - t_k * pencil.getGP() / 1000 << ","   
             << setw(15) << d_l << ","  
             << setw(15) << h_k << "," 
             << setw(15) << b_k << ","   
             << setw(15) << t_k << ","   
             << setw(15) << paper.getB_v() << ","   
             << setw(15) << paper.getL_k() << "#"
             << setw(15) << paper.getH() << ","
             << setw(15) << paper.getH_max() << ","
             << setw(15) << paper.getH_min() << "#"
             << setw(15) << paper.getHp_max() << ","
             << setw(15) << paper.getHp_min() << "\n";
*/
        paper.updateH(h_k);
        paper.updateT(t_k);

        float grey =  1 - paper.getT_k() * pencil.getGP() / 1000;

        glColor3f(grey, grey, grey);
        glBegin(GL_POINTS);
            glVertex2f(it->x + mx, it->y + my);
        glEnd();
 
    }
}

