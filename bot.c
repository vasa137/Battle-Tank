#include "tank.h"
int array_bot_barrel[] = { 4, 2, 4, 3, 4, 2, 4, 3, 4 }, s = 0, x1;

int hit_tank(int y, int x)
{
	int b = lst->first->tankAll.tank.position.y-y1b;
	int a = lst->first->tankAll.tank.position.x-x1b;
	if (((x == (a - 1)) && (y == (b - 1))) || ((x == a) && (y == (b - 1))) || ((x == (a + 1)) && (y == (b - 1))) || ((x == (a - 1)) && (y == b)) ||
		((x == (a + 1)) && (y == b)) || ((x == (a - 1)) && (y == (b + 1))) || ((x == a) && (y == (b + 1))) || ((x == (a + 1)) && (y == (b + 1))))
		return 1;
	return 0;
}

void move_bot_up()
{
	if ((!can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 2)) &&
		(!can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 3)) &&
		(!can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 4)) ||

		(can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 2) &&
		can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 3) &&
		(!can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 4))))

		lst->curr->tankAll.tank.position.barrel = 1;
	else  if (!can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 1))
                lst->curr->tankAll.tank.position.barrel = array_bot_barrel[rand()%9];
}

void shoot() //izbaciti travu, da ne vidi bot igraca, tj. da ne bi pucao na njega dok je u travi.
{
	int i = 0;
	if (!lst->curr->tankAll.projectile[0].phase)
	{
		switch (lst->curr->tankAll.tank.position.barrel)
		{
		case 1:
			while ((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b]==' ') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'w'))
				i++;

			if  ((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'b') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'h') ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == '*') &&
				((lst->curr->tankAll.tank.position.y - y1b - 2 - i) == lst->first->tankAll.projectile[0].position.y) &&
				((lst->curr->tankAll.tank.position.x - x1b) == lst->first->tankAll.projectile[0].position.x)) ||
			
				((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b]=='t') &&
				((hit_tank(lst->curr->tankAll.tank.position.y - y1b - 2 - i, lst->curr->tankAll.tank.position.x - x1b)))))
					lst->curr->tankAll.projectile[0].phase = 1;
			break;
		case 2:
			while ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == ' ') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'w'))
				i++;

			if  ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'b') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b] [lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'h') ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == '*') &&
				((lst->curr->tankAll.tank.position.y - y1b) == lst->first->tankAll.projectile[0].position.y) &&
				((lst->curr->tankAll.tank.position.x - x1b - 2 - i) == lst->first->tankAll.projectile[0].position.x)) ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 't') &&
				(hit_tank(lst->curr->tankAll.tank.position.y - y1b, lst->curr->tankAll.tank.position.x - x1b - 2 - i))))
				lst->curr->tankAll.projectile[0].phase = 1;
			break;
		case 3:
			while ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == ' ') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'w'))
				i++;

			if ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'b') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'h') ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == '*') &&
				((lst->curr->tankAll.tank.position.y - y1b) == lst->first->tankAll.projectile[0].position.y) &&
				((lst->curr->tankAll.tank.position.x - x1b + 2 + i) == lst->first->tankAll.projectile[0].position.x)) ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 't') &&
				(hit_tank(lst->curr->tankAll.tank.position.y - y1b, lst->curr->tankAll.tank.position.x - x1b + 2 + i))))
				lst->curr->tankAll.projectile[0].phase = 1;
			break;
		case 4:
			while ((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == ' ') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'w'))
				i++;

			if ((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'b') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'h') ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == '*') &&
				((lst->curr->tankAll.tank.position.y - y1b + 2 + i) == lst->first->tankAll.projectile[0].position.y) &&
				((lst->curr->tankAll.tank.position.x - x1b) == lst->first->tankAll.projectile[0].position.x)) ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 't') &&
				((hit_tank(lst->curr->tankAll.tank.position.y - y1b + 2 + i, lst->curr->tankAll.tank.position.x - x1b)))))
				lst->curr->tankAll.projectile[0].phase = 1;
			break;
		}
	}
}

