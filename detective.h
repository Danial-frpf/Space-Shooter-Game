#pragma once


//Creating class
class detective
{
private:


public:
	//Function to check for collision in two rectangles
	static bool rect_rect(double rect1[], double rect2[]);
	//Function to check for collision between a rectangle and a point
	static bool point_rect(double point[], double rect[]);

};

