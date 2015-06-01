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

chtype matrix[dimx + 1][dimy + 1];                         // velicina mape

int top[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int left[] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
int right[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int bottom[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

tank special_tank_v[] = { { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_VLINE, 1 }, { ACS_BULLET, 5 }, { ACS_VLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_HLINE, 4 }, { ACS_DIAMOND, 4 } };
tank special_tank_h[] = { { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_HLINE, 1 }, { ACS_BULLET, 5 }, { ACS_HLINE, 1 }, { ACS_DIAMOND, 4 }, { ACS_VLINE, 4 }, { ACS_DIAMOND, 4 } };

tank normal_tank_v[] = { { 126, 6 }, { ACS_VLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };
tank normal_tank_h[] = { { 126, 6 }, { ACS_HLINE, 1 }, { 126, 6 }, { ACS_DIAMOND, 2 }, { 79, 7 }, { ACS_DIAMOND, 2 }, { ACS_DIAMOND, 2 }, { ACS_CKBOARD, 8 }, { ACS_DIAMOND, 2 } };

void init_colors(){
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW , COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_GREEN);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_YELLOW);
	init_pair(10, COLOR_WHITE, COLOR_BLUE);
	init_pair(11, COLOR_YELLOW, COLOR_BLUE);
}

void init_curses(){
	initscr();
	init_colors();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	resize_term(70, 150);
}

void print_tank(int y, int x, tank *tank_type, int *position)
{
	attron(COLOR_PAIR(tank_type[position[0]].paint));
	mvaddch(y - 1, x - 1, tank_type[position[0]].ch);
	matrix[y - 1 - 2][x - 1 - 2] = 't';

	attron(COLOR_PAIR(tank_type[position[1]].paint));
	mvaddch(y - 1, x, tank_type[position[1]].ch);
	matrix[y - 1 - 2][x - 2] = 't';

	attron(COLOR_PAIR(tank_type[position[2]].paint));
	mvaddch(y - 1, x + 1, tank_type[position[2]].ch);
	matrix[y - 1 - 2][x + 1 - 2] = 't';

	attron(COLOR_PAIR(tank_type[position[3]].paint));
	mvaddch(y, x - 1, tank_type[position[3]].ch);
	matrix[y - 2][x - 1 - 2] = 't';

	attron(COLOR_PAIR(tank_type[position[4]].paint));
	mvaddch(y, x, tank_type[position[4]].ch);
	matrix[y - 2][x - 2] = 't';

	attron(COLOR_PAIR(tank_type[position[5]].paint));
	mvaddch(y, x + 1, tank_type[position[5]].ch);
	matrix[y - 2][x + 1 - 2] = 't';

	attron(COLOR_PAIR(tank_type[position[6]].paint));
	mvaddch(y + 1, x - 1, tank_type[position[6]].ch);
	matrix[y + 1 - 2][x - 1 - 2] = 't';

	attron(COLOR_PAIR(tank_type[position[7]].paint));
	mvaddch(y + 1, x, tank_type[position[7]].ch);
	matrix[y + 1 - 2][x - 2] = 't';

	attron(COLOR_PAIR(tank_type[position[8]].paint));
	mvaddch(y + 1, x + 1, tank_type[position[8]].ch);
	matrix[y + 1 - 2][x + 1 - 2] = 't';
	refresh();
}

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

	attron(COLOR_PAIR(6));

	mvaddch(y - 1, x - 1, ' ');
	matrix[y - 1 - 2][x - 1 - 2] = ' ';

	mvaddch(y - 1, x, ' ');
	matrix[y - 1 - 2][x - 2] = ' ';

	mvaddch(y - 1, x + 1, ' ');
	matrix[y - 1 - 2][x + 1 - 2] = ' ';

	mvaddch(y, x - 1, ' ');
	matrix[y - 2][x - 1 - 2] = ' ';

	mvaddch(y, x, ' ');
	matrix[y - 2][x - 2] = ' ';

	mvaddch(y, x + 1, ' ');
	matrix[y - 2][x + 1 - 2] = ' ';

	mvaddch(y + 1, x - 1, ' ');
	matrix[y + 1 - 2][x - 1 - 2] = ' ';

	mvaddch(y + 1, x, ' ');
	matrix[y + 1 - 2][x - 2] = ' ';

	mvaddch(y + 1, x + 1, ' ');
	matrix[y + 1 - 2][x + 1 - 2] = ' ';
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
	case 1: case 4: if (matrix[y - 2][x - 2 - 1] == ' ' && matrix[y - 2][x - 2] == ' ' && matrix[y - 2][x - 2 + 1] == ' ') return 1; else return 0;
	case 2: case 3: if (matrix[y - 2 - 1][x - 2] == ' ' && matrix[y - 2][x - 2] == ' ' && matrix[y - 2 + 1][x - 2] == ' ') return 1; else return 0;
	}
}

