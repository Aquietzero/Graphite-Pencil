
#ifndef PAPER_MODEL
#define PAPER_MODEL

class Paper {

private:
    //vector<vector<Grain> > grains;// 存放突起的二维数组
    Grain** grains;               // 存放突起的二维数组
    int   width;
    int   height;
                                  // 放弃边界上的所有突起以便后续操作，实际索引起始为［1，h-2］［1, w-2］
    float f_v;              // 常量属性，值域范围[1000, 3000]
    float M;                // 常量，值域范围[0.97, 0.99]
    float W;

    Grain* g;
    
    void initAllGrains();

public:
    Paper();   
    void init(int w, int h, float fv, float pw, float pm);        // 根据输入参数初始化纸张及各个高度
    void updateH(float gh) { g->updateH(gh); }
    void updateT(float gt) { g->updateT(gt); }

    float  getM() { return M; }
    float  getW() { return W; }
    float  getH()      { return g->getH(); }
    float  getH_max()  { return g->getH_max(); }
    float  getH_min()  { return g->getH_min(); }
    float  getHp_max() { return g->getHp_max(); }
    float  getHp_min() { return g->getHp_min(); }
    float  getT_k()    { return g->getT_k(); }
    float  getT_v()    { return g->getT_v(f_v); }    
    float  getL_k()    { return g->getL_k(f_v); } 
    float  getB_v()    { return g->getB_v(); }
    float  getB_k(float p)  { return g->getB_k(M, p, f_v); }
    void   setB_v(float bv) { g->setB_v(bv); }
    void setPosition(int x, int y);                               // 获取突起

    void show(float p);
    //void show();
};

#endif
