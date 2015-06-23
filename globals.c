#include "tank.h"

Lst *lst;

char meni[][dimx] = { " New Game ", " Load Game ", " Settings ", " Map Editor ", " Play Custom map", " High Scores ", " Exit " };

char map_name[50] = "dobraje.txt";

chtype matrix[dimx + 1][dimy + 1];                         // velicina mape

chtype element = 'b';

Powerups powerup;

char pUps[6] = { 'x', 'l', 's', 'q', 'a', 'y' };

int pridx;

int top[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int left[] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
int right[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int bottom[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };


Levels level1[] = { { 0, 0, 1 }, { 1, 2, 1 }, { 0, 3, 1 }, { 1, 20, 1 }, { 1, 22, 1 } };
Levels level2[] = { { 0, 0, 1 }, { 1, 2, 1 }, { 0, 15, 1 }, { 1, 20, 2 }, { 1, 30, 2 }, { 0, 35, 2 }, { 0, 37, 2 } };
Levels level3[] = { { 0, 0, 1 }, { 1, 2, 2 }, { 1, 15, 2 }, { 1, 20, 2 }, { 1, 30, 3 }, { 0, 35, 3 }, { 0, 37, 3 } };
int lvl[] = { 5, 7, 7 }; // broj botova u svakom nivou.


TankDesign special_tank_v[] = { { ACS_VLINE | A_BOLD, 1 }, { ACS_VLINE | A_BOLD, 1 }, { ACS_VLINE | A_BOLD, 1 },
{ ACS_VLINE | A_BOLD, 1 }, { ACS_BULLET | A_BOLD | A_ALTCHARSET, 4 }, { ACS_VLINE | A_BOLD, 1 },
{ ACS_DIAMOND | A_BOLD, 4 }, { ACS_HLINE | A_BOLD, 4 }, { ACS_DIAMOND | A_BOLD, 4 } };

TankDesign special_tank_h[] = { { ACS_HLINE | A_BOLD, 1 }, { ACS_HLINE | A_BOLD, 1 }, { ACS_HLINE | A_BOLD, 1 },
{ ACS_HLINE | A_BOLD, 1 }, { ACS_BULLET | A_BOLD | A_ALTCHARSET, 4 }, { ACS_HLINE | A_BOLD, 1 },
{ ACS_DIAMOND | A_BOLD, 4 }, { ACS_VLINE | A_BOLD, 4 }, { ACS_DIAMOND | A_BOLD, 4 } };

TankDesign normal_tank_v[] = { { ' ', 1 }, { ACS_VLINE | A_BOLD, 1 }, { ' ', 1 }, { ACS_PLUS | A_BOLD, 18 },
{ ACS_CKBOARD | A_BOLD, 2 }, { ACS_PLUS | A_BOLD, 18 }, { ACS_PLUS | A_BOLD, 18 },
{ ACS_BLOCK, 2 }, { ACS_PLUS | A_BOLD, 18 } };

TankDesign normal_tank_h[] = { { ' ', 1 }, { ACS_HLINE | A_BOLD, 1 }, { ' ', 1 },
{ ACS_PLUS | A_BOLD, 18 }, { ACS_CKBOARD | A_BOLD, 2 }, { ACS_PLUS | A_BOLD, 18 },
{ ACS_PLUS | A_BOLD, 18 }, { ACS_BLOCK, 2 }, { ACS_PLUS | A_BOLD, 18 } };

TankDesign brat_tank_v[] = { { ACS_BOARD, 8 }, { ACS_VLINE | A_BOLD, 1 }, { ACS_BOARD, 8 },
{ ACS_VLINE | A_BOLD, 18 }, { ACS_CKBOARD, 2 }, { ACS_VLINE | A_BOLD, 18 },
{ ACS_BOARD, 8 }, { ACS_HLINE | A_BOLD, 18 }, { ACS_BOARD, 8 } };

TankDesign brat_tank_h[] = { { ACS_BOARD, 8 }, { ACS_HLINE | A_BOLD, 1 }, { ACS_BOARD, 8 },
{ ACS_HLINE | A_BOLD, 18 }, { ACS_CKBOARD, 2 }, { ACS_HLINE | A_BOLD, 18 },
{ ACS_BOARD, 8 }, { ACS_VLINE | A_BOLD, 18 }, { ACS_BOARD, 8 } };