void medium_bot()
{
	struct timeb vreme;	
	clock_t x;
	ftime(&vreme);
	if (lst->curr->tankAll.tank.phase == 2)
	{
		lst->curr->tankAll.tank.counter1 = 0;
		lst->curr->tankAll.tank.time = clock();
	}
	//if (delay_s(890, x = vreme1.millitm, lst->curr->tankAll.tank.pp1, lst->curr->tankAll.tank.phase)) 
	if (lst->curr->tankAll.tank.counter1 < 3)
	{
		easy_bot();
		if ((((x = clock()) - lst->curr->tankAll.tank.time)*1000 / CLOCKS_PER_SEC) > 5000)
		{
			lst->curr->tankAll.tank.counter1++;
			lst->curr->tankAll.tank.time = x;
		}
	}
	else
	{
		if (lst->curr->tankAll.tank.counter1 == 1)
		{
			lst->curr->tankAll.tank.counter1++;
			lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
			lst->curr->tankAll.tank.counter = 1;
			lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;

		}
		lst->curr->tankAll.tank.end = vreme.millitm;

		if (((((x = clock()) - lst->curr->tankAll.tank.time)*1000 / CLOCKS_PER_SEC) > 800) && (!lst->curr->tankAll.tank.phase))
		{
			shoot();
			lst->curr->tankAll.tank.time = x;
		}
		else if (!(s = can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, lst->curr->tankAll.tank.position.barrel)) || 
			(delay_s(rand() % 250 + 749, lst->curr->tankAll.tank.end, lst->curr->tankAll.tank.start, lst->curr->tankAll.tank.phase)))
		{
			if (s)
			{
				lst->curr->tankAll.tank.counter += 1;
				lst->curr->tankAll.tank.counter %= 6;
			}
			if ((!(lst->curr->tankAll.tank.counter)) || (!s))
			{
				lst->curr->tankAll.tank.counter = 1;
				srand(time(NULL));
				x1 = rand() % 9;
				if (array_bot_barrel[x1] == lst->curr->tankAll.tank.position.barrel)
				{
					x1++;
					x1 %= 9;
				}
				lst->curr->tankAll.tank.position.barrel = array_bot_barrel[x1]; // Ovde neka budu dodele vrednosti generatora za sve tezine.
			}
			lst->curr->tankAll.tank.start = vreme.millitm;
		}
		move_bot_up();
		lst->curr->tankAll.tank.mm = vreme.millitm;
		
		if (delay_s(250, lst->curr->tankAll.tank.mm, lst->curr->tankAll.tank.pp, lst->curr->tankAll.tank.phase))
		{
			action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
			ftime(&vreme);
			lst->curr->tankAll.tank.pp = vreme.millitm;
			if (!lst->curr->tankAll.projectile[0].phase)
			{
				lst->curr->tankAll.projectile[0].counter++;
				lst->curr->tankAll.projectile[0].counter %= 5;
				lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.last_move;
			}
		}
	}
}
void easy_bot()
{ // Mislim da bi bilo dobro da se fja zove bot, a da se tezina razlikuje u generatorima koje ces implementirati dole.
	// koristi matricu da bi odredio puteve, nemoj ubacivati kodove u vec postojece fje da bi odredio put.
	int array_bot_barrel[] = {2, 4, 3, 4, 2, 4, 3, 1, 4 }, x,s = 0;
	struct timeb vreme;
	ftime(&vreme);
	if (lst->curr->tankAll.tank.phase == 2)
	{
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
		lst->curr->tankAll.tank.phase = 0;
		lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
		lst->curr->tankAll.tank.counter = 1;
		lst->curr->tankAll.projectile[0].counter = 0;
	}
	lst->curr->tankAll.tank.mm = lst->curr->tankAll.tank.end = vreme.millitm;
	srand(time(NULL));
	if ((!(s = can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, lst->curr->tankAll.tank.position.barrel)) || (delay_s(rand()%250+749, lst->curr->tankAll.tank.end, lst->curr->tankAll.tank.start, lst->curr->tankAll.tank.phase))))
	{
		if (s)
		{
			lst->curr->tankAll.tank.counter += 1;
			lst->curr->tankAll.tank.counter %= 6;
		}
		if ((!(lst->curr->tankAll.tank.counter)) || (!s))
		{
			lst->curr->tankAll.tank.counter = 1;
			srand(time(NULL));
			if ((x = (rand() % 9)), array_bot_barrel[x] == lst->curr->tankAll.tank.position.barrel)
			{
				x++;
				x %= 9;
			}
			lst->curr->tankAll.tank.position.barrel = array_bot_barrel[x]; // Ovde neka budu dodele vrednosti generatora za sve tezine.
		}
		if (lst->curr->tankAll.tank.position.barrel == 1)
		{
			lst->curr->tankAll.tank.counter =3;
		}
		lst->curr->tankAll.tank.start = vreme.millitm;

	}
	if (delay_s(250, lst->curr->tankAll.tank.mm, lst->curr->tankAll.tank.pp, lst->curr->tankAll.tank.phase))
	{
		if (lst->curr->tankAll.tank.phase != 5)
			action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
		ftime(&vreme);
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
	if (!lst->curr->tankAll.projectile[0].phase)
		{
		if (!(lst->curr->tankAll.projectile[0].counter))
		{
			lst->curr->tankAll.projectile[0].phase = 1;
		}
		lst->curr->tankAll.projectile[0].counter++;
		lst->curr->tankAll.projectile[0].counter %= 5;
		lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.last_move;
		}
	}
}
