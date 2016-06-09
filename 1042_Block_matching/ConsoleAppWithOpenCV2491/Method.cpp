#include "stdafx.h"
#include "Method.h"



using namespace cv;
using namespace std;

struct Method::movVector{
public:
	movVector(cv::Rect input){ rect = input; };
	cv::Rect rect;
	float angle, length;
	bool movement;
};
struct Method::searchBlocks{
public:
	searchBlocks(cv::Rect input, double PSNR_in){
		rect = input;
		PSNR = PSNR_in;
	};
	cv::Rect rect;
	double PSNR;
	bool marked;
};
struct Method::UCBDS_search_point{
public:
	UCBDS_search_point(Point pos_in, Method::UCBDS_stage stage_in){
		pos = pos_in;
		stage = stage_in;
	};
	Point pos;
	Method::UCBDS_stage stage;
};

Method::Method()
{
	this->_BLOCK_WIDTH = 16;
	this->block_height = _BLOCK_WIDTH;
	this->block_width = _BLOCK_WIDTH;
	this->search_height = 30;
	this->search_width = 30;

	//-- Three Step Search
	this->TSSearch_first = new Point[9]{
		Point(3, 3), Point(7, 3), Point(11, 3),
			Point(3, 7), Point(7, 7), Point(11, 7),
			Point(3, 11), Point(7, 11), Point(11, 11) };

	//-- UCBD Search
	this->UCBDSearch_first = new Point[9]{
		Point(7, 5),
			Point(6, 6), Point(8, 6),
			Point(5, 7), Point(7, 7), Point(9, 7),
			Point(6, 8), Point(8, 8),
			Point(7, 9)
	};
	this->UCBDSearch_relative = new Point[9]{
		Point(0, -2),
			Point(-1, -1), Point(1, -1),
			Point(-2, 0), Point(0, 0), Point(2, 0),
			Point(-1, 1), Point(1, 1),
			Point(0, 2)
	};
#pragma region //--UCBDS_sturct
	UCBDS_search_point_first = /*new UCBDS_search_point[9]*/{
		UCBDS_search_point(Point(7, 5), _up),
		UCBDS_search_point(Point(6, 6), _u_left),
		UCBDS_search_point(Point(8, 6), _u_right),
		UCBDS_search_point(Point(5, 7), _left),
		UCBDS_search_point(Point(7, 7), _final),
		UCBDS_search_point(Point(9, 7), _right),
		UCBDS_search_point(Point(6, 8), _d_left),
		UCBDS_search_point(Point(8, 8), _d_right),
		UCBDS_search_point(Point(7, 9), _down)
	};

	UCBDS_search_point_up = /*new UCBDS_search_point[5]*/{
		UCBDS_search_point(Point(0, -2), _up),
		UCBDS_search_point(Point(-1, -1), _u_left),
		UCBDS_search_point(Point(1, -1), _u_right),
		UCBDS_search_point(Point(-2, 0), _left),
		UCBDS_search_point(Point(2, 0), _right)
	};
	UCBDS_search_point_down = /*new UCBDS_search_point[5]*/{
		UCBDS_search_point(Point(-2, 0), _left),
		UCBDS_search_point(Point(2, 0), _right),
		UCBDS_search_point(Point(-1, 1), _d_left),
		UCBDS_search_point(Point(1, 1), _d_right),
		UCBDS_search_point(Point(0, 2), _down)
	};
	UCBDS_search_point_left = /*new UCBDS_search_point[5]*/{
		UCBDS_search_point(Point(0, -2), _up),
		UCBDS_search_point(Point(-1, -1), _u_left),
		UCBDS_search_point(Point(-2, 0), _left),
		UCBDS_search_point(Point(-1, 1), _d_left),
		UCBDS_search_point(Point(0, 2), _down)
	};
	UCBDS_search_point_right = /*new UCBDS_search_point[5]*/{
		UCBDS_search_point(Point(0, -2), _up),
		UCBDS_search_point(Point(1, -1), _u_right),
		UCBDS_search_point(Point(2, -2), _right),
		UCBDS_search_point(Point(1, 1), _d_right),
		UCBDS_search_point(Point(0, 2), _down)
	};

	UCBDS_search_point_u_left = /*new UCBDS_search_point[3]*/{
		UCBDS_search_point(Point(0, -2), _up),
		UCBDS_search_point(Point(-1, -1), _u_left),
		UCBDS_search_point(Point(-2, 0), _left)
	};
	UCBDS_search_point_u_right = /*new UCBDS_search_point[3]*/{
		UCBDS_search_point(Point(0, -2), _up),
		UCBDS_search_point(Point(1, -1), _u_right),
		UCBDS_search_point(Point(2, -2), _right)
	};

	UCBDS_search_point_d_left = /*new UCBDS_search_point[3]*/{
		UCBDS_search_point(Point(-2, 0), _left),
		UCBDS_search_point(Point(-1, 1), _d_left),
		UCBDS_search_point(Point(0, 2), _down)
	};
	UCBDS_search_point_d_right = /*new UCBDS_search_point[3]*/{
		UCBDS_search_point(Point(2, -2), _right),
		UCBDS_search_point(Point(1, 1), _d_right),
		UCBDS_search_point(Point(0, 2), _down)
	};

	UCBDS_search_point_final = /*new UCBDS_search_point[4]*/{
		UCBDS_search_point(Point(0, -1), _final),
		UCBDS_search_point(Point(-1, 0), _final),
		UCBDS_search_point(Point(0, 1), _final),
		UCBDS_search_point(Point(0, 1), _final)
	};
#pragma endregion
}

