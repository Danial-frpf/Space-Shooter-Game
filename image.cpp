//Adding header file
#include "image.h"

//Initializing static variables
vector<int> image::path;
int image::tracer = -1;

//Constructor
image::image(int image_type, double image_width, double image_height, double xcor, double ycor)
	:width(image_width), height(image_height), x(xcor), y(ycor)
{
	r = g = b = a = 1;
	if (image_type - 1 <= tracer && image_type > 0)
	{
		index = image_type - 1;
	}
}

//Function load image
void image::add_image(const char* image_path)
{
	path.push_back(slLoadTexture(image_path));
	tracer++;
}

//Defining creator function
void image::creator(double x_axis, double y_axis, double angle)
{
	x_pos = x_axis;
	y_pos = y_axis;
	slPush();
	slTranslate(x_pos, y_pos);
	slRotate(angal);
	slSetForeColor(r, g, b, a);
	slSprite(path[index], x, y, width, height);
	slPop();
}

//Function to change position
void image::change_pos(double new_xcor, double new_ycor)
{
	x_pos = new_xcor;
	y_pos = new_ycor;
}

//Function to change dimensions
void image::change_size(double new_width, double new_height)
{
	width = new_width;
	height = new_height;
}

//Function to change texture
void image::change_texture(int new_texture)
{
	if (new_texture - 1 <= tracer && new_texture > 0)
	{
		index = new_texture - 1;
	}
}

//Function to change color
void image::change_color(double red, double green, double blue, double alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

//Function to change ang
void image::change_ang(double angle)
{
	angal = angle;
	ang = angle * 3.14159 / 180;
}

//Function to return curent transition coordinates array
double image::get_x_pos()
{
	return x_pos;
}

double image::get_y_pos()
{
	return y_pos;
}

//Function to return width and height
double image::get_width()
{
	return width;
}

double image::get_height()
{
	return height;
}

//Function to get ang
double image::get_ang()
{
	return ang;
}

//Function to return transitional rect array
double* image::get_rect()
{
	rect[0] = x_pos;
	rect[1] = y_pos;
	rect[2] = width;
	rect[3] = height;
	return rect;
}
