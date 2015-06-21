#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "curses.h"
#include <time.h>
#include <sys/timeb.h>
#include "level_order.h"

#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

#define dimx 65
#define dimy 90
#define x1b 2
#define y1b 2
#define x2b 92
#define y2b 67

#define y1m 2
#define x1m 100
#define y2m 23
#define x2m 145

#define y1c 46
#define x1c 100
#define y2c 67
#define x2c 145

#define BACKSPACE 8
#define ENTER '\n'
#define ESC 27
// stavke menija

extern char meni[][dimx];

extern char map_name[50]; 

typedef int int3x3[3][3];
// ====================================================.
typedef struct Tank_Design{
	chtype ch;
	int paint;
}TankDesign;

typedef struct Tank_Position{
	int x;
	int y;
	int barrel;
	int projectil_dir;
	int last_move;
}TankPosition;

typedef struct Projectile_Position{
	int x;
	int y;
	int projectil_dir;
}ProjectilePosition;

typedef struct TAnk{
	TankDesign *tankDesign_v;
	TankDesign *tankDesign_h;
	TankPosition tPos;
	int3x3 visit_grass;
}Tank;

typedef struct PRojectile{
	unsigned short mm, pp;
	ProjectilePosition pPos;
	int projectPhase;
	char last_object;
}Projectile;

typedef struct Whole_Struct{
	Tank tank;
	Projectile projectile;
}TankAll;

typedef struct Linked_list{
	TankAll tankAll;
	struct Linked_list* next;
}List;
// ===============================================.
typedef struct LST{
	List *first;
	List *curr;
	List *last;
	int n;
} Lst;

extern Lst *lst;

typedef struct Barrier{
	int flag;
	char obs;
} barrier;

extern chtype matrix[dimx + 1][dimy + 1];                         // velicina mape

extern chtype element;

extern int top[];
extern int left[];
extern int right[];
extern int bottom[];

extern int visit_grass[3][3];

extern TankDesign special_tank_v[]; 
extern TankDesign special_tank_h[];

extern TankDesign normal_tank_v[];
extern TankDesign normal_tank_h[];

void init_colors();

void init_curses();

void print_brick(int y,int x);

void print_grass(int y, int x);

void print_water(int y,int x);

void print_wall(int y, int x);

void print_blanko(int y,int x);

void print_tank(int y, int x, TankDesign *tank_type, int *position);

void alloc_tank();

void free_tank(List *curr);

void create_tank(int barrel, TankAll current);

void delete_tank(int y, int x);

void move_tank(int y, int x, int mov, TankDesign* ver, TankDesign* hor);

int can_move(int y, int x, int barrel);

int delay_s(int timeToDelay, unsigned short* mm, unsigned short* pp, int *check);

barrier can_fly(int y, int x);

void delete_projectile(int y, int x, char *last_object);

void print_projectile(int y, int x, char object);

List* which_tank(int y, int x);

void collision(int y, int x, int projectil_dir, char object );

char move_projectile(int *y, int *x, int projectil_dir, int *check, char *last_object);

void projectile(int *py, int*px, int y, int x, int projectil_dir, unsigned short* mm, unsigned short* pp, int *check,char *last_object);

void action(int *y, int *x, TankDesign* ver, TankDesign* hor, int keyPressed, int *check, int *last_move, int *projectil_dir);

void print_object(int y,int x,int c);

void print_border();

void create_map(char map_name[]);

void time_now();

void move_bot(int *z, int *t, int *bot_barrel);
 
void easy_bot(clock_t *start, int *flag, int *bot_barrel, int *z, int *t);

void print_border_menu(int y1, int x1, int y2, int x2);

void menu_up(int *mv, int limit, int *ind, int from);

void menu_down(int *mv, int limit, int *ind, int from);

int option_selected(int mv,int mainm);

void menu_content(int mainm);

void delete_menu(int y1, int x1, int y2, int x2);

void print_commands();

int main_menu(int mainm);

void print_red(int y, int x);

void print_blue(int y, int x);

void print_white(int y, int x);

void print_head(int y, int x);

#endif
