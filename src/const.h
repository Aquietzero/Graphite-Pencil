
#ifndef GRAPHITE_PENCIL_CONST
#define GRAPHITE_PENCIL_CONST

#include <GL/glut.h>
#include <set>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

#include "Element.h"
#include "Pencil.h"
#include "Grain.h"
#include "Paper.h"
#include "Interaction.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

// 定义出两个数中的最大值与最小值
#define MAX2(a, b) (a > b ? a : b)
#define MIN2(a, b) (a < b ? a : b)
// 定义出三个数中的最大值与最小值
#define MAX3(a, b, c) (a > b ? MAX2(a, c) : MAX2(b, c))
#define MIN3(a, b, c) (a < b ? MIN2(a, c) : MIN2(b, c))
// 定义出四个数中的最大值与最小值
#define MAX4(a, b, c, d) (a > b ? MAX3(a, c, d) : MAX3(b, c, d))
#define MIN4(a, b, c, d) (a < b ? MIN3(a, c, d) : MIN3(b, c, d))

// 浮点数比较时当两个数字的差值不超过DIFF就认为相等
#define DIFF 0.000001

#define GRAIN_HK_MAX 100

#endif
