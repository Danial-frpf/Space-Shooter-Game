//Adding main directory
#include "detective.h"

//Function to check for collision in two rectangles
bool detective::rect_rect(double rect1[], double rect2[])
{
	double x1, x2, y1, y2;
	double x3, x4, y3, y4;
	x1 = rect1[0] - (rect1[2] / 2);
	x2 = rect1[0] + (rect1[2] / 2);
	y1 = rect1[1] - (rect1[3] / 2);
	y2 = rect1[1] + (rect1[3] / 2);
	x3 = rect2[0] - (rect2[2] / 2);
	x4 = rect2[0] + (rect2[2] / 2);
	y3 = rect2[1] - (rect2[3] / 2);
	y4 = rect2[1] + (rect2[3] / 2);
	if ((x1 <= x4 && x2 >= x3) && (y1 <= y4 && y2 >= y3))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Function to check for collision between a rectangle and a point
bool detective::point_rect(double point[], double rect[])
{
	double x1 = rect[0] - (rect[2] / 2);
	double x2 = rect[0] + (rect[2] / 2);
	double y1 = rect[1] - (rect[3] / 2);
	double y2 = rect[1] + (rect[3] / 2);
	double x = point[0];
	double y = point[1];
	if (x1 <= x && x <= x2 && y1 <= y && y <= y2)
	{
		return true;
	}
	else
	{
		return false;
	}
}