#include "tank.h"

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

List* which_tank(int y, int x){
	List *temp=lst->first;
	while(temp){
		if( (y==temp->tankAll.tank.tPos.y || y==temp->tankAll.tank.tPos.y+1 || y==temp->tankAll.tank.tPos.y-1) && (x==temp->tankAll.tank.tPos.x || x==temp->tankAll.tank.tPos.x+1 || x==temp->tankAll.tank.tPos.x-1)) return temp;
		temp=temp->next;
	}
}

void collision(int y, int x, int projectil_dir, char object ){ // saljes mi koordinate udara.
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
		temp=which_tank(y,x);
		free_tank(temp);
		break;
				
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