int delay_s(int timeToDelay, unsigned short* mm, unsigned short* pp, int *check){
	if (*check == 1){    
		return 1;
	}
	if (*mm - *pp > 0){
		if (*mm - *pp >= timeToDelay)	{
			return 1;
		}
	}
	else if (*mm - *pp < 0){
		if (1000 - *pp + *mm >= timeToDelay){
			return 1;
		}
	}
	return 0;
}

void print_brick(int y,int x){
	attron(COLOR_PAIR(3));
	mvaddch(y,x, ACS_PLUS);
	attroff(A_BOLD);
	matrix[y-y1][x-x1] = 'b';
}

void print_grass(int y, int x){
	attron(COLOR_PAIR(2));
	mvaddch(y,x,'#');
	matrix[y-y1][x-x1] = 'g';
}

void print_water(int y,int x){
	attron(COLOR_PAIR(10));
	mvaddch(y,x,'~');
	matrix[y-y1][x-x1] = 'w';
}

void print_blanko(int y,int x){
	attron(COLOR_PAIR(6));
	mvaddch(y,x,' ');
	matrix[y-y1][x-x1] = ' ';
}

barrier can_fly(int y, int x)
{
	barrier ret; //return
	ret.obs = matrix[y - 2][x - 2];
	switch (ret.obs){
	case ' ': case 'w':
		ret.flag = 1;
		break;
	case 'g':
		ret.flag = 2;
		break;
	case 'b': case 'e':
		ret.flag = 0;
		break;
	}
	return ret;
	// I jos za tenkove, projektile i ostale stvari.
}

void delete_projectile(int y, int x, char *last_object)
{
	if( *last_object=='w') print_water(y,x); // umesto if-a moze print object da se pozove on je sam po sebi case
	else if ( *last_object==' ') print_blanko(y,x);
}

void print_projectile(int y, int x, char object)
{
	if( object == 'w')  attron(COLOR_PAIR(11)); // ako naidje na vodu
	else if(object == ' ')  attron(COLOR_PAIR(8));
	mvaddch(y, x, ACS_BULLET | A_BOLD);
	matrix[y - 2][x - 2] = '*';
}

void collision(int y, int x, int projectil_dir, char object ){ // saljes mi koordinate udara.
	switch (object){
	case 'b':
		switch (projectil_dir){
		case 1://up 
			if ((matrix[y - 2][x - 2 - 1] == 'b') && (matrix[y - 2 + 1][x - 2 - 1] != 'b')) print_blanko(y, x - 1);
			if (matrix[y - 2][x - 2] == 'b') print_blanko(y, x);
			if (matrix[y - 2][x - 2 + 1] == 'b' && (matrix[y - 2 + 1][x - 2 + 1] != 'b')) print_blanko(y, x + 1);
			break;
		case 2: // left.
			if ((matrix[y - 2 - 1][x - 2] == 'b') && (matrix[y - 2 - 1][x - 2 + 1] != 'b')) print_blanko(y - 1, x);
			if (matrix[y - 2][x - 2] == 'b') print_blanko(y, x);
			if ((matrix[y - 2 + 1][x - 2] == 'b') && (matrix[y - 2 + 1][x - 2 + 1] != 'b'))print_blanko(y + 1, x);
			break;
		case 3: //right.
			if ((matrix[y - 2 - 1][x - 2] == 'b') && (matrix[y - 2 - 1][x - 2 - 1] != 'b')) print_blanko(y - 1, x);
			if (matrix[y - 2][x - 2] == 'b') print_blanko(y, x);
			if ((matrix[y - 2 + 1][x - 2] == 'b') && (matrix[y - 2 + 1][x - 2 - 1] != 'b')) print_blanko(y + 1, x);
			break;
		case 4:
			if ((matrix[y - 2][x - 2 - 1] == 'b') && (matrix[y - 2 - 1][x - 2 - 1] != 'b')) print_blanko(y, x - 1);
			if (matrix[y - 2][x - 2] == 'b') print_blanko(y, x);
			if (matrix[y - 2][x - 2 + 1] == 'b' && (matrix[y - 2 - 1][x - 2 + 1] != 'b')) print_blanko(y, x + 1);
			break;
		}
	case 'o':; // za botove.
	case 'c':; // za beton, kada budemo imali strukturu.
	case '*':; // za metak o metak, gledamo razlicite strane i gledamo da li se sudaraju, pazimo na mimoilazenje.
	}

}

