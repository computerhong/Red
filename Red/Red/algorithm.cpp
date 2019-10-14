/**
 *
 * @file  algorithm.cpp
 *
 * @brief  Any algorithmic implementations
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
* @brief run any examples for these algorithms
*/
void red::algorithm::Examples()
{
	////////////////////////////////////////////////////////////////////////////////
	/********************************* getPolygonArea *****************************/
	vector<Point> points;
	points.push_back(Point(0,0));
	points.push_back(Point(0,3));
	points.push_back(Point(4,0));

	double area = red::algorithm::getPolygonArea(points);
	cout << "Exp.1 Polygon Area = " << area << ", expect(6)." << endl;
	////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	/************************************* Hungary ********************************/
	Mat1f exp_cost = red::Hungary::getExpInput();

	Mat1i indices = red::algorithm::getCostMatchings(exp_cost);
	cout << "Exp.2 Hungary Result is " << indices << ", expect(1,2,4,3,0)." << endl;
	////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	/*********************************** (next Exp.) ******************************/
	/***																		***/
	////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	/************************************** Cacel *********************************/
	cout << endl << "Press enter to cancel." << endl;
	getchar();
	////////////////////////////////////////////////////////////////////////////////
}

/**
* @brief calculate the Polygon Area with vertex coordinates
* @refer https://blog.csdn.net/qq_38862691/article/details/87886871
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

/**
* @brief solve the minimum weighted bipartite matching problem by using Hungary Algorithm
* @refer https://wenku.baidu.com/view/20428d2cba0d4a7303763a8c.html
* @param cost: matching cost matrix
* @return Mat1i: matching indices
*/
Mat1i red::algorithm::getCostMatchings(Mat1f const& cost)
{
	Hungary hgy(cost);
	hgy.Invoke();

	Mat1i indices = hgy.getIndices();
	return indices;
}

/**
* @brief __init__
* @param cost: input cost matrix
*/
red::Hungary::Hungary(Mat1f const& cost)
{
	this->costM = cost.clone();
	this->indices.clear();
}

/**
* @brief run the matchings for input cost matrix
*/
void red::Hungary::Invoke()
{
	Mat1f costN;
	normRowsCols(costM, costN);

	ezres ez;
	while (true)
	{
		szres sz;
		getSingleZeros(costN, sz);

		mkres mk;
		markRowsCols(sz, mk);

		ercas er = { costN, sz.rowsum, mk };
		if(setEndRowZeros(er, ez)) {
			break;
		}

		costN = ez.mat.clone();
	}

	indices.clear();
	zerosAlloc(ez.erzeros, indices, 0);
}

/**
* @brief get the result of matchings.
* @return Mat1i: matching indices
*/
Mat1i red::Hungary::getIndices()
{
	int sizeid = indices.size();
	int* indices1i = new int[sizeid];
	memcpy(indices1i, indices.data(), sizeid * sizeof(int));
	return Mat1i(1, sizeid, indices1i);
}

/**
* @brief get an example of input cost matrix
* @return Mat1f: cost matrix
*/
Mat1f red::Hungary::getExpInput()
{
	const int w = 5;
	const int h = 5;
	const int size = w * h;

	static float exp_arr[size] = 
						  { 12,  7,  9,  7,  9, 
							 8,  9,  6,  6,  6,
							 7, 17, 12, 14,  9,
							15, 14,  6,  6, 10,
							 4, 10,  7, 10,  9 };
	
	Mat1f exp_mat = Mat(h, w, CV_32FC1, exp_arr);
	return exp_mat;
}

/**
* @brief cost matrix minimum normalization
* @param in: input cost matrix
* @param out: normalized cost matrix
*/
void red::Hungary::normRowsCols(Mat1f const& in, Mat1f & out)
{
	out = in.clone();
    int w = out.cols;
    int h = out.rows;

    for (int i = 0; i < h; i++) {
        float imin = 99999;
        for (int j = 0; j < w; j++) {
            float value = out.at<float>(i, j);
            imin = min(imin, value);
        }
        for (int j = 0; j < w; j++) {
            out.at<float>(i, j) -= imin;
        }
    }

    for (int j = 0; j < w; j++) {
        float jmin = 99999;
        for (int i = 0; i < h; i++) {
            float value = out.at<float>(i, j);
            jmin = min(jmin, value);
        }
        for (int i = 0; i < h; i++) {
            out.at<float>(i, j) -= jmin;
        }
    }
}

