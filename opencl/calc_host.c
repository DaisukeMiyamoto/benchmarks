#include <stdio.h>
#include <stdio.h>
#include <math.h>

#include <CL/cl.h>
#include "opencl_utils.h"
#include "calc_utils.h"


static CLInfo *cli;

static void calc_opencl(const int datasize, const double *data1, const double *data2, double *result)
{
  //cl_int cl_datasize = datasize;
  //cl_uint num_compute_unit;
  //cl_uint num_work_item;

  cl_kernel kernel = NULL;
  cl_mem d_data1, d_data2, d_result;
  size_t global_item_size[3], local_item_size[3];

  cl_event ev_calc_end, ev_copy_end;
  cl_ulong prof_start, prof_end, prof_copy_end;

  int i;
  cl_int ret;
  size_t mem_size = datasize * sizeof(double);

  /* setup item size */
  global_item_size[0] = (int)ceil((double)datasize / cli->num_compute_unit) * cli->num_compute_unit;
  global_item_size[1] = 1;
  global_item_size[2] = 1;
  local_item_size[0] = cli->num_compute_unit;
  local_item_size[1] = 1;
  local_item_size[2] = 1;

  /* read and build kernel */
  kernel = clCreateKernel(cli->program, "vec_add", &ret);

  /* setup global memory */
  d_data1  = clCreateBuffer(cli->context, CL_MEM_READ_ONLY, mem_size, NULL, NULL);
  d_data2  = clCreateBuffer(cli->context, CL_MEM_READ_ONLY, mem_size, NULL, NULL);
  d_result = clCreateBuffer(cli->context, CL_MEM_WRITE_ONLY, mem_size, NULL, NULL);
  
  clEnqueueWriteBuffer(cli->queue, d_data1, CL_TRUE, 0, mem_size, data1, 0, NULL, NULL);
  clEnqueueWriteBuffer(cli->queue, d_data2, CL_TRUE, 0, mem_size, data2, 0, NULL, NULL);

  clSetKernelArg(kernel, 0, sizeof(unsigned int), &datasize);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_data1);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_data2);
  clSetKernelArg(kernel, 3, sizeof(cl_mem), &d_result);

  /* execute kernel */
  clEnqueueNDRangeKernel(cli->queue, kernel, 1, NULL, global_item_size, local_item_size, 0, NULL, &ev_calc_end);
  clFinish(cli->queue);

  /* read buffers */
  clEnqueueReadBuffer(cli->queue, d_result, CL_TRUE, 0, mem_size, result, 0, NULL, &ev_copy_end);

  /* show result */
  /*
  clGetEventProfilingInfo(ev_mt_end, CL_PROFILING_COMMAND_QUEUED, sizeof(cl_ulong), &prof_start, NULL);
  clGetEventProfilingInfo(ev_mt_end, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &prof_mt_end, NULL);
  clGetEventProfilingInfo(ev_pi_end, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &prof_pi_end, NULL);
  clGetEventProfilingInfo(ev_copy_end, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &prof_copy_end, NULL);

  printf("   * mt:   %8.2f [ms]\n", (prof_mt_end - prof_start)/ 1000000.0);
  printf("   * pi:   %8.2f [ms]\n", (prof_pi_end - prof_mt_end)/ 1000000.0);
  printf("   * copy: %8.2f [ms]\n", (prof_copy_end - prof_pi_end)/ 1000000.0);
  */

  /* finalize */
  clReleaseEvent(ev_calc_end);
  clReleaseEvent(ev_copy_end);
  clReleaseMemObject(d_data1);
  clReleaseMemObject(d_data2);
  clReleaseMemObject(d_result);
  clReleaseKernel(kernel);

}


void calc_host(const int datasize, const double *data1, const double *data2, double *result)
{
  int i;
  for (i=0; i<datasize; i++)
    {
      result[i] = data1[i] + data2[i];
    }
}


int main()
{
  int i;
  const int datasize = 10024 * 1024;
  double *data1;
  double *data2;
  double *result_host, *result_opencl;
  double diff = 0.0;
  double time_host, time_opencl=0.f;
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

  data1 = malloc(datasize * sizeof(double));
  data2 = malloc(datasize * sizeof(double));
  result_host = malloc(datasize * sizeof(double));
  result_opencl = malloc(datasize * sizeof(double));

  setRandomData(datasize, data1);
  setRandomData(datasize, data2);

  printf(" [Host Calculation]\n");
  time_host   = timeFunc (calc_host,   100, datasize, data1, data2, result_host);
  printf(" [OpenCL Calculation]\n");
  time_opencl = timeFunc (calc_opencl, 100, datasize, data1, data2, result_opencl);

  diff = diffArray(datasize, result_host, result_opencl);

  free (data1);
  free (data2);
  free (result_host);
  free (result_opencl);
  finalize_cl(cli);


  printf (" [Result]\n");
  printf ("   * Host   : %10.6f [sec]\n", time_host);
  printf ("   * OpenCL : %10.6f [sec]\n", time_opencl);
  printf ("   * Diff   : %10.2f (%s)\n", diff, (diff < 0.00001? "OK!" : "Fail"));

  return (0);
}

