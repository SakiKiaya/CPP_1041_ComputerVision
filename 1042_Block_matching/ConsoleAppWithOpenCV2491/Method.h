#pragma once 
using namespace std;
using namespace cv;

class Method
{
public:
	Method();
	~Method();
	void doSomethingAndShow(Mat &input, int stage);
	struct movVector;
	struct searchBlocks;
	struct UCBDS_search_point;
	enum UCBDS_stage{
		_first = 0,
			_up,
		_u_left, _u_right,
	_left, _final, _right,
		_d_left, _d_right,
			_down,_blank
	};

private:
	//-- Function
	void initial();
	vector<searchBlocks> do_UCBDS(Mat &Origin, Mat &Search_Kernel, vector<cv::Point> vec_point, float max_match, UCBDS_stage stage = _first);
	vector<searchBlocks> do_Three_Step_Search(Mat &Origin, Mat &Search_Kernel, vector<cv::Point> vec_point, int stage,float max_match = 0);
	double MSE(Mat& A, Mat& B);
	double MAE(Mat& A, Mat& B);
	void drawArrow(Mat &image, Point p, Point q, Scalar color, int arrowMagnitude = 9, int thickness = 1, int line_type = 8, int shift = 0);
	void draw_arrow_with_match_mat(Mat& draw_at, Rect& start, Rect& end, Scalar color);
	double get_length_with_two_point(Point x, Point y);
	void release_vector();
	
	//-- Variable
	vector<movVector> blocks;
	vector<movVector> blocks_match;
	vector<UCBDS_search_point> UCBDS_search_point_first, 
		UCBDS_search_point_up, UCBDS_search_point_down, 
		UCBDS_search_point_left, UCBDS_search_point_right, 
		UCBDS_search_point_u_right, UCBDS_search_point_u_left, 
		UCBDS_search_point_d_right, UCBDS_search_point_d_left, 
		UCBDS_search_point_final;

	Point *TSSearch_first, *UCBDSearch_first, *UCBDSearch_relative;
	Mat src, pre_src;
	Mat temp_bgr;
	int src_height,
		src_width,
		block_height,
		block_width,
		search_height,
		search_width,
		_BLOCK_WIDTH;
};

