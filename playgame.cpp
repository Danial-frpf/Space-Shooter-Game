//Adding header file
#include "playgame.h"

//Constructor
playgame::playgame()
{
	col = settings::get_col();
	row = settings::get_row();
	width = settings::get_width();
	height = settings::get_height();
}

//Main playgame loop
void playgame::loop_play()
{
	if (initialize_flag)
	{
		initialize_resourses();
		initialize_flag = false;
	}
	flags[7] = true;
	player_lives = settings::get_lives();
	while (settings::play_flag)
	{
		//Respond to keyboard events
		key_event();

		//Respond to mouse event
		mouse_event();

		//Update according to previous events
		event_response();

		//Update animation
		update_animation();

		//Update bomb
		update_bomb();

		//Update bullets
		update_bullets();
	
		//Update player ship
		update_ship();

		//Update enemy ship
		update_enemy();

		//Update basic shapes
		update_basicshapes();

		//Update text
		update_text();

		//Render console window
		slRender();
	}
}

//Initialize game resourses
void playgame::initialize_resourses()
{
	//Assigning ships to ships vector
	//Player ship
	image ship(29, col * 0.6, row);
	ship.change_pos(col * 5, row);
	ships.push_back(ship);

	//Bose 1
	ship.change_texture(32);
	ship.change_size(8 * col, 4 * row);
	ship.change_pos(5 * col, 12 * row);
	ships.push_back(ship);

	//Pushing player movement flags into flag record
	for (int i = 0; i < 20; i++)
	{
		flags.push_back(false);
	}

	//Create enemy fleet
	create_fleet();

	//Adding ingame basic shapes
	create_basicshapes();

	//Adding ingame text
	create_text();
}

//Function to create emeny fleet
void playgame::create_fleet()
{
	if (level == 1)
	{
		image ship(29, col * 0.6, row);
		ship.change_texture(31);
		ship.change_size(col, 1.4 * row);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				ship.change_pos((j + 0.5) * col * 1.4, (i + 3) * row * 1.7);
				fleet.push_back(ship);
				direction.push_back(1);
			}
		}
	}
}

//Function to create basic shapes
void playgame::create_basicshapes()
{
	shapes s1, s2, s3, s4, s5;
	s1.change_size(2 * col, row);
	s2.change_radius(0.5 * row);
	s3.change_size(0.13 * col, 0.7 * row);
	s4.change_size(4 * col, 6 * row);
	s5.change_size(4 * col, 2 * row);
	basic_shapes.push_back(s1);
	basic_shapes.push_back(s2);
	basic_shapes.push_back(s3);
	basic_shapes.push_back(s4);
	basic_shapes.push_back(s5);
	for (int i = 0; i < basic_shapes.size(); i++)
	{
		basic_shapes[i].change_color(1, 0.755, 0, 0.3);
	}
	basic_shapes[2].change_color(1, 0, 0, 0.3);
}

//Function to create onscreen text
void playgame::create_text()
{
	text t1, t2, t3, t4, t5, t6;
	t1.change_pos(9.9 * col, 9.1 * row);
	t2.change_pos(9.9 * col, 0.5 * row);
	t3.change_pos(0.1 * col, 9.55 * row);
	t4.change_pos(0.1 * col, 0.5 * row);
	t5.change_pos(5 * col, 5 * row);
	t1.change_align('R');
	t2.change_align('R');
	t5.change_align('C');
	t6.change_align('C');
	t5.change_text("Game Over");
	board.push_back(t1);
	board.push_back(t2);
	board.push_back(t3);
	board.push_back(t4);
	board.push_back(t5);
	//Mini menu items
	t6.change_pos(5 * col, 6.8 * row);
	t6.change_text("Resume");
	board.push_back(t6);
	t6.change_pos(5 * col, 4.8 * row);
	t6.change_text("New Game");
	board.push_back(t6);
	t6.change_pos(5 * col, 2.8 * row);
	t6.change_text("Main Menu");
	board.push_back(t6);


	for (int i = 0; i < board.size(); i++)
	{
		board[i].change_color(0.8, 0.8, 0.8, 1);
		board[i].change_size(0.5 * row);
	}
	board[2].change_size(0.4 * row);
	board[4].change_size(2 * row);
	board[5].change_size(0.7 * row);
	board[6].change_size(0.7 * row);
	board[7].change_size(0.7 * row);
}

