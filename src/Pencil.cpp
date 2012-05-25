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
 *         Author:  yveschen
 *        Company:  
 *
 * =====================================================================================
 */

#include "Pencil.h"

// 对多边形进行三角化
void Pencil::triangulate() {

    vector<Element>::iterator iter = vertices.begin() + 1;
    vector<Element>::iterator nextiter = iter + 1;
    vector<Element>::iterator nniter = nextiter + 1;
    for (; nniter != vertices.end(); ++nextiter, ++nniter) 
        rasterize(*iter, *nextiter, *nniter);

}

// 对三角形进行光栅化
void Pencil::rasterize(Element v1, Element v2, Element v3) {

    float x_min, x_max, y_min, y_max;
    float e_0, e_1, e_2;
    float a_0, a_1, a_2, b_0, b_1, b_2, c_0, c_1, c_2;

    cout << v1.x << "  " << v1.y << "  "
         << v2.x << "  " << v2.y << "  "
         << v3.x << "  " << v3.y << endl;
    // 找出最小矩形
    x_min = MINNUM(v1.x, v2.x, v3.x);
    x_max = MAXNUM(v1.x, v2.x, v3.x);
    y_min = MINNUM(v1.y, v2.y, v3.y);
    y_max = MAXNUM(v1.y, v2.y, v3.y);

    cout << x_min << "  " << x_max << "  "
        << y_min << "  " << y_max << endl;
    a_0 = v2.y - v1.y;
    a_1 = v1.x - v2.x;
    a_2 = v2.x * v1.y - v1.x * v2.y;

    b_0 = v3.y - v2.y;
    b_1 = v2.x - v3.x;
    b_2 = v3.x * v2.y - v2.x * v3.y;
    
    c_0 = v1.y - v3.y;
    c_1 = v3.x - v1.x;
    c_2 = v1.x * v3.y - v3.x * v1.y;
    static int i = 0;
    for (float y = y_min; y <= y_max; ++y)
        for (float x = x_min; x <= x_max; ++x) {
            e_0 = a_0 * x + a_1 * y + a_2;          
            e_1 = b_0 * x + b_1 * y + b_2;
            e_2 = c_0 * x + c_1 * y + c_2;
            cout << "--" << e_0 << " " << e_1 <<" " << e_2 << endl; 
            if (e_0 >= 0 && e_1 >= 0 && e_2 >= 0) {
         
                Element temv(x, y, 0, 0);
                points.push_back(temv);
                ++i;
         
            }
        }
    cout << i << endl;
}


int cmp(const Element v1, const Element v2) {

    if (v1.x < v2.x)
        return 1;
    else if (v1.x == v2.x)
        return (v1.y <= v2.y ? 1: 0);
    else 
        return 0;

}

bool isCmp(Element v1, Element v2) {

    return ((v1.x == v2.x) && (v1.y == v2.y));

}


void Pencil::calAllpoints() {

    triangulate();

    // 去除重复点 
    vector<Element>::iterator iter;
    sort(points.begin(), points.end(), cmp);
    iter = unique(points.begin(), points.end(), isCmp);
    if (iter != points.end())
        points.erase(iter, points.end());

    for (int i = 0; i < points.size(); ++i)
        cout << points[i].x << "  " << points[i].y << "  " 
             << points[i].c_i << "  " << points[i].p_i << endl;
}


void Pencil::calCoefficient() {

    float* percentage = new float[num_vertices];
    float sum;
    float distance;
    
    for (int i = 0; i < num_points; ++i) {
        
        sum = 0;
        for (int j = 0; j < num_vertices; ++j) {
            distance = pow(points[i].x - vertices[j].x, 2) +
                          (points[i].y - vertices[j].y, 2);
            if (distance == 0) {

                points[i].c_i = vertices[j].c_i;
                break;
            }
                
            *(percentage + j) = 1 / sqrt(distance);
            sum += *(percentage + j);
        }
       
        for (int j = 0; j < num_vertices; ++j) {
            
            if (distance == 0)
                break;
      
            points[i].c_i += vertices[j].c_i * percentage[j] / sum;
        }
    }
}


void Pencil::calPressures() {
    
    for (int i = 0; i < num_points; ++i) {

        if (points[i].x == vertices[0].x && points[i].y == vertices[0].y)
            continue;
        else  // 中心点压力乘以压力系数
            points[i].p_i = points[i].c_i * vertices[0].p_i;
    }
    
}


void Pencil::calAvgPressures() {

    float sum_pi = 0;

    for (int i = 0; i < num_points; ++i)
        sum_pi += points[i].p_i;

    avg_pressure = sum_pi / num_points;
}


Pencil::Pencil() {

/* =======================test============================ */    
    GRAPHITE_PERCENT = 0.41;
    CLAY_PERCENT = 0.53;
    WAX_PERCENT = 0.05;
    //中心点有压力 
    Element v0(5, 5, 0.1, 1);
    Element v1(0, 5, 0.1, 0);
    Element v2(5, 10, 0.1, 0);
    Element v3(10, 5, 0.1, 0);
    Element v4(5, 0, 0.1, 0);
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
/* ======================================================= */

    num_vertices = vertices.size();

    calAllpoints();
    num_points = points.size();

    calCoefficient();

    calPressures();
    calAvgPressures();

}
