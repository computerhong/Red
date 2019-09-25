/**
 *
 * @file  algorithm.cpp
 *
 * @brief  A few algorithmic implementations
 *
 * @version  1.0
 *
 * @date  2019/09/25 10:32:55
 *
 * @author  Red, 735467224@qq.com
 *
 */

#include "algorithm.h"

/**
* @brief run any examples for this algorithm
*/
void red::algorithm::Examples()
{
	/*** getPolygonArea ***/
	vector<Point> points;
	points.push_back(Point(0,0));
	points.push_back(Point(0,3));
	points.push_back(Point(4,0));

	double area = red::algorithm::getPolygonArea(points);
	cout << "Exp.1 Polygon Area = " << area << ", expect(6)." << endl;

	/*** (next Exp.) ***/

	/*** Cancel ***/
	cout << endl << "Press enter to cancel." << endl;
	getchar();
}

/**
* @brief calculate the Polygon Area with vertex coordinates
* @refer https://blog.csdn.net/qq_38862691/article/details/87886871
*
* @param points: input vertex coordinates
* @return float: polygon area
*/
double red::algorithm::getPolygonArea(vector<Point> const& points)
{
	const int sizep = points.size();
	if(sizep<3)	return 0.0;

	double area = points.back().x * points[0].y - points[0].x * points.back().y;
	for(int i=1,v=0;i<sizep;i++,v++) {
		area += (points[v].x * points[i].y);
		area -= (points[i].x * points[v].y);
	}

	return fabs(0.5 * area);
}