#pragma once

//Adding external files
#include<sl.h>

//Defining general namespace
using namespace std;

//Creating class
class shapes
{
private:
	double x, y;
	double width, height;
	double r, g, b, a;
	double radi;
	double x_pos, y_pos;
	double rect[4];

public:
	//Declearing constructor
	shapes(double shape_width = 100, double shape_height = 100, double xcor = 0, double ycor = 0, double raduis = 1);
	//Function to create filled rectangle on screen
	void rect_fill(double x_axis = 0, double y_axis = 0, double angle = 0);
	//Function to create unfilled rectangle on screen
	void rect_unfill(double x_axis = 0, double y_axis = 0, double angle = 0);
	//Function to create filled circle on screen
	void circle_fill(double x_axis = 0, double y_axis = 0, double angle = 0, int vertix = 0);
	//Function to create unfilled circle on screen
	void circle_unfill(double x_axis = 0, double y_axis = 0, double angle = 0, int vertix = 0);
	//Function to create filled semicircle on screen
	void semicircle_fill(double x_axis = 0, double y_axis = 0, double amount = 0, int vertix = 0, double angle = 0);
	//Function to create unfilled semicircle on screen
	void semicircle_unfill(double x_axis = 0, double y_axis = 0, double amount = 0, int vertix = 0, double angle = 0);
	//Function to change shape position
	void change_pos(double new_xcor, double new_ycor);
	//Function to change shape dimensions
	void change_size(double new_width, double new_height);
	//Function to change color
	void change_color(double red = 1, double green = 1, double blue = 1, double alpha = 1);
	//Function to change radius
	void change_radius(double radius);
	//Function to get transitional coordinates
	double get_x_pos();
	double get_y_pos();
	//Function to return width and height
	double get_width();
	double get_height();
	//Function to return transitional rect array
	double* get_rect();
};

