#include "tank.h"

void projectile(int y, int x, int projectil_dir){
	// Global: Coordinates of projectile, var for delay, phase of projectile, last object for projectile.
	struct timeb vreme;
	ftime(&vreme);
	if (lst->curr->tankAll.projectile.phase == 1) // prvo postavljanje checka na 1, samo taj put ulazi u petlju
	{
		switch (projectil_dir){       //definisanje pocetnog mesta na kome je cevka
		case 1:  lst->curr->tankAll.projectile.position.y = y - 1;   lst->curr->tankAll.projectile.position.x = x;      break;
		case 2:	 lst->curr->tankAll.projectile.position.y = y;       lst->curr->tankAll.projectile.position.x = x - 1;  break;
		case 3:	 lst->curr->tankAll.projectile.position.y = y;       lst->curr->tankAll.projectile.position.x = x + 1;  break;
		case 4:  lst->curr->tankAll.projectile.position.y = y + 1;   lst->curr->tankAll.projectile.position.x = x;      break;
		}
		lst->curr->tankAll.projectile.pp = lst->curr->tankAll.projectile.mm = vreme.millitm;
	}
	lst->curr->tankAll.projectile.mm = vreme.millitm;
	if (delay_s(40, lst->curr->tankAll.projectile.mm, lst->curr->tankAll.projectile.pp, lst->curr->tankAll.projectile.phase)) { //u prvoj inicijalizaciji last object saljemo bez inicijalizacije jer ga ne koristimo
		lst->curr->tankAll.projectile.last_object = move_projectile(projectil_dir); // u prvom pozivu check ce preci u 2->stanje leta
		ftime(&vreme);
		lst->curr->tankAll.projectile.pp = lst->curr->tankAll.projectile.mm = vreme.millitm;
	}
}

char move_projectile(int projectil_dir) //vraca nam poslednji objekat na putu u slucaju da treba da ga vratimo posle prolaska metka.
/*Global: - delete_projectile: Coordinates of projectile, last object
- can_fly: Coordinates of projectile
- print_projectile: Coordinates of projectile
- collision: Coordinates of projectile
phase of projectile*/
{
	barrier object;
	if (lst->curr->tankAll.projectile.phase == 2){
		delete_projectile(lst->curr->tankAll.projectile.position.y, lst->curr->tankAll.projectile.position.x, lst->curr->tankAll.projectile.last_object);
		refresh(); 
	}
	else if (lst->curr->tankAll.projectile.phase == 1) lst->curr->tankAll.projectile.phase = 2; //ako je metak bio u letu brisi ga
	switch (projectil_dir){ //switch za stranu u koju metak treba da leti.

	case 1:
		object = can_fly(lst->curr->tankAll.projectile.position.y - 1, lst->curr->tankAll.projectile.position.x);
		switch (object.flag)  // switch za povratnu vrednost can_fly, 1 naisao na prazno polje, 0 nestaje metak ostale vrednosti metak leti ali se ne printa(trava)
		{
		case 1: print_projectile(--lst->curr->tankAll.projectile.position.y, lst->curr->tankAll.projectile.position.x, object.obs); break;
		case 0: collision(lst->curr->tankAll.projectile.position.y - 1, lst->curr->tankAll.projectile.position.x, projectil_dir, object.obs);
			lst->curr->tankAll.projectile.phase = 0; break;
		case 2: --lst->curr->tankAll.projectile.position.y; break; //ako naidje na travu samo pomeri metak ali ga ne ispisuj!
		}
		break;

	case 2:
		object = can_fly(lst->curr->tankAll.projectile.position.y, lst->curr->tankAll.projectile.position.x - 1);
		switch (object.flag)
		{
		case 1: print_projectile(lst->curr->tankAll.projectile.position.y, --lst->curr->tankAll.projectile.position.x, object.obs); break;
		case 0: collision(lst->curr->tankAll.projectile.position.y, lst->curr->tankAll.projectile.position.x - 1, projectil_dir, object.obs);
			lst->curr->tankAll.projectile.phase = 0; break;
		case 2: --lst->curr->tankAll.projectile.position.x; break;
		}
		break;
	case 3:
		object = can_fly(lst->curr->tankAll.projectile.position.y, lst->curr->tankAll.projectile.position.x + 1);
		switch (object.flag)
		{
		case 1: print_projectile(lst->curr->tankAll.projectile.position.y, ++lst->curr->tankAll.projectile.position.x, object.obs); break;
		case 0: collision(lst->curr->tankAll.projectile.position.y, lst->curr->tankAll.projectile.position.x + 1, projectil_dir, object.obs);
			lst->curr->tankAll.projectile.phase = 0; break;
		case 2: ++lst->curr->tankAll.projectile.position.x; break;
		}
		break;

	case 4:
		object = can_fly(lst->curr->tankAll.projectile.position.y + 1, lst->curr->tankAll.projectile.position.x);
		switch (object.flag)
		{
		case 1: print_projectile(++lst->curr->tankAll.projectile.position.y, lst->curr->tankAll.projectile.position.x, object.obs); break;
		case 0: collision(lst->curr->tankAll.projectile.position.y + 1, lst->curr->tankAll.projectile.position.x, projectil_dir, object.obs);
			lst->curr->tankAll.projectile.phase = 0; break;
		case 2: ++lst->curr->tankAll.projectile.position.y; break;
		}
		break;

	}
	refresh();
	return object.obs;
}

