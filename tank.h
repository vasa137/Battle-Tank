#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "curses.h"
#include <time.h>
#include <sys/timeb.h>

#define dimx 65
#define dimy 90
#define x1 2
#define y1 2
#define x2 92
#define y2 67

typedef struct Tank{
	chtype ch;
	int paint;
} tank;

typedef struct Barrier{
	int flag;
	char obs;
}barrier;

void init_colors();

void init_curses();

void print_tank(int y, int x, tank *tank_type, int *position);

void create_tank(int y, int x, int barrel, tank* tank_type);

void delete_tank(int y, int x);

void move_tank(int y, int x, int mov, tank* ver, tank* hor);

int can_move(int y, int x, int barrel);

int delay_s(int timeToDelay, unsigned short* mm, unsigned short* pp, int *check);

void print_brick(int y, int x);

void print_grass(int y, int x);

void print_water(int y, int x);

void print_blanko(int y, int x);

barrier can_fly(int y, int x);

void delete_projectile(int y, int x, char *last_object);

void print_projectile(int y, int x, char object);

void collision(int y, int x, int projectil_dir, char object);
//
char move_projectile(int *y, int *x, int projectil_dir, int *check, char *last_object);

void projectile(int *py, int*px, int y, int x, int projectil_dir, unsigned short* mm, unsigned short* pp, int *check, char *last_object);

void action(int *y, int *x, tank* ver, tank* hor, int keyPressed, int *check, int *last_move, int *projectil_dir);

void print_object(int y, int x, int c);

void print_border();

void create_map(char map_name[]);

void time_now();
