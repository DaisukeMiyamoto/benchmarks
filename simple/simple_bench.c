#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef KCOMPUTER
#include <fjcoll.h>
#include <fj_tool/fapp.h>
#define START_PROF(x, y) (fapp_start(x, y, 1))
#define STOP_PROF(x, y)  (fapp_stop(x, y, 1))
#else
#define START_PROF(x, y)
#define STOP_PROF(x, y)
#endif


//#define BENCH_INT
#define BENCH_FLOAT
//#define BENCH_DOUBLE


#define CALC_LOOP 100
#define DATA_SIZE 3000000

int a_i[DATA_SIZE], b_i[DATA_SIZE], c_i[DATA_SIZE];
float a_f[DATA_SIZE], b_f[DATA_SIZE], c_f[DATA_SIZE];
double a_d[DATA_SIZE], b_d[DATA_SIZE], c_d[DATA_SIZE];

float ex_f[DATA_SIZE];
double ex_d[DATA_SIZE];

/**************************** print ******************************/
void print_value_int()
{
  int i;
  for(i=0; i<DATA_SIZE; i++){
    printf("%d %d : %d\n", a_i[i], b_i[i], c_i[i]);
  }
  return;
}

void print_value_float()
{
  int i;
  for(i=0; i<DATA_SIZE; i++){
    printf("%f %f : %f\n", a_f[i], b_f[i], c_f[i]);
  }
  return;
}

void print_value_double()
{
  int i;
  for(i=0; i<DATA_SIZE; i++){
    printf("%f %f : %f\n", a_d[i], b_d[i], c_d[i]);
  }
  return;
}

/***************************** init ******************************/
void set_value_int()
{
  int i;
  for(i=0; i<DATA_SIZE; i++){
    a_i[i] = rand() >> 2;
    b_i[i] = rand() >> 2;
    c_i[i] = 0;
  }
  return;
}

void set_value_float()
{
  int i;
  for(i=0; i<DATA_SIZE; i++){
    a_f[i] = rand() / (float)RAND_MAX;
    b_f[i] = rand() / (float)RAND_MAX;
    c_f[i] = 0.f;
    ex_f[i] = rand() / (float)RAND_MAX;
  }
  return;
}

void set_value_double()
{
  int i;
  for(i=0; i<DATA_SIZE; i++){
    a_d[i] = rand() / (double)RAND_MAX;
    b_d[i] = rand() / (double)RAND_MAX;
    c_d[i] = 0.;
    ex_d[i] = rand() / (double)RAND_MAX;
  }
  return;
}

/****************************** add ******************************/
void calc_add_int()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_i[i] = a_i[i] + b_i[i];
    }
  }
  return;
}

void calc_add_float()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_f[i] = a_f[i] + b_f[i];
    }
  }
  return;
}

void calc_add_double()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_d[i] = a_d[i] + b_d[i];
    }
  }
  return;
}

/****************************** mul ******************************/
void calc_mul_int()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_i[i] = a_i[i] * b_i[i];
    }
  }
  return;
}

void calc_mul_float()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_f[i] = a_f[i] * b_f[i]; 
   }
  }
  return;
}

void calc_mul_double()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_d[i] = a_d[i] * b_d[i];
    }
  }
  return;
}


/****************************** div ******************************/
void calc_div_int()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_i[i] = a_i[i] / b_i[i];
    }
  }
  return;
}

void calc_div_float()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_f[i] = a_f[i] / b_f[i];
    }
  }
  return;
}

void calc_div_double()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_d[i] = a_d[i] / b_d[i];
    }
  }
  return;
}


/**************************** mul+add ****************************/

void calc_mul_add_float()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_f[i] = a_f[i] * b_f[i] + ex_f[i];
    }
  }
  return;
}

void calc_mul_add_double()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_d[i] = a_d[i] * b_d[i] + ex_d[i];
    }
  }
  return;
}


/****************************** exp ******************************/
void calc_exp_float()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_f[i] = expf(a_f[i]);
    }
  }
  return;
}

void calc_exp_double()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_d[i] = exp(a_d[i]);
    }
  }
  return;
}


/**************************** others ******************************/

void calc_sum_float()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_f[i] += a_f[i];
    }
  }
  return;
}

void calc_cadd_float()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_f[i] = a_f[i] + 3.0f;
    }
  }
  return;
}

void calc_cmp_float()
{
  int i, j;
  for(j=0; j<CALC_LOOP; j++){
    for(i=0; i<DATA_SIZE; i++){
      c_f[i] = (b_f[0] * (2.0f * a_f[i] * a_f[i] + b_f[1])) + 2.1f;
    }
  }
  return;
}


