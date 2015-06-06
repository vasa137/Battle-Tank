#include "tank.h"

void load_matrix(char name[]){
	FILE *file;
	int i = 0, j = 0;
	char key;
	file = fopen(name, "r");
	while ((key = fgetc(file)) != EOF)
		{
		if (key == '/') i++;
		if (key == '\n') { j = 0; continue; }
		lvl_matrix[i][j++] = key;
		}	
	fclose(file);
	
}

int print_a_page(char **book, int c_page, int limitdown, int limitup, int per_page)
{
	int i, j = limitup;
	for (i = (c_page - 1)*per_page; book[i] != NULL; i++)
	{
		mvprintw(j, 113, "%s", book[i]);
		j += 2;
		if (j == limitdown) break;
	}
	mvprintw(38, 117, "         ");
	mvprintw(38, 117, "PAGE %d", c_page);
	attron(COLOR_PAIR(8));
	mvprintw(8, 113, "%s", book[(c_page-1)*per_page]);
	attroff(COLOR_PAIR(8));
	refresh();
	return j;
}

void lmenu_up(char **book, int *mv, int limit, int *ind, int from)
{
	int i;
	if (*mv == limit) return;
	*mv = *mv - 2;
	attron(COLOR_PAIR(8));
	mvprintw(*mv, from, "%s  ", book[--(*ind)]);
	attroff(COLOR_PAIR(8));
	mvprintw(*mv + 2, from, "%s ", book[*ind + 1]);
	refresh();

}

void lmenu_down(char **book, int *mv, int limit, int *ind, int from)
{
	int i;
	if (*mv == limit) return;
	*mv = *mv + 2;
	attron(COLOR_PAIR(8));
	mvprintw(*mv, from, "%s ", book[++(*ind)]);
	attroff(COLOR_PAIR(8));
	mvprintw(*mv - 2, from, "%s ", book[*ind - 1]);
	refresh();
} // kretanje po meniju

int load_maps(){
	char **book = (char**)calloc(1, sizeof(char*));
	FILE *saved_maps; 
	int pages, num = 0, per_page = 10, c_page = 1;
	int x1 = 100, y1 = 2, x2 = 145, y2 = 45;
	int limitup = 8, limitdown = 28, mv = 8, i = 0, j = 6;
	int from = 113;
	if(!(saved_maps = fopen("saved_maps.txt", "r"))) return 1;
	while (!feof(saved_maps))
	{
		book[num] = (char*)calloc(20, sizeof(char));
		fscanf(saved_maps, "%s", book[num++]);
		if (book[num - 1][0] == '\0') { num--; book[num] = NULL; continue; };
		book = (char**)realloc(book, (num + 1)*sizeof(char*));
		book[num] = NULL;
	}
	if (num == 0) return 1;

	fclose(saved_maps);
	pages = (num - 1) / per_page + 1;
	print_border_menu(y1, x1, y2, x2);
	mvprintw(4, 115, "L O A D   M A P");
	mvprintw(42, 102, "ARROW LEFT/RIGHT : navigate through pages");
	mvprintw(44, 102, "ARROW UP/RIGHT : navigate through files");
	refresh();

	while (1)
	{
		j = print_a_page(book, c_page, limitdown, limitup, per_page) - 2;
		while (1){
			switch (getch()){
			case KEY_UP: lmenu_up(book, &mv, limitup, &i, from); break;
			case KEY_DOWN: lmenu_down(book, &mv, j, &i, from); break;
			case KEY_LEFT: if (c_page > 1) 
			{
				delete_menu(5, 101, 38, 144); j = print_a_page(book, --c_page, limitdown, limitup, per_page) - 2; mv = 8; i = (c_page - 1)*per_page;
			} break;
			case KEY_RIGHT: if (c_page < pages) {
				delete_menu(5, 101, 38, 144);  j = print_a_page(book, ++c_page, limitdown, limitup, per_page) - 2; mv = 8; i = (c_page - 1)*per_page;
			} break;
			case ENTER: strcpy(buffer, book[i]); load_matrix(book[i]); print_matrix();  delete_menu(y1, x1, y2, x2); return 0; break;
			case ESC: delete_menu(y1, x1, y2, x2); return 1; break;
			}

		}



	}


}