/**
* @brief try marking zeros with the least lines
* @param in: input single zeros matrix
* @param out: marked zeros matrix
*/
void red::Hungary::markRowsCols(szres const& in, mkres & out)
{
    int h = in.rowsum.size();
    int w = in.colsum.size();

    bool marking = false;
    std::vector<bool> rowmark(h, false);
    std::vector<bool> colmark(w, false);
    for (int i = 0; i < h; i++) {
        if (in.rowsum[i].empty()) {
            rowmark[i] = true;
            marking = true;
        }
    }

    while (marking) {
        marking = false;
        for (int i = 0; i < h; i++) {
            if (rowmark[i]) {
                std::vector<int> ors = in.orowsum[i];
				for (size_t j = 0; j < ors.size(); j++) {
                    int x = ors[j];
                    if (!colmark[x]) {
                        colmark[x] = true;
                        marking = true;
                    }
                }
            }
        }

        for (int j = 0; j < w; j++) {
            if (colmark[j]) {
                std::vector<int> cs = in.colsum[j];
                for (size_t i = 0; i < cs.size(); i++) {
                    int y = cs[i];
                    if (!rowmark[y]) {
                        rowmark[y] = true;
                        marking = true;
                    }
                }
            }
        }
    }
	rowmark.swap(out.rowmark);
	colmark.swap(out.colmark);
}

/**
* @brief try matching to get single zeros
* @param in: input normalized cost matrix
* @param out: single zeros matrix
*/
void red::Hungary::getSingleZeros(Mat1f const& in, szres & out)
{
    int w = in.cols;
    int h = in.rows;

    vector2i rowsum(h);
    vector2i colsum(w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            float value = in.at<float>(i, j);
            if (value < 1e-9) {
                rowsum[i].push_back(j);
                colsum[j].push_back(i);
            }
        }
    }

	vector2i orowsum(rowsum);
    bool singlezero = true;
    while (singlezero) {
        singlezero = false;
        for (size_t i = 0; i < rowsum.size(); i++) {
            std::vector<int> rcs = rowsum[i];
            if (rcs.size() == 1) {
                int x = rcs[0];
                singlezero = (colsum[x].size() != 1);

                for (size_t j = 0; j < colsum[x].size(); j++) {
                    int y = colsum[x][j];
                    if (y != i) {
                        rowsum[y].erase(std::find(rowsum[y].begin(), rowsum[y].end(), x));
                    }
                }

                std::vector<int> newcolsum;
                newcolsum.push_back(i);
                colsum[x] = newcolsum;
            }
        }

        for (size_t j = 0; j < colsum.size(); j++) {
            std::vector<int> rcs = colsum[j];
            if (rcs.size() == 1) {
                int y = rcs[0];
                singlezero = (rowsum[y].size() != 1);

                for (size_t i = 0; i < rowsum[y].size(); i++) {
                    int x = rowsum[y][i];
                    if (x != j) {
                        colsum[x].erase(std::find(colsum[x].begin(), colsum[x].end(), y));
                    }
                }

                std::vector<int> newrowsum;
                newrowsum.push_back(j);
                rowsum[y] = newrowsum;
            }
        }
    }

    rowsum.swap(out.rowsum);
    colsum.swap(out.colsum);
    orowsum.swap(out.orowsum);
}

/**
* @brief try marking other zeros to get the final matrix
* @param in: input marked zeros matrix
* @param out: marked zeros final matrix
*/
bool red::Hungary::setEndRowZeros(ercas const& in, ezres & out)
{
	int h = in.mk.rowmark.size();
	int w = in.mk.colmark.size();
    int line = 0;
    for (int i = 0; i < h; i++) {
        if (!in.mk.rowmark[i]) {
            line++;
        }

        if (in.mk.colmark[i]) {
            line++;
        }
    }

	out.mat = in.mat.clone();
    if (line < w) {
        float minval = 99999;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                bool iscorvered = (!in.mk.rowmark[i] || in.mk.colmark[j]);
                if (!iscorvered) {
                    float value = in.mat.at<float>(i, j);
                    minval = std::min(minval, value);
                }
            }
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (in.mk.rowmark[i]) {
                    out.mat.at<float>(i, j) -= minval;
                }

				if (in.mk.colmark[j]) {
                    out.mat.at<float>(i, j) += minval;
                }
            }
        }
    } else {
        for (int i = 0; i < h; i++) {
            std::vector<cv::Point> vps;
            std::vector<int> rs = in.rowsum[i];
            for (size_t j = 0; j < rs.size(); j++) {
                int x = rs[j];
                int y = i;
                cv::Point2d zero(x, y);
                vps.push_back(zero);
            }
            out.erzeros.push_back(vps);
        }
        return true;
    }
    return false;
}

/**
* @brief get the result of matchings from the marked zeros final matrix
* @param in: input marked zeros final matrix
* @param out: result of matchings
* @param iter: obj for iteration
*/
void red::Hungary::zerosAlloc(vector2p const& in, vector1u & out, int iter)
{
    if ((size_t)iter >= in.size()) {
        return;
    }

    std::vector<cv::Point> zeros = in[iter];
    for (size_t j = 0; j < zeros.size(); j++) {
        cv::Point zero = zeros[j];
        int x = zero.x;

        int size = out.size();
        bool isalloc = false;
        for (int k = 0; k < size; k++) {
            if (x == out[k]) {
                isalloc = true;
                break;
            }
        }

        if (!isalloc) {
            out.push_back(x);
            zerosAlloc(in, out, iter+1);
        }
    }

    if (out.size() > 0 && out.size() < in.size()) {
        out.pop_back();
    }
}