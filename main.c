#include "tank.h"

Lst *lst;

char meni[][dimx] = { " New Game ", " Load Game ", " Settings ", " Map Editor ", " Play Custom map", " High Scores ", " Exit " };

char map_name[50] = "dobraje.txt";

chtype matrix[dimx + 1][dimy + 1];                         // velicina mape

chtype element = 'b';

int top[]    = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int left[]   = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
int right[]  = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int bottom[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

TankDesign special_tank_v[] = { { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_BULLET, 5 }, { ACS_VLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_HLINE, 4 }, { ACS_DIAMOND, 4 } };
TankDesign special_tank_h[] = { { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_BULLET, 5 }, { ACS_HLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_VLINE, 4 }, { ACS_DIAMOND, 4 } };
TankDesign normal_tank_v[]  = { { 126, 6 }, { ACS_VLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };
TankDesign normal_tank_h[]  = { { 126, 6 }, { ACS_HLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };

void main(){ // Da sredimo main kasnije.
	struct timeb vreme;
	int keyPressed, i;
	lst = (Lst*)malloc(sizeof(Lst));
	lst->first = NULL;
	lst->curr = NULL;
	lst->last = NULL;
	lst->n = 0;
	init_curses();
	create_map();
	alloc_tank();
	lst->curr = lst->first; // ovo mora posle alokacije
	main_menu(1);
	for (i = 0, lst->curr = lst->first; i < lst->n; i++, lst->curr = lst->curr->next)  
		free_tank(lst->curr);
	alloc_tank();
	alloc_tank();
	while (1){
		time_now();
		if (_kbhit())
		{
			keyPressed = getch();
			lst->curr = lst->first;
			action(keyPressed, &lst->first->tankAll);
		}
		for (i = 0, lst->curr = lst->first; i < lst->n; i++, lst->curr = lst->curr->next){
			if (i != 0) easy_bot();
			if (lst->curr->tankAll.projectile.phase) projectile(lst->curr->tankAll.tank.position.y,
				lst->curr->tankAll.tank.position.x, lst->curr->tankAll.projectile.position.projectil_dir);
		}
	}
}
