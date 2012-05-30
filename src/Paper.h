
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
    float W;                // 纸张重量，值域范围[0, 1]
    float M;                // 常量，值域范围[0.97, 0.99]
    
    Grain& grain(int x, int y);                               // 获取突起
    void initAllGrains();

public:
    Paper();   
    void init(int w, int h, float fv, float pw, float pm);        // 根据输入参数初始化纸张及各个高度
    void update(float newH, int x, int y);                        // 更具交互结果更新相应突起

    float  getW() { return W; }
    float  getM() { return M; }
    float  getH(int x, int y)  { return grain(x, y).getH(); }
    float  getH_max(int x, int y)  { return grain(x, y).getH_max(); }
    float  getH_min(int x, int y)  { return grain(x, y).getH_min(); }
    float  getHp_max(int x, int y) { return grain(x, y).getHp_max(); }
    float  getHp_min(int x, int y) { return grain(x, y).getHp_min(); }

    float  getD_k(int x, int y)    { return grain(x, y).getD_k(); }    
    float  getT_v(int x, int y)    { return grain(x, y).getT_v(); }    
    float  getL_k(int x, int y)    { return grain(x, y).getL_k(); } 
    Grain& getLeft(int x, int y)        { return Grain(x, y).getLeft(); }
    Grain& getTop(int x, int y)         { return Grain(x, y).getTop(); }
    Grain& getLeftTop(int x, int y)     { return Grain(x, y).getLeftTop(); }
    Grain& getRight(int x, int y)       { return Grain(x, y).getRight(); }
    Grain& getBottom(int x, int y)      { return Grain(x, y).getBottom(); }
    Grain& getRightBottom(int x, int y) { return Grain(x, y).getRightBottom(); }
};

#endif
