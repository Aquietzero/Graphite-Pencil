#include "const.h"
#include <iomanip>

Paper::Paper() {

    width  = height = f_v = M = 0;
    grains = NULL;
    g = NULL;

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

    srand(time(NULL));
    for (int x = 1; x < width - 1; ++x)
        for (int y = 1; y < height - 1; ++y) {
            grains[x][y].updateH(rand() % 1001 / 1000.0);
            grains[x][y].init(&grains[x-1][y], &grains[x][y-1], &grains[x-1][y-1],
                              &grains[x+1][y], &grains[x][y+1], &grains[x+1][y+1]);
        }

}

void Paper::setPosition(int x, int y) {

    int posX = x, posY = y;
    if (x < 2)
        posX = 2;
    else if (x > width - 2) 
        posX = width - 3;
    if (y < 2) 
        posY = 2;
    else if (y > height - 2) 
        posY = height - 3;
    g = &grains[posX][posY];

}

void Paper::show(float g_p) {
//void Paper::show() {
 /* 
    for (int x = 2; x < width - 2; ++x)
        for (int y = 2; y < height - 2; ++y) {
            cout << "(" << x << "," << y << ")->";
            setPosition(x, y);
            cout << setw(9) << g->getH() << ","
                 << setw(9) << g->getH_max() << ","
                 << setw(9) << g->getH_min() << ","
                 << setw(9) << g->getH_sum() << "#"
                 << setw(9) << g->getHp_max() << ","
                 << setw(9) << g->getHp_min() << ","
                 << setw(9) << g->getHp_sum() << "#"
                 << setw(9) << g->getD_k(g->getH()) << ","
                 << setw(9) << g->getT_v(f_v) << ","
                 << setw(9) << g->getB_k(M, p, f_v) << ","
                 << setw(9) << g->getT_k() << endl;
        }      
*/
  
    for(int i=0; i < width; ++i) 
        for (int j = 0; j < height; ++j){
            float grey = 1 - grains[i][j].getT_k() * g_p / 1000;
            glColor3f(grey, grey, grey);
            glBegin(GL_POINTS);
                glVertex2i(i, j);
            glEnd();
        }

}

