//Adding header file
#include "frames.h"


//Constructor
frames::frames(double frame_width, double frame_height, double x, double y)
	:width(frame_width), height(frame_height), x_pos(x), y_pos(y)
{

}
//Function to set width and height
void frames::set_size(double frame_width, double frame_height)
{
	width = frame_width;
	height = frame_height;
}
//Function to set x and y coordinates
void frames::set_pos(double x, double y)
{
	x_pos = x;
	y_pos = y;
}
//Function to draw the frames on screen
bool frames::creator()
{
	image frame(34, width, height);
	slSetSpriteTiling(0.0625, -0.05);
	slSetSpriteScroll(frame1, frame2);
	frame.creator(x_pos, y_pos);
	slSetSpriteTiling(1, 1);
	slSetSpriteScroll(0, 0);
	frame1 += 0.0625;
	if (frame1 >= 1)
	{
		frame1 = 0;
		frame2 -= 0.0625;
	}
	if (frame2 <= 0)
	{
		frame1 = 0;
		frame2 = 1;
		return true;
	}
	return false;
}