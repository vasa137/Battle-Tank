#include "tank.h"

Lst *lst;

char meni[][dimx] = { " New Game ", " Load Game ", " Settings ", " Map Editor ", " Play Custom map", " High Scores ", " Exit " };

char map_name[50] = "dobraje.txt";

chtype matrix[dimx + 1][dimy + 1];                         // velicina mape

chtype element = 'b';

Powerups powerup;

char pUps[6]={'x','l','s','q','a','y'};

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
	int keyPressed, i, rez, l;
	

	Levels *level[10];
	Levels level1[] = { { 0, 0, 1 }, { 1, 2, 1 }, { 0, 15, 1 }, { 1, 20, 1 }, { 0, 30, 1 } };
	Levels level2[] = { { 0, 0, 1 }, { 1, 2, 1 }, { 0, 15, 1 }, { 1, 20, 2 }, { 1, 30, 2 }, { 0, 35, 2 }, { 0, 37, 2 } };
	Levels level3[] = { { 0, 0, 1 }, { 1, 2, 2 }, { 1, 15, 2 }, { 1, 20, 2 }, { 1, 30, 3 }, { 0, 35, 3 }, { 0, 37, 3 } };
	clock_t start_level, ;
	int lvl[]={5,7,7}, br ;
	level[0] = level1;
	level[1] = level2;
	level[2] = level3;
	
	lst = (Lst*)malloc(sizeof(Lst));
	lst->first = NULL;
		lst->curr = NULL;
		lst->last = NULL;
	lst->n = 0;
	init_curses();
	create_map();
	refresh();
	alloc_tank(0);
	lst->curr = lst->first; // ovo mora posle alokacije
	main_menu(1);
	for (i = 0, lst->curr = lst->first; i < lst->n; i++, lst->curr = lst->curr->next)  
		free_tank(lst->curr);

	for(l=0; l<3;l++){
		start_level=clock();
		br=0;
		lst->first = NULL;
		lst->curr = NULL;
		lst->last = NULL;
		create_map();
		alloc_tank(0);
		while (1){
			time_now();
			if(br < lvl[l] && (( (rez=free_place(0)) && ( ((clock()-start_level)*1000/CLOCKS_PER_SEC)>level[l][br].time*1000 )) || (lst->n==1)) )
			{ alloc_tank(rez); br++;}
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
			if(lst->n==1 && br>=lvl[l]) { free_tank(lst->first);break;}
		}
	}
}
