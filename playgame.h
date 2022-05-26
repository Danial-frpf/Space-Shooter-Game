#pragma once

//Adding STD libraries
#include<string>
#include<vector>
#include<cmath>
//Adding external libraries
#include<sl.h>
//Adding user defined classes
#include"settings.h"
#include"image.h"
#include"shapes.h"
#include"text.h"
#include"detective.h"
#include"frames.h"

//Testing
#include<iostream>
using namespace std;

//Creating class
class playgame
{
private:
	double col, row;
	double width, height;
	bool initialize_flag = true;
	bool mouse_flag = false;
	vector<image> ships;
	vector<image> fleet;
	vector<shapes> bullets;
	vector<shapes> bullets_enemy;
	vector<shapes> basic_shapes;
	vector<text> board;
	vector<bool> flags;
	vector<int> direction;
	vector<frames> animation;
	vector<image> bomb;
	vector<int> bomb_dir_x;
	vector<int> bomb_dir_y;
	vector<int> bomb_num;
	double mouse_x = 0;
	double mouse_y = 0;
	int tracer = 1;
	int count = 1;
	int player_lives;
	int boss_lives = 100;
	int score = 0;
	int highscore = 0;
	int level = 1;
	int stopper = 0;
	double frame1 = 0;
	double frame2 = 0;
	string tempps = "FPS: ";

public:
	//Constructor
	playgame();
	//Initialize game resourses
	void initialize_resourses();
	//Main playgame loop
	void loop_play();
	//Function to create emeny fleet
	void create_fleet();
	//Function to create basic shapes
	void create_basicshapes();
	//Function to create onscreen text
	void create_text();
	//Function to update animation
	void update_animation();
	//Function to update bomb attack
	void update_bomb();
	//Function to update player ship
	void update_ship();
	//Function to update player bullets on screen
	void update_bullets();
	//Function to update enemy ship
	void update_enemy();
	//Function to update ingame text
	void update_text();
	//Function to draw basic shapes
	void update_basicshapes();
	//Function for keyboard event response
	void key_event();
	//Function for mouse event response
	void mouse_event();
	//Function to update according to most recent event
	void event_response();
};

