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
	level[0] = Level1_e;
	level[1] = Level2_e;
	level[2] = Level3_e;
	init_curses();
	while(1){
		demo_mode();
		refresh();
		main_menu(1);
		delete_tank_list();
		for (l = 0; l<10; l++){ // Begin.
			start_level(&start_lvl_time, &l, &br, &random_pup_gen, &random_element_gen);
			while (1){
				random_element_gen++; 
				if (random_element_gen == 280000) random_element_gen = 0,rand_gen();
				execute_powerups(&pw_shield_start, &pw_clock_start, &pw_shovel_start, &random_pup_gen);
				should_spawn_bot(&start_lvl_time, &rez, &br, l, level);
				if (_kbhit())	execute_our_tank();
				execute_bots();
				if( (!powerup.life) || (!strcmp(map_name,"gameover.map"))) break;
				if (lst->n == 1 && br >= lvl[l]) { _sleep(2000); free_tank(lst->first); break; }
			}
			delete_tank_list();
			delete_powerup_list();
			if(!strcmp(map_name,"gameover.map")) break;
		}
	}
}
