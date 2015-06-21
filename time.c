#include "tank.h"

int delay_s(int timeToDelay){
 // Global: var for delay, phase of projectile.
 if (lst->curr->tankAll.projectile.projectPhase == 1){
  return 1;
 }
 if (lst->curr->tankAll.projectile.mm - lst->curr->tankAll.projectile.pp > 0){
  if (lst->curr->tankAll.projectile.mm - lst->curr->tankAll.projectile.pp >= timeToDelay) {
   return 1;
  }
 }
 else if (lst->curr->tankAll.projectile.mm - lst->curr->tankAll.projectile.pp < 0){
  if (1000 + lst->curr->tankAll.projectile.mm - lst->curr->tankAll.projectile.pp >= timeToDelay){
   return 1;
  }
 }
 return 0;
}

void time_now(){
	time_t pIntTime;
	struct tm* currentLocalTime;
	char* dateTimeString = (char*)calloc(100 + 1, sizeof(char));
	pIntTime = time(NULL);
	currentLocalTime = localtime(&pIntTime);
	attron(COLOR_PAIR(1));
	if (currentLocalTime && dateTimeString)
		strftime(dateTimeString, 100, "%H:%M:%S", currentLocalTime);
	mvaddstr(1, 42, dateTimeString);
	refresh();
	free(dateTimeString);
}