Method::~Method()
{
}

void Method::initial(){
	int block_number, block_rows, block_cols, count;
	float temp;

	block_rows = src_height / _BLOCK_WIDTH;
	if (block_rows > src_height % _BLOCK_WIDTH)
		block_rows++;

	block_cols = src_width / _BLOCK_WIDTH;
	if (block_cols > src_width % _BLOCK_WIDTH)
		block_cols++;
	block_number = block_cols * block_rows;

	count = 0;
	for (int cols = 1; cols < block_cols - 2; cols++){
		for (int rows = 1; rows < block_rows - 2; rows++){
			this->blocks.push_back(movVector(Rect(rows * _BLOCK_WIDTH, cols * _BLOCK_WIDTH, _BLOCK_WIDTH, _BLOCK_WIDTH)));
			count++;
		}
	}

	//-- Draw the rect areas on screen
	for (count = 0; count < blocks.size(); count++){
		rectangle(src, this->blocks[count].rect, Scalar(255, 0, 0), 1, 8, 0);
	}
}

void Method::doSomethingAndShow(Mat &input, int stage){
	cvtColor(input, src, CV_BGR2GRAY);
	Mat res = src.clone(), src_BGR = input.clone();
	this->src_height = src.cols;
	this->src_width = src.rows;
	if (blocks.empty())
		this->initial();
	if (!pre_src.empty()){
		//-- Draw the initial blocks
		/*for (int count = 0; count < blocks.size(); count++){
			rectangle(src_BGR, this->blocks[count].rect, Scalar(255, 0, 0), 1, 8, 0);
			}*/
#pragma region --Match
		for (int i = 0; i < blocks.size(); i++){
			//-- Create search blocks, width and height plus 14
			Rect block_x_rect = blocks[i].rect;
			Mat block_x = pre_src(block_x_rect);
			Point start;
			Point end;

			start = block_x_rect.tl() - Point(7, 7);
			end = block_x_rect.br() + Point(7, 7);
			if (start.x < 0)
				start.x = 0;
			if (start.y < 0)
				start.y = 0;
			if (end.y > src.rows - 1)
				end.y = src.rows - 1;
			if (end.x > src.cols - 1)
				end.x = src.cols - 1;
			Rect Search_Kernel_rect(start, end);
			//-- Draw the Search Kernel with yellow
			//rectangle(src_BGR, Search_Kernel_rect.tl(), Search_Kernel_rect.br(), Scalar(0, 255, 255));
			Mat Search_Kernel = src(Search_Kernel_rect);

			vector<cv::Point> match_Pos_vector;
			match_Pos_vector.push_back(start);
			vector<searchBlocks> Matched_Blocks;
			switch (stage){
			case 1:
				//-- Use Three Step Search in search blocks and use PSNR to match blocks 
				Matched_Blocks = do_Three_Step_Search(block_x, Search_Kernel, match_Pos_vector, 1);
				//rectangle(src_BGR, Matched_Blocks[0].rect.tl(), Matched_Blocks[0].rect.br(), Scalar(0, 255, 0));
				break;
			case 2:
				//-- Use UCBDS in search blocks and use PSNR to match blocks
				Matched_Blocks = do_UCBDS(block_x, Search_Kernel, match_Pos_vector, Method::UCBDS_stage::_first);
				//rectangle(src_BGR, Matched_Blocks[0].rect.tl(), Matched_Blocks[0].rect.br(), Scalar(0, 255, 0));
				break;
			}
			draw_arrow_with_match_mat(src_BGR, block_x_rect, Matched_Blocks[0].rect, Scalar(255, 0, 255));
		}
#pragma endregion
	}

	pre_src.release();
	pre_src = res.clone();
	release_vector();

	resize(src_BGR, src_BGR, Size(640, 480));
	imshow("Result", src_BGR);
	bool debug = true;
}
// Do UCBDSearch and return a rect in vector
vector<Method::searchBlocks> Method::do_UCBDS(Mat &Origin, Mat &Search_Kernel, vector<cv::Point> vec_point, float max_match, Method::UCBDS_stage stage){
	vector<Method::searchBlocks> result;
	vector<UCBDS_search_point> now_search_point;
	Mat src = Origin.clone();
	Point Result_pos, now_pos;
	Point now_point;
	UCBDS_stage now_stage;

	bool is_edge = false, is_final = false, is_first = false;
	switch (stage){
#pragma region case_UCBD_inital
	case _first:
		is_first = true;
		now_search_point = UCBDS_search_point_first;
		cvtColor(Search_Kernel, temp_bgr, CV_GRAY2BGR);
		/*for (int i = 0; i < 9; i++){
			float match;
			//match = PSNR(Origin, Search_Kernel(Rect(TSSearch_first[i], TSSearch_first[i] + Point(16, 16))));
			match = MSE(Origin, Search_Kernel(Rect(UCBDSearch_first[i], UCBDSearch_first[i] + Point(16, 16))));
			if (max_match < match){
			max_match = match;
			now_stage = UCBDS_stage(i);
			}
			}
			Result_pos = UCBDSearch_first[now_stage];
			vec_point.push_back(Result_pos);
			cvtColor(Search_Kernel, temp_bgr, CV_GRAY2BGR);
			circle(temp_bgr, Result_pos, 0.5, Scalar(255, 0, 0), -1);
			vec_point.push_back(Result_pos);
			return do_UCBDS(Origin, Search_Kernel, vec_point, now_stage);*/
		break;
#pragma endregion
#pragma region case_UCBD_search_point_inital
	case _up:
		now_search_point = UCBDS_search_point_up;
		break;
	case _u_left:
		now_search_point = UCBDS_search_point_u_left;
		break;
	case _u_right:
		now_search_point = UCBDS_search_point_u_right;
		break;
	case _left:
		now_search_point = UCBDS_search_point_left;
		break;
	case _right:
		now_search_point = UCBDS_search_point_right;
		break;
	case _d_left:
		now_search_point = UCBDS_search_point_d_left;
		break;
	case _d_right:
		now_search_point = UCBDS_search_point_d_right;
		break;
	case _down:
		now_search_point = UCBDS_search_point_down;
		break;

#pragma region case_UCBD_final
	case _final:
		is_final = true;
		now_search_point = UCBDS_search_point_final;
		//result.push_back(searchBlocks(Rect(match_pos.x, match_pos.y, 16, 16), max_match));
		break;
#pragma endregion
#pragma endregion
	}

	if (is_first)
		now_point = Point(0, 0);
	else
		now_pos = vec_point[vec_point.size() - 1];
	now_stage = _blank;
	for (int i = 0; i < now_search_point.size(); i++){
		float match;
		now_point = now_pos + now_search_point[i].pos;
		bool debug = true;
		if (now_point.x > 14 || now_point.y > 14 || now_point.x < 0 || now_point.y < 0)
			is_edge = true;
		else{
			//match = MSE(Origin, Search_Kernel(Rect(now_point, now_point + Point(16, 16))));
			match = PSNR(Origin, Search_Kernel(Rect(now_point, now_point + Point(16, 16))));
			if (max_match < match){
				max_match = match;
				Result_pos = now_point;
				now_stage = now_search_point[i].stage;
			}
		}
	}
	if (now_stage == _blank){
		Result_pos = now_pos;
		now_stage = _final;
	}
	//cvtColor(Search_Kernel, temp_bgr, CV_GRAY2BGR);
	circle(temp_bgr, Result_pos, 0.5, Scalar(255, 0, 0), -1);
	vec_point.push_back(Result_pos);

	if (is_final){
		Point match_pos;
		match_pos += vec_point[0];
		match_pos += vec_point[vec_point.size() - 1];
		//cout << "res_point" << ":" << match_pos << endl;
		result.push_back(searchBlocks(Rect(match_pos.x, match_pos.y, 16, 16), max_match));
		return result;
	}
	else{
		if (!is_edge)
			return do_UCBDS(Origin, Search_Kernel, vec_point, max_match, now_stage);
		else
			return do_UCBDS(Origin, Search_Kernel, vec_point, max_match, _final);
	}
}
// Do TSSearch and return a rect in vector
vector<Method::searchBlocks> Method::do_Three_Step_Search(Mat &Origin, Mat &Search_Kernel, vector<cv::Point> vec_point, int stage, float max_match){
	vector<Method::searchBlocks> result;
	Mat src = Origin.clone();
	int position = 0;
	int next_stage;
	Point Result_pos(0, 0), match_pos(0, 0), now_pos = vec_point[vec_point.size() - 1];
	switch (stage){
	case 1:
		for (int i = 0; i < 9; i++){
			float match;
			match = PSNR(Origin, Search_Kernel(Rect(TSSearch_first[i], TSSearch_first[i] + Point(16, 16))));
			//match = MSE(Origin, Search_Kernel(Rect(TSSearch_first[i], TSSearch_first[i] + Point(16, 16))));
			//match = MAE(Origin, Search_Kernel(Rect(TSSearch_first[i], TSSearch_first[i] + Point(16, 16))));
			if (max_match < match){
				max_match = match;
				position = i;
			}
		}
		Result_pos = TSSearch_first[position];
		vec_point.push_back(Result_pos);
		Search_Kernel = Search_Kernel(
			Rect(Result_pos - Point(3, 3), Result_pos + Point(19, 19)));
		if (position == 4){
			next_stage = 4;
			return do_Three_Step_Search(Origin, Search_Kernel, vec_point, next_stage, max_match);
		}
		else{
			next_stage = 2;
			return do_Three_Step_Search(Origin, Search_Kernel, vec_point, next_stage, max_match);
		}
		break;
	case 2:
		for (int y = 1; y < 6; y += 2){
			for (int x = 1; x < 6; x += 2){
				if (x != 3 && y != 3){
					float match;
					match = PSNR(Origin, Search_Kernel(Rect(x, y, 16, 16)));
					//match = MSE(Origin, Search_Kernel(Rect(x, y, 16, 16)));
					//match = MAE(Origin, Search_Kernel(Rect(x, y, 16, 16)));
					if (max_match < match){
						max_match = match;
						Result_pos = Point(x, y);
					}
				}
				else{
					if (Result_pos == Point(0, 0)){
						Result_pos = Point(x, y);
					}
				}
			}
		}
		vec_point.push_back(Result_pos);
		Search_Kernel = Search_Kernel(Rect(Result_pos - Point(1, 1), Result_pos + Point(17, 17)));
		next_stage = 3;
		return do_Three_Step_Search(Origin, Search_Kernel, vec_point, next_stage, max_match);
		break;
	case 3:
		for (int y = 0; y < 3; y++){
			for (int x = 0; x < 3; x++){
				if (x != 1 && y != 1){
					float match;
					match = PSNR(Origin, Search_Kernel(Rect(x, y, 16, 16)));
					//match = MSE(Origin, Search_Kernel(Rect(x, y, 16, 16)));
					//match = MAE(Origin, Search_Kernel(Rect(x, y, 16, 16)));
					if (max_match < match){
						max_match = match;
						Result_pos = Point(x, y);
					}
				}
				else{
					if (Result_pos == Point(0, 0)){
						Result_pos = Point(x, y);
					}
				}
			}
		}
		vec_point.push_back(Result_pos);

		for (int i = 0; i < vec_point.size(); i++){
			match_pos += vec_point[i];
		}
		result.push_back(searchBlocks(Rect(match_pos.x, match_pos.y, 16, 16), max_match));
		return result;
		break;
	case 4:
		for (int i = 0; i < vec_point.size(); i++){
			match_pos += vec_point[i];
		}
		result.push_back(searchBlocks(Rect(match_pos.x, match_pos.y, 16, 16), max_match));
		return result;
		break;
	}
}

