#include <curses.h>
/*
create_map(char c, int x,int y)
{
	switch(c)
	{
		' ':
		attron(COLOR_PAIR(1));
		addch(1);
		break;
		' ':
		attron(COLOR_PAIR(2));
		addch(2);
		break;
		' ':
		attron(COLOR_PAIR(3));
		addch(3);
		break;
		' ':
		attron(COLOR_PAIR(4));
		addch(4);
		break;
		' ':
		attron(COLOR_PAIR(5));
		addch(5);
		break;
		' ':
		attron(COLOR_PAIR(6));
		addch(6);
		break;
		default:
		attron(COLOR_PAIR(7));
		addch(' ');
		break;
	}
	refresh();
}

void print_tank(int y,int x, char *tank_type,int *position)
{
	mvaddch(y-1,x-1,tank_type[position[0]]);
	mvaddch(y-1,x,tank_type[position[1]]);
	mvaddch(y-1,x+1,tank_type[position[2]]);
	mvaddch(y,x-1,tank_type[position[3]]);
	mvaddch(y,x,tank_type[position[4]]);
	mvaddch(y,x+1,tank_type[position[5]]);
	mvaddch(y+1,x-1,tank_type[position[6]]);
	mvaddch(y+1,x,tank_type[position[7]]);
	mvaddch(y+1,x+1,tank_type[position[8]]);
}

create_tank(int y,int x,int barrel,char* tank_type)
{
	int top[]={0,1,2,3,4,5,6,7,8};
	int left[]={2,5,8,1,4,7,0,3,6};
	int right[]={6,3,0,7,4,1,8,5,2};
	int bottom[]={8,7,6,5,4,3,2,1,0};

	switch(barrel)
	{
		case 1: print_tank(y,x,tank_type,top);

		case 2: print_tank(y,x,tank_type,left);

		case 3: print_tank(y,x,tank_type,right);

		case 4: print_tank(y,x,tank_type,bottom);
	}


}


delete_movedtank(int x,int y)
{
	int i,j;
	i=x;
	for(j=y;j<y+3;j++)
	{
			mvaddch(i,j,' ');
	}
	//mozda refresh a mozda i ne
}

move_tank(char mov,int x,int y)
{
	//trava iznad ispod, most
	switch(mov)
	{
		case LEFT:	delete_movedtank(y+1,x-1);  create_tank(x-1,y-2,x,y-2); return x,y-1; //struct da vraca
		case RIGHT: delete_movedtank(y-1,x-1,); create_tank(x-1,y,x,y+2); return x,y+1;
		case UP:	delete_movedtank(x+1,y-1);  create_tank(x-2,y-1,x-2,y) return x-1,y;
		case DOWN:	delete_movedtank(x-1,y-1);  create_tank(x,y-1,x+2,y) return x+1,y;
	}
}

destroy_wall(int type,int )
{
	
}

shoot()
{
	
}

*/




int main(){
	int y,x,i,j;
    initscr();
    start_color();
	resize_term(70,180);
	curs_set(0);
    init_pair(1,COLOR_WHITE , COLOR_BLACK);
	init_pair(2,COLOR_GREEN, COLOR_BLACK);
	init_pair(4,COLOR_WHITE, COLOR_YELLOW);
	init_pair(3,COLOR_WHITE,COLOR_RED);
	init_pair(5,COLOR_BLACK,COLOR_YELLOW);
	getmaxyx(stdscr,y,x);
	refresh();
    printw("This should be printed in black with a red background!\n");
    attron(COLOR_PAIR(2));
	for(i=21;i<=23;i++)
	{
		for(j=30;j<=32;j++)
		{
		 if(j!=31)
			 {
					 if(i==23) 
						 {
							attron(COLOR_PAIR(4));
							 mvaddch(i,j,167|A_BOLD);

							}
					 else
					 {
					 attron(COLOR_PAIR(1));
					 mvaddch(i,j,ACS_VLINE|A_BOLD);
					 }
			 }
		 else 
		 {
			 if(i==21)
			 {attron(COLOR_PAIR(1));  mvaddch(i,j,ACS_VLINE);}
			 else 
			{
					if(i==22 && j==31) 
					{
						attron(COLOR_PAIR(5));
						mvaddch(i,j, ACS_BULLET);
					}
					else 
					{
						attron(COLOR_PAIR(4));
						mvaddch(i,j, ACS_HLINE);
					}
			}
		 }
		}
	}
	attron(COLOR_PAIR(3));
	for(i=28;i<=31;i++)
	{
		for(j=30;j<=33;j++)
		{
		 mvaddch(i,j,ACS_PLUS);
		}
	}
	



	refresh();
    refresh();
	refresh();
	getch();
    getch();
	getch();
    endwin();
}