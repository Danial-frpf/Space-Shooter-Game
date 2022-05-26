#pragma once

//Adding STL libraries
#include<string>
#include<vector>
//Adding external libraries
#include<sl.h>

//Defining general namespace
using namespace std;

//Creating class
class text
{
private:
	static vector <int> path;
	int static tracer;
	const char* words;
	int index = 0;
	double x, y;
	int size;
	char align;
	double r, g, b, a;
	double x_pos, y_pos;

public:
	//Declaring constructor
	text(const char* text_words = "Empty", int font = 1, int text_size = 32, double xcor = 0, double ycor = 0);
	//Declaring function to load font
	static void add_font(const char* font_path);
	//Create text on screen
	void text_creator(double x_axis = 0, double y_axis = 0, double angle = 0);
	//Function to change the text position
	void change_pos(double new_xcor, double new_ycor);
	//Function to change text size
	void change_size(int new_text_size);
	//Function to change text font
	void change_font(int new_font);
	//Function to change the text itself
	void change_text(const char* new_text_words);
	//Function to change text align location
	void change_align(char new_align);
	//Function to change color
	void change_color(double red = 1, double green = 1, double blue = 1, double alpha = 1);
};

