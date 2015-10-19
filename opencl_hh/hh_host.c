#include <stdio.h>
#include <stdio.h>
#include <math.h>

//#define USE_MPI
#ifdef USE_MPI
#include <mpi.h>
#endif

#include <CL/cl.h>
#include "opencl_utils.h"
#include "calc_utils.h"
#include "hh.h"


static CLInfo *cli;


static void calc_opencl(const unsigned long datasize, const double *data1, const double *data2, double *result)
{
  cl_mem d_data1, d_data2, d_result;
  size_t global_item_size[3], local_item_size[3];

  cl_event ev_calc, ev_copy;
  double calc_time, copy_time;
  cl_ulong prof_start, prof_calc_end, prof_copy_end;

  cl_int ret;
  size_t mem_size = datasize * sizeof(data1[0]);
  cl_uint block_size;
  block_size = cli->num_compute_unit*32;

  char kernel_name[] = "vec_add";

  cli->kernel = clCreateKernel(cli->program, kernel_name, NULL);

  /* setup item size */
  global_item_size[0] = (unsigned long)ceil((double)datasize / block_size) * block_size;
  global_item_size[1] = 1;
  global_item_size[2] = 1;
  local_item_size[0] = block_size;
  local_item_size[1] = 1;
  local_item_size[2] = 1;

  /* setup global memory */
  d_data1  = clCreateBuffer(cli->context, CL_MEM_READ_ONLY, mem_size, NULL, NULL);
  d_data2  = clCreateBuffer(cli->context, CL_MEM_READ_ONLY, mem_size, NULL, NULL);
  d_result = clCreateBuffer(cli->context, CL_MEM_WRITE_ONLY, mem_size, NULL, NULL);
  
  clEnqueueWriteBuffer(cli->queue, d_data1, CL_TRUE, 0, mem_size, data1, 0, NULL, NULL);
  clEnqueueWriteBuffer(cli->queue, d_data2, CL_TRUE, 0, mem_size, data2, 0, NULL, NULL);

  clSetKernelArg(cli->kernel, 0, sizeof(unsigned long), &datasize);
  clSetKernelArg(cli->kernel, 1, sizeof(cl_mem), &d_data1);
  clSetKernelArg(cli->kernel, 2, sizeof(cl_mem), &d_data2);
  clSetKernelArg(cli->kernel, 3, sizeof(cl_mem), &d_result);

  /* execute kernel */
  clEnqueueNDRangeKernel(cli->queue, cli->kernel, 1, NULL, global_item_size, local_item_size, 0, NULL, &ev_calc);
  clFinish(cli->queue);

  /* read buffers */
  clEnqueueReadBuffer(cli->queue, d_result, CL_TRUE, 0, mem_size, result, 0, NULL, &ev_copy);

  clGetEventProfilingInfo(ev_calc, CL_PROFILING_COMMAND_QUEUED, sizeof(cl_ulong), &prof_start, NULL);
  clGetEventProfilingInfo(ev_calc, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &prof_calc_end, NULL);
  clGetEventProfilingInfo(ev_copy, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &prof_copy_end, NULL);

  calc_time = (double)(prof_calc_end - prof_start) / 1000000.0;
  copy_time = (double)(prof_copy_end - prof_calc_end) / 1000000.0;
  printf("   * calc_time = %8.2f, copy_time = %8.2f\n", calc_time, copy_time);

  /* finalize */
  clReleaseEvent(ev_calc);
  clReleaseEvent(ev_copy);
  clReleaseMemObject(d_data1);
  clReleaseMemObject(d_data2);
  clReleaseMemObject(d_result);
  clReleaseKernel(cli->kernel);
}


void calc_host_exp_add(const unsigned long datasize, const double *data1, const double *data2, double *result)
{
  int i;
  for (i=0; i<datasize; i++)
    {
      result[i] = exp(data1[i]) + data2[i];
    }
}

