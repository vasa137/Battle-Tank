#include "tank.h"

void move_bot(int *z, int *t, int *bot_barrel)
{
        int array_bot_barrel[] = { 1, 2, 3, 4 };
        int a = *z, b = *t;
        int bot_barrel1 = *bot_barrel;
        switch (*bot_barrel)
        {
        case 1:
                if ((matrix[a - 4][b - 1] == ' ') && (matrix[a - 4][b - 2] == ' ') && (matrix[a - 4][b - 3] == ' '))
                {
                        delete_tank(a, b);
						(*z)--;
                        create_tank(bot_barrel1, lst->curr->tankAll);
                        refresh();
                }
                else
                        *bot_barrel = array_bot_barrel[rand() % 4];
                break;
        case 2:
                if ((matrix[a - 1][b - 4] == ' ') && (matrix[a - 2][b - 4] == ' ') && (matrix[a - 3][b - 4] == ' '))
                {
                        delete_tank(a, b);
						(*t)--;
                        create_tank(bot_barrel1, lst->curr->tankAll);
                        refresh();
                }
                else
                        *bot_barrel = array_bot_barrel[rand() % 4];
                break;
        case 3:
                if ((matrix[a - 1][b] == ' ') && (matrix[a - 2][b] == ' ') && (matrix[a - 3][b] == ' '))
                {
                        delete_tank(a, b);
						(*t)++;
                        create_tank(bot_barrel1, lst->curr->tankAll);
                        refresh();
                }
                else
                        *bot_barrel = array_bot_barrel[rand() % 4];
                break;
        case 4:
                if ((matrix[a][b - 1] == ' ') && (matrix[a][b - 2] == ' ') && (matrix[a][b - 3] == ' '))
                {
                        delete_tank(a, b);
						(*z)++;
                        create_tank(bot_barrel1, lst->curr->tankAll);
                        refresh();
                }
                else
                        *bot_barrel = array_bot_barrel[rand() % 4];
        }
}
 
void easy_bot(clock_t *start, int *flag, int *bot_barrel, int *z, int *t)
{
        clock_t end;
        end = clock();
        if ((end - (*start)) > 80)
        {
                if (*flag==1)
                {
						create_tank(*bot_barrel, lst->curr->tankAll);
                        *flag = 2;
                }
                else{
				move_bot(z, t, bot_barrel);
                *start = clock();
				}
        }
}
