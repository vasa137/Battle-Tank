#include "tank.h"

void alloc_tank(){
	List *novi;
	int i, j;
	novi = (List*)malloc(sizeof(List));
	novi->next = NULL;
	if (lst->first == NULL){
		lst->first = novi;
		lst->first->tankAll.tank.position.y = 38;// Pocetne koordinate za nas tenk, zameniti sa konstantama.
		lst->first->tankAll.tank.position.x = 24;
	}
	else{
		lst->last->next = novi;
		novi->tankAll.tank.position.y = 4;
		novi->tankAll.tank.position.x = 72;
	}
	lst->last = novi;
	lst->n++;
	novi->tankAll.tank.position.last_move = 4;
	novi->tankAll.tank.position.barrel = 4;
	novi->tankAll.tank.phase = 2;
	novi->tankAll.projectile.phase = 0;
	novi->tankAll.tank.tankDesign_v = special_tank_v;
	novi->tankAll.tank.tankDesign_h = special_tank_h;
	novi->tankAll.projectile.last_object = ' ';
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++) novi->tankAll.tank.visit_grass[i][j] = 0;
	create_tank(novi->tankAll.tank.position.barrel, novi->tankAll);
}

void free_tank(List *curr){
	List *temp = lst->first, *prev = NULL, *lstcurrcopy;
	while (temp != curr){
		prev = temp;
		temp = temp->next;
	}
	if (!prev) lst->first = curr->next;
	else prev->next = curr->next;
	if (curr == lst->last) lst->last = prev;
	lstcurrcopy=lst->curr; // da ne brise travu jer globalnim lst->curr brisemo a taj lst->curr je nas tenk, curr je tenk koji se brise
	lst->curr=curr;
	delete_tank(curr->tankAll.tank.position.y, curr->tankAll.tank.position.x);
	lst->curr=lstcurrcopy;
	free(curr);
	lst->n--;
}

void action(int keyPressed, TankAll *current){
	switch (keyPressed)
	{
	case KEY_UP: case 1:  current->tank.position.last_move = 1;
		if (can_move(current->tank.position.y, current->tank.position.x, 1))
			move_tank(--current->tank.position.y, current->tank.position.x, KEY_UP);
		else { delete_tank(current->tank.position.y, current->tank.position.x);  create_tank(1, *current); } refresh(); break;

	case KEY_LEFT: case 2: current->tank.position.last_move = 2;
		if (can_move(current->tank.position.y, current->tank.position.x, 2))
			move_tank(current->tank.position.y, --current->tank.position.x, KEY_LEFT);
		else { delete_tank(current->tank.position.y, current->tank.position.x);  create_tank(2, *current); } refresh(); break;

	case KEY_RIGHT: case 3: current->tank.position.last_move = 3;
		if (can_move(current->tank.position.y, current->tank.position.x, 3))
			move_tank(current->tank.position.y, ++current->tank.position.x, KEY_RIGHT);
		else { delete_tank(current->tank.position.y, current->tank.position.x);  create_tank(3, *current); } refresh(); break;

	case KEY_DOWN: case 4:  current->tank.position.last_move = 4;
		if (can_move(current->tank.position.y, current->tank.position.x, 4))
			move_tank(++current->tank.position.y, current->tank.position.x, KEY_DOWN);
		else { delete_tank(current->tank.position.y, current->tank.position.x);  create_tank(4, *current); } refresh(); break;

	case ' ':       if (!(current->projectile.phase)) {
		current->projectile.position.projectil_dir = current->tank.position.last_move;
		current->projectile.phase = 1;
	} break;
	}
}

int can_move(int y, int x, int barrel) {
	switch (barrel)
	{
	case 1: 
		if (((matrix[y - y1b - 2][x - x1b - 1] == ' ') || (matrix[y - y1b - 2][x - x1b - 1] == 'g')) &&
			((matrix[y - y1b - 2][x - x1b] == ' ') || (matrix[y - y1b - 2][x - x1b] == 'g')) &&
			((matrix[y - y1b - 2][x - x1b + 1] == ' ') || (matrix[y - y1b - 2][x - x1b + 1] == 'g'))) return 1; else return 0;
	case 2:
		if (((matrix[y - y1b - 1][x - x1b - 2] == ' ') || (matrix[y - y1b - 1][x - x1b - 2] == 'g')) &&
			((matrix[y - y1b][x - x1b - 2] == ' ') || (matrix[y - y1b][x - x1b - 2] == 'g')) &&
			((matrix[y - y1b + 1][x - x1b - 2] == ' ') || (matrix[y - y1b + 1][x - x1b - 2] == 'g'))) return 1; else return 0;
	case 3:
		if (((matrix[y - y1b - 1][x - x1b + 2] == ' ') || (matrix[y - y1b - 1][x - x1b + 2] == 'g')) &&
			((matrix[y - y1b][x - x1b + 2] == ' ') || (matrix[y - y1b][x - x1b + 2] == 'g')) &&
			((matrix[y - y1b + 1][x - x1b + 2] == ' ') || (matrix[y - y1b + 1][x - x1b + 2] == 'g'))) return 1; else return 0;
	
	case 4:
		if (((matrix[y - y1b + 2][x - x1b - 1] == ' ') || (matrix[y - y1b + 2][x - x1b - 1] == 'g')) &&
			((matrix[y - y1b + 2][x - x1b] == ' ') || (matrix[y - y1b + 2][x - x1b] == 'g')) &&
			((matrix[y - y1b + 2][x - x1b + 1] == ' ') || (matrix[y - y1b + 2][x - x1b + 1] == 'g'))) return 1; else return 0;
	}
}

void move_tank(int y, int x, int mov){
	switch (mov){
	case KEY_UP:    delete_tank(y + 1, x);  create_tank(1, lst->curr->tankAll);  break;
	case KEY_LEFT:  delete_tank(y, x + 1);  create_tank(2, lst->curr->tankAll);  break;
	case KEY_RIGHT: delete_tank(y, x - 1);  create_tank(3, lst->curr->tankAll);  break;
	case KEY_DOWN:  delete_tank(y - 1, x);  create_tank(4, lst->curr->tankAll);  break;
	}
}