/*
int main()
{
  int i;
  const unsigned long datasize = 10024 * 1024 * 4;
  int times = 10;
  double *data1;
  double *data2;
  double *result_host, *result_opencl;
  double diff = 0.0;
  double time_host, time_opencl=0.f;
  size_t mem_size = datasize * sizeof(double);
  CLInfo _cli;
  cli = &_cli;
  
  printf (" [Initialize Device]\n");
  init_cl(cli, "vec_calc.cl");
  if (cli->state != 1)
    {
      printf ("No device found.\n");
      exit(-1);
    }
  print_cl_info(cli);

  data1 = (double *)malloc(mem_size);
  data2 = (double *)malloc(mem_size);
  result_host = (double *)malloc(mem_size);
  result_opencl = (double *)malloc(mem_size);
  if (data1 == NULL || data2 == NULL || result_host == NULL || result_opencl == NULL)
    {
      printf ("Memory allocation error.\n");
      exit(-1);
    }

  setRandomData(datasize, data1);
  setRandomData(datasize, data2);

  printf(" [Host Calculation]\n");
  //time_host   = timeFunc (calc_host_add,   times, datasize, data1, data2, result_host);
  time_host   = timeFunc (calc_host_exp_add,   times, datasize, data1, data2, result_host);
  printf(" [OpenCL Calculation]\n");
  //set_kernel(cli, "vec_add");
  set_kernel(cli, "vec_exp_add");
  time_opencl = timeFunc (calc_opencl, times, datasize, data1, data2, result_opencl);

  diff = diffArray(datasize, result_host, result_opencl);

  free (data1);
  free (data2);
  free (result_host);
  free (result_opencl);
  release_kernel(cli);
  finalize_cl(cli);

  printf (" [Result]\n");
  printf ("   * Host   : %10.6f [sec]\n", time_host);
  printf ("   * OpenCL : %10.6f [sec]\n", time_opencl);
  printf ("   * Diff   : %10.2f (%s)\n", diff, (diff < 0.00001? "OK!" : "Fail"));

  return (0);
}
*/

void host_add(const unsigned long datasize, const double *data1, const double *data2, double *result)
{
  int i;
  for (i=0; i<datasize; i++)
    {
      result[i] = data1[i] + data2[i];
    }
}

void opencl_hh(CLInfo *cli,
	       const int max_t,
	       const unsigned long datasize,
	       const FLOAT *host_n,
	       const FLOAT *host_m,
	       const FLOAT *host_h,
	       const FLOAT *host_table,
	       FLOAT *host_v,
	       FLOAT *host_dv,
	       FLOAT *result)
{
  size_t global_item_size[3]={1, 1, 1}, local_item_size[3]={1, 1, 1};

  cl_mem dev_n, dev_m, dev_h, dev_v, dev_dv, dev_table;

  cl_kernel kernel_hh_init, kernel_hh_calc;

  cl_event ev_calc, ev_copy;
  double calc_time, copy_time;
  cl_ulong prof_start, prof_calc_end, prof_copy_end;

  cl_int ret;
  int i;

  size_t mem_size = datasize * sizeof(FLOAT);
  cl_uint block_size;
  block_size = cli->num_compute_unit*32;

  kernel_hh_init = clCreateKernel(cli->program, "cl_hh_init", NULL);
  kernel_hh_calc = clCreateKernel(cli->program, "cl_hh_calc", NULL);

  /* setup item size */
  global_item_size[0] = (unsigned long)ceil((double)datasize / block_size) * block_size;
  local_item_size[0] = block_size;

  /* setup global memory */
  dev_n = clCreateBuffer(cli->context,  CL_MEM_READ_WRITE, mem_size, NULL, NULL);
  dev_m = clCreateBuffer(cli->context,	CL_MEM_READ_WRITE, mem_size, NULL, NULL);
  dev_h = clCreateBuffer(cli->context,	CL_MEM_READ_WRITE, mem_size, NULL, NULL);
  dev_table = clCreateBuffer(cli->context, CL_MEM_READ_WRITE, TABLE_SIZE * 6 * sizeof(FLOAT), NULL, NULL);
  dev_v = clCreateBuffer(cli->context,  CL_MEM_READ_WRITE, mem_size, NULL, NULL);
  dev_dv = clCreateBuffer(cli->context, CL_MEM_READ_WRITE, mem_size, NULL, NULL);

  clEnqueueWriteBuffer(cli->queue, dev_n,  CL_TRUE, 0, mem_size, host_n,  0, NULL, NULL);
  clEnqueueWriteBuffer(cli->queue, dev_m,  CL_TRUE, 0, mem_size, host_m,  0, NULL, NULL);
  clEnqueueWriteBuffer(cli->queue, dev_h,  CL_TRUE, 0, mem_size, host_h,  0, NULL, NULL);
  clEnqueueWriteBuffer(cli->queue, dev_table,  CL_TRUE, 0, TABLE_SIZE * 6 * sizeof(FLOAT), host_table,  0, NULL, NULL);
  clEnqueueWriteBuffer(cli->queue, dev_v,  CL_TRUE, 0, mem_size, host_v,  0, NULL, NULL);
  clEnqueueWriteBuffer(cli->queue, dev_dv, CL_TRUE, 0, mem_size, host_dv, 0, NULL, NULL);

  /* setup arguments */
  clSetKernelArg(kernel_hh_calc, 0, sizeof(unsigned long), &datasize);
  clSetKernelArg(kernel_hh_calc, 1, sizeof(cl_mem), &dev_n);
  clSetKernelArg(kernel_hh_calc, 2, sizeof(cl_mem), &dev_m);
  clSetKernelArg(kernel_hh_calc, 3, sizeof(cl_mem), &dev_h);
  clSetKernelArg(kernel_hh_calc, 4, sizeof(cl_mem), &dev_table);
  clSetKernelArg(kernel_hh_calc, 5, sizeof(cl_mem), &dev_v);

  /* execute kernel */
  for (i=0; i<max_t/DT; i++)
    {
      clEnqueueNDRangeKernel(cli->queue, kernel_hh_calc, 1, NULL, global_item_size, local_item_size, 0, NULL, &ev_calc);
      clFinish(cli->queue);
      clEnqueueReadBuffer(cli->queue, dev_v, CL_TRUE, 0, mem_size, host_v, 0, NULL, &ev_copy);
      result[i] = host_v[0];
    }

  /* get profile */


  /* finalize */
  clReleaseMemObject(dev_n);
  clReleaseMemObject(dev_m);
  clReleaseMemObject(dev_h);
  clReleaseMemObject(dev_table);
  clReleaseMemObject(dev_v);
  clReleaseMemObject(dev_dv);
  clReleaseKernel(kernel_hh_init);
  clReleaseKernel(kernel_hh_calc);
}

