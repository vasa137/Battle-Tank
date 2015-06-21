#include "tank.h"

void alloc_tank(){
	List *novi;
	int i, j;
	novi = (List*)malloc(sizeof(List));
	novi->next = NULL;
	if (lst->first == NULL){
		lst->first = novi;
		lst->first->tankAll.tank.position.y = 38;
		lst->first->tankAll.tank.position.x = 24;
	}
	else{
		lst->last->next = novi;
		novi->tankAll.tank.position.y = 4;
		novi->tankAll.tank.position.x = 62;
	}
	lst->last = novi;
	lst->n++;
	novi->tankAll.tank.position.last_move = 1;
	novi->tankAll.tank.position.barrel = 1;
	novi->tankAll.projectile.projectPhase = 0;
	novi->tankAll.tank.tankDesign_v = special_tank_v;
	novi->tankAll.tank.tankDesign_h = special_tank_h;
	novi->tankAll.projectile.last_object = ' ';
	for(i=0; i<3; i++)
		for (j=0; j<3; j++) novi->tankAll.tank.visit_grass[i][j]=0;
	create_tank(novi->tankAll.tank.position.barrel, novi->tankAll);
}

void free_tank(List *curr){
	List *temp=lst->first,*prev=NULL;
	while(temp!=curr){
		prev=temp;
		temp=temp->next;
	}
	if(!prev) lst->first=curr->next;
	else prev->next=curr->next;
	if(curr==lst->last) lst->last=prev;
	delete_tank(curr->tankAll.tank.position.y,curr->tankAll.tank.position.x);
	free(curr);
	lst->n--;
}

void move_tank(int y, int x, int mov){
	switch (mov){
	case KEY_UP:    delete_tank(y + 1, x);  create_tank(1, lst->curr->tankAll);  break;
	case KEY_LEFT:  delete_tank(y, x + 1);  create_tank(2, lst->curr->tankAll);  break;
	case KEY_RIGHT: delete_tank(y, x - 1);  create_tank(3, lst->curr->tankAll);  break;
	case KEY_DOWN:  delete_tank(y - 1, x);  create_tank(4, lst->curr->tankAll);  break;
	}
}

int can_move(int y, int x, int barrel) {
	switch (barrel)
	{
	case 1: case 4: 
		if (((matrix[y - y1b][x - x1b - 1] == ' ') || (matrix[y - y1b][x - x1b - 1] == 'g')) && 
		((matrix[y - y1b][x - x1b] == ' ') || (matrix[y - y1b][x - x1b] == 'g')) && 
		((matrix[y - y1b][x - x1b + 1] == ' ') || (matrix[y - y1b][x - x1b + 1] == 'g'))) return 1; else return 0;

	case 2: case 3: 
		if (((matrix[y - y1b - 1][x - x1b] == ' ') || (matrix[y - y1b - 1][x - x1b] == 'g')) && 
		((matrix[y - y1b][x - x1b] == ' ') || (matrix[y - y1b][x - x1b] == 'g')) && 
		((matrix[y - y1b + 1][x - x1b] == ' ') || (matrix[y - y1b + 1][x - x1b] == 'g'))) return 1; else return 0;
	}
}

void action(int keyPressed){
	switch (keyPressed)
	{
	case KEY_UP:    lst->first->tankAll.tank.position.last_move = 1; 
					if (can_move(lst->first->tankAll.tank.position.y - 2, lst->first->tankAll.tank.position.x, 1)) move_tank(--lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x, KEY_UP);
					else { delete_tank(lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x);  create_tank(1, lst->curr->tankAll); } refresh(); break;

	case KEY_LEFT:  lst->first->tankAll.tank.position.last_move = 2; 
					if (can_move(lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x - 2, 2)) move_tank(lst->first->tankAll.tank.position.y, --lst->first->tankAll.tank.position.x, KEY_LEFT);
					else { delete_tank(lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x);  create_tank(2, lst->curr->tankAll); } refresh(); break;

	case KEY_RIGHT: lst->first->tankAll.tank.position.last_move = 3; 
					if (can_move(lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x + 2, 3)) move_tank(lst->first->tankAll.tank.position.y, ++lst->first->tankAll.tank.position.x, KEY_RIGHT);
					else { delete_tank(lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x);  create_tank(3, lst->curr->tankAll); } refresh(); break;

	case KEY_DOWN:  lst->first->tankAll.tank.position.last_move = 4; 
					if (can_move(lst->first->tankAll.tank.position.y + 2, lst->first->tankAll.tank.position.x, 4)) move_tank(++lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x, KEY_DOWN);
					else { delete_tank(lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x);  create_tank(4, lst->curr->tankAll); } refresh(); break;

	case ' ':       if (!(lst->first->tankAll.projectile.projectPhase)) { lst->first->tankAll.projectile.position.projectil_dir = lst->first->tankAll.tank.position.last_move ;  lst->first->tankAll.projectile.projectPhase = 1; } break;
	}
}
