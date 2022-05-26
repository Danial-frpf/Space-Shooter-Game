#pragma once

//Adding STL
#include<wtypes.h>
#include<time.h>
#include<cstdlib>
#include<vector>
#include<string>
//Adding external libraries
#include<sl.h>

//Defining standard namespace
using namespace std;

//Creating settings class
class settings
{
private:
	static double width, height;
	static double row, col;
	static int player_lives;
	static vector<int> wav;

public:
	//Flag
	static bool flag, menu_flag, play_flag;
	//Constructor
	settings();
	//Return value of row & col
	static const double get_row();
	static const double get_col();
	//Return value of width and height of native display
	static const double get_width();
	static const double get_height();
	//Return value of player_lives
	static const int get_lives();
	//Return speed factor
	static const double get_fleetspeed();
	static const double get_bulletspeed();
	//Function to return random number
	static const int get_rand();
	//Return probabilty factor
	static const double get_prob(int i = 0, int factor = 10);
	//Return sound value
	static const int get_wav(int wave_index = 0);
	//Function to load ingame sound
	static void load_wav();
};

