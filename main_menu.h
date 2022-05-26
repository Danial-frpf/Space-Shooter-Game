#pragma once

//Adding STL libraries
#include<vector>
#include<string>
//Adding external libraries
#include<sl.h>
//Adding user defined classes
#include"settings.h"
#include"text.h"
#include"image.h"
#include"shapes.h"
#include"detective.h"

//Defining standard namespace
using namespace std;

//Creating main menu class
class main_menu
{
private:
	double col, row;
	double width, height;
	vector<text> options;
	vector<image> frame;
	vector<image> background;
	vector<shapes> shape;
	bool mouse_flag = false;
	double mouse_x = 0;
	double mouse_y = 0;
	int num1 = 0;
	int num2 = 25;
	int num3 = 0;
	int tracer = 4;
	int check = 1;
	string temp;

public:
	//Constructor
	main_menu();
	//Make main menu operations
	void operation();
	//Main menu loop
	void loop_menu();
	//Function to initialize text objects for options
	void initialize_options();
	//Function to display options
	void render_options();
	//Function to initialize frames
	void initialize_frames();
	//Function to display frames
	void render_frames();
	//Function to initialize shapes
	void initialize_shapes();
	//Function for keyboard event response
	void key_event();
	//Function for mouse event response
	void mouse_event();
	//Function to update according to most recent event
	void event_response();

};

