#include "tank.h"

void easy_bot(){ // Mislim da bi bilo dobro da se fja zove bot, a da se tezina razlikuje u generatorima koje ces implementirati dole.
	// koristi matricu da bi odredio puteve, nemoj ubacivati kodove u vec postojece fje da bi odredio put.
	int array_bot_barrel[] = { 1, 2, 3, 4 };
	struct timeb vreme;
	ftime(&vreme);
	if (lst->curr->tankAll.tank.phase == 2)	{
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
		lst->curr->tankAll.tank.phase = 0;
	}
	lst->curr->tankAll.tank.mm = vreme.millitm;
	if (delay_s(120, lst->curr->tankAll.tank.mm, lst->curr->tankAll.tank.pp, lst->curr->tankAll.tank.phase)){
		action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
		lst->curr->tankAll.tank.position.barrel = array_bot_barrel[rand() % 4]; // Ovde neka budu dodele vrednosti generatora za sve tezine.
		ftime(&vreme);
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
	}
}
