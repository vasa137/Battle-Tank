#include "tank.h"


unsigned long long int RSA_D(long long int checksum)
{
	unsigned long long int d = 17; // p = 49; q = 43 11 13
	unsigned long long int n = 3 * 11;
	unsigned long long int rez;
	rez = ((unsigned long long int)pow(checksum, d) % n);
	return rez;
}


unsigned long long int RSA_E(long long int sum)
{
	unsigned long long int e = 7;
	unsigned long long int n = 3 * 11;
	unsigned long long int rez;
	rez = (unsigned long long int)pow(sum, e) % n;
	return rez;
}




FILE* create_scoreboard_n_check(FILE* hs, score** best)
{
	score *zurzeit, *prev = NULL;
	unsigned  long long int sum = 0;
	unsigned  long long int checksum = 0;
	if(fread(&checksum, sizeof( unsigned long long int), 1, hs) == 0) return hs;  // this checks for possible unauthorized changes in high scores
	// =======Reads the binary file that contains high scores======
	zurzeit = (score*)calloc(1, sizeof(score));
	while (!feof(hs)) // until it hits eof of binary file
	{
		//fread(zurzeit, sizeof(score*), 1, hs);
		fread(zurzeit->name, sizeof(chtype), 10, hs);
		fread(&zurzeit->score, sizeof(long long int), 1, hs);
		zurzeit->name[9] = '\0';
		sum += zurzeit->score;
		if (best[0] == NULL) best[0] = zurzeit;
		else
			prev->next = zurzeit;
		prev = zurzeit;
		zurzeit = (score*)calloc(1, sizeof(score));
	}
	//=============================================================

	//=======checks if the score was  changed========

	 if (!(checksum == RSA_E(sum)))
	{
	fclose(hs);
	hs = fopen("high_scores.dat", "wb");
	fclose(hs);
	return NULL;
	}
	//===============================================
	return hs;
	}

int show_scores(score* zurzeit, int j, score* cmp)
{
	int i = 1, rvl = 0;
	//======prints scores on screen========
	while ((zurzeit) && (i <11))
	{
		if ((zurzeit) == cmp ) rvl = j;
		if (zurzeit->score == 0) {
			zurzeit = zurzeit->next;
			continue;
		}
		mvprintw(j, 110, "%d. %-4s    %4d", i++, zurzeit->name, zurzeit->score);
		zurzeit = zurzeit->next;
		j += 2;
	}
	return rvl;
	refresh();
	//=====================================

}
void destroy_scoreboard(score* best)
{
	score* zurzeit;
	while (best != NULL)
	{
		zurzeit = best;
		best = best->next;
		free(zurzeit);
	}
}



score* insert_n_h(score** best, long long int s) // new high score is added to the list of top scores
{
	score* rvl, *zurzeit = best[0];
	rvl = (score*)calloc(1, sizeof(score));
	if (best[0] == NULL) { best[0] = rvl; rvl->score = s; return best[0]; }
	else
		while (zurzeit)
		{
			if (zurzeit->score < s)
			{
				rvl->score = zurzeit->score;
				zurzeit->score = s;
				zurzeit->next = rvl;
				return zurzeit;
			}
			zurzeit = zurzeit->next;
		}
	return NULL;

}







void new_high_score(long long int s)
{
	FILE* hs;
	score* best = NULL, *zurzeit = NULL, *neu = NULL;
	chtype Key;
	char name[10];
	long long int sum = 0, checksum = 0;
	int i = 0, tru, j = 114, row;
	int min = 114, max = 123;
	int x1 = 100, y1 = 2, x2 = 145, y2 = 45;
	if (!(hs = fopen("high_scores.dat", "rb"))) hs = fopen("high_scores.dat", "wb"); // if it doesnt exist;
	else{
		if (!(hs = create_scoreboard_n_check(hs, &best))) return 1;
	}

	fclose(hs);
	
	tru = 1;

	delete_menu(y1c, x1c, y2c, x2c);
	print_border_menu(y1, x1, y2, x2);

	name[0] = '\0';

	attron(COLOR_PAIR(10));
	mvaddstr(y1 + 3, x1 + 12, "H I G H  S C O R E S :");
	attroff(COLOR_PAIR(10));

	neu = insert_n_h(&best, s);
	if (!(row = show_scores(best, y1 + 7, neu)))
	{
		delete_menu(y1, x1, y2, x2);
		destroy_scoreboard(best);
		return;
	}
	hs = fopen("high_scores.dat", "wb");
	zurzeit = best;
	while (tru)
	{
		//=====choosing your name =========
		switch (Key = getch())
		{
		case KEY_UP: case KEY_DOWN: case KEY_LEFT: case KEY_RIGHT: case ESC:							   break;
		case ENTER:   tru = 0;																			   break;// name chosen 
		default: if (j < max)	{	name[i++] = Key; name[i] = '\0'; mvaddch(row, j++, Key);};	refresh(); break;
		case BACKSPACE: if (j > min){	name[--i] = '\0'; mvaddch(row, --j, ' ');	}; refresh();		   break;
		}
	}
	//=====================================

	for (i; i < 9; name[i] = ' ', i++);
	name[9] = '\0';


	strcpy(neu->name, name);
	zurzeit = best;

	while (zurzeit)
	{
		sum += zurzeit->score;
		zurzeit = zurzeit->next;

	}
	checksum = RSA_E(sum);


	fwrite(&checksum, sizeof(unsigned long long int), 1, hs);
	while (best)
	{
		zurzeit = best;
	//	fwrite(best, sizeof(score*), 1, hs);
		fwrite(best->name, sizeof(char), sizeof(best->name), hs);
		fwrite(&best->score, sizeof(long long int), 1, hs);
		best = best->next;
		free(zurzeit);
	}
	fclose(hs);

	delete_menu(y1, x1, y2, x2);


}

// ===========================================================


int read_high_scores()
{
	FILE* hs;
	score *best = NULL, *zurzeit = NULL;
	int i, j;
	int x1 = 100, y1 = 2, x2 = 145, y2 = 45;

	attron(COLOR_PAIR(10));
	mvaddstr(y1 + 3, x1 + 12, "H I G H  S C O R E S :");
	attroff(COLOR_PAIR(10));

	print_border_menu(y1, x1, y2, x2);
	delete_menu(y1c, x1c, y2c, x2c);

	if (!(hs = fopen("high_scores.dat", "rb")))		  return 1; // if it doesn't exist, just go back :)
	if (!(create_scoreboard_n_check(hs, &best))) return 1; // creates scoreboard

	zurzeit = best;


	j = y1 + 7;
	show_scores(best, j, NULL); // prints scores on the menu
	destroy_scoreboard(best); // destroys the list of scores

	while (1) // until the users hits a button enter || ESC, he'll be able to see scores
	{
		switch (getch())
		{
		case ENTER: case ESC: delete_menu(y1, x1, y2, x2);  return 1; break;
		default:													  break;
		}
	}
}
