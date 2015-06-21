#include "tank.h"

void easy_bot()
{ // Mislim da bi bilo dobro da se fja zove bot, a da se tezina razlikuje u generatorima koje ces implementirati dole.
	// koristi matricu da bi odredio puteve, nemoj ubacivati kodove u vec postojece fje da bi odredio put.
	int array_bot_barrel[] = { 4, 3, 1, 4, 2, 4, 3, 1, 4, 2 },x;
	struct timeb vreme;
	ftime(&vreme);
	if (lst->curr->tankAll.tank.phase == 2)
	{
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
		lst->curr->tankAll.tank.phase = 0;
		lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
	}
	lst->curr->tankAll.tank.mm = lst->curr->tankAll.tank.end = vreme.millitm;
	if (delay_s(998, lst->curr->tankAll.tank.end, lst->curr->tankAll.tank.start,lst->curr->tankAll.tank.phase) || (!(can_move(lst->curr->tankAll.tank.position.y,lst->curr->tankAll.tank.position.x,lst->curr->tankAll.tank.position.barrel))))
	{
		srand(time(NULL));
		if ((x = (rand()%9)),array_bot_barrel[x]==lst->curr->tankAll.tank.position.barrel)
			(++x)%9;
		lst->curr->tankAll.tank.position.barrel = array_bot_barrel[x]; // Ovde neka budu dodele vrednosti generatora za sve tezine.
		lst->curr->tankAll.tank.start = vreme.millitm;
	}
	if (delay_s(150, lst->curr->tankAll.tank.mm, lst->curr->tankAll.tank.pp, lst->curr->tankAll.tank.phase))
	{
		action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
		ftime(&vreme);
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
	}
}
