//Adding main header
#include "shapes.h"

//Constructor
shapes::shapes(double shape_width, double shape_height, double xcor, double ycor, double radius)
	:width(shape_width), height(shape_height), x(xcor), y(ycor), radi(radius)
{
	r = g = b = a = 1;
}

//Fuunction to create filled rectangle
void shapes::rect_fill(double x_axis, double y_axis, double angle)
{
	x_pos = x_axis;
	y_pos = y_axis;
	slPush();
	slTranslate(x_pos, y_pos);
	slRotate(angle);
	slSetForeColor(r, g, b, a);
	slRectangleFill(x, y, width, height);
	slPop();
}

//Function to create unfilled rectangle
void shapes::rect_unfill(double x_axis, double y_axis, double angle)
{
	x_pos = x_axis;
	y_pos = y_axis;
	slPush();
	slTranslate(x_pos, y_pos);
	slRotate(angle);
	slSetForeColor(r, g, b, a);
	slRectangleOutline(x, y, width, height);
	slPop();
}

//Function to create filled circle
void shapes::circle_fill(double x_axis, double y_axis, double angle, int vertix)
{
	x_pos = x_axis;
	y_pos = y_axis;
	slPush();
	slTranslate(x_pos, y_pos);
	slRotate(angle);
	slSetForeColor(r, g, b, a);
	slCircleFill(x, y, radi, vertix);
	slPop();
}

//Function to create unfilled circle
void shapes::circle_unfill(double x_axis, double y_axis, double angle, int vertix)
{
	x_pos = x_axis;
	y_pos = y_axis;
	slPush();
	slTranslate(x_pos, y_pos);
	slRotate(angle);
	slSetForeColor(r, g, b, a);
	slCircleOutline(x, y, radi, vertix);
	slPop();
}

//Function to create filled semicircle
void shapes::semicircle_fill(double x_axis, double y_axis, double amount, int vertix, double angle)
{
	x_pos = x_axis;
	y_pos = y_axis;
	slPush();
	slTranslate(x_pos, y_pos);
	slRotate(angle);
	slSetForeColor(r, g, b, a);
	slSemiCircleFill(x, y, radi, vertix, amount);
	slPop();
}

//Function to create unfilled semicircle
void shapes::semicircle_unfill(double x_axis, double y_axis, double amount, int vertix, double angle)
{
	x_pos = x_axis;
	y_pos = y_axis;
	slPush();
	slTranslate(x_pos, y_pos);
	slRotate(angle);
	slSetForeColor(r, g, b, a);
	slSemiCircleOutline(x, y, radi, vertix, amount);
	slPop();
}

//Function to change position
void shapes::change_pos(double new_xcor, double new_ycor)
{
	x_pos = new_xcor;
	y_pos = new_ycor;
}

//Function to change dimensions
void shapes::change_size(double new_width, double new_height)
{
	width = new_width;
	height = new_height;
}

//Function to change color
void shapes::change_color(double red, double green, double blue, double alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

//Function to change radius
void shapes::change_radius(double radius)
{
	radi = radius;
}

//Function to get transitional coordinates
double shapes::get_x_pos()
{
	return x_pos;
}

double shapes::get_y_pos()
{
	return y_pos;
}

//Function to return width and height
double shapes::get_width()
{
	return width;
}

double shapes::get_height()
{
	return height;
}

//Function to return transitional rect array
double* shapes::get_rect()
{
	rect[0] = x_pos;
	rect[1] = y_pos;
	rect[2] = width;
	rect[3] = height;
	return rect;
}