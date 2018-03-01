#ifndef _PSTAT_H_
#define _PSTAT_H_

##include "param.h"

struct pstat{
	int inuse[NPROCS];
	int pid[NPROCS];
	int tickets[NPROCS];
};

#endif //_PSTAT_H_
