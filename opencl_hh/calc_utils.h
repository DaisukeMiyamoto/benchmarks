#ifndef __CALC_UTILS_H__
#define __CALC_UTILS_H__

//#define GET_TIME_METHOD 1

double getTime();
void setRandomData(const int size, double *data);
double diffArray(const int datasize, const double *data1, const double *data2);
double timeFunc(void (*func)(const unsigned long datasize, const double *data1, const double *data2, double *result),
		const int loop,
		const int datasize,
		const double *data1,
		const double *data2,
		double *result);

#endif
