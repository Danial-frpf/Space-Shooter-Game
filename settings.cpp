//Adding header file
#include "settings.h"

//Initializing static variables
double settings::width = 0;
double settings::height = 0;
double settings::col = 0;
double settings::row = 0;
int settings::player_lives = 5;
vector<int> settings::wav;

//Flag
bool settings::flag = true;
bool settings::menu_flag = true;
bool settings::play_flag = false;

//Consrtuctor
settings::settings()
{
	//To obtain native dimensions of user screen
	RECT dextop;
	GetWindowRect(GetDesktopWindow(), &dextop);
	width = dextop.right;
	height = dextop.bottom;
	col = width / 10;
	row = height / 10;
	srand((unsigned)time(0));
}

//Return value of row
const double settings::get_row()
{
	return row;
}
//Return value of col
const double settings::get_col()
{
	return col;
}
//Return value of width
const double settings::get_width()
{
	return width;
}
//Return value of height
const double settings::get_height()
{
	return height;
}

//Return value of player_lives
int const settings::get_lives()
{
	return player_lives;
}

//Return enemy fleet speed
const double settings::get_fleetspeed()
{
	double speed = 100 * slGetDeltaTime();
	return speed;
}

//Return bullet speed
const double settings::get_bulletspeed()
{
	double speed = 40 * row * slGetDeltaTime();
	return speed;
}

//Function to return random number
const int settings::get_rand()
{
	return rand();
}

//Return probabilty factor
const double settings::get_prob(int i, int factor)
{
	int prob = rand() % ((i + 1) * factor);
	return prob;
}

//Return sound value
const int settings::get_wav(int wave_index)
{
	if (wave_index < wav.size())
	{
		return wav[wave_index];
	}
}

//Function to load ingame sound
void settings::load_wav()
{
	for (int i = 0; i < 25; i++)
	{
		string temp = "wav/wav" + to_string(i) + ".wav";
		wav.push_back(slLoadWAV(temp.c_str()));
	}
}
