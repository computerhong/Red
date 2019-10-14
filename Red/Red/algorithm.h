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

using namespace std;
using namespace cv;

namespace red {

	class Hungary;

	typedef vector<bool>			vector1b;
	typedef vector<unsigned int>	vector1u;
	typedef vector<vector<int>>		vector2i;
	typedef vector<vector<Point>>	vector2p;

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

	/** 
	* @brief Hungarian Optimal Matching Algorithm
	*/
	class Hungary
	{
		public:
		/**
		* @brief __init__
		* @param cost: input cost matrix
		*/
		Hungary(Mat1f const& cost);
		~Hungary(){};
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
		typedef struct szres{
			vector2i rowsum;
			vector2i colsum;
			vector2i orowsum;
		} szres;
		typedef struct mkres{
			vector1b rowmark;
			vector1b colmark;
		} mkres;
		typedef struct ercas{
			Mat1f mat;
			vector2i rowsum;
			mkres mk;
		} ercas;
		typedef struct ezres{
			Mat1f mat;
			vector2p erzeros;
		} ezres;
	};
}
#endif //_ALGORITHM_H_