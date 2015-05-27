#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "conio.h"
#include <curses.h>


#define dimx 65
#define dimy 90

typedef struct Tank{ chtype ch; int paint; } tank;

chtype matrix[dimx+1][dimy+1];                         // velicina mape

int top[]    = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int left[]   = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
int right[]  = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int bottom[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

tank special_tank_v[] = { { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_BULLET, 5 }, { ACS_VLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_HLINE, 4 }, { ACS_DIAMOND, 4 } };
tank special_tank_h[] = { { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_BULLET, 5 }, { ACS_HLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_VLINE, 4 }, { ACS_DIAMOND, 4 } };

tank normal_tank_v[] = { { 126, 6 }, { ACS_VLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };
tank normal_tank_h[] = { { 126, 6 }, { ACS_HLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };

void init_colors(){
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_GREEN);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_YELLOW);
	init_pair(10, COLOR_WHITE, COLOR_BLUE);
}

void init_curses(){
	initscr();
	init_colors();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	resize_term(70, 150);
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

void create_tank(int y, int x, int barrel, tank* tank_type)
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
	matrix[y - 1 - 2][x - 1 - 2]='.';

	mvaddch(y - 1, x, ' ');
	matrix[y - 1 - 2][x - 2]='.';

	mvaddch(y - 1, x + 1, ' ');
	matrix[y - 1 - 2][x + 1 - 2]='.';

	mvaddch(y, x - 1, ' ');
	matrix[y - 2][x - 1 - 2]='.';

	mvaddch(y, x, ' ');
	matrix[y - 2][x - 2]='.';

	mvaddch(y, x + 1, ' ');
	matrix[y - 2][x + 1- 2]='.';

	mvaddch(y + 1, x - 1, ' ');
	matrix[y + 1 - 2][x - 1 - 2]='.';

	mvaddch(y + 1, x, ' ');
	matrix[y + 1 - 2][x - 2]='.';

	mvaddch(y + 1, x + 1, ' ');
	matrix[y + 1 - 2][x + 1 - 2]='.';
	refresh();
}

void move_tank(int y, int x, int mov, tank* ver, tank* hor){
	switch (mov){
	case KEY_UP:    delete_tank(y + 1, x);  create_tank(y, x, 1, ver);  break;
	case KEY_LEFT:  delete_tank(y, x + 1);  create_tank(y, x, 2, hor);  break;
	case KEY_RIGHT: delete_tank(y, x - 1);  create_tank(y, x, 3, hor);  break;
	case KEY_DOWN:  delete_tank(y - 1, x);  create_tank(y, x, 4, ver);  break;
	}
}

void start_tank(int *y, int *x, tank* ver, tank* hor, int keyPressed){
	switch (keyPressed)
	{
	case KEY_UP:    if(can_move(*y-2,*x,1)) move_tank(--*y, *x, KEY_UP, ver, hor);    else create_tank(*y, *x, 1, ver); refresh(); break;
	case KEY_LEFT:  if(can_move(*y,*x-2,2)) move_tank(*y, --*x, KEY_LEFT, ver, hor);  else create_tank(*y, *x, 2, hor); refresh(); break;
	case KEY_RIGHT: if(can_move(*y,*x+2,3)) move_tank(*y, ++*x, KEY_RIGHT, ver, hor); else create_tank(*y, *x, 3, hor); refresh(); break;
	case KEY_DOWN:  if(can_move(*y+2,*x,4)) move_tank(++*y, *x, KEY_DOWN, ver, hor);  else create_tank(*y, *x, 4, ver); refresh(); break;
	}
}

void print_brick(){
	attron(COLOR_PAIR(9) | A_BOLD);
	addch(ACS_CKBOARD);
	attroff(A_BOLD);
}

void print_grass(){
	attron(COLOR_PAIR(2));
	addch('#');
}

void print_water(){
	attron(COLOR_PAIR(10));
	addch('~');
}

void print_blanko(){
	attron(COLOR_PAIR(6));
	addch(' ');
}

void print_object(int c){
	switch (c)
	{
	case 'b': print_brick(); break;
	case 'v': print_water(); break;
	case 'g': print_grass(); break;
	default:  print_blanko();break;
	}
}

void print_border(int y1, int x1, int y2, int x2)
{
	int i;
	attron(COLOR_PAIR(10)); // dodaj atribut za boju
	mvaddch(y1, x1, ACS_ULCORNER);
	mvaddch(y2, x1, ACS_LLCORNER);
	mvaddch(y1, x2, ACS_URCORNER);
	mvaddch(y2, x2, ACS_LRCORNER);

	matrix[0][0] = 'e';
	matrix[dimx][0] = 'e';
	matrix[0][dimy] = 'e';
	matrix[dimx][dimy] = 'e';
	for (i = y1 + 1; i<y2; i++)
	{
		mvaddch(i, x1, ACS_VLINE);
		mvaddch(i, x2, ACS_VLINE);

		matrix[i-3][0] = 'e';
		matrix[i-2][dimy] = 'e';
	}

	for (i = x1 + 1; i<x2; i++)
	{
		mvaddch(y1, i, ACS_HLINE);
		mvaddch(y2, i, ACS_HLINE);

		matrix[0][i-3] = 'e';
		matrix[dimx][i-3] = 'e';
	}
	refresh();
}

void create_map(char map_name[])
{
	FILE *map;
	int c;
	int xM, yM;
	int x1 = 2, y1 = 2, x2 = 67, y2 = 92, pom;
	pom = y1;                            //da ne izgubimo parametar za okvir kopiramo ga u pom
	yM = 1;
	xM = 1;
	map = fopen(map_name, "r");

	print_border(x1,y1,x2,y2); //okvir

	move(++pom, x1 + 1);
	while ((c=fgetc(map)) != EOF)
	{
		if(c=='\n') continue;
		if (c != '/')
		{
			matrix[xM][yM++] = c;
			print_object(c);
			refresh();
		}
		else {
			move(++pom, x1 + 1);
			xM++; yM = 1;
		}
	}
}

int can_move(int y,int x,int barrel){      
	switch(barrel)
	{
	case 1: case 4: if ( matrix[y-2][x-2-1]=='.' && matrix[y-2][x-2]=='.' && matrix[y-2][x-2+1]=='.') return 1; else return 0; 
	case 2: case 3: if ( matrix[y-2-1][x-2]=='.' && matrix[y-2][x-2]=='.' && matrix[y-2+1][x-2]=='.') return 1; else return 0;
	}
}

void main(){
	int x = 4, y = 4, keyPressed;
	char map_name[50] = "vasa.txt";
	init_curses();
	create_map(map_name);
	create_tank(y, x, 1, normal_tank_v);
	while (1){
			keyPressed=getch();
		  start_tank(&y, &x, special_tank_v, special_tank_h, keyPressed);
	}
}
