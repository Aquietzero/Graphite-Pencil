/*
 * =====================================================================================
 *
 *       Filename:  Pencil.cpp
 *
 *    Description:  Pencil.cpp implement Pencil.h
 *
 *        Version:  1.0
 *        Created:  2012年05月19日 21时43分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xxspc 
 *        Company:  XXSpace && NullSpace 
 *
 * =====================================================================================
 */

#include "const.h"

Pencil::Pencil(float p, float d, float gp, float cp, float wp,
        Elem* first, Elem* last):
        pressure(p), degree(d), g_p(gp), c_p(cp), w_p(wp) {

    vertices = set<Elem>(first, last);
    points   = set<Elem>();

}

void Pencil::setPoints() {

    points.clear();
    set<Elem>::iterator it0 = vertices.begin();
    set<Elem>::iterator it1 = vertices.begin();
    set<Elem>::iterator it2 = ++it1;
    for (it1 = ++it1; it1 != vertices.end(); ++it1, ++it2)
        rasterize(*it0, *it1, *it2);

}

/*          /|1
 *         / |
 *        /  |
 *       / __|
 *     2/__|_|3   vs   1_____2_____3
 */
void Pencil::cInterpolation(const Elem& e1, Elem& e2, const Elem& e3) {

    float d13 = sqrt((e1.x - e3.x) * (e1.x - e3.x) + (e1.y - e3.y) * (e1.y - e3.y));
    float d12 = sqrt((e1.x - e2.x) * (e1.x - e2.x) + (e1.y - e2.y) * (e1.y - e2.y));
    e2.c = d12 / d13 * (e3.c - e1.c) + e1.c;
    e2.p = e2.c * pressure;

}


/*         1/\
 *         /  \
 *        / 0. \
 *       /      \
 *     2.————.———.3
 *           4  
 */
void Pencil::rasterize(const Elem& e1, const Elem& e2, const Elem& e3) {
    float x_min = MIN3(e1.x, e2.x, e3.x);
    float x_max = MAX3(e1.x, e2.x, e3.x);
    float y_min = MIN3(e1.y, e2.y, e3.y);
    float y_max = MAX3(e1.y, e2.y, e3.y);

    float e_1, e_2, e_3, k1, k2, x4, y4, d23, d24, d14, d10, c4, c0, p0;
    k2 = (e2.y - e3.y)
       / (fabs(e2.x - e3.x) <= DIFF ? (e2.x > e3.x ? DIFF : -DIFF) : (e2.x - e3.x));
    d23 = sqrt((e2.x - e3.x)*(e2.x - e3.x) + (e2.y - e3.y)*(e2.y - e3.y));

    for (float x0 = x_min; x0 <= x_max; x0 += 1) {
        for (float y0 = y_min; y0 <= y_max; y0 += 1) {

            e_1 = (e2.x - e1.x) * (y0 - e1.y) - (x0 - e1.x) * (e2.y - e1.y);
            e_2 = (e3.x - e2.x) * (y0 - e2.y) - (x0 - e2.x) * (e3.y - e2.y);
            e_3 = (e1.x - e3.x) * (y0 - e3.y) - (x0 - e3.x) * (e1.y - e3.y);

            if ((e_1 >= 0 && e_2 >= 0 && e_3 >= 0) ||
                (e_1 <= 0 && e_2 <= 0 && e_3 <= 0)) {

                k1 = (y0 - e1.y)
                   / (fabs(x0 - e1.x) <= DIFF ? (x0 > e1.x ? DIFF : -DIFF) : (x0 - e1.x));

                x4 = (k1 * e1.x - e1.y - k2 * e2.x + e2.y)
                   / (fabs(k1 - k2) <= DIFF ? (k1 > k2 ? DIFF : -DIFF) : (k1 - k2 ));
                y4 = k1 * (x4 - e1.x) + e1.y;

                d24 = sqrt((e2.x - x4)*(e2.x - x4) + (e2.y - y4)*(e2.y - y4));
                d14 = sqrt((e1.x - x4)*(e1.x - x4) + (e1.y - y4)*(e1.y - y4));
                d10 = sqrt((e1.x - x0)*(e1.x - x0) + (e1.y - y0)*(e1.y - y0));

                c4  = (e3.c - e2.c) * d24 / d23 + e2.c;
                c0  = (c4   - e1.c) * d10 / d14 + e1.c;
                p0  = c0 * pressure;

                points.insert(Elem(x0 , y0, c0, p0));
            }
        }
    }
}

float Pencil::getAvgPressure() {

    float p_sum = 0;
    set<Elem>::iterator it = points.begin();
    for (; it != points.end(); ++it)
        p_sum += it->p;

    return p_sum / points.size();

}

float Pencil::BVAdjuster(float bv)  {

    return bv;

}

void Pencil::update(float bv) {

    float c_bv = BVAdjuster(bv);

    set<Elem> newVertices;
    set<Elem>::iterator it = vertices.begin();
    for (; it != vertices.end(); ++it)
        newVertices.insert(Elem(it->x * (1 + c_bv),
                                it->y * (1 + c_bv),
                                it->c * (1 - c_bv)));

    vertices = newVertices;
    setPoints();
    pressure *= (1 - bv / 5);

}

/* 3__4__0
 * |  | /|
 *2|__|/_|5
 * | /|it|
 * |/_|__|
 * 1  7  6
 */

void Pencil::update(set<Elem>::iterator it, float bv) {
 
    float c_bv = BVAdjuster(bv);
    Elem e[8];
    e[0] = Elem(it->x * (1 - c_bv), it->y * (1 - c_bv));
    e[1] = Elem(it->x * (1 + c_bv), it->y * (1 + c_bv));
    cInterpolation(e[0], e[1], *it);
    e[2] = Elem(it->x * (1 + c_bv), it->y);
    e[3] = Elem(it->x * (1 + c_bv), it->y * (1 - c_bv), it->c, it->p);
    cInterpolation(e[1], e[2], e[3]);
    e[4] = Elem(it->x, it->y * (1 + c_bv));
    cInterpolation(e[0], e[4], e[3]);
    e[5] = Elem(it->x * (1 - c_bv), it->y, e[4].c, e[4].p);
    e[6] = Elem(it->x * (1 - c_bv), it->y * (1 + c_bv), e[3].c, e[3].p);
    e[7] = Elem(it->x, it->y * (1 + c_bv), e[2].c, e[2].p);

    for (int i = 1; i < 7; ++i)
        points.insert(e[i]);

}






