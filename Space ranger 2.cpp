//Adding STL libraries

//Adding external libraries
#include<sl.h>
//Addding user defined classes
#include"settings.h"
#include"main_menu.h"
#include"playgame.h"

//Defining general namespace
using namespace std;

//Creating main function
int main()
{
	settings setting;
	//Creating window
	slWindow(setting.get_width(), setting.get_height(), "Space rangers 2", true);

	//Loading wav files
	settings::load_wav();

	main_menu menu;
	playgame play;

	//Main game loop
	while (!slShouldClose() && settings::flag)
	{
		menu.loop_menu();
		play.loop_play();

		slRender();
	}




	//Terminating program successfully
	return 0;
}