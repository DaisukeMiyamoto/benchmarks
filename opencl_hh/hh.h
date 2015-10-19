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

#define N_COMPARTMENT 4000
static const FLOAT DT = 0.025;        // [msec]
static const FLOAT CELSIUS = 6.3;     // [degC]

// functions
void hh_initialize(unsigned long n_compartment);
void hh_makeTable();
void hh_save_result(unsigned int i_max, char *filename, FLOAT *result);
int  hh_calc(FLOAT stoptime, FLOAT *result);


extern FLOAT hh_v[N_COMPARTMENT];     // [mV]
extern FLOAT hh_dv[N_COMPARTMENT];
extern FLOAT hh_n[N_COMPARTMENT];
extern FLOAT hh_m[N_COMPARTMENT];
extern FLOAT hh_h[N_COMPARTMENT];


#define TABLE_SIZE 201
#define TABLE_MAX_V 100.0f
#define TABLE_MIN_V -100.0f


#define TABLE_TYPE 1

#ifdef TABLE_TYPE
extern FLOAT hh_table[TABLE_SIZE][6];
#define TABLE_N_TAU(x) hh_table[(x)][0]
#define TABLE_N_INF(x) hh_table[(x)][1]
#define TABLE_M_TAU(x) hh_table[(x)][2]
#define TABLE_M_INF(x) hh_table[(x)][3]
#define TABLE_H_TAU(x) hh_table[(x)][4]
#define TABLE_H_INF(x) hh_table[(x)][5]

#else

extern FLOAT hh_table[6][TABLE_SIZE];
#define TABLE_N_TAU(x) hh_table[0][(x)]
#define TABLE_N_INF(x) hh_table[1][(x)]
#define TABLE_M_TAU(x) hh_table[2][(x)]
#define TABLE_M_INF(x) hh_table[3][(x)]
#define TABLE_H_TAU(x) hh_table[4][(x)]
#define TABLE_H_INF(x) hh_table[5][(x)]
#endif

#endif
