#include "tank.h"

chtype lvl_matrix[dimx][dimy];

char lvl_meni[][dimx] = { " Create New Map ", " Load Map ", " Save Map As", " Exit ", " Yes ", " No " }; // stavke menija

char button[][dimx] = { " ESC : Return to menu ", " R : Turn resizing on/off ", " W : Change element to water ", " B : Change element to brick", " G : Change element to grass ",
" SPACE : Save element on map ", };

void buttons(){
	int y1 = 55, y2 = 67;
	int x1 = 95, i = 0, x2 = 120;
	for (; y1 <= y2; y1 += 2)
	{
		mvprintw(y1, x1, button[i++]);
	}
}

void init_matrix(){
	int i, j;
	for (i = 0; i < 65; i++)
		for (j = 0; j < 90; j++){
		matrix[i][j] = '.';
		}
}

int option_selected(int mv,int mainm){ // mainm ako smo u glavnom meniju
	switch (mv){ 
	case 7:      if(mainm) return 0;											else { init_matrix(); print_matrix(); element = 'b'; return 0; } break;
	case 9:	 	 if(!mainm)														return load_maps();                                              break;	
	case 11:     if(!mainm)														return save_map();                                               break;
	case 13:     if(mainm)	{ level_editor(); print_border_menu(y1c,x1c,y2c,x2c); print_commands(); create_map(); return 1; }	else return 0;                                                   break;
	case 15:	 								        break;
	case 17:     								        break;
	case 19:     if(mainm)   { system("cls"); exit(0);   }          break;
	}

} //  koji blok je izabran

void menu_content(int mainm){
	int i, j;
	if(mainm)
	{
		attron(COLOR_PAIR(10));
		mvprintw(4, 117, " M E N U : ");
		attroff(COLOR_PAIR(10));
		attron(COLOR_PAIR(8));
		mvprintw(7, 117, meni[0]);
		attroff(COLOR_PAIR(8));
		mvprintw(9, 117, meni[1]);
		mvprintw(11, 117, meni[2]);
		mvprintw(13, 117, meni[3]);
		mvprintw(15, 117, meni[4]);
		mvprintw(17, 117, meni[5]);
		mvprintw(19, 117, meni[6]);
	}
	else
	{
		mvprintw(4, 117, " LEVEL EDITOR : ");
		attron(COLOR_PAIR(8));
		mvprintw(7, 117, lvl_meni[0]);
		attroff(COLOR_PAIR(8));
		mvprintw(9, 117, lvl_meni[1]);
		mvprintw(11, 117, lvl_meni[2]);
		mvprintw(13, 117, lvl_meni[3]);
	}
	refresh();
} // sadrzaj menija

void delete_menu(int y1, int x1, int y2, int x2){
	int i, j;
	attron(COLOR_PAIR(1));
	for (j = y1; j <= y2; j++)
		for (i = x1; i <= x2; i++)
			mvaddch(j, i, ' ');
	attroff(COLOR_PAIR(1));
	refresh();
} // brise meni

int main_menu(int mainm){
	int  xu, xd, yd, mv = 7, ind = 0, tru = 1, limitup=7, limitdown;
	int flag = 1, flag1 = 1;
	clock_t start = clock();
    clock_t start1 = clock();
    clock_t end= clock();
    clock_t end1 = clock();
	if (mainm){
		print_border_menu(y1c,x1c,y2c,x2c);
		print_commands();
	}
	if(!mainm) limitdown=13;
	else limitdown=19;
	print_border_menu(y1m,x1m,y2m,x2m);
	menu_content(mainm);
	while (tru){
		if(kbhit())
		{
		switch (getch()){
			case KEY_UP: menu_up(&mv, limitup, &ind, 117, mainm);  break;
			case KEY_DOWN: menu_down(&mv, limitdown, &ind, 117, mainm);  break;
			case ENTER: delete_menu(y1m,x1m,y2m,x2m);  /*delete command menu*/ 
				if (tru = option_selected(mv,mainm))
					{
						print_border_menu(y1m,x1m,y2m,x2m);
						menu_content(mainm);
						mv = limitup;
						ind = 0;
					}
				else{
						delete_menu(y1c,x1c,y2c,x2c);
						if(mainm)
						{ 
							delete_tank(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x);
							return 0;
						}
						else{
							if(mv==limitup) return 1; //za Create new map
							else return 0;  
						}
					}
			}
		}
		if(mainm) easy_bot(&start, &lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll.tank.position.y, &lst->curr->tankAll.tank.position.x); //demo mod za bota
	}
}

void level_editor(){
	int yu = 32, xd = 32, yd = 32, xu = 32; // yu ~ y up ;  yd ~ y down; xu ~ x up; xd ~ x down     [yu]|    [xd]...[xu] |											//													[yd]|    [xd]...]xu] |
	int i, j, dify = 0, difx = 0, tru = 1; // i,j pomocne promenljive;tru promenljiva koja prekida kretanje bloka po mapi; dify i difx vracaju visinu i sirinu bloka koji 
	//treba da  se pojavi na mapi;
	buffer[0] = '\0';
	init_matrix();
	clear();
	print_border_menu(2, 2, dimx + 2, dimy + 2); // screen dimensions
	while (1){
		if(!main_menu(0)) { delete_menu(55 ,95 ,67 ,120); return; } // enter the menu
		tru = 1;
		buttons();
		/*	resize_window(&difx, &dify); // prozor gde se podesavaju dimenzije bloka(elementa)*/
		yd = yu = 32;
		xd = xu = 32;
		switch (element){ //  element se iscrtava na mapi
		case 'b': print_brick_lvl(yu, xu, yd, xd); refresh(); break;
		case 'w': print_water_lvl(yu, xu, yd, xd); refresh();  break;
		case 'g': print_grass_lvl(yu, xu, yd, xd); refresh(); break;
		}
		while (tru){
			switch (getch()){ // kretanje po mapi i cuvanje elementa na mapi// biranje elementa//menjanje dimenzija elementa
			case KEY_UP: if (lvl_can_move(yu, xu, yd, xd, 1)) move_up2x2(yu--, xu, yd--, xd); break;
			case KEY_DOWN:if (lvl_can_move(yu, xu, yd, xd, 2)) move_down2x2(yu++, xu, yd++, xd); break;
			case KEY_LEFT: if (lvl_can_move(yu, xu, yd, xd, 3))move_left2x2(yu, xu--, yd, xd--); break;
			case KEY_RIGHT:if (lvl_can_move(yu, xu, yd, xd, 4)) move_right2x2(yu, xu++, yd, xd++); break;
			case ' ': save_in_matrix(yu, xu, yd, xd, element); break;
			case ESC: tru = 0; break;
			case 'R': case 'r': size_resize(&yu, &xu, &yd, &xd); break;
			case'B':case 'b': print_brick_lvl(yu, xu, yd, xd); element = 'b'; break;
			case'G':case'g': print_grass_lvl(yu, xu, yd, xd); element = 'g'; break;
			case 'W':case'w': print_water_lvl(yu, xu, yd, xd); element = 'w'; break;
			case 's': case 'S': if (buffer[0] != '\0') save_it(); else save_map(); break;

			}
		}
	}
	
}
