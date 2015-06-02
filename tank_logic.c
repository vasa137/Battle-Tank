#include "tank.h"

extern chtype matrix[dimx + 1][dimy + 1];   // velicina mape

extern int visit_grass[3][3];

extern int top[];
extern int left[];
extern int right[];
extern int bottom[];

void create_tank(int y, int x, int barrel, tank* tank_type)
{
	switch (barrel)
	{
	case 1: print_tank(y, x, tank_type, top);
		break;
	case 2: print_tank(y, x, tank_type, left);
		break;
	case 3: print_tank(y, x, tank_type, right);
		break;
	case 4: print_tank(y, x, tank_type, bottom);
		break;
	}
}

void delete_tank(int y, int x){

	if (!visit_grass[0][0]) print_blanko(y - 1, x - 1); //ako je blanko, to znaci da je u visitu 0!print_blanko(y - 1, x - 1);
	else{
		print_grass(y - 1, x - 1);
		visit_grass[0][0] = 0;
	}

	if (!visit_grass[0][1]) print_blanko(y - 1, x);
	else{
		print_grass(y - 1, x);
		visit_grass[0][1] = 0;
	}

	if (!visit_grass[0][2]) print_blanko(y - 1, x + 1);
	else{
		print_grass(y - 1, x + 1);
		visit_grass[0][2] = 0;
	}

	if (!visit_grass[1][0]) print_blanko(y, x - 1);
	else{
		print_grass(y, x - 1);
		visit_grass[1][0] = 0;
	}

	if (!visit_grass[1][1]) print_blanko(y, x);
	else{
		print_grass(y, x);
		visit_grass[1][1] = 0;
	}

	if (!visit_grass[1][2]) print_blanko(y, x + 1);
	else{
		print_grass(y, x + 1);
		visit_grass[1][2] = 0;
	}

	if (!visit_grass[2][0]) print_blanko(y + 1, x - 1);
	else{
		print_grass(y + 1, x - 1);
		visit_grass[2][0] = 0;
	}

	if (!visit_grass[2][1]) print_blanko(y + 1, x);
	else{
		print_grass(y + 1, x);
		visit_grass[2][1] = 0;
	}

	if (!visit_grass[2][2]) print_blanko(y + 1, x + 1);
	else{
		print_grass(y + 1, x + 1);
		visit_grass[2][2] = 0;
	}

	refresh();
}

void move_tank(int y, int x, int mov, tank* ver, tank* hor){
	switch (mov){
	case KEY_UP:    delete_tank(y + 1, x);  create_tank(y, x, 1, ver);  break;
	case KEY_LEFT:  delete_tank(y, x + 1);  create_tank(y, x, 2, hor);  break;
	case KEY_RIGHT: delete_tank(y, x - 1);  create_tank(y, x, 3, hor);  break;
	case KEY_DOWN:  delete_tank(y - 1, x);  create_tank(y, x, 4, ver);  break;
	}
}

int can_move(int y, int x, int barrel) {
	switch (barrel)
	{
	case 1: case 4:
		if (((matrix[y - 2][x - 2 - 1] == ' ') || (matrix[y - 2][x - 2 - 1] == 'g')) &&
			((matrix[y - 2][x - 2] == ' ') || (matrix[y - 2][x - 2] == 'g')) &&
			((matrix[y - 2][x - 2 + 1] == ' ') || (matrix[y - 2][x - 2 + 1] == 'g'))) return 1; else return 0;

	case 2: case 3:
		if (((matrix[y - 2 - 1][x - 2] == ' ') || (matrix[y - 2 - 1][x - 2] == 'g')) &&
			((matrix[y - 2][x - 2] == ' ') || (matrix[y - 2][x - 2] == 'g')) &&
			((matrix[y - 2 + 1][x - 2] == ' ') || (matrix[y - 2 + 1][x - 2] == 'g'))) return 1; else return 0;
	}
}

void action(int *y, int *x, tank* ver, tank* hor, int keyPressed, int *check, int *last_move, int *projectil_dir){
	switch (keyPressed)
	{
	case KEY_UP:    *last_move = 1; if (can_move(*y - 2, *x, 1)) move_tank(--*y, *x, KEY_UP, ver, hor);    else { delete_tank(*y, *x);  create_tank(*y, *x, 1, ver); } refresh(); break;
	case KEY_LEFT:  *last_move = 2; if (can_move(*y, *x - 2, 2)) move_tank(*y, --*x, KEY_LEFT, ver, hor);  else { delete_tank(*y, *x); create_tank(*y, *x, 2, hor); } refresh(); break;
	case KEY_RIGHT: *last_move = 3; if (can_move(*y, *x + 2, 3)) move_tank(*y, ++*x, KEY_RIGHT, ver, hor); else { delete_tank(*y, *x);  create_tank(*y, *x, 3, hor); } refresh(); break;
	case KEY_DOWN:  *last_move = 4; if (can_move(*y + 2, *x, 4)) move_tank(++*y, *x, KEY_DOWN, ver, hor);  else { delete_tank(*y, *x);  create_tank(*y, *x, 4, ver); } refresh(); break;
	case ' ':       if (!(*check)) { *projectil_dir = *last_move;  *check = 1; } break;
	}
}
