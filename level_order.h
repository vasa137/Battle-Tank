#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include "tank.h"

typedef struct Map
{
	chtype mapa[dimx][dimy];
}map;

typedef struct Score
{
	char name[6];
	double score;
	struct Score* next;
}score;


extern chtype lvl_matrix[dimx][dimy];
extern char lvl_meni[][dimx]; // stavke menija
extern char button[][dimx];
extern char buffer[20];

void print_matrix();

void save_in_matrix(int yu, int xu, int yd, int xd, chtype k);

int check_if_legit(char buff[16]);

void name_it();

void save_it();

int save_map();

void print_brick_lvl(int yu, int xu, int yd, int xd);
void print_grass_lvl(int yu, int xu, int yd, int xd);
void print_water_lvl(int yu, int xu, int yd, int xd);
void print_blanko_lvl(int yu, int xu, int yd, int xd);
void print_eraser(int yu, int xu, int yd, int xd);
void print_wall_lvl(int yu, int xu, int yd, int xd);


void what_to_print(int yu, int xu, int yd, int xd, chtype k);

int lvl_can_move(int yu, int xu, int yd, int xd, int num);

void move_up2x2(int yu, int xu, int yd, char xd);
void move_right2x2(int yu, int xu, int yd, int xd);
void move_down2x2(int yu, int xu, int yd, int xd);
void move_left2x2(int yu, int xu, int yd, int xd);

void menu_content();

int load_maps();

void size_resize(int *yu, int *xu, int *yd, int *xd);

void buttons();

void level_editor();

int print_a_page(char **book, int c_page, int limitdown, int limitup, int per_page);

void lmenu_up(char **book, int *mv, int limit, int *ind, int from);
void lmenu_down(char **book, int *mv, int limit, int *ind, int from);

int load_maps();
void load_matrix(char name[]);

void PUSH_unredo(map** unredo, int* n_unredo);
void copy_matrix(map** unredo, int n_unredo);
void destroy_undo_redo(map** undo, map **redo, int n_redo, int n_undo);

void _undo_redo(map** pop, map** push, int* n_undo, int* n_redo);
int POP(map** unredo, int* n_unredo);
#endif