char move_projectile(int *y, int *x, int projectil_dir, int *check, char *last_object) //vraca nam poslednji objekat na putu u slucaju da treba da ga vratimo posle prolaska metka
{
	barrier object;
	if (*check == 2) delete_projectile(*y, *x, last_object);
	else if (*check == 1) *check = 2; //ako je metak bio u letu brisi ga
	switch (projectil_dir){ //switch za stranu u koju metak treba da leti
	
	case 1: 
		object=can_fly(*y - 1, *x);
		switch (object.flag)  // switch za povratnu vrednost can_fly, 1 naisao na prazno polje, 0 nestaje metak ostale vrednosti metak leti ali se ne printa(trava)
		{
			case 1: print_projectile(--*y, *x, object.obs); break;
			case 0: collision(*y-1,*x,projectil_dir,object.obs); *check = 0; break;
			case 2: --*y; break; //ako naidje na travu samo pomeri metak ali ga ne ispisuj!
		}
		break;
	
	case 2:	 
		object=can_fly(*y, *x - 1);
		switch (object.flag)
		{
			case 1: print_projectile(*y, --*x, object.obs); break;
			case 0: collision(*y,*x-1,projectil_dir,object.obs); *check = 0; break;
			case 2: --*x; break;
		}
		break;
	case 3:	
		object=can_fly(*y, *x + 1);
		switch (object.flag)
		{
			case 1: print_projectile(*y, ++*x, object.obs); break;
			case 0: collision(*y,*x+1,projectil_dir,object.obs); *check = 0; break;
			case 2: ++*x; break;
		}
		break;

	case 4: 
		object=can_fly(*y + 1, *x);
		switch (object.flag)
		{
			case 1: print_projectile(++*y, *x, object.obs); break;
			case 0: collision(*y+1,*x,projectil_dir,object.obs); *check = 0; break;
			case 2: ++*y; break;
		}
		break;

	}
	refresh();
	return object.obs;
}

void projectile(int *py, int*px, int y, int x, int projectil_dir, unsigned short* mm, unsigned short* pp, int *check,char *last_object)
{
	struct timeb vreme;
	ftime(&vreme);
	if (*check == 1) // prvo postavljanje checka na 1, samo taj put ulazi u petlju
	{
		switch (projectil_dir){       //definisanje pocetnog mesta na kome je cevka
		case 1:  *py = y - 1;   *px = x;      break;
		case 2:	 *py = y;       *px = x - 1;  break;
		case 3:	 *py = y;       *px = x + 1;  break;
		case 4:  *py = y + 1;   *px = x;      break;
		} 
		*pp = *mm = vreme.millitm;
	}
	*mm = vreme.millitm;
	if (delay_s(40, mm, pp, check)) { //u prvoj inicijalizaciji last object saljemo bez inicijalizacije jer ga ne koristimo
		*last_object=move_projectile(py, px, projectil_dir, check, last_object); // u prvom pozivu check ce preci u 2->stanje leta
		ftime(&vreme);
		*pp = *mm = vreme.millitm;
	}
}

