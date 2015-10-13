#include <stdio.h>
#include <CL/cl.h>
#include <stdio.h>
#include <math.h>

#include "opencl_utils.h"

void calc_opencl(int datasize, double *data1, double *data2, double *result, const char *cl_filename)
{
  //cl_int num_rand = 4096 * 256;
  cl_int num_rand = 4096 * 256;
  int count_all, i;
  //int num_generator = sizeof(mts)/sizeof(mts[0]);
  int num_generator = 32;
  double pi;

  cl_platform_id platform_id = NULL;
  cl_device_id device_id = NULL;
  cl_context context = NULL;
  cl_command_queue command_queue = NULL;
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

  cl_int ret;

  /* initialize */
  printf (" [Initialize Device]\n");
  num_compute_unit = init_cl(&platform_id, &device_id, &context, &command_queue);
  if (num_compute_unit < 1)
    {
      exit(-1);
    }
  num_work_item = (num_generator+(num_compute_unit-1)) / num_compute_unit;
  printf ("   * Wrok Items: %d\n", num_work_item);

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

  /* setup local memory */
  //result = (cl_uint*)malloc(sizeof(cl_uint)*num_generator);


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
  printf(" [Calculation]\n");
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

  /* show profile */
  printf(" [Profile]\n");
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

  //clReleaseProgram(program);
  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);

}


double *calc_host(int datasize, double *data1, double *data2, double *result)
{
  ;
}

int main()
{
  const int datasize = 100;
  double *data1;
  double *data2;
  double *result;

  calc_host (datasize, data1, data2, result);
  calc_opencl (datasize, data1, data2, result, "vec_add.cl");

  return 0;
}

