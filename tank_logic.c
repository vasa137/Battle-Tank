#include "tank.h"

void alloc_tank(){
	List *novi;
	novi = (List*)malloc(sizeof(List));
	novi->next = NULL;
	if (lst->first == NULL){
		lst->first = novi;
		lst->first->tankAll.tank.tPos.x = 38;
		lst->first->tankAll.tank.tPos.y = 24;
		lst->first->tankAll.tank.tPos.barrel = 1;
		lst->first->tankAll.tank.tPos.last_move = 1;
	}
	else lst->last->next = novi;
	lst->last = novi;
	lst->n++;;
	novi->tankAll.projectile.projectPhase = 0;
	novi->tankAll.tank.tankDesign_v = special_tank_v;
	novi->tankAll.tank.tankDesign_h = special_tank_h;
	novi->tankAll.projectile.last_object = ' ';
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
	free(curr);
	lst->n--;
}

void move_tank(int y, int x, int mov, TankDesign* ver, TankDesign* hor){
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

void action(int *y, int *x, TankDesign* ver, TankDesign* hor, int keyPressed, int *check, int *last_move, int *projectil_dir){
	switch (keyPressed)
	{
	case KEY_UP:    *last_move = 1; if (can_move(*y - 2, *x, 1)) move_tank(--*y, *x, KEY_UP, ver, hor);    else { delete_tank(*y, *x);  create_tank(1, lst->curr->tankAll); } refresh(); break;
	case KEY_LEFT:  *last_move = 2; if (can_move(*y, *x - 2, 2)) move_tank(*y, --*x, KEY_LEFT, ver, hor);  else { delete_tank(*y, *x);  create_tank(2, lst->curr->tankAll); } refresh(); break;
	case KEY_RIGHT: *last_move = 3; if (can_move(*y, *x + 2, 3)) move_tank(*y, ++*x, KEY_RIGHT, ver, hor); else { delete_tank(*y, *x);  create_tank(3, lst->curr->tankAll); } refresh(); break;
	case KEY_DOWN:  *last_move = 4; if (can_move(*y + 2, *x, 4)) move_tank(++*y, *x, KEY_DOWN, ver, hor);  else { delete_tank(*y, *x);  create_tank(4, lst->curr->tankAll); } refresh(); break;
	case ' ':       if (!(*check)) { *projectil_dir = *last_move;  *check = 1; } break;
	}
}
