#include "tank.h"




void custom_map(char* mapz)
{
	int i, rez;
	int br, phase = 1, lastKey = 5;
	long int random_element_gen = 0;
	unsigned long int random_pup_gen = 0;
	unsigned short mm = 0, pp = 0;
	clock_t start_lvl_time = clock(), pw_shield_start, pw_clock_start, pw_shovel_start;
	Levels tank_struct;
	br = 0;
	lst->first = NULL;
	lst->curr = NULL;
	lst->last = NULL;
	lst->n = 0;
	Plst->first = NULL;
	Plst->last = NULL;
	init_powerups();
	create_map(mapz);
	tank_struct.kind = -1;
	tank_struct.smart = 0;
	LVL = 0;
	print_border_side_menu(2, x1m, 25, x2m, 3); // bots left.
	print_bots_left(); // saljes tezinu izabranu u podesavanjima( Easy-0 medium-1 hard-2) LVL(koji je nivo).  NOVO!
	print_border_side_menu(47, x1m + 20, 56, x2m, 4);// high score counter. // changed coordinates-Andrija // sve spusteno za 21
	print_border_side_menu(58, x1m, 67, x2m, 4); // pw disclaimer.
	print_menu_pups(61);
	alloc_tank(0, tank_struct);
	while (1){
		time_now();
		print_high_score();
		random_element_gen++;
		if (random_element_gen == 280000) random_element_gen = 0, rand_gen();
		execute_powerups(&pw_shield_start, &pw_clock_start, &pw_shovel_start, &random_pup_gen);
		should_spawn_bot(&start_lvl_time, &rez, &br, LVL);
		if (_kbhit())
			execute_our_tank(&mm, &pp, &phase, &lastKey, start_lvl_time, br, 0);
		if (lst->n == 1 && br >= botsInLevel[BOT_DIF][LVL]) { 
			//Sleep(2000); 
			clear();
			free_tank(lst->first);
			delete_powerup_list();
			demo_mode();
		return;
		}
		execute_bots(1);
		if ((!powerup.life) || (!strcmp(map_name, "gameover.map")))
		{
			clear();
			delete_tank_list();
			delete_powerup_list();
			demo_mode();
			return;
		}
	}
}

