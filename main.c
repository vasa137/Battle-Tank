#include "tank.h"

void main(){ // Da sredimo main kasnije.
	int i, rez, l;
	int br;
	long int random_element_gen;
	unsigned long int random_pup_gen;
	clock_t start_lvl_time, pw_shield_start, pw_clock_start, pw_shovel_start;
	Levels *level[10];
	Levels **LEVEL[3];
	LEVEL[0] = level;
	level[0] = level1;
	level[1] = level2;
	level[2] = level3;
	init_curses();
	create_map(map_name);
	refresh();
	time_now();
	demo_mode();
	main_menu(1);
	for (i = 0, lst->curr = lst->first; i < lst->n; i++, lst->curr = lst->curr->next)
		free_tank(lst->curr);// demo mode off.

	for (l = 0; l<3; l++){ // Begin.
		start_level(&start_lvl_time, &l, &br, &random_pup_gen, &random_element_gen);
		while (1){
			random_element_gen++; 
			if (random_element_gen == 280000) random_element_gen = 0,rand_gen();
			execute_powerups(&pw_shield_start, &pw_clock_start, &pw_shovel_start, &random_pup_gen);
			should_spawn_bot(&start_lvl_time, &rez, &br, l, level);
			if (_kbhit())	execute_our_tank();
			execute_bots();
			if (lst->n == 1 && br >= lvl[l]) { free_tank(lst->first); break; }
		}
	}
}
