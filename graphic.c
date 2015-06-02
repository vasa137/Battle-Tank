#include "tank.h"

extern chtype matrix[dimx + 1][dimy + 1];                         // velicina mape

extern int top[];
extern int left[];
extern int right[];
extern int bottom[];

extern int visit_grass[3][3];

extern tank special_tank_v[];
extern tank special_tank_h[];
extern tank normal_tank_v[];
extern tank normal_tank_h[];


void init_colors(){
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_GREEN);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_YELLOW);
	init_pair(10, COLOR_WHITE, COLOR_BLUE);
	init_pair(11, COLOR_YELLOW, COLOR_BLUE);
	init_pair(12, COLOR_CYAN, COLOR_BLUE);
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
	if (matrix[y - 1 - 2][x - 1 - 2] == 'g') visit_grass[0][0] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[0]].paint));
		mvaddch(y - 1, x - 1, tank_type[position[0]].ch);
	}
	matrix[y - 1 - 2][x - 1 - 2] = 't';

	if (matrix[y - 1 - 2][x - 2] == 'g')	visit_grass[0][1] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[1]].paint));
		mvaddch(y - 1, x, tank_type[position[1]].ch);
	}
	matrix[y - 1 - 2][x - 2] = 't';

	if (matrix[y - 1 - 2][x + 1 - 2] == 'g') visit_grass[0][2] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[2]].paint));
		mvaddch(y - 1, x + 1, tank_type[position[2]].ch);
	}
	matrix[y - 1 - 2][x + 1 - 2] = 't';

	if (matrix[y - 2][x - 1 - 2] == 'g')	visit_grass[1][0] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[3]].paint));
		mvaddch(y, x - 1, tank_type[position[3]].ch);
	}
	matrix[y - 2][x - 1 - 2] = 't';

	if (matrix[y - 2][x - 2] == 'g')		visit_grass[1][1] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[4]].paint));
		mvaddch(y, x, tank_type[position[4]].ch);
	}
	matrix[y - 2][x - 2] = 't';

	if (matrix[y - 2][x + 1 - 2] == 'g')	visit_grass[1][2] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[5]].paint));
		mvaddch(y, x + 1, tank_type[position[5]].ch);
	}
	matrix[y - 2][x + 1 - 2] = 't';

	if (matrix[y + 1 - 2][x - 1 - 2] == 'g') visit_grass[2][0] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[6]].paint));
		mvaddch(y + 1, x - 1, tank_type[position[6]].ch);
	}
	matrix[y + 1 - 2][x - 1 - 2] = 't';

	if (matrix[y + 1 - 2][x - 2] == 'g')	visit_grass[2][1] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[7]].paint));
		mvaddch(y + 1, x, tank_type[position[7]].ch);
	}
	matrix[y + 1 - 2][x - 2] = 't';

	if (matrix[y + 1 - 2][x + 1 - 2] == 'g') visit_grass[2][2] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[8]].paint));
		mvaddch(y + 1, x + 1, tank_type[position[8]].ch);
	}
	matrix[y + 1 - 2][x + 1 - 2] = 't';
	refresh();
}

void print_brick(int y, int x){
	attron(COLOR_PAIR(3));
	mvaddch(y, x, ACS_PLUS);
	attroff(A_BOLD);
	matrix[y - y1][x - x1] = 'b';
}

void print_grass(int y, int x){
	attron(COLOR_PAIR(2));
	mvaddch(y, x, ACS_BOARD);
	matrix[y - y1][x - x1] = 'g';
}

void print_water(int y, int x){
	attron(COLOR_PAIR(12));
	mvaddch(y, x, ACS_BOARD);
	matrix[y - y1][x - x1] = 'w';
}

void print_blanko(int y, int x){
	attron(COLOR_PAIR(6));
	mvaddch(y, x, ' ');
	matrix[y - y1][x - x1] = ' ';
}

void print_object(int y, int x, int c){
	switch (c)
	{
	case 'b': print_brick(y, x); break;
	case 'w': print_water(y, x); break;
	case 'g': print_grass(y, x); break;
	default:  print_blanko(y, x); break;
	}
}

void print_border()
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

		matrix[i - 3][0] = 'e';
		matrix[i - 2][dimy] = 'e';
	}

	for (i = x1 + 1; i<x2; i++)
	{
		mvaddch(y1, i, ACS_HLINE);
		mvaddch(y2, i, ACS_HLINE);

		matrix[0][i - 3] = 'e';
		matrix[dimx][i - 3] = 'e';
	}
	refresh();
}

void create_map(char map_name[])
{
	FILE *map;
	int c;
	int y = y1 + 1, x = x1 + 1;

	map = fopen(map_name, "r");

	print_border();  //okvir

	while ((c = fgetc(map)) != EOF)
	{
		if (c == '\n') continue;
		if (c != '/')
		{
			if (c == '.') c = ' ';
			print_object(y, x, c);
			x++;
			refresh();
		}
		else {
			y++;
			x = x1 + 1;
		}
	}
}