double Method::MSE(Mat& A, Mat& B){
	double sum = 0.0;
	for (int x = 0; x < A.rows; x++){
		for (int y = 0; y < A.cols; y++){
			double difference = A.at<unsigned char>(Point(x, y)) - B.at<unsigned char>(Point(x, y));
			sum = sum + difference*difference;
		}
	}
	double mse = sum / (A.rows*A.cols);
	return mse;
}

double Method::MAE(Mat& A, Mat& B){
	double sum = 0.0;
	for (int x = 0; x < A.rows; x++){
		for (int y = 0; y < A.cols; y++){
			double difference = A.at<unsigned char>(Point(x, y)) - B.at<unsigned char>(Point(x, y));
			sum = sum + sqrt(difference*difference);
		}
	}
	double mse = sum / (A.rows*A.cols);
	return mse;
}
// If arrow's length is zero than draw a blue point, if the arrow is from left to right then draw in yellow, if arrow is from right to left than draw in red
void Method::draw_arrow_with_match_mat(Mat& draw_at, Rect& start, Rect& end, Scalar color){
	Point Point_start, Point_end;
	double PI = 3.141592653;
	double length;
	if (start.tl() != end.tl()){
		Point_start = start.tl() + Point(7, 7);
		Point_end = end.tl() + Point(7, 7);
		length = get_length_with_two_point(Point_start, Point_end);
		if (length > 0){
			double angle = atan2((double)Point_start.y - Point_end.y, (double)Point_start.x - Point_end.x);
			angle = angle *(180 / PI);
			if (angle <= 180 && angle >= 90 || angle >= -180 && angle < -90){
				drawArrow(draw_at, Point_start, Point_end, color, 3, 1, 8, 0);
			}
			else if (angle >= 0 && angle < 90 || angle >= -90 && angle < 90){
				drawArrow(draw_at, Point_start, Point_end, color - Scalar(255, -255, 0), 3, 1, 8, 0);
			}
		}
	}
	else{
		Point_start = start.tl() + Point(7, 7);
		circle(draw_at, Point_start, 0.5, Scalar(255, 0, 0));
	}
}

