#include "tank.h"

void print_brick_lvl(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_PAIR(3));
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_PLUS);
	}
	attroff(A_BOLD | COLOR_PAIR(3));
}

void print_grass_lvl(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_PAIR(2));
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_BOARD);
	}
	attroff(COLOR_PAIR(2));
}

void print_water_lvl(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_PAIR(12));
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_BOARD);
	}
	attroff(COLOR_PAIR(12));
}

void print_blanko_lvl(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_PAIR(6));
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ' ');
	}
	attroff(COLOR_PAIR(6));
}

void what_to_print(int yu, int xu, int yd, int xd, chtype k){
	switch (k){
	case 'b': print_brick_lvl(yu, xu, yd, xd); break;
	case 'w': print_water_lvl(yu, xu, yd, xd); break;
	case 'g': print_grass_lvl(yu, xu, yd, xd); break;
	default: print_blanko_lvl(yu, xu, yd, xd); break;
	}
}

void print_matrix(){
	int i, j;
	for (i = 3; i < (dimx + 2); i++)
		for (j = 3; j < (dimy + 2); j++){
		what_to_print(i, j, i, j, lvl_matrix[i-3][j-3]);
		}
	refresh();
}