#define MAX_T 1

int main(int argc, char **argv)
{
  double host_start, host_finish;
  double opencl_start, opencl_finish;
  double diff;
  unsigned long datasize = N_COMPARTMENT;
  size_t mem_size = datasize * sizeof(double);

  CLInfo _cli;
  cli = &_cli;

  FLOAT *result_host;
  FLOAT *result_opencl;
  int i;

  printf (" [Initialize Device]\n");

#ifdef USE_MPI
  int myid;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
#endif

  init_cl(cli, "hh.cl");
  if (cli->state != 1)
    {
      printf ("No device found.\n");
      exit(-1);
    }
  print_cl_info(cli);

  hh_initialize(datasize);
  hh_makeTable();

  result_host = (FLOAT *)malloc(MAX_T / DT * sizeof(FLOAT));
  result_opencl = (FLOAT *)malloc(MAX_T / DT * sizeof(FLOAT));

#ifdef KCOMPUTER
  fapp_start("calc", 1, 1);  
#endif


  printf(" [Host Calculation]\n");
  host_start = getTime();
  //host_add(datasize, hh_n, hh_m, result_host);
  hh_calc(MAX_T, result_host);
  host_finish = getTime();

  printf(" [OpenCL Calculation]\n");

  hh_initialize(datasize);
  hh_makeTable();

  opencl_start = getTime();
  opencl_hh(cli, MAX_T, datasize, hh_n, hh_m, hh_h, (FLOAT *)hh_table, hh_v, hh_dv, result_opencl);
  //host_add(datasize, hh_n, hh_m, result_opencl);
  opencl_finish = getTime();

#ifdef KCOMPUTER
  fapp_stop("calc", 1, 1);
#endif

  diff = diffArray(datasize, result_host, result_opencl);

  for (i=0; i<MAX_T/DT; i++)
    {
      printf ("%6d %8.2f %8.2f\n", i, result_host[i], result_opencl[i]);
    }

#ifdef USE_MPI
  MPI_Finalize();
#endif

  finalize_cl(cli);

  printf (" [Result]\n");
  printf ("   * Host   : %10.6f [sec]\n", host_finish - host_start);
  printf ("   * OpenCL : %10.6f [sec]\n", opencl_finish - opencl_start);
  printf ("   * Diff   : %10.2f (%s)\n", diff, (diff < 0.00001? "OK!" : "Fail"));

  free(result_host);
  free(result_opencl);

  return(0);

}