double get_mflops(double t, int n)
{
  return(n * CALC_LOOP*(double)DATA_SIZE/t*1000/1000/1000);
}

/***************************** main ******************************/
int main(int argc, char** argv)
{
  clock_t t_start;
#ifdef BENCH_INT
  double time_add_int,    time_mul_int,    time_div_int;
#endif
#ifdef BENCH_FLOAT
  double time_add_float,  time_mul_float,  time_div_float,  time_exp_float, time_mul_add_float;
#endif
  double time_sum_float, time_cadd_float, time_cmp_float;
#ifdef BENCH_DOUBLE
  double time_add_double, time_mul_double, time_div_double, time_exp_double, time_mul_add_double;
#endif


  printf("/********************** SIMPLE BECHMARKS ***********************/\n");
  printf("                                           by nebula 20141124  \n\n");
  printf("[%s]\n", argv[0]);
  printf("calc num = %d * %d\n", CALC_LOOP, DATA_SIZE);

  // int
#ifdef BENCH_INT
  set_value_int();
  calc_add_int();

  t_start = clock();
  calc_add_int();
  time_add_int = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("add(int)\t\t: %8.2f [msec]\n", time_add_int);
  t_start = clock();
  calc_mul_int();
  time_mul_int = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul(int)\t\t: %8.2f [msec]\n", time_mul_int);
  t_start = clock();
  calc_div_int();
  time_div_int = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("div(int)\t\t: %8.2f [msec]\n", time_div_int);
#endif

  // float
#ifdef BENCH_FLOAT
  set_value_float();
  calc_add_float();

  set_value_float();
  t_start = clock();
  START_PROF("add_float", 11);
  calc_add_float();
  STOP_PROF("add_float", 11);
  time_add_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("add(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_add_float, get_mflops(time_add_float, 1));

  set_value_float();
  t_start = clock();
  START_PROF("mul_float", 12);
  calc_mul_float();
  STOP_PROF("mul_float", 12);
  time_mul_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_mul_float, get_mflops(time_mul_float, 1));

  set_value_float();
  t_start = clock();
  START_PROF("div_float", 13);
  calc_div_float();
  STOP_PROF("div_float", 13);
  time_div_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("div(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_div_float, get_mflops(time_div_float, 1));

  set_value_float();
  t_start = clock();
  START_PROF("mul_add_float", 14);
  calc_mul_add_float();
  STOP_PROF("mul_add_float", 14);
  time_mul_add_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul+add(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_mul_add_float, get_mflops(time_mul_add_float, 2));

  set_value_float();
  t_start = clock();
  START_PROF("exp_float", 15);
  calc_exp_float();
  STOP_PROF("exp_float", 15);
  time_exp_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("exp(float)\t\t: %8.2f [msec]\n", time_exp_float);

  set_value_float();
  t_start = clock();
  START_PROF("sum_float", 16);
  calc_sum_float();
  STOP_PROF("sum_float", 16);
  time_sum_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("sum(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_sum_float, get_mflops(time_sum_float, 1));

  set_value_float();
  t_start = clock();
  START_PROF("cadd_float", 17);
  calc_cadd_float();
  STOP_PROF("cadd_float", 17);
  time_cadd_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("cadd(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_cadd_float, get_mflops(time_cadd_float, 1));

  set_value_float();
  t_start = clock();
  START_PROF("cmp_float", 18);
  calc_cmp_float();
  STOP_PROF("cmp_float", 18);
  time_cmp_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("cmp(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_cmp_float, get_mflops(time_cmp_float, 3));
#endif

  // double
#ifdef BENCH_DOUBLE
  set_value_double();
  calc_add_double();

  set_value_double();
  t_start = clock();
  calc_add_double();
  time_add_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("add(double)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_add_double, get_mflops(time_add_double, 1));

  set_value_double();
  t_start = clock();
  calc_mul_double();
  time_mul_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul(double)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_mul_double, get_mflops(time_mul_double, 1));

  set_value_double();
  t_start = clock();
  calc_div_double();
  time_div_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("div(double)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_div_double, get_mflops(time_div_double, 1));

  set_value_double();
  t_start = clock();
  calc_mul_add_double();
  time_mul_add_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul+add(double)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_mul_add_double, get_mflops(time_mul_add_double, 2));

  set_value_double();
  t_start = clock();
  calc_exp_double();
  time_exp_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("exp(double)\t\t: %8.2f [msec]\n", time_exp_double);
#endif

  //print_value_int();

  return(0);
}
