#pragma once

//Adding external directories
#include<sl.h>

//Adding user defined classes
#include"image.h"

//Creating class
class frames
{
private:
	double frame1 = 0;
	double frame2 = 1;
	double x_pos, y_pos;
	double width, height;

public:
	//Constructor
	frames(double frame_width = 0, double frame_height = 0, double x = 0, double y = 0);
	//Function to set width and height
	void set_size(double frame_width, double frame_height);
	//Function to set x and y coordinates
	void set_pos(double x, double y);
	//Function to draw the frames on screen
	bool creator();

};

