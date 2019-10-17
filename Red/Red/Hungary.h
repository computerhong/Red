/**
 *
 * @file  Hungary.h
 *
 * @brief  Hungarian Optimal Matching Algorithm
 *
 * @version  1.0
 *
 * @date  2019/10/17 10:32:55
 *
 * @author  Red, 735467224@qq.com
 *
 */

#ifndef _HUNGARY_H_
#define _HUNGARY_H_

#include <vector>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

namespace red {

typedef vector<bool>	vector1b;
typedef vector<unsigned int>	vector1u;
typedef vector<vector<int>>	vector2i;
typedef vector<vector<Point>>	vector2p;

class Hungary
{
public:
    /**
    * @brief __init__
    * @param cost: input cost matrix
    */
    Hungary(Mat1f const& cost);
    ~Hungary() {};
    /**
    * @brief run the matchings for input cost matrix
    */
    void Invoke();
    /**
    * @brief get the result of matchings.
    * @return Mat1i: matching indices
    */
    Mat1i getIndices();
    /**
    * @brief get an example of input cost matrix
    * @return Mat1f: cost matrix
    */
    static Mat1f getExpInput();

protected:
    /**
    * @brief any structure declarations
    */
    typedef struct szres;
    typedef struct mkres;
    typedef struct ercas;
    typedef struct ezres;
    /**
    * @brief cost matrix minimum normalization
    * @param in: input cost matrix
    * @param out: normalized cost matrix
    */
    void normRowsCols(Mat1f const& in, Mat1f & out);
    /**
    * @brief try marking zeros with the least lines
    * @param in: input single zeros matrix
    * @param out: marked zeros matrix
    */
    void markRowsCols(szres const& in, mkres & out);
    /**
    * @brief try matching to get single zeros
    * @param in: input normalized cost matrix
    * @param out: single zeros matrix
    */
    void getSingleZeros(Mat1f const& in, szres & out);
    /**
    * @brief try marking other zeros to get the final matrix
    * @param in: input marked zeros matrix
    * @param out: marked zeros final matrix
    */
    bool setEndRowZeros(ercas const& in, ezres & out);
    /**
    * @brief get the result of matchings from the marked zeros final matrix
    * @param in: input marked zeros final matrix
    * @param out: result of matchings
    * @param iter: obj for iteration
    */
    void zerosAlloc(vector2p const& in, vector1u & out, int iter);
protected:
    Mat1f costM;		/*** cost matrix ***/
    vector1u indices;	/*** result of matchings ***/
protected:
    /**
    * @brief any structure definitions
    */
    typedef struct szres {
        vector2i rowsum;
        vector2i colsum;
        vector2i orowsum;
    } szres;
    typedef struct mkres {
        vector1b rowmark;
        vector1b colmark;
    } mkres;
    typedef struct ercas {
        Mat1f mat;
        vector2i rowsum;
        mkres mk;
    } ercas;
    typedef struct ezres {
        Mat1f mat;
        vector2p erzeros;
    } ezres;
};
}
#endif _HUNGARY_H_
