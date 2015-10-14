#ifndef __OPENCL_UTILS_H__
#define __OPENCL_UTILS_H__

#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)
#define MAX_PLATFORMS (1)
#define MAX_DEVICES (1)
#define MAX_TEXT_BUFFER_SIZE 256

typedef struct _cl_info {
  int state;
  cl_platform_id platform_id;
  cl_device_id device_id;
  cl_context context;
  cl_command_queue queue;
  cl_program program;
  //cl_uint num_work_item;

  char vender_name[MAX_TEXT_BUFFER_SIZE];
  char device_name[MAX_TEXT_BUFFER_SIZE];
  cl_uint num_compute_unit;
  cl_uint clock_freq;
  cl_ulong mem_size;
  char version[MAX_TEXT_BUFFER_SIZE];
  cl_uint address_bit;
} CLInfo;

/*
cl_uint init_cl(cl_platform_id *p_platform_id, cl_device_id *p_device_id
		, cl_context *p_context, cl_command_queue *p_command_queue);
*/

int init_cl(CLInfo *cli, char *kernel_filename);
int finalize_cl(CLInfo *cli);
void print_cl_info(CLInfo *cli);

cl_program read_cl_kernel_src(cl_context context, const char* filename);

#endif
