#include "tank.h"

void init_powerups(){
	powerup.life = 1;
	powerup.bomb = 0;
	powerup.star = 0;
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

void execute_powerups(){
	int i;
	List *current;
	if (powerup.bomb){
		for (current = lst->first->next; current != NULL; current = current->next)
			free_tank(current);
		powerup.bomb = 0;
	}

	if (powerup.clock){ // ostalo se obavlja u delay_s.
		for (current = lst->first->next; current != NULL; current = current->next)
			current->tankAll.tank.phase = 5;
	}

	if (powerup.shovel){
		// stampaj beton oko baze. 
	}
	// shield cemo namestiti kad namestimo skidanje zivota pogotkom.

}
