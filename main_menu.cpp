//Adding header file
#include "main_menu.h"

//Constructor
main_menu::main_menu()
{
	//Setting up total screen coloumns and rows
	col = settings::get_col();
	row = settings::get_row();
	width = settings::get_width();
	height = settings::get_height();
	operation();
}

//Defining main control function
void main_menu::operation()
{
	//Initializing option objects
	initialize_options();

	//Loading background
	image::add_image("images/shoki.bmp");
	image bg(1, width, height);
	background.push_back(bg);

	//Initializing frames
	initialize_frames();

	//Initializing shapes
	initialize_shapes();

	//Adding ship resourses
	for (int i = 0; i < 6; i++)
	{
		string title = "images/ships/ship" + to_string(i) + ".png";
		image::add_image(title.c_str());
	}
	//Initialize explosion
	image::add_image("images/explosion.png");
	image::add_image("images/bomb.png");

}

//Defining main menu functionality loop
void main_menu::loop_menu()
{
	//Soundtrack
	slSoundLoop(settings::get_wav(24));

	//Main menu while loop
	while (settings::menu_flag)
	{
		//Displaying background
		background[0].creator(col * 5, row * 5);

		//Displaying frames
		render_frames();

		//Drawing shapes
		shape[0].rect_fill(col * 5, row * 2.25);
		shape[1].rect_unfill(col * 5, row * 2.25);

		//Respond to keyboard events
		key_event();

		//Respond to mouse event
		mouse_event();

		//Update according to previous events
		event_response();

		//Displaying images
		render_options();

		//Render console window
		slRender();
	}
}

//Function to initialize text objects for options
void main_menu::initialize_options()
{
	//Adding text fonts
	text::add_font("fonts/Exo2-Bold.TTF");
	//Intializing text objects
	text t1, t2, t3, t4, t5, t6;
	//Creating menu text
	t1.change_text("Play Game");
	t2.change_text("High Score");
	t3.change_text("Settings");
	t4.change_text("Credits");
	t5.change_text("Quite");
	t6.change_text("FPS: N/A");
	options.push_back(t5);
	options.push_back(t4);
	options.push_back(t3);
	options.push_back(t2);
	options.push_back(t1);
	options.push_back(t6);
	//Change options size and alignment point
	for (int i = 0; i < 5; i++)
	{
		options[i].change_size(int(row * 0.65));
		options[i].change_align('C');

	}
	options[5].change_size(int(row * 0.35));
	options[5].change_align('L');
}

//Function to display options
void main_menu::render_options()
{
	//Displaying options on screen
	for (int i = 0; i < 5; i++)
	{
			options[i].text_creator(col * 5, 0.9 * row * (i + 0.3));
	}
	//Finding fps value
	if (num3 % int(500 * slGetDeltaTime() + 1) == 0)
	{
		int fps = int(1 / slGetDeltaTime() + 1);
		temp = "FPS: " + to_string(fps);
		options[5].change_text(temp.c_str());
	}
		options[5].text_creator(col * 0, row * 9.65);
}

//Function to initialize frame
void main_menu::initialize_frames()
{
	//Loading frames
	string title;
	for (int i = 0; i < 26; i++)
	{
		title = "images/frames/title" + to_string(i) + ".png";
		image::add_image(title.c_str());
	}
	//Settings frame vector
	image img(1, col * 8, row * 3);
	frame.push_back(img);
}

//Function to display frames on screen
void main_menu::render_frames()
{
	//Displaying frames
	//Reset delay
	int speed = int(100 * slGetDeltaTime()) + 1;
	if (num1 >= 500)
	{
		num1 = 0;
		num2 = 25;
	}
	if (num3 >= 9999999999)
	{
		num3 = 0;
	}
	//Forward motion
	if(num1 < 26 && num1 >= 0)
	{
		frame[0].change_texture(num1 + 2);
		frame[0].creator(col * 5, row * 8);
	}
	//Stable final frame
	if (num1 >= 26 && num1 < 250)
	{
		frame[0].change_texture(25 + 2);
		frame[0].creator(col * 5, row * 8);
	}
	//Backword motion with delay
	if (num1 >= 250 && num1 < 276)
	{
		frame[0].change_texture(num2 + 2);
		frame[0].creator(col * 5, row * 8);
		if ((num3 % speed) == 0)
		{
			num2--;
		}
	}
	//Stable initial frame
	if (num1 >= 276)
	{
		frame[0].change_texture(0 + 2);
		frame[0].creator(col * 5, row * 8);
	}
	if ((num3 % speed) == 0)
	{
		num1++;
	}
	num3++;
}