barrier can_fly(int y, int x)
{
	barrier ret; //return
	ret.obs = matrix[y - y1b][x - x1b];
	switch (ret.obs){
	case ' ': case 'w':
		ret.flag = 1;
		break;
	case 'g':
		ret.flag = 2;
		break;
	case 'b': case 'e': case 'c': case 't':
		ret.flag = 0;
		break;
	}
	return ret;
	// I jos za tenkove, projektile i ostale stvari.
}

void collision(int y, int x, int projectil_dir, char object){ // saljes mi koordinate udara.
	List *temp;
	switch (object){
	case 'b':
		switch (projectil_dir){
		case 1://up 
			if (matrix[y - y1b][x - x1b - 1] == 'b' && (matrix[y - y1b + 1][x - x1b - 1] != 'b')) print_blanko(y, x - 1);
			if (matrix[y - y1b][x - x1b] == 'b') print_blanko(y, x);
			if (matrix[y - y1b][x - x1b + 1] == 'b' && (matrix[y - y1b + 1][x - x1b + 1] != 'b')) print_blanko(y, x + 1);
			break;
		case 2: // left.
			if ((matrix[y - y1b - 1][x - x1b] == 'b') && (matrix[y - y1b - 1][x - x1b + 1] != 'b')) print_blanko(y - 1, x);
			if (matrix[y - y1b][x - x1b] == 'b') print_blanko(y, x);
			if ((matrix[y - y1b + 1][x - x1b] == 'b') && (matrix[y - y1b + 1][x - x1b + 1] != 'b'))print_blanko(y + 1, x);
			break;
		case 3: //right.
			if ((matrix[y - y1b - 1][x - x1b] == 'b') && (matrix[y - y1b - 1][x - x1b - 1] != 'b')) print_blanko(y - 1, x);
			if (matrix[y - y1b][x - x1b] == 'b') print_blanko(y, x);
			if ((matrix[y - y1b + 1][x - x1b] == 'b') && (matrix[y - y1b + 1][x - x1b - 1] != 'b')) print_blanko(y + 1, x);
			break;
		case 4:
			if ((matrix[y - y1b][x - x1b - 1] == 'b') && (matrix[y - y1b - 1][x - x1b - 1] != 'b')) print_blanko(y, x - 1);
			if (matrix[y - y1b][x - x1b] == 'b') print_blanko(y, x);
			if (matrix[y - y1b][x - x1b + 1] == 'b' && (matrix[y - y1b - 1][x - x1b + 1] != 'b')) print_blanko(y, x + 1);
			break;
		}
		break;
	case 't':
		temp = which_tank(y, x);
		free_tank(temp);
		break;

	case 'c':; // za beton, kada budemo imali strukturu.
	case '*':; // za metak o metak, gledamo razlicite strane i gledamo da li se sudaraju, pazimo na mimoilazenje.
	}

}

List* which_tank(int y, int x){
	List *temp = lst->first;
	while (temp){
		if ((y == temp->tankAll.tank.position.y || y == temp->tankAll.tank.position.y + 1 || y == temp->tankAll.tank.position.y - 1) && (x == temp->tankAll.tank.position.x || x == temp->tankAll.tank.position.x + 1 || x == temp->tankAll.tank.position.x - 1)) return temp;
		temp = temp->next;
	}
}
