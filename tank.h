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

#define PW_DURATION 7000
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
	unsigned short mm, pp;
	unsigned short start, end;
	int counter;
	int counter1;
	int time;
	int phase;
	TankDesign *tankDesign_v;
	TankDesign *tankDesign_h;
	TankPosition position;
	int3x3 visit_grass;
}Tank;

typedef struct PRojectile{
	unsigned short mm, pp;
	ProjectilePosition position;
	int phase;
	int counter;
	char last_object;
}Projectile;

typedef struct Whole_Struct{
	Tank tank;
	Projectile* projectile;
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

typedef struct PowerUps{//   in matrix:
	unsigned short life; //  - l
	unsigned short bomb; //  - q
	unsigned short star; //  - s
	unsigned short clock; // - a
	unsigned short shovel;// - y
	unsigned short shield;// - x
}Powerups;

typedef struct Spawn_place{
	int y;
	int x;
} spawn_place;

typedef struct LEvels{
	int kind;
	int time;
	int smart;
}Levels;

extern Levels level1[];
extern Levels level2[];
extern Levels level3[];
extern int lvl[];

extern Powerups powerup;

extern char pUps[];

extern char matrix[dimx + 1][dimy + 1];                         // velicina mape

extern chtype element;

extern int pridx;

extern int top[];
extern int left[];
extern int right[];
extern int bottom[];

extern TankDesign special_tank_v[];
extern TankDesign special_tank_h[];

extern TankDesign normal_tank_v[];
extern TankDesign normal_tank_h[];

extern TankDesign brat_tank_v[];
extern TankDesign brat_tank_h[];

extern TankDesign novi_tank_v[];
extern TankDesign novi_tank_h[];

void init_colors();
void init_curses();

void start_level(clock_t *start_lvl_time, int *l, int *br, unsigned long int *random_pup_gen,long int* random_element_gen);//
void fire_rate_assessment(int keyPressed);//
void execute_our_tank();//
void execute_bots();//
void demo_mode();//
void should_spawn_bot(clock_t *start_lvl_time, int *rez, int *br, int l, Levels *level[]);//

int free_place(int place);

void print_powerup(int y, int x, chtype pup, char A);
void print_brick(int y, int x);
void print_grass(int y, int x);
void print_water(int y, int x);
void print_wall(int y, int x);
void print_blanko(int y, int x);
void print_tank(int y, int x, TankDesign *tank_type, int *position);

void alloc_tank(int place);
void free_tank(List *curr);
void create_tank(int barrel, TankAll current);
void delete_tank(int y, int x);
void move_tank(int y, int x, int mov);
int can_move(int y, int x, int barrel);
List* which_tank(int y, int x);

int delay_s(int timeToDelay, unsigned short mm, unsigned short pp, int phase);

barrier can_fly(int y, int x);

void delete_projectile(int y, int x, char last_object);
void print_projectile(int y, int x, char object);
void collision(int y, int x, int projectil_dir, char object);
char move_projectile(int projectil_dir);
void projectile(int y, int x, int projectil_dir);
void action(int keyPressed, TankAll *current);

void print_object(int y, int x, int c);
void print_border();
void create_map(char *map_name);
void time_now();
void print_border_menu(int y1, int x1, int y2, int x2);

void menu_up(int *mv, int limit, int *ind, int from, int mainm);
void menu_down(int *mv, int limit, int *ind, int from, int mainm);
int option_selected(int mv, int mainm);
int main_menu(int mainm);
void delete_menu(int y1, int x1, int y2, int x2);

void print_menu_pups();
void print_commands();
void menu_content(int mainm);

void print_red(int y, int x);
void print_blue(int y, int x);
void print_white(int y, int x);
void print_head(int y, int x);

int stars();
void init_powerups();
void update_powerups(char pw);
int check_powerups(int y, int x, int a);
void execute_powerups(clock_t *pw_shield_start, clock_t *pw_clock_start, clock_t *pw_shovel_start, unsigned long int*random_pup_gen);

void easy_bot();
void medium_bot();
int hit_tank(int y, int x);
void shoot();
void move_bot(int *z, int *t, int *bot_barrel);

#endif
