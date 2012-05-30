#include "const.h"

Paper::Paper() {

    width  = height = f_v = M = 0;
    grains = NULL;

}
void Paper::init(int w, int h, float fv, float pw, float pm) {
    
    width  = w;
    height = h;
    f_v    = fv;
    W      = pw;
    M      = pm;
    grains = new Grain* [w];
    for (int i = 0; i < w; ++i)
        grains[i] = new Grain[h];

    initAllGrains();

}

void Paper::initAllGrains() {

    for (int x = 1; x < width - 1; ++x)
        for (int y = 1; y < height - 1; ++y)
            grains[x][y].init(&grains[x+1][y], &grains[x][y+1], &grains[x+1][y+1],
                              &grains[x-1][y], &grains[x][y-1], &grains[x-1][y-1]);

    srand(time(NULL));
    for (int x = 1; x < width - 1; ++x)
        for (int y = 1; y < height - 1; ++y)
            grains[x][y].updateH(rand() / float(RAND_MAX));

}

Grain& Paper::grain(int x, int y) {

    int posX = x, posY = y;
    if (x < 1)
        posX = 1;
    else if (x > width - 2) 
        posX = width - 2;
    if (y < 1) 
        posY = 1;
    else if (y > height - 2) 
        posY = height - 2;

    return grains[posX][posY];

}

void Paper::show() {

    for(int i=0; i < width; ++i) 
        for (int j = 0; j < height; ++j){
            float gray = 1- log(grains[i][j].getT());
            glColor3f(gray, gray, gray);
            glBegin(GL_POINT);
                glVertex2i(i, j);
            glEnd();
    }
    
}

