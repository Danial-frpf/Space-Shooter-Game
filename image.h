#pragma once

//Adding STL libraries
#include<vector>
//Adding external libraries
#include<sl.h>

//Defining standard namespace
using namespace std;

//Creating class
class image
{
private:
	static vector<int> path;
	static int tracer;
	int index = 0;
	double x, y;
	double width, height;
	double r, g, b, a;
	double x_pos, y_pos;
	double ang = 0;
	double angal = 0;
	double rect[4];

public:
	//Declearing constructor
	image(int image_type, double image_width, double image_height, double xcor = 0, double ycor = 0);
	//Function to load image
	static void add_image(const char* image_path);
	//Function to create image on screen
	void creator(double x_axis = 0, double y_axis = 0, double angle = 0);
	//Function to change image position
	void change_pos(double new_xcor, double new_ycor);
	//Function to change image dimensions
	void change_size(double new_width, double new_height);
	//Function to change image type
	void change_texture(int new_texture);
	//Function to change color
	void change_color(double red = 1,double green = 1, double blue = 1, double alpha = 1);
	//Function to change ang
	void change_ang(double angle);
	//Function to return curent transition coordinates array
	double get_x_pos();
	double get_y_pos();
	//Function to return width and height
	double get_width();
	double get_height();
	//Function to get ang
	double get_ang();
	//Function to return transitional rect array
	double* get_rect();

};

