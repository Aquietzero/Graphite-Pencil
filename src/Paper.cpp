
#include "const.h"

Paper::Paper(int w, int h, float fv, float pw, float pm): f_v(fv), W(pw), M(pm) {
    
    grains = new Grain* [w];
    for (int i = 0; i < w; ++i)
        grains[i] = new Grain[h];

    width  = w;//实际的索引是［1，w-2］
    height = h;//实际的索引是［1，h-2］

    init();

}

void Paper::init() {
    // 初始化每个突起相关的三个副高度和三个主高度
    // 纸张实际操作大小为［1，width-2］［1, height-2］,边界不处理
    for (int x = 1; x < width - 1; ++x)
        for (int y = 1; y < height - 1; ++y) 
            grains[x][y].init(&grains[x+1][y], &grains[x][y+1], &grains[x+1][y+1],
                              &grains[x-1][y], &grains[x][y-1], &grains[x-1][y-1]);
        
}

Grain& Paper::grain(int x, int y) {

    int posX = x, posY = y;
    if (x < 1) 
        posX = 1;
    else if (x > width - 2) 
        posX = width - 1;
    if (y < 1) 
        posY = 1;
    else if (y > height - 2) 
        posY = height - 2;

    return grains[posX][posY];

}

void Paper::update(float newH, int x, int y) {

    grain(x, y).update(newH, f_v);

}

