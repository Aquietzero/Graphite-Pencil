/*
 * =====================================================================================
 *
 *       Filename:  Paper.h
 *
 *    Description:  Paper.h defines the basic model of paper.
 *
 *        Version:  1.0
 *        Created:  05/15/2012 10:42:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef GRAPHITE_PENCIL_PAPER_MODEL
#define GRAPHITE_PENCIL_PAPER_MODEL

class Grain {

private:
    float h_k;    // 高度
    float hs_k;   // 高度的补
    float hs_min;
    float hs_max;
    float v_g;    // 突起体积
    int t_v;      // 突起最大笔屑容量
    float d_k;    // D_k, 各高度比率
    int l_k;      // 各高度的最大笔屑容量
    float b_v;    // 纸张突起的体积损耗
    int b_k;      // 各高度接到的笔屑
    int t_k;      // 实际接收的笔屑数量
    float G_k;  
    float C_k;
    float W_k;

public:
    Grain();      // 初始化各参数
    
    calHs_k();             // 计算突起补的体积
    calT_v();              // 计算突起最大笔屑容量
    calL_k();              // 计算各高度的最大笔屑容量

    calB_v();     // 计算突起损耗B_v
    adjustB_v();  // 调整B_v
    updateH_k(Pd /*，纸的厚度*/);  // 更新突起高度
    calB_k();     // 计算各高度上接到的笔屑
    calT_k(/* Pencil的三个const常量 */);  // 计算实际接收的笔屑数量，同时调用上面4个函数操作
};


class Paper {

private:
    vector<vector<Grain>>; // 存放突起的二维数组
    const int f_v;         // 常量属性，值域范围[1000, 3000]
    const float W;         // 纸张重量，值域范围[0, 1]
    const float M;         // 常量，值域范围[0.97, 0.99]
    
public:
    Paper();               // 根据输入参数初始化纸张及各个高度
                           // （利用分形算法求出各个高度）

    calGrain(int x, int y/*, 传进纸的信息 */); // 计算纸张受影响部分接收的笔屑,通过调用calB_k(),calT_k()
    
};

#endif
