#include "tank.h"

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
		lst->curr->tankAll.projectile.counter = 0;
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
		action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
		ftime(&vreme);
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
	if (!lst->curr->tankAll.projectile.phase)
		{
		if (!(lst->curr->tankAll.projectile.counter))
		{
			lst->curr->tankAll.projectile.phase = 1;
		}
		lst->curr->tankAll.projectile.counter++;
		lst->curr->tankAll.projectile.counter %= 5;
		lst->curr->tankAll.projectile.position.projectil_dir = lst->curr->tankAll.tank.position.last_move;
		}
	}
}
