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
    float  d_l;             // 铅笔距离纸平面的高度
    float  e_k;             // 纸张损耗的总重量
    float  ba();            // 返回值域[0, 1]
    Paper  paper;
    Pencil pencil;
   
public:
    Interaction(Paper p, Pencil pen);
    void calD_l();              // 计算铅笔距纸平面高度
    void calE_k();              // 计算纸张损耗的总重量
    void calGray(int x, int y); // 通过xy计算灰度值，调用铅笔的calAllPoints()函数得到所影响的点，传给Paper的calGrain()进行运算
    void updateAllGrains(pencil, d_l); // 通过传进铅笔的硬度和铅笔距离纸的高度更新突起的高度,调用Grain的updateH_k()函数
    void calPencilB_v(pencil);  // 调用calB_v()和adjustB_v()函数
     
    
};
    
class show {
/*
private:
    Interation interation;
    
public:
    showGray(); // 通过interation的calGray()函数得到的灰度值进行显示
*/
};

#endif