//Function to initialize shapes
void main_menu::initialize_shapes()
{
	shapes s1, s2, s3;
	s1.change_size(col * 11, row * 4.6);
	s2.change_size(col * 11, row * 4.6);
	s3.change_size(col * 11, row * 1);
	s1.change_color(0.3, 0.3, 0.3, 0.4);
	s2.change_color(0, 0, 0, 0.7);
	s3.change_color(1, 0.755, 0, 0.3);
	shape.push_back(s1);
	shape.push_back(s2);
	shape.push_back(s3);
}

//Function for keyboard event response
void main_menu::key_event()
{
	//While key is pressed
	if (slGetKey('W') || slGetKey(SL_KEY_UP))
	{
		if (tracer < 4 && check == 0)
		{
			tracer++;
			check++;
		}
		if (tracer == 4 && check == 0)
		{
			tracer = 0;
			check++;
		}
		mouse_flag = false;
	}
	if (slGetKey('S') || slGetKey(SL_KEY_DOWN))
	{
		if (tracer > 0 && check == 0)
		{
			tracer--;
			check++;
		}
		if (tracer == 0 && check == 0)
		{
			tracer = 4;
			check++;
		}
		mouse_flag = false;
	}
	if (slGetKey(SL_KEY_ENTER) && check == 0)
	{
		switch (tracer)
		{
		case 0:
			settings::menu_flag = false;
			settings::flag = false;
			check++;
			break;
		case 1:
			slSoundPlay(settings::get_wav(17));
			check++;
			break;
		case 2:
			slSoundPlay(settings::get_wav(18));
			check++;
			break;
		case 3:
			slSoundPlay(settings::get_wav(19));
			check++;
			break;
		case 4:
			settings::menu_flag = false;
			settings::play_flag = true;
			check++;
			break;
		}
		mouse_flag = false;
	}
	//When key aren't pressed
	if (!slGetMouseButton(SL_MOUSE_BUTTON_1) && !slGetKey(SL_KEY_ENTER) && !slGetKey('W') && !slGetKey(SL_KEY_UP) && !slGetKey('S') && !slGetKey(SL_KEY_DOWN))
	{
		if (check == 1)
		{
			check--;
		}
	}
}

//Function for mouse event response
void main_menu::mouse_event()
{
	//Check whether the mouse is in motion or not
	if (mouse_x != slGetMouseX() && mouse_y != slGetMouseY())
	{
		mouse_flag = true;
	}
	mouse_x = slGetMouseX();
	mouse_y = slGetMouseY();
	//Mouse position array
	double mouse_cor[] = { mouse_x ,mouse_y };
	//Mouse control
	for (int i = 0; i < 5; i++)
	{
		double rect[] = { col * 5, 0.9 * row * (i + 0.5), col * 10, 1 * row };
		if (detective::point_rect(mouse_cor, rect))
		{
			if (mouse_flag)
			{
				tracer = i;
			}
			if (slGetMouseButton(SL_MOUSE_BUTTON_1) && check == 0)
			{
				switch (tracer)
				{
				case 0:
					settings::menu_flag = false;
					settings::flag = false;
					check++;
					break;
				case 1:
					slSoundPlay(settings::get_wav(17));
					check ++;
					break;
				case 2:
					slSoundPlay(settings::get_wav(18));
					check++;
					break;
				case 3:
					slSoundPlay(settings::get_wav(19));
					check++;
					break;
				case 4:
					check++;
					settings::menu_flag = false;
					settings::play_flag = true;
					break;
				}
			}
		}
	}
}

//Function to update according to most recent event
void main_menu::event_response()
{
	for (int i = 0; i < 5; i++)
	{
		if (i != tracer)
		{
			options[i].change_color();
		}
		else
		{
			options[i].change_color(1, 0.7, 0, 1);
			shape[2].rect_fill(col * 5, row * 0.9 * (i + 0.5));

		}
	}
}
