/*
 * =====================================================================================
 *
 *       Filename:  const.h
 *
 *    Description:  const.h defines some common constants.
 *
 *        Version:  1.0
 *        Created:  05/15/2012 10:11:46 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zero, yveschen
 *        Company:  NullSpace
 *
 * =====================================================================================
 */

#ifndef GRAPHITE_PENCIL_CONST
#define GRAPHITE_PENCIL_CONST

#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

// ====================================================================================
// 定义出三个数中的最大值
#define MAXNUM(a, b, c) (a > b ? (a > c ? a : c) : (b > c) ? b : c)
// 定义出三个数中的最小值
#define MINNUM(a, b, c) (a < b ? (a < c ? a : c) : (b < c) ? b : c)
// ====================================================================================

#endif