//Function to update player ship
void playgame::update_ship()
{
	if (flags[4] && player_lives > 0)
	{
		player_lives--;
		flags[4] = false;
	}
	if (!flags[4])
	{
		double x = ships[0].get_x_pos();
		double y = ships[0].get_y_pos();
		if (flags[0] && x > 0.3 * col)
		{
			x -= 10 * col * slGetDeltaTime();
		}
		if (flags[1] && x < 9.7 * col)
		{
			x += 10 * col * slGetDeltaTime();
		}
		if (flags[2] && y < 9.3 * row)
		{
			y += 15 * row * slGetDeltaTime();
		}
		if (flags[3] && y > 0.7 * row)
		{
			y -= 15 * row * slGetDeltaTime();
		}
		ships[0].creator(x, y);
	}
}

//Function to update player bullet on screen
void playgame::update_bullets()
{
	//Updating player bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		double x = bullets[i].get_x_pos();
		double y = bullets[i].get_y_pos();
		//Update if mini menu isn't open
		if (!flags[6])
		{
			y += settings::get_bulletspeed();
		}
		bullets[i].rect_fill(x, y);
		if (y > 10 * row)
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}

	//Updating enemy fleet bullets
	for (int i = 0; i < bullets_enemy.size(); i++)
	{
		double x = bullets_enemy[i].get_x_pos();
		double y = bullets_enemy[i].get_y_pos();
		//Update if mini menu isn't open
		if (!flags[6])
		{
			y -= settings::get_bulletspeed();
		}
		bullets_enemy[i].rect_fill(x, y);
		if (y < 0.5 * row)
		{
			bullets_enemy.erase(bullets_enemy.begin() + i);
			i--;
		}
	}
}