void action(int *y, int *x, tank* ver, tank* hor, int keyPressed, int *check, int *last_move, int *projectil_dir){
	switch (keyPressed)
	{
	case KEY_UP:    *last_move = 1; if (can_move(*y - 2, *x, 1)) move_tank(--*y, *x, KEY_UP, ver, hor);    else create_tank(*y, *x, 1, ver); refresh(); break;
	case KEY_LEFT:  *last_move = 2; if (can_move(*y, *x - 2, 2)) move_tank(*y, --*x, KEY_LEFT, ver, hor);  else create_tank(*y, *x, 2, hor); refresh(); break;
	case KEY_RIGHT: *last_move = 3; if (can_move(*y, *x + 2, 3)) move_tank(*y, ++*x, KEY_RIGHT, ver, hor); else create_tank(*y, *x, 3, hor); refresh(); break;
	case KEY_DOWN:  *last_move = 4; if (can_move(*y + 2, *x, 4)) move_tank(++*y, *x, KEY_DOWN, ver, hor);  else create_tank(*y, *x, 4, ver); refresh(); break;
	case ' ':       if (!(*check)) { *projectil_dir = *last_move;  *check = 1; } break;
	}
}

void print_object(int y,int x,int c){
	switch (c)
	{
	case 'b': print_brick(y,x); break;
	case 'w': print_water(y,x); break;
	case 'g': print_grass(y,x); break;
	default:  print_blanko(y,x); break;
	}
}

void print_border()
{
	int i;
	attron(COLOR_PAIR(10)); // dodaj atribut za boju
	mvaddch(y1, x1, ACS_ULCORNER);
	mvaddch(y2, x1, ACS_LLCORNER);
	mvaddch(y1, x2, ACS_URCORNER);
	mvaddch(y2, x2, ACS_LRCORNER);

	matrix[0][0] = 'e';
	matrix[dimx][0] = 'e';
	matrix[0][dimy] = 'e';
	matrix[dimx][dimy] = 'e';
	for (i = y1 + 1; i<y2; i++)
	{
		mvaddch(i, x1, ACS_VLINE);
		mvaddch(i, x2, ACS_VLINE);

		matrix[i - 3][0] = 'e';
		matrix[i - 2][dimy] = 'e';
	}

	for (i = x1 + 1; i<x2; i++)
	{
		mvaddch(y1, i, ACS_HLINE);
		mvaddch(y2, i, ACS_HLINE);

		matrix[0][i - 3] = 'e';
		matrix[dimx][i - 3] = 'e';
	}
	refresh();
}

void create_map(char map_name[])
{
	FILE *map;
	int c;
	int y=y1+1, x=x1+1; 

	map = fopen(map_name, "r");

	print_border();  //okvir

	while ((c = fgetc(map)) != EOF)
	{
		if (c == '\n') continue;
		if (c != '/')
		{
			if (c == '.') c = ' ';
			print_object(y,x,c);
			x++;
			refresh();
		}
		else {
			y++;
			x = x1 + 1;
		}
	}
}

void time_now(){
	time_t pIntTime;
	struct tm* currentLocalTime;
	char* dateTimeString = (char*)calloc(100 + 1, sizeof(char));
	pIntTime = time(NULL);
	currentLocalTime = localtime(&pIntTime);
	attron(COLOR_PAIR(1));
	if (currentLocalTime && dateTimeString)
		strftime(dateTimeString, 100, "%H:%M:%S", currentLocalTime);
	mvaddstr(1, 42, dateTimeString);
	refresh();
	free(dateTimeString);
}

void main(){
	unsigned short mm, pp;
	struct timeb vreme;
	char last_object=' ';
	int y = 4, x = 4, check = 0, keyPressed, last_move, projectil_dir, px, py; // f- da li postoji projektil
	char map_name[50] = "vasa.txt";
	init_curses();
	create_map(map_name);
	create_tank(y, x, 1, special_tank_v);
	last_move = 1; //zato sto tenk stvaramo uspravno
	while (1){
		time_now();
		if (_kbhit())
		{
			keyPressed = getch();
			action(&y, &x, special_tank_v, special_tank_h, keyPressed, &check, &last_move, &projectil_dir);
		}
		if (check) projectile(&py, &px, y, x, projectil_dir, &mm, &pp, &check, &last_object);
	}
}
