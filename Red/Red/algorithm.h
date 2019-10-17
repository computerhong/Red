/**
 *
 * @file  algorithm.h
 *
 * @brief  Any algorithmic declarations
 *
 * @version  1.0
 *
 * @date  2019/09/25 10:32:55
 *
 * @author  Red, 735467224@qq.com
 *
 */

#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <vector>
#include <opencv2\opencv.hpp>
#include "Hungary.h"

using namespace std;
using namespace cv;

namespace red {

static class algorithm
{
public :
    /**
    * @brief run any examples for these algorithms
    */
    static void Examples();

    /**
    * @brief calculate the area of polygon with vertex coordinates
    * @refer https://blog.csdn.net/qq_38862691/article/details/87886871
    * @param points: input vertex coordinates
    * @return float: polygon area
    */
    static double getPolygonArea(vector<Point> const& points);

    /**
    * @brief solve the minimum weighted bipartite matching problem by using Hungary Algorithm
    * @refer https://wenku.baidu.com/view/20428d2cba0d4a7303763a8c.html
    * @param cost: matching cost matrix
    * @return Mat1i: matching indices
    */
    static Mat1i getCostMatchings(Mat1f const& cost);
};
}
#endif //_ALGORITHM_H_