//Function to update enemy ship
void playgame::update_enemy()
{
	for (int i = 0; i < fleet.size(); i++)
	{
		//Updating fleet position
		double x = fleet[i].get_x_pos();
		double y = fleet[i].get_y_pos();
		if (x > col * 9.5 || x < col * 0.5)
		{
			direction[i] *= -1;
		}
		double fleet_speed = settings::get_fleetspeed();
		fleet_speed *= direction[i];
		//Update if mini menu isn't open
		if (!flags[6])
		{
			x += fleet_speed;
		}
		fleet[i].creator(x, y);

		//Update if mini menu isn't open
		if (!flags[6] && flags[9])
		{
			//Creating enemy bullets
			int j = settings::get_prob(i);
			if (j == 0)
			{
				shapes bullet(0.05 * col, 0.5 * row);
				bullet.change_pos(fleet[i].get_x_pos(), fleet[i].get_y_pos());
				bullet.change_color(1, 0, 0, 1);
				bullets_enemy.push_back(bullet);
				slSoundPlay(settings::get_wav(1));
			}
			if (!flags[12])
			{
				slSoundLoop(settings::get_wav(21));
				flags[12] = true;
			}
		}
	}

	//Behaviour of bose 1
	if (level == 2)
	{
		double x = ships[1].get_x_pos();
		double y = ships[1].get_y_pos();
		double speed = settings::get_fleetspeed();
		if (y > 7.5 * row && !flags[6])
		{
			y -= speed * 0.2;
		}

		if (y < 7.8 * row && !flags[11])
		{
			flags[11] = true;
		}
		if (!flags[6] && flags[11])
		{
			if (x >= 6 * col || x <= 4 * col)
			{
				direction[0] *= -1;
			}
			x += speed * direction[0];
		}
		ships[1].creator(x, y);

		if (!flags[6] && flags[11])
		{
			for (int i = 0; i < 10; i++)
			{
				//Creating enemy bullets
				int j = settings::get_prob(i);
				if (j == 0)
				{
					shapes bullet(0.05 * col, 0.5 * row);
					bullet.change_pos(ships[1].get_x_pos() + i * col * 0.3, ships[1].get_y_pos());
					bullet.change_color(1, 0, 0, 1);
					bullets_enemy.push_back(bullet);
					bullet.change_pos(ships[1].get_x_pos() - i * col * 0.3, ships[1].get_y_pos());
					bullets_enemy.push_back(bullet);
					slSoundPlay(settings::get_wav(1));
				}
			}
		}
	}

	//Level 3 bose behaviour
	if (level == 3)
	{
		double x = ships[1].get_x_pos();
		double y = ships[1].get_y_pos();
		double speed = settings::get_fleetspeed();
		if (y > 7.8 * row && !flags[6])
		{
			y -= speed * 0.5;
		}

		if (y < 8 * row && !flags[11])
		{
			flags[11] = true;
		}
		if (!flags[6] && flags[11])
		{
			if (x >= 8.4 * col || x <= 1.6 * col)
			{
				direction[0] *= -1;
			}
			x += speed * direction[0] * 2;
		}

		//Low health animation
		if (boss_lives <= 50)
		{
			if (frame2 >= 1)
			{
				frame2 = 0;
			}
			frame2 += 1 * slGetDeltaTime();
			ships[1].change_color(1, frame2, frame2, 1);
		}
		else
		{
			ships[1].change_color(1, 1, 1, 1);
		}
		ships[1].creator(x, y);

		if (!flags[6] && flags[11] && flags[13])
		{
			for (int i = 0; i < 10; i++)
			{
				//Creating enemy bullets
				int j = settings::get_prob(i, (boss_lives / 5) + 1);
				if (j == 0)
				{
					shapes bullet(0.05 * col, 0.5 * row);
					bullet.change_pos(ships[1].get_x_pos() + i * col * 0.15, ships[1].get_y_pos());
					bullet.change_color(1, 0, 0, 1);
					bullets_enemy.push_back(bullet);
					bullet.change_pos(ships[1].get_x_pos() - i * col * 0.15, ships[1].get_y_pos());
					bullets_enemy.push_back(bullet);
					slSoundPlay(settings::get_wav(1));
				}
			}
		}
	}

	//Level 4 bose behaviour
	if (level == 4)
	{
		double x = ships[1].get_x_pos();
		double y = ships[1].get_y_pos();
		double speed = settings::get_fleetspeed();
		if (y > 7.8 * row && !flags[6])
		{
			y -= speed * 0.3;
		}

		if (y < 8 * row && !flags[11])
		{
			flags[11] = true;
		}
		if (!flags[6] && flags[11])
		{
			if (x >= 8.4 * col || x <= 1.6 * col)
			{
				direction[0] *= -1;
			}
			x += speed * direction[0] * 4;
		}
		//Low health animation
		if (boss_lives <= 200)
		{
			if (frame2 >= 1)
			{
				frame2 = 0;
			}
			frame2 += 1 * slGetDeltaTime();
			ships[1].change_color(1, frame2, frame2, 1);
		}
		else
		{
			ships[1].change_color(1, 1, 1, 1);
		}
		ships[1].creator(x, y);

		if (!flags[6] && flags[11] && flags[13])
		{
			for (int i = 0; i < 10; i++)
			{
				//Creating enemy bullets
				int j = settings::get_prob(i, (boss_lives / 20) + 1);
				if (j == 0)
				{
					shapes bullet(0.05 * col, 0.5 * row);
					bullet.change_pos(ships[1].get_x_pos() + i * col * 0.15, ships[1].get_y_pos());
					bullet.change_color(1, 0, 0, 1);
					bullets_enemy.push_back(bullet);
					bullet.change_pos(ships[1].get_x_pos() - i * col * 0.15, ships[1].get_y_pos());
					bullets_enemy.push_back(bullet);
					slSoundPlay(settings::get_wav(1));
				}
			}
			int prob = settings::get_prob(0, (boss_lives / 4) + 50);
			if (prob == 0)
			{
				image bang(35, 0.5 * col, row);
				bang.change_pos(ships[1].get_x_pos(), ships[1].get_y_pos());
				bang.change_ang(settings::get_rand() % 360);
				bomb.push_back(bang);
				bomb_dir_x.push_back(1);
				bomb_dir_y.push_back(1);
				bomb_num.push_back(0);
			}
		}
	}
}

