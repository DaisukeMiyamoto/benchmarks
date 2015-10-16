#ifndef __HH_H__
#define __HH_H__

#ifdef KCOMPUTER
#include "fj_tool/fapp.h"
#endif

#ifdef USE_FLOAT
#define EXP(x) expf((x))
typedef float FLOAT;
#else
#define EXP(x) exp((x))
typedef double FLOAT;
#endif

// constants
//#define PRINT_RESULT 1
#define SAVE_RESULT 1

#define N_COMPARTMENT 1000
static const FLOAT DT = 0.025;        // [msec]
static const FLOAT CELSIUS = 6.3;     // [degC]

// functions
void hh_initialize(unsigned long n_compartment);
void hh_makeTable();
int  hh_calc(FLOAT stoptime);


extern FLOAT hh_v[N_COMPARTMENT];     // [mV]
extern FLOAT hh_dv[N_COMPARTMENT];
extern FLOAT hh_n[N_COMPARTMENT];
extern FLOAT hh_m[N_COMPARTMENT];
extern FLOAT hh_h[N_COMPARTMENT];


#endif
