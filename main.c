#include "tank.h"

chtype matrix[dimx + 1][dimy + 1];                         // velicina mape

int top[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int left[] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
int right[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int bottom[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

int visit_grass[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

tank special_tank_v[] = { { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_BULLET, 5 }, { ACS_VLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_HLINE, 4 }, { ACS_DIAMOND, 4 } };
tank special_tank_h[] = { { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_BULLET, 5 }, { ACS_HLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_VLINE, 4 }, { ACS_DIAMOND, 4 } };

tank normal_tank_v[] = { { 126, 6 }, { ACS_VLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };
tank normal_tank_h[] = { { 126, 6 }, { ACS_HLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };



void main(){
	unsigned short mm, pp;
	struct timeb vreme;
	char last_object = ' ';
	int y = 4, x = 4, check = 0, keyPressed, last_move, projectil_dir, px, py; // f- da li postoji projektil
	char map_name[50] = "map.txt";
	init_curses();
	create_map(map_name);
	create_tank(y, x, 1, special_tank_v);
	last_move = 1; //zato sto tenk stvaramo uspravno
	while (1){
		time_now();
		if (_kbhit())
		{
			keyPressed = getch();
			action(&y, &x, special_tank_v, special_tank_h, keyPressed, &check, &last_move, &projectil_dir);
		}
		if (check) projectile(&py, &px, y, x, projectil_dir, &mm, &pp, &check, &last_object);
	}
}
