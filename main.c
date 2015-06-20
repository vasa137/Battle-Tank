#include "tank.h"

char meni[][dimx] = { " New Game ", " Load Game ", " Settings ", " Map Editor ", " Play Custom map" , " High Scores ", " Exit " };

char map_name[50] = "dobraje.txt"; 

chtype matrix[dimx + 1][dimy + 1];                         // velicina mape

chtype element = 'b';

Lst *lst;

int top[]    = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int left[]   = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
int right[]  = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int bottom[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

int visit_grass[3][3]={0,0,0,0,0,0,0,0,0};

TankDesign special_tank_v[] = { { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_BULLET, 5 }, { ACS_VLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_HLINE, 4 }, { ACS_DIAMOND, 4 } };
TankDesign special_tank_h[] = { { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_BULLET, 5 }, { ACS_HLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_VLINE, 4 }, { ACS_DIAMOND, 4 } };

TankDesign normal_tank_v[] = { { 126, 6 }, { ACS_VLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };
TankDesign normal_tank_h[] = { { 126, 6 }, { ACS_HLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };

void main(){
	unsigned short mm, pp;
	struct timeb vreme;
	char last_object=' ';
	int y = 24, x = 38, check = 0, keyPressed, last_move, projectil_dir, px, py; // f- da li postoji projektil
	int bot_barrel = 2, z = 4, t = 62, flag = 1, flag1 = 1, bot_barrel1 = 3;
	int z1 = 4, t1 = 50;
	clock_t start = clock();
    clock_t start1 = clock();
    clock_t end= clock();
    clock_t end1 = clock();
	lst->first = NULL;
	lst->last = NULL;
	init_curses();
	create_map(map_name);
	main_menu(1);
	alloc_tank();
	create_tank(y, x, 1, special_tank_v);
	last_move = 1; //zato sto tenk stvaramo uspravno
	while (1){
		time_now();
		if (_kbhit())
		{
			keyPressed = getch();
			action(&y, &x, special_tank_v, special_tank_h, keyPressed, &check, &last_move, &projectil_dir);
		}
		easy_bot(&start, &flag, &bot_barrel, &z, &t);
		//easy_bot(&start1, &flag1, &bot_barrel1, &z1, &t1);
		if (check) projectile(&py, &px, y, x, projectil_dir, &mm, &pp, &check, &last_object);
	}
}
