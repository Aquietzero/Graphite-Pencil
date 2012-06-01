/*
 * =====================================================================================
 *
 *       Filename:  Interaction.h
 *
 *    Description:  Interaction.h defines the basic interaction model between grahite
 *                  pencil and paper.
 *
 *        Version:  1.0
 *        Created:  05/15/2012 10:46:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zero, yveschen
 *        Company:  NullSpace
 *
 * =====================================================================================
 */

#ifndef GRAPHITE_PENCIL_INTERACTION
#define GRAPHITE_PENCIL_INTERACTION

class Interaction {
 
private:

    Paper&  paper;
    Pencil& pencil;
    int x, y;

public:
    Interaction(Paper& pp,Pencil& pn);
    void setPosition(float ox, float oy, float offsetX, float offsetY);

    float calD_l();
    float calH_k(float d_l);
    float calB_v(float d_l);
    float calT_k(float b_k);
    
    void act(float mx, float my);

};
    
#endif
