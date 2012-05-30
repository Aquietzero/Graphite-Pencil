
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
    
    Grain& grain(int x, int y);                               // 获取突起
    void initAllGrains();

public:
    Paper();   
    void init(int w, int h, float fv, float pw, float pm);        // 根据输入参数初始化纸张及各个高度
    void updateH(int x, int y, float gh) { grain(x, y).updateH(gh); }
    void updateT(int x, int y, float gt) { grain(x, y).updateH(gt); }

    float  getM() { return M; }
    float  getW() { return W; }
    float  getH(float x, float y)      { return grain(x, y).getH(); }
    float  getH_max(float x, float y)  { return grain(x, y).getH_max(); }
    float  getH_min(float x, float y)  { return grain(x, y).getH_min(); }
    float  getHp_max(float x, float y) { return grain(x, y).getHp_max(); }
    float  getHp_min(float x, float y) { return grain(x, y).getHp_min(); }
    float  getT_v(float x, float y)    { return grain(x, y).getT_v(f_v); }    
    float  getL_k(float x, float y)    { return grain(x, y).getL_k(f_v); } 
    float  getB_k(float p, float x, float y)      { return grain(x, y).getB_k(M, p, f_v); }
    void   setB_v(float bv, float x, float y)     { grain(x, y).setB_v(bv); }

    void show();
};

#endif
