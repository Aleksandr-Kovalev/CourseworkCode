#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "disk.h"

/*

Header file for the Menu and the algorithms to choose from

Author: Aleksandr Kovalev
Date: 05/08/2018
*/

void userMenu(Disk& disk);
int FCFS(Disk& disk);
int SSTF(Disk& dis);
int SCAN(Disk& dis);
int cSCAN(Disk& dis);
int LOOK(Disk& dis);
int cLOOK(Disk& dis);

#endif
