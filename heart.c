#include "tank.h"

void start_level(clock_t *start_lvl_time, int *l, int *br, unsigned long int *random_pup_gen,long int* random_element_gen){
	char lvlprint[31];
	char lvl_num[3];
	*random_pup_gen=0;
	* random_element_gen=0;
	strcpy(lvlprint, "level");
	sprintf(lvl_num, "%d", *l + 1);
	strcat(lvlprint, lvl_num);
	strcat(lvlprint, ".lvl");
	strcpy(map_name, lvlprint);
	create_map(map_name);
	Sleep(3000);
	init_powerups();
	*start_lvl_time = clock();
	*br = 0;
	lst->first = NULL;
	lst->curr = NULL;
	lst->last = NULL;
	strcpy(map_name, "putIN.dat");
	create_map(map_name);
	alloc_tank(0);
}

void fire_rate_assessment(int keyPressed){
	int j;
	if (stars() == 2){
		for (pridx = 0; pridx < 4; pridx = pridx + 2){
			if ((!(lst->first->tankAll.projectile[pridx].phase))) { action(keyPressed, &lst->first->tankAll); break; }
		}
	}
	else if (stars() == 4){
		for (j = 0; j < 4; j = j + 2)
			if ((!(lst->first->tankAll.projectile[j].phase)) && (!(lst->first->tankAll.projectile[j + 1].phase))){
				for (pridx = j; pridx < j + 2; pridx = pridx++) { action(keyPressed, &lst->first->tankAll); }
				break;
			}
	}
	else { pridx = 0; if ((!(lst->first->tankAll.projectile[pridx].phase))) action(keyPressed, &lst->first->tankAll); }
}

void execute_our_tank(){
	int keyPressed;
	keyPressed = getch();
	lst->curr = lst->first;
	if (keyPressed == ' '){
		fire_rate_assessment(keyPressed); // for different powerup stars.
	}
	else action(keyPressed, &lst->first->tankAll);
}

void execute_bots(){
	int i;

	for (i = 0, lst->curr = lst->first; i < lst->n; i++, lst->curr = lst->curr->next){
		if (i != 0){
			pridx = 0; // vodi racuna da ne bi slao bilo koji pridx!
			medium_bot();
			if (lst->curr->tankAll.projectile[0].phase) projectile(lst->curr->tankAll.tank.position.y,
				lst->curr->tankAll.tank.position.x, lst->curr->tankAll.projectile[0].position.projectil_dir);
		}
		else{
			for (pridx = 0; pridx < 4; pridx++)
				if (lst->curr->tankAll.projectile[pridx].phase) projectile(lst->curr->tankAll.tank.position.y,
					lst->curr->tankAll.tank.position.x, lst->curr->tankAll.projectile[pridx].position.projectil_dir);
		}
	}
}

void demo_mode(){
	lst = (Lst*)malloc(sizeof(Lst));
	lst->first = NULL;
	lst->curr = NULL;
	lst->last = NULL;
	lst->n = 0;
	alloc_tank(0);
	lst->curr = lst->first; // ovo mora posle alokacije
}

void should_spawn_bot(clock_t *start_lvl_time, int *rez, int *br, int l, Levels *level[]){
	if (*br < lvl[l] && (((*rez = free_place(0)) && (((clock() - *start_lvl_time) * 1000 / CLOCKS_PER_SEC)>level[l][*br].time * 1000)) || (lst->n == 1))){

		pridx = 0;
		alloc_tank(*rez); (*br)++;
	}
}
