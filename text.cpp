//Adding header file
#include "text.h"


//Intializing static variables
int text::tracer = -1;
vector<int> text::path;


//Defining constructer
text::text(const char* text_words, int font, int text_size, double xcor, double ycor)
	:x(xcor), y(ycor), size(text_size), words(text_words), align('L')
{
	r = g = b = 0.8;
	a = 1;
	if (font - 1 <= tracer && font > 0)
	{
		index = font - 1;
	}

}

//Defining font_path function
void text::add_font(const char* font_path)
{
	path.push_back(slLoadFont(font_path));
	tracer++;
}

//Defining font_creator
void text::text_creator(double x_axis, double y_axis, double angle)
{
	x_pos = x_axis;
	y_pos = y_axis;
	slPush();
	slTranslate(x_pos, y_pos);
	slRotate(angle);
	slSetFont(path[index], size);
	slSetForeColor(r, g, b, a);
	change_align(align);
	slText(x, y, words);
	slPop();
}

//Defining function to change text position
void text::change_pos(double new_xcor, double new_ycor)
{
	x = new_xcor;
	y = new_ycor;
}

//Defining function to change text size
void text::change_size(int new_text_size)
{
	size = new_text_size;
}

//Defining function to change text font
void text::change_font(int new_font)
{
	if (new_font - 1 <= tracer && new_font > 0)
	{
		index = new_font - 1;
	}
}

//Defining function to chage text itself
void text::change_text(const char* new_text_words)
{
	words = new_text_words;
}

//Defining function to change text align location
void text::change_align(char new_align)
{
	align = new_align;
	switch (align)
	{
	case 'L':
		slSetTextAlign(SL_ALIGN_LEFT);
		break;
	case 'R':
		slSetTextAlign(SL_ALIGN_RIGHT);
		break;
	case 'C':
		slSetTextAlign(SL_ALIGN_CENTER);
		break;
	}
}

//Function to change color
void text::change_color(double red, double green, double blue, double alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}