//Function to draw basic shapes
void playgame::update_basicshapes()
{
	//Creating health-bare
	basic_shapes[0].rect_fill(1 * col, 0.7 * row);
	basic_shapes[1].semicircle_fill(2 * col, 0.7 * row, 180, 4, -90);
	for (int i = 0; i < player_lives; i++)
	{
		basic_shapes[2].rect_fill((i + 2.5) * col * 0.26, 0.7 * row);
	}
	
	//Create score and highscore shapes
	basic_shapes[0].rect_fill(9 * col, 0.7 * row);
	basic_shapes[1].semicircle_fill(8 * col, 0.7 * row, 180, 4, 90);
	basic_shapes[0].rect_fill(9 * col, 9.3 * row);
	basic_shapes[1].semicircle_fill(8 * col, 9.3 * row, 180, 4, 90);

	//Creating mini menu shapes
	if (flags[6])
	{
		basic_shapes[3].rect_fill(5 * col, row * 5);
		switch (tracer)
		{
		case 1:
			basic_shapes[4].rect_fill(5 * col, row * 7);
			break;
		case 2:
			basic_shapes[4].rect_fill(5 * col, row * 5);
			break;
		case 3:
			basic_shapes[4].rect_fill(5 * col, row * 3);
			break;
		}
	}
}

//Function to update animation
void playgame::update_animation()
{
	if (!flags[6])
	{
		for (int i = 0; i < animation.size(); i++)
		{
			if (animation[i].creator())
			{
				animation.erase(animation.begin() + i);
				i--;
			}
		}
	}
}

//Function to update bomb attack
void playgame::update_bomb()
{
	for (int i = 0; i < bomb.size(); i++)
	{
		double x = bomb[i].get_x_pos();
		double y = bomb[i].get_y_pos();
		double angle = bomb[i].get_ang();
		double speed = settings::get_fleetspeed() * 3;
		if (!flags[6])
		{
			if (x > 9.3 * col || x < 0.7 * col)
			{
				bomb_dir_x[i] *= -1;
				bomb_num[i] += 1;
			}
			if (y > 9.3 * row || y < 0.7 * row)
			{
				bomb_dir_y[i] *= -1;
				bomb_num[i] += 1;
			}
			x += speed * cos(angle) * bomb_dir_x[i];
			y += speed * sin(angle) * bomb_dir_y[i];
		}
		bomb[i].creator(x, y);
		if (bomb_num[i] == 5)
		{
			//Load animation
			frames explosion(2 * col, 2 * row, x, y);
			animation.push_back(explosion);
			//Play explosion sound
			slSoundPlay(settings::get_wav(3));
			//Erase bomb
			bomb.erase(bomb.begin() + i);
			bomb_num.erase(bomb_num.begin() + i);
			bomb_dir_x.erase(bomb_dir_x.begin() + i);
			bomb_dir_y.erase(bomb_dir_y.begin() + i);
			i--;
		}
	}
}

//Function to update ingame text
void playgame::update_text()
{
	//Chack and assign new highscore
	if (score > highscore)
	{
		highscore = score;
	}

	//Assign new value to text
	string temp1 = to_string(highscore);
	board[0].change_text(temp1.c_str());
	string temp2 = to_string(score);
	board[1].change_text(temp2.c_str());
	
	if (settings::get_rand() % 10 == 0)
	{
		int fps = int(1 / slGetDeltaTime());
		string temp3 = "FPS: " + to_string(fps);
		tempps = temp3;
	}
	board[2].change_text(tempps.c_str());
	string temp4 = "HP: ";
	board[3].change_text(temp4.c_str());

	//Draw text on screen
	for (int i = 0; i < board.size(); i++)
	{
		if (i >= 4)
		{
			if (flags[5] && !flags[6] && i == 4)
			{
				board[i].change_color(1, 1, 1, frame1);
				board[i].text_creator();
				if (frame1 < 1)
				{
					frame1 += 0.5 * slGetDeltaTime();
				}
			}
			if (i > 4 && flags[6])
			{
				if (i == tracer + 4)
				{
					board[i].change_color(1, 0.755, 0, 1);
					board[i].text_creator();
				}
				else
				{
					board[i].change_color();
					board[i].text_creator();
				}
			}
		}
		else
		{
			board[i].text_creator();
		}
	}
}

