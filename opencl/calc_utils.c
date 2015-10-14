#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc_utils.h"

#ifdef GET_TIME_METHOD
#include <time.h>
double getTime()
{
  clock_t ct;
  ct = clock();

  return((double)ct / CLOCKS_PER_SEC);
}

#else

#include <sys/time.h>
double getTime()
{
  struct timeval tv;
  gettimeofday (&tv, NULL);

  return ((double)tv.tv_sec + (double)tv.tv_usec * 0.001 * 0.001);
}
#endif

void setRandomData(const int datasize, double *data)
{
  int i;

  for (i=0; i<datasize; i++)
    {
      data[i] = ((double)rand())/((double)RAND_MAX+1);
    }
}

double diffArray(const int datasize, const double *data1, const double *data2)
{
  int i;
  double diff_sum;

  for (i=0; i<datasize; i++)
    {
      // rouding error
      diff_sum += fabs(data1[i] - data2[i]);
    }
}

