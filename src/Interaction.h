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
    float  e_k;             // 纸张损耗的总重量
    float  ba() {return 0.98;} // 返回值域[0, 1]，暂定0.98 

    Paper  paper;
    Pencil pencil;
    int x;
    int y;
   
public:
    Interaction();
    void initPencil(float p, float d, float gp, float cp, float wp 
                    Elem* first, Elem* last);
    void initPaper();
    void setXY(int coordx, int coordy);
    void calT_k(); // 计算值后Pencil的BVadjust()函数
    
};
    
#endif
