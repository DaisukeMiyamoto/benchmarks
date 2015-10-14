#include <stdio.h>
#include <stdio.h>
#include <math.h>

#include <CL/cl.h>
#include "opencl_utils.h"
#include "calc_utils.h"


static CLInfo cli;

static void calc_opencl(const int datasize, const double *data1, const double *data2, double *result)
{
  char cl_filename[] = "vec_add.cl";
  cl_int cl_datasize = datasize;
  int num_generator = 32;
  cl_uint num_compute_unit;
  cl_uint num_work_item;

  cl_program program = NULL;
  cl_kernel kernel_mt = NULL, kernel_pi = NULL;

  cl_mem rand, count;
  //cl_uint *result;
  size_t global_item_size[3], local_item_size[3];
  cl_mem dev_mts;
  cl_event ev_mt_end, ev_pi_end, ev_copy_end;
  cl_ulong prof_start, prof_mt_end, prof_pi_end, prof_copy_end;

  int i;
  cl_int ret;

  /* initialize */

  num_compute_unit = cli.num_compute_unit;
  if (num_compute_unit < 1)
    {
      exit(-1);
    }
  num_work_item = (num_generator+(num_compute_unit-1)) / num_compute_unit;

  /* setup item size */
  //global_item_size[0] = num_generator;
  global_item_size[0] = num_work_item * num_compute_unit;
  global_item_size[1] = 1;
  global_item_size[2] = 1;
  //local_item_size[0] = num_generator;
  local_item_size[0] = num_work_item;
  local_item_size[1] = 1;
  local_item_size[2] = 1;

  /* read and build kernel */
  /*
  program = read_cl_kernel_src(context, cl_filename);
  clBuildProgram(program, 1, &device_id, "", NULL, NULL);
  kernel_mt = clCreateKernel(program, "genrand", &ret);
  kernel_pi = clCreateKernel(program, "calc_pi", &ret);
  */

  /* setup global memory */
  /*
  rand = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_uint)*num_rand*num_generator, NULL, &ret);
  count = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_uint)*num_generator, NULL, &ret);
  dev_mts = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(mts), NULL, &ret);
  clEnqueueWriteBuffer(command_queue, dev_mts, CL_TRUE, 0, sizeof(mts), mts, 0, NULL, NULL);

  clSetKernelArg(kernel_mt, 0, sizeof(cl_mem), (void*)&rand);
  clSetKernelArg(kernel_mt, 1, sizeof(cl_mem), (void*)&dev_mts);
  clSetKernelArg(kernel_mt, 2, sizeof(num_rand), &num_rand);
  clSetKernelArg(kernel_mt, 3, sizeof(num_generator), &num_generator);

  clSetKernelArg(kernel_pi, 0, sizeof(cl_mem), (void*)&count);
  clSetKernelArg(kernel_pi, 1, sizeof(cl_mem), (void*)&rand);
  clSetKernelArg(kernel_pi, 2, sizeof(num_rand), &num_rand);
  clSetKernelArg(kernel_pi, 3, sizeof(num_generator), &num_generator);
  */
  
  /* execute kernel */
  /*
  clEnqueueNDRangeKernel(command_queue, kernel_mt, 1, NULL, global_item_size, local_item_size, 0, NULL, &ev_mt_end);
  clEnqueueNDRangeKernel(command_queue, kernel_pi, 1, NULL, global_item_size, local_item_size, 0, NULL, &ev_pi_end);
  clFinish(command_queue);
  */

  /* read buffers */
  //clEnqueueReadBuffer(command_queue, count, CL_TRUE, 0, sizeof(cl_uint)*num_generator, result, 0, NULL, &ev_copy_end);


  /* show result */
  /*
  count_all = 0;
  for(i=0; i<num_generator; i++){
    count_all += result[i];
  }

  pi = ((double)count_all)/(num_rand * num_generator) * 4;
  printf("   * pi = %f\n", pi);
  */

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
  /*
  clReleaseEvent(ev_mt_end);
  clReleaseEvent(ev_pi_end);
  clReleaseEvent(ev_copy_end);

  clReleaseMemObject(rand);
  clReleaseMemObject(count);
  clReleaseKernel(kernel_mt);
  clReleaseKernel(kernel_pi);
  */

}


void calc_host(const int datasize, const double *data1, const double *data2, double *result)
{
  int i;
  for (i=0; i<datasize; i++)
    {
      result[i] = data1[i] + data2[i];
    }
}

double timeFunc(void (*func)(const int datasize, const double *data1, const double *data2, double *result),
		const int loop,
		const int datasize,
		const double *data1,
		const double *data2,
		double *result)
{
  double start, end;
  int i;

  start = getTime();
  for (i=0; i<loop; i++)
    {
      func(datasize, data1, data2, result);
    }
  end = getTime();

  return (end - start);
    
}

int main()
{
  const int datasize = 1000000;
  double *data1;
  double *data2;
  double *result;
  double time_host, time_opencl=0.f;

  printf (" [Initialize Device]\n");
  init_cl(&cli);
  print_cl_info(&cli);

  data1 = malloc(datasize * sizeof(double));
  data2 = malloc(datasize * sizeof(double));
  result = malloc(datasize * sizeof(double));

  printf(" [Host Calculation]\n");
  time_host   = timeFunc (calc_host,   100, datasize, data1, data2, result);
  printf(" [OpenCL Calculation]\n");
  time_opencl = timeFunc (calc_opencl, 100, datasize, data1, data2, result);

  free (data1);
  free (data2);
  free (result);
  finalize_cl(&cli);

  printf (" [Result]\n");
  printf ("   * Host   : %8.2f [ms]\n", time_host);
  printf ("   * OpenCL : %8.2f [ms]\n", time_opencl);

  return 0;
}

