#include "tank.h"

void main(){ // Da sredimo main kasnije.
	int i, rez;
	int br, phase = 1, lastKey = 5;
	long int random_element_gen;
	unsigned long int random_pup_gen;
	unsigned short mm = 0, pp = 0;
	clock_t start_lvl_time, pw_shield_start, pw_clock_start, pw_shovel_start;
	Plst = (Poweruplst*)malloc(sizeof(Poweruplst));
	Plst->first = Plst->last = NULL;
	lst = (Lst*)malloc(sizeof(Lst));
	init_curses();
	link_levels();
	while (1){
		demo_mode();
		refresh();
		main_menu(1);
		delete_tank_list();
		for (LVL = 0; LVL<10; LVL++){ // Begin.
			start_level(&start_lvl_time, &LVL, &br, &random_pup_gen, &random_element_gen);
			while (1){
				time_now();
				print_high_score();
				random_element_gen++;
				if (random_element_gen == 280000) random_element_gen = 0, rand_gen();
				execute_powerups(&pw_shield_start, &pw_clock_start, &pw_shovel_start, &random_pup_gen);
				should_spawn_bot(&start_lvl_time, &rez, &br, LVL);
				if (_kbhit())
					execute_our_tank(&mm, &pp, &phase, &lastKey);
				execute_bots();
				if ((!powerup.life) || (!strcmp(map_name, "gameover.map"))) break;
				if (lst->n == 1 && br >= botsInLevel[BOT_DIF][LVL]) { print_high_score(); Sleep(2000); free_tank(lst->first); break; }
			}
			delete_tank_list();
			delete_powerup_list();
			if (!strcmp(map_name, "gameover.map")) break;
		}
		delete_menu(2, x1m, 25, x2m);
		delete_menu(27, x1m + 20, 36, x2m);
		delete_menu(58, x1m, 67, x2m);
	}
	free(lst);
	free(Plst);
}
