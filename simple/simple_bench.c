#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define CALC_LOOP 1000
#define DATA_SIZE 1000000

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
  }
  return;
}

void set_value_float()
{
  int i;
  for(i=0; i<DATA_SIZE; i++){
    a_f[i] = rand() / (float)RAND_MAX;
    b_f[i] = rand() / (float)RAND_MAX;
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


double get_mflops(double t, int n)
{
  return(n * CALC_LOOP*DATA_SIZE/t*1000/1000/1000);
}

/***************************** main ******************************/
int main()
{
  clock_t t_start;
  double time_add_int,    time_mul_int,    time_div_int;
  double time_add_float,  time_mul_float,  time_div_float,  time_exp_float;
  double time_add_double, time_mul_double, time_div_double, time_exp_double;

  double time_mul_add_float, time_mul_add_double;


  printf("/********************** SIMPLE BECHMARKS ***********************/\n");
  printf("                                           by nebula 20141124  \n\n");
  printf("calc num = %d * %d = %d\n", CALC_LOOP, DATA_SIZE, CALC_LOOP*DATA_SIZE);

  set_value_int();
  set_value_float();
  set_value_double();

  // int
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


  // float
  calc_add_float();

  t_start = clock();
  calc_add_float();
  time_add_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("add(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_add_float, get_mflops(time_add_float, 1));
  t_start = clock();
  calc_mul_float();
  time_mul_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_mul_float, get_mflops(time_mul_float, 1));
  t_start = clock();
  calc_div_float();
  time_div_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("div(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_div_float, get_mflops(time_div_float, 1));
  t_start = clock();
  calc_mul_add_float();
  time_mul_add_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul+add(float)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_mul_add_float, get_mflops(time_mul_add_float, 2));
  t_start = clock();
  calc_exp_float();
  time_exp_float = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("exp(float)\t\t: %8.2f [msec]\n", time_exp_float);


  // double
  calc_add_double();

  t_start = clock();
  calc_add_double();
  time_add_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("add(double)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_add_double, get_mflops(time_add_double, 1));
  t_start = clock();
  calc_mul_double();
  time_mul_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul(double)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_mul_double, get_mflops(time_mul_double, 1));
  t_start = clock();
  calc_div_double();
  time_div_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("div(double)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_div_double, get_mflops(time_div_double, 1));
  t_start = clock();
  calc_mul_add_double();
  time_mul_add_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("mul+add(double)\t\t: %8.2f [msec] = %8.2f [MFLOPS]\n", time_mul_add_double, get_mflops(time_mul_add_double, 2));
  t_start = clock();
  calc_exp_double();
  time_exp_double = (clock()- t_start)*1000./CLOCKS_PER_SEC;
  printf("exp(double)\t\t: %8.2f [msec]\n", time_exp_double);

  //print_value_int();

  return(0);
}
