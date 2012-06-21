
#include "const.h"

Pencil::Pencil() {

    pressure = degree = g_p = c_p = w_p = 0;
    vertices = vector<Elem>();
    points   = set<Elem>();
}

void Pencil::init(float p, float d, float gp, float cp, float wp,
              Elem* first, Elem* last) {

    pressure = p;
    degree   = d;
    g_p      = gp;
    c_p      = cp;
    w_p      = wp;

    vertices = vector<Elem>(first, last);
    setPoints();
    
}

void Pencil::setPoints() {

    points.clear();
    vector<Elem>::iterator it0 = vertices.begin();
    vector<Elem>::iterator it1 = it0;
    vector<Elem>::iterator it2 = ++it1;
    for (it2 = ++it2; it2 != vertices.end(); ++it1, ++it2) 
        setPointsByRasterize(*it0, *it1, *it2);

}

/* 
 *    1_____2_____3
 */
bool Pencil::setElemByLinearInterpolation(const Elem& e1, Elem& e2, const Elem& e3) { float d13 = sqrt((e1.x - e3.x) * (e1.x - e3.x) + (e1.y - e3.y) * (e1.y - e3.y)); float d12 = sqrt((e1.x - e2.x) * (e1.x - e2.x) + (e1.y - e2.y) * (e1.y - e2.y));
    if (d13 < DIFF)
        return false;
    e2.c = d12 / d13 * (e3.c - e1.c) + e1.c;
    e2.p = e2.c * pressure;
    return true;

}


/*         1/\
 *         /  \
 *        / 0. \
 *       /      \
 *     2.————.———.3
 *           4  
 */
bool Pencil::setLineEquation(const Elem& e1, const Elem& e2, float& a, float& b, float& c) {

    if (fabs(e1.x - e2.x) < DIFF) {
        if (fabs(e1.y - e2.y) < DIFF)
            return false;
        a = 1;
        b = 0;
        c = -e1.x;
    }
    else {
        float k  = (e1.y - e2.y) / (e1.x - e2.x);
        a = k;
        b = -1;
        c = e1.y - k * e1.x;
    }
    return true;

}
bool Pencil::setIntersectionElem(const Elem& e0, const Elem& e1, const Elem& e2, const Elem& e3, Elem& e4) {

    //  y = k(x - x0) + y0   ax + by + c = 0;

    float a1, b1, c1, a2, b2, c2;
    if (!setLineEquation(e0, e1, a1, b1, c1))
        return false;
    if (!setLineEquation(e2, e3, a2, b2, c2))
        return false;
    float k = a1 * b2 - a2 * b1;
    if (fabs(k) < DIFF)
        return false;
    
    e4.x = (c2 * b1 - c1 * b2) / k;
    e4.y = (c1 * a2 - c2 * a1) / k;
    return true;

}


bool Pencil::setElemByTriangleInterpolation(const Elem& e1, const Elem& e2, const Elem& e3, Elem& e0) {


    Elem e4;
    return setIntersectionElem(e0, e1, e2, e3, e4) 
        && setElemByLinearInterpolation(e2, e4, e3)
        && setElemByLinearInterpolation(e1, e0, e4);

}



void Pencil::setBorder(float& left, float& right, float& up, float& down, 
                       const Elem& e1, const Elem& e2, const Elem& e3) {

    left  = MIN3(e1.x, e2.x, e3.x);
    right = MAX3(e1.x, e2.x, e3.x);
    up    = MAX3(e1.y, e2.y, e3.y);
    down  = MIN3(e1.y, e2.y, e3.y);

}


bool Pencil::isInner(const Elem& e1, const Elem& e2, const Elem& e3, const Elem& e0) {

    float e_1 = (e2.x - e1.x) * (e0.y - e1.y) - (e0.x - e1.x) * (e2.y - e1.y);
    float e_2 = (e3.x - e2.x) * (e0.y - e2.y) - (e0.x - e2.x) * (e3.y - e2.y);
    float e_3 = (e1.x - e3.x) * (e0.y - e3.y) - (e0.x - e3.x) * (e1.y - e3.y);

    if ((e_1 >= 0 && e_2 >= 0 && e_3 >= 0) || (e_1 <= 0 && e_2 <= 0 && e_3 <= 0)) 
        return true;
    return false;

}

void Pencil::setPointsByRasterize(const Elem& e1, const Elem& e2, const Elem& e3) {

    float left, right, up, down;
    setBorder(left, right, up, down, e1, e2, e3);
    for (float x0 = left; x0 <= right; x0 += 1) 
        for (float y0 = down; y0 <= up; y0 += 1) {
            Elem e0(x0, y0);
            if (setElemByTriangleInterpolation(e1, e2, e3, e0) && isInner(e1, e2, e3, e0)) 
                points.insert(e0);
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

    vector<Elem> newVertices;
    vector<Elem>::iterator it = vertices.begin();
    for (; it != vertices.end(); ++it)
        newVertices.push_back(Elem(it->x * (1 + c_bv),
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
    setElemByLinearInterpolation(e[0], e[1], *it);
    e[2] = Elem(it->x * (1 + c_bv), it->y);
    e[3] = Elem(it->x * (1 + c_bv), it->y * (1 - c_bv), it->c, it->p);
    setElemByLinearInterpolation(e[1], e[2], e[3]);
    e[4] = Elem(it->x, it->y * (1 + c_bv));
    setElemByLinearInterpolation(e[0], e[4], e[3]);
    e[5] = Elem(it->x * (1 - c_bv), it->y, e[4].c, e[4].p);
    e[6] = Elem(it->x * (1 - c_bv), it->y * (1 + c_bv), e[3].c, e[3].p);
    e[7] = Elem(it->x, it->y * (1 + c_bv), e[2].c, e[2].p);

    for (int i = 1; i < 7; ++i)
        points.insert(e[i]);

}

