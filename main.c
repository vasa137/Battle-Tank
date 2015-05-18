#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "curses.h"

typedef struct Tank{ chtype ch; int paint; } tank;

int top[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int left[] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
int right[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int bottom[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

tank special_tank_v[] = { { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_BULLET, 5 }, { ACS_VLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_HLINE, 4 }, { ACS_DIAMOND, 4 } };
tank special_tank_h[] = { { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_BULLET, 5 }, { ACS_HLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_VLINE, 4 }, { ACS_DIAMOND, 4 } };

tank normal_tank_v[] = { { , }, { ,  }, { ,  }, { , }, { , }, { , }, { , }, { , }, { , } }

void init_colors(){
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
}

void init_curses(){
	initscr();
	init_colors();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	resize_term(100, 100);
}

void print_tank(int y, int x, tank *tank_type, int *position)
{
	attron(COLOR_PAIR(tank_type[position[0]].paint));
	mvaddch(y - 1, x - 1, tank_type[position[0]].ch);
	refresh();
	attron(COLOR_PAIR(tank_type[position[1]].paint));
	mvaddch(y - 1, x, tank_type[position[1]].ch);
	refresh();
	attron(COLOR_PAIR(tank_type[position[2]].paint));
	mvaddch(y - 1, x + 1, tank_type[position[2]].ch);
	refresh();
	attron(COLOR_PAIR(tank_type[position[3]].paint));
	mvaddch(y, x - 1, tank_type[position[3]].ch);
	refresh();
	attron(COLOR_PAIR(tank_type[position[4]].paint));
	mvaddch(y, x, tank_type[position[4]].ch);
	refresh();
	attron(COLOR_PAIR(tank_type[position[5]].paint));
	mvaddch(y, x + 1, tank_type[position[5]].ch);
	refresh();
	attron(COLOR_PAIR(tank_type[position[6]].paint));
	mvaddch(y + 1, x - 1, tank_type[position[6]].ch);
	refresh();
	attron(COLOR_PAIR(tank_type[position[7]].paint));
	mvaddch(y + 1, x, tank_type[position[7]].ch);
	refresh();
	attron(COLOR_PAIR(tank_type[position[8]].paint));
	mvaddch(y + 1, x + 1, tank_type[position[8]].ch);
	refresh();
}

create_tank(int y, int x, int barrel, char* tank_type)
{
	switch (barrel)
	{
	case 1: print_tank(y, x, tank_type, top);
		break;
	case 2: print_tank(y, x, tank_type, left);
		break;
	case 3: print_tank(y, x, tank_type, right);
		break;
	case 4: print_tank(y, x, tank_type, bottom); 
		break;
	}
}

void delete_tank(int y, int x){
	attron(COLOR_PAIR(6));
	mvaddch(y - 1, x - 1, ' '); 
	mvaddch(y - 1, x, ' ');
	mvaddch(y - 1, x + 1, ' ');
	mvaddch(y, x - 1, ' ');
	mvaddch(y, x, ' ');
	mvaddch(y, x + 1, ' ');
	mvaddch(y + 1, x - 1, ' ');
	mvaddch(y + 1, x, ' ');
	mvaddch(y + 1, x + 1, ' ');
	refresh();

}

void move_tank(int y, int x, int mov, tank* ver, tank* hor){
	switch (mov){
	case KEY_UP: delete_tank(y + 1, x); create_tank(y, x, 1, ver); break;
	case KEY_LEFT: delete_tank(y, x + 1); create_tank(y, x, 2, hor); break;
	case KEY_RIGHT: delete_tank(y, x - 1); create_tank(y, x, 3, hor); break;
	case KEY_DOWN: delete_tank(y - 1, x); create_tank(y, x, 4, ver); break;
	}
}


void start_tank(tank* ver, tank* hor){
	int c, y=20, x=20;
	create_tank(y, x, 1,special_tank_v);
	while (1){
		switch (c = getch())
		{
		case KEY_UP:    move_tank(--y, x, KEY_UP, ver, hor); break;
		case KEY_LEFT:  move_tank(y, --x, KEY_LEFT, ver, hor); break;
		case KEY_RIGHT: move_tank(y, ++x, KEY_RIGHT, ver, hor); break;
		case KEY_DOWN:  move_tank(++y, x, KEY_DOWN, ver, hor); break;
		}
	}
}

void main(){
	init_curses();
	start_tank(special_tank_v, special_tank_h);
}
