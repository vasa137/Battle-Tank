#include "tank.h"

void init_powerups(){
	powerup.life = 1;
	powerup.bomb = 0;
	powerup.star = 2;
	powerup.clock = 0;
	powerup.shovel = 0;
	powerup.shield = 0;
}

void update_powerups(char pw){
	switch (pw){
	case 'l': powerup.life++;		break;
	case 'q': powerup.bomb = 1;		break;
	case 's': powerup.star++;		break;
	case 'a': powerup.clock = 1;	break;
	case 'y': powerup.shovel = 1;	break;
	case 'x': powerup.shield = 1;	break;
	}
}

int check_powerups(int y, int x, int a){
	int i;
	switch (a){
	case 1:
		for (i = 0; i < 6; i++){
			if ((matrix[y - y1b - 2][x - x1b - 1] == pUps[i]) || (matrix[y - y1b - 2][x - x1b] == pUps[i]) || (matrix[y - y1b - 2][x - x1b + 1] == pUps[i])){
				update_powerups(pUps[i]);
				// negde da ubacimo brisanje powerupa.
				return 1;
			}
		} return 0;
	case 2:
		for (i = 0; i < 6; i++){
			if ((matrix[y - y1b - 1][x - x1b - 2] == pUps[i]) || (matrix[y - y1b][x - x1b - 2] == pUps[i]) || (matrix[y - y1b + 1][x - x1b - 2] == pUps[i])){
				update_powerups(pUps[i]);
				// negde da ubacimo brisanje powerupa.
				return 1;
			}
		} return 0;
	case 3:
		for (i = 0; i < 6; i++){
			if ((matrix[y - y1b - 1][x - x1b + 2] == pUps[i]) || (matrix[y - y1b][x - x1b + 2] == pUps[i]) || (matrix[y - y1b + 1][x - x1b + 2] == pUps[i])){
				update_powerups(pUps[i]);
				// negde da ubacimo brisanje powerupa.
				return 1;
			}
		} return 0;
	case 4:
		for (i = 0; i < 6; i++){
			if ((matrix[y - y1b + 2][x - x1b - 1] == pUps[i]) || (matrix[y - y1b + 2][x - x1b] == pUps[i]) || (matrix[y - y1b + 2][x - x1b + 1] == pUps[i])){
				update_powerups(pUps[i]);
				// negde da ubacimo brisanje powerupa.
				return 1;
			}
		} return 0;
	}
}

void execute_powerups(clock_t *pw_shield_start, clock_t *pw_clock_start, clock_t *pw_shovel_start, unsigned long int*random_pup_gen){
	int i, j, check, x, y;
	List *current, *temp;
	random_pup_gen++;
	if (*random_pup_gen == 777000) *random_pup_gen = 0, rand_pup_gen();
	if (powerup.bomb){
		for (current = lst->first->next; current != NULL;){
			check = 0;
			for (i = 0; i < 3; i++) // proverava da li je u travi.
				for (j = 0; j < 3; j++)
					if (current->tankAll.tank.visit_grass[i][j])
					{
						check = 1; break;
					}
			if (!check){
				temp = current;
				current = current->next;
				free_tank(temp);
			}// ako nije u travi brise ga.
			else current = current->next;
		}
		powerup.bomb = 0;
	}

	if (powerup.clock){ // if unutar delay-a za botove, ali to cu promeniti kad dodju normalni.
		if (powerup.clock == 1){
			*pw_clock_start = clock();
			powerup.clock = 2;
			for (current = lst->first->next; current != NULL; current = current->next)
				current->tankAll.tank.phase = 5;
		}
		if (((clock() - *pw_clock_start) * 1000 / CLOCKS_PER_SEC) > PW_DURATION){ //  konstanta! PW_DURATION
			for (current = lst->first->next; current != NULL; current = current->next)
				current->tankAll.tank.phase = 2;
			powerup.clock = 0;
		}
	}

	if (powerup.shovel){ // ===========
		if (powerup.shovel == 1){
			*pw_clock_start = clock();
			x = 41;
			for (y = 62; y < 67; y++) print_wall(y, x);
			x = 49;
			for (y = 62; y < 67; y++) print_wall(y, x);
			y = 62;
			for (x = 41; x < 50; x++) print_wall(y, x);

			powerup.shovel = 2;
		}
		if (((clock() - *pw_shovel_start) * 1000 / CLOCKS_PER_SEC) > PW_DURATION){ // konstanta! PW_DURATION
			x = 41;
			for (y = 62; y < 67; y++) print_head(y, x);
			x = 49;
			for (y = 62; y < 67; y++) print_head(y, x);
			y = 62;
			for (x = 41; x < 50; x++) print_head(y, x);
			powerup.shovel = 0;
		}
	}

	if (powerup.shield){ // imam if u funkciji collision: if (!((temp == lst->first) && powerup.shield)) free_tank(temp);
		if (powerup.shield == 1){
			*pw_shield_start = clock();
			powerup.shield = 2;
		}
		if (((clock() - *pw_shield_start) * 1000 / CLOCKS_PER_SEC) > PW_DURATION){//  konstanta! PW_DURATION
			powerup.shield = 0;
		}
	}
}

int stars()
{
	switch (powerup.star){
	case 0: return 1;
	case 1: return 2;
	case 2: case 3: return 4;
	}
}