double Method::get_length_with_two_point(Point x, Point y){
	double result;
	if (x.x > y.x){
		bool debug = true;
	}
	result = sqrt(
		pow((x.x - y.x), 2) +
		pow((x.y - y.y), 2)
		);
	return result;
}

void Method::drawArrow(Mat &image, Point p, Point q, Scalar color, int arrowMagnitude, int thickness, int line_type, int shift)
{
	//Draw the principle line
	line(image, p, q, color, thickness, line_type, shift);
	const double PI = 3.141592653;
	//compute the angle alpha
	double angle = atan2((double)p.y - q.y, (double)p.x - q.x);
	//compute the coordinates of the first segment
	p.x = (int)(q.x + arrowMagnitude * cos(angle + PI / 4));
	p.y = (int)(q.y + arrowMagnitude * sin(angle + PI / 4));
	//Draw the first segment
	line(image, p, q, color, thickness, line_type, shift);
	//compute the coordinates of the second segment
	p.x = (int)(q.x + arrowMagnitude * cos(angle - (PI / 4)));
	p.y = (int)(q.y + arrowMagnitude * sin(angle - (PI / 4)));
	//Draw the second segment
	line(image, p, q, color, thickness, line_type, shift);
}

void Method::release_vector(){
	if (blocks_match.size() > 0)
		blocks_match.erase(blocks_match.begin(), blocks_match.begin() + blocks_match.size() - 1);
}