//Function for keyboard event response
void playgame::key_event()
{
	//For key presses
	if (slGetKey(SL_KEY_ESCAPE) && count == 0)
	{
		if (flags[6])
		{
			flags[6] = false;
		}
		else
		{
			flags[6] = true;
		}
		count++;
		mouse_flag = false;
	}
	if (!flags[4] && !flags[6])
	{
		if (slGetKey('A') || slGetKey(SL_KEY_LEFT))
		{
			flags[0] = true;
			mouse_flag = false;
		}
		if (slGetKey('D') || slGetKey(SL_KEY_RIGHT))
		{
			flags[1] = true;
			mouse_flag = false;
		}
		if (slGetKey('W') || slGetKey(SL_KEY_UP))
		{
			flags[2] = true;
			mouse_flag = false;
		}
		if (slGetKey('S') || slGetKey(SL_KEY_DOWN))
		{
			flags[3] = true;
			mouse_flag = false;
		}
		if (slGetKey(' ') && count == 0)
		{
			if (level == 1 || flags[11] )
			{
				shapes bullet(0.05 * col, 0.5 * row);
				bullet.change_pos(ships[0].get_x_pos(), ships[0].get_y_pos() + (0.25 * row));
				bullet.change_color(1, 0, 0.7, 1);
				bullets.push_back(bullet);
				if (level > 2)
				{
					bullet.change_pos(ships[0].get_x_pos() + (0.2 * col), ships[0].get_y_pos());
					bullets.push_back(bullet);
					bullet.change_pos(ships[0].get_x_pos() - (0.2 * col), ships[0].get_y_pos());
					bullets.push_back(bullet);
					if (level > 3)
					{
						bullet.change_pos(ships[0].get_x_pos() + (0.4 * col), ships[0].get_y_pos() - (0.25 * row));
						bullets.push_back(bullet);
						bullet.change_pos(ships[0].get_x_pos() - (0.4 * col), ships[0].get_y_pos() - (0.25 * row));
						bullets.push_back(bullet);
					}
				}
				slSoundPlay(settings::get_wav(2));
				count++;
				mouse_flag = false;
				//Stop the intro sound
				if (!flags[10])
				{
					slSoundStop(stopper);
					flags[10] = true;
				}
			}
		}
	}
	if (flags[6] && count == 0)
	{
		if (slGetKey('W') || slGetKey(SL_KEY_UP))
		{
			if (tracer > 1)
			{
				tracer--;
				count++;
				mouse_flag = false;
			}
			else
			{
				tracer = 3;
				count++;
				mouse_flag = false;
			}
		}
		if (slGetKey('S') || slGetKey(SL_KEY_DOWN))
		{
			if (tracer < 3)
			{
				tracer++;
				count++;
				mouse_flag = false;
			}
			else
			{
				tracer = 1;
				count++;
				mouse_flag = false;
			}
		}
		if (slGetKey(SL_KEY_ENTER))
		{
			switch (tracer)
			{
			case 1:
				flags[6] = false; //Flag to display and close mini menu
				count++;
				mouse_flag = false;
				break;
			case 2:
				flags[7] = true;
				count++;
				mouse_flag = false;
				break;
			case 3:
				slSoundStopAll();
				slSoundPlay(settings::get_wav(16));
				settings::play_flag = false;
				settings::menu_flag = true;
				count++;
				mouse_flag = false;
				break;
			}
		}
	}
	//When key aren't pressed
	if (!flags[6])
	{
		if (!slGetKey('A') && !slGetKey(SL_KEY_LEFT))
		{
			flags[0] = false;
		}
		if (!slGetKey('D') && !slGetKey(SL_KEY_RIGHT))
		{
			flags[1] = false;
		}
		if (!slGetKey('W') && !slGetKey(SL_KEY_UP))
		{
			flags[2] = false;
		}
		if (!slGetKey('S') && !slGetKey(SL_KEY_DOWN))
		{
			flags[3] = false;
		}
		if (!slGetKey(SL_KEY_ESCAPE) && !slGetKey(' ') && count == 1)
		{
			count--;
		}
	}
	if (flags[6] && count == 1)
	{
		if (!slGetMouseButton(SL_MOUSE_BUTTON_1) && !slGetKey(SL_KEY_ENTER) && !slGetKey('S') && !slGetKey(SL_KEY_DOWN) && !slGetKey('W') && !slGetKey(SL_KEY_UP) && !slGetKey(SL_KEY_ESCAPE))
		{
			count--;
		}
	}
}

//Function for mouse event response
void playgame::mouse_event()
{
	//Check whether the mouse is in motion or not
	if (mouse_x != slGetMouseX() && mouse_y != slGetMouseY())
	{
		mouse_flag = true;
	}
	mouse_x = slGetMouseX();
	mouse_y = slGetMouseY();

	//respopnse to mini menu events
	if (flags[6])
	{
		int j = 3;
		for (int i = 0; i < 5; i++)
		{
			i++;
			double point[] = { mouse_x, mouse_y };
			double rect[] = { 5 * col, row * (i + 2), 4 * col, 2 * row };
			bool check = detective::point_rect(point, rect);
			if (mouse_flag)
			{
				if (check)
				{
					tracer = j;
				}
			}
			j--;
			if (check && slGetMouseButton(SL_MOUSE_BUTTON_1) && count == 0)
			{
				switch (tracer)
				{
				case 1:
					flags[6] = false; //Flag to display and close mini menu
					count++;
					mouse_flag = false;
					break;
				case 2:
					flags[7] = true;
					count++;
					mouse_flag = false;
					break;
				case 3:
					slSoundStopAll();
					slSoundPlay(settings::get_wav(16));
					settings::play_flag = false;
					settings::menu_flag = true;
					count++;
					mouse_flag = false;
					break;
				}
			}
		}
	}
}

//Function to update according to most recent event
void playgame::event_response()
{
	//Check and response to bullet and enemy collisions
	for (int i = 0; i < bullets.size(); i++)
	{
		bool check = false;
		int tracer = 0;
		for (int j = 0; j < fleet.size(); j++)
		{
			double* rect1 = bullets[i].get_rect();
			double* rect2 = fleet[j].get_rect();
			check = detective::rect_rect(rect1, rect2);
			if (check)
			{
				//Load animation
				frames explosion(2 * col, 2 * row, fleet[j].get_x_pos(), fleet[j].get_y_pos());
				animation.push_back(explosion);
				//Erase enemy
				fleet.erase(fleet.begin() + j);
				direction.erase(direction.begin() + j);
				slSoundPlay(settings::get_wav(3));
				j--;
				score += 10;
				tracer++;
				//Play the start fight sound
				if (!flags[9])
				{
					slSoundPlay(settings::get_wav(4));
				}
				flags[9] = true; //Start the attack
			}
		}
		if (tracer != 0)
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}

	//Check for player bullet and bomb collision
	for (int i = 0; i < bullets.size(); i++)
	{
		bool check = false;
		int tracer = 0;
		for (int j = 0; j < bomb.size(); j++)
		{
			double* rect1 = bullets[i].get_rect();
			double* rect2 = bomb[j].get_rect();
			check = detective::rect_rect(rect1, rect2);
			if (check)
			{
				//Load animation
				frames explosion(2 * col, 2 * row, bomb[j].get_x_pos(), bomb[j].get_y_pos());
				animation.push_back(explosion);
				//Play explosion sound
				slSoundPlay(settings::get_wav(3));
				//Erase bomb
				bomb.erase(bomb.begin() + j);
				bomb_num.erase(bomb_num.begin() + j);
				bomb_dir_x.erase(bomb_dir_x.begin() + j);
				bomb_dir_y.erase(bomb_dir_y.begin() + j);
				j--;
				score += 10;
				tracer++;
			}
		}
		if (tracer != 0)
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}

	//Check for boss ship and player bullets collision
	if (level > 1)
	{
		double* rect1 = ships[1].get_rect();
		for (int i = 0; i < bullets.size(); i++)
		{
			double* rect2 = bullets[i].get_rect();
			if (detective::rect_rect(rect1, rect2))
			{
				if (level == 2 && player_lives > 0)
				{
					//Load animation
					frames explosion(25 * col, 25 * row, ships[1].get_x_pos(), 5 * row);
					animation.push_back(explosion);

					//Update score, levels and flags
					score += 1;
					level++;
					flags[11] = false;
					player_lives = settings::get_lives();
					//Clear bullets and directions
					bullets.clear();
					direction.clear();
					int rand = settings::get_prob(0, 2);
					if (rand == 0)
					{
						direction.push_back(1);
					}
					else
					{
						direction.push_back(-1);
					}
					//Set up boss 2
					boss_lives = 250;
					slSoundStopAll();
					slSoundPlay(settings::get_wav(3));
					slSoundPlay(settings::get_wav(6));
					slSoundLoop(settings::get_wav(23));
					ships[1].change_texture(33);
					ships[1].change_size(3 * col, 4 * row);
					ships[1].change_pos(5 * col, 11 * row);
					ships[1].change_ang(0);
				}
				else if (level == 3)
				{
					bullets.erase(bullets.begin() + i);
					i--;
					score += 20;
					if (!flags[13])
					{
						slSoundPlay(settings::get_wav(7));
						flags[13] = true;
					}
					if (boss_lives > 0)
					{
						boss_lives--;
						if (boss_lives == 150)
						{
							slSoundPlay(settings::get_wav(11));
						}
						if (boss_lives == 50)
						{
							slSoundPlay(settings::get_wav(12));
						}
					}
				}
				else if (level == 4)
				{
					bullets.erase(bullets.begin() + i);
					i--;
					score += 30;
					if (!flags[13])
					{
						slSoundPlay(settings::get_wav(9));
						flags[13] = true;
					}
					if (boss_lives > 0)
					{
						boss_lives--;
						if (boss_lives == 750)
						{
							slSoundPlay(settings::get_wav(13));
						}
						if (boss_lives == 500)
						{
							slSoundPlay(settings::get_wav(14));
						}
						if (boss_lives == 250)
						{
							slSoundPlay(settings::get_wav(15));
						}
					}
				}
			}
		}
	}

	//Check and response to player ship related events
	if (!flags[4])
	{
		//Check for enemy and player collision
		for (int j = 0; j < fleet.size(); j++)
		{
			double* rect1 = ships[0].get_rect();
			double* rect2 = fleet[j].get_rect();
			if (detective::rect_rect(rect1, rect2))
			{
				//Load animation
				frames explosion(2 * col, 2 * row, fleet[j].get_x_pos(), fleet[j].get_y_pos());
				animation.push_back(explosion);
				//Erase enemy
				fleet.erase(fleet.begin() + j);
				direction.erase(direction.begin() + j);
				j--;
				flags[4] = true;
			}
		}
		//check for player and enemy bullet collision
		for (int j = 0; j < bullets_enemy.size(); j++)
		{
			double* rect1 = ships[0].get_rect();
			double* rect2 = bullets_enemy[j].get_rect();
			if (detective::rect_rect(rect1, rect2))
			{
				bullets_enemy.erase(bullets_enemy.begin() + j);
				j--;
				flags[4] = true;
			}
		}

		//Check for player and bomb collision
		for (int j = 0; j < bomb.size(); j++)
		{
			double* rect1 = ships[0].get_rect();
			double* rect2 = bomb[j].get_rect();
			if (detective::rect_rect(rect1, rect2))
			{
				//Load animation
				frames explosion(2 * col, 2 * row, bomb[j].get_x_pos(), bomb[j].get_y_pos());
				animation.push_back(explosion);
				//Play explosion sound
				slSoundPlay(settings::get_wav(3));
				//Erase bomb
				bomb.erase(bomb.begin() + j);
				bomb_num.erase(bomb_num.begin() + j);
				bomb_dir_x.erase(bomb_dir_x.begin() + j);
				bomb_dir_y.erase(bomb_dir_y.begin() + j);
				j--;
				flags[4] = true;
			}
		}
		//Check for player and boss ship collision
		if (level > 1)
		{
			double* rect1 = ships[0].get_rect();
			double* rect2 = ships[1].get_rect();
			if (detective::rect_rect(rect1, rect2))
			{
				player_lives--;
			}
		}
	}

	//If player dies show game over
	if (player_lives == 0 && !flags[5])
	{
		flags[4] = true; //Flag for player ship display on/off
		flags[5] = true; //Flag to display gameover msg
		//Load animation
		frames explosion(2 * col, 2 * row, ships[0].get_x_pos(), ships[0].get_y_pos());
		animation.push_back(explosion);
		
	}

	//Create new game
	if (flags[7])
	{
		slSoundStopAll();
		stopper = slSoundPlay(settings::get_wav(0));
		fleet.clear();
		direction.clear();
		bullets_enemy.clear();
		bullets.clear();
		bomb.clear();
		bomb_dir_x.clear();
		bomb_dir_y.clear();
		bomb_num.clear();
		animation.clear();
		level = 1;
		create_fleet();
		score = 0;
		player_lives = settings::get_lives();
		ships[0].change_pos(5 * col, row);
		flags[4] = false; //Flag for player ship display on/off 
		flags[5] = false; //Flag to display gameover msg
		flags[6] = false; //Flag to display and close mini menu
		flags[7] = false; //Flag to reset game by clicking new game
		flags[8] = false; //Flag to start level 1
		flags[9] = false; //Flag to play first kill sound in level 1
		flags[10] = false; //Flag to stop intro sound at start by using space
		flags[11] = false; //Flag to start bose 1, 2, 3 horizontal motion , bullets and player bullets
		flags[12] = false; //Flag to play first background track
		flags[13] = false; //Flag to start level 3, 4 bullet firing
		frame1 = 0;
		frame2 = 0;
	}

	//Next level
	if (fleet.size() == 0 && !flags[8] && level == 1 && player_lives > 0)
	{
		level = 2;
		slSoundStopAll();
		slSoundPlay(settings::get_wav(5));
		slSoundLoop(settings::get_wav(22));
		flags[8] = true; //Don't turn this on uuntill level 1
		flags[5] = false;
		player_lives = settings::get_lives();
		bullets.clear();
		direction.clear();
		int rand = settings::get_prob(0, 2);
		if (rand == 0)
		{
			direction.push_back(1);
		}
		else
		{
			direction.push_back(-1);
		}
		//Set up boss 1
		ships[1].change_texture(32);
		ships[1].change_size(8 * col, 4 * row);
		ships[1].change_pos(5 * col, 12 * row);
		ships[1].change_ang(0);
	}

	if (level == 3 && boss_lives == 0 && player_lives > 0)
	{
		//Load animation
		frames explosion(25 * col, 25 * row, ships[1].get_x_pos(), 5 * row);
		animation.push_back(explosion);
		//Update level, boss health and flags
		level++;
		boss_lives = 1000;
		flags[11] = false;
		flags[13] = false;
		player_lives = settings::get_lives() + 1;
		//Clear bullets and direction
		bullets.clear();
		direction.clear();
		int rand = settings::get_prob(0, 2);
		if (rand == 0)
		{
			direction.push_back(1);
		}
		else
		{
			direction.push_back(-1);
		}
		//Set up sound
		slSoundStopAll();
		slSoundPlay(settings::get_wav(3));
		slSoundPlay(settings::get_wav(8));
		slSoundLoop(settings::get_wav(20));
		//Set up boss 3
		ships[1].change_texture(28);
		ships[1].change_size(3 * col, 4 * row);
		ships[1].change_pos(5 * col, 11 * row);
		ships[1].change_ang(0);
	}
	if (level == 4 && boss_lives == 0 && player_lives > 0)
	{
		//Load animation
		frames explosion(25 * col, 25 * row, ships[1].get_x_pos(), 5 * row);
		animation.push_back(explosion);
		//Update level, boss health and flags
		level++;
		boss_lives = 50;
		flags[11] = false;
		flags[13] = false;
		flags[5] = true;
		player_lives = settings::get_lives() + 1;
		//Clear bullets and direction
		bullets.clear();
		direction.clear();
		int rand = settings::get_prob(0, 2);
		if (rand == 0)
		{
			direction.push_back(1);
		}
		else
		{
			direction.push_back(-1);
		}
		//Set up sound
		slSoundPlay(settings::get_wav(3));
		slSoundPlay(settings::get_wav(10));
		//Set up boss 4
		ships[1].change_texture(28);
		ships[1].change_size(3 * col, 4 * row);
		ships[1].change_pos(5 * col, 14 * row);
		ships[1].change_ang(0);
	}
}
