#pragma once

using namespace std;
using namespace cv;

class MotionVector
{
public:
	MotionVector(Rect input, float angle_in, float length_in, bool isMovementObject_in);
	~MotionVector();
	void set(Rect input){};
	bool isMovementObject(){ return movement; };
private:
	Rect rect;
	float angle, length;
	bool movement;
};

