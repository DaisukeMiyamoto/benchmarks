#include <stdio.h>

#include "opencl_utils.h"

cl_uint init_cl(cl_platform_id *p_platform_id, cl_device_id *p_device_id
	    , cl_context *p_context, cl_command_queue *p_command_queue)
{
  cl_context context = NULL;
  cl_command_queue command_queue = NULL;
  cl_uint num_platforms;
  cl_uint num_devices;
  cl_uint num_compute_unit;
  cl_int ret;
  size_t ret_size;

  clGetPlatformIDs(MAX_PLATFORMS, p_platform_id, &num_platforms);
  clGetDeviceIDs(*p_platform_id, CL_DEVICE_TYPE_DEFAULT, MAX_DEVICES, p_device_id, &num_devices);
  if (num_devices == 0)
    {
      printf ("No device found.\n");
      return (-1);
    }
  else
    {
      cl_device_id dev = *p_device_id;
      char buf[MAX_BUFFER_SIZE];
      cl_uint ui;
      cl_ulong ul;

      clGetDeviceInfo (dev, CL_DEVICE_VENDOR, sizeof(buf), buf, &ret_size);
      printf ("   * Vendor: %s\n", buf);
      clGetDeviceInfo (dev, CL_DEVICE_NAME, sizeof(buf), buf, &ret_size);
      printf ("   * Device: %s\n", buf);
      clGetDeviceInfo (dev, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(num_compute_unit), &num_compute_unit, &ret_size);
      printf ("   * Compute Units: %d\n", num_compute_unit);
      clGetDeviceInfo (dev, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(ui), &ui, &ret_size);
      printf ("   * Clock Frequency: %d [MHz]\n", ui);
      clGetDeviceInfo (dev, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(ul),  &ul, &ret_size);
      printf ("   * Memory Size: %d [MiB]\n", (int)(ul / 1024 / 1024));
      clGetDeviceInfo (dev, CL_DRIVER_VERSION, sizeof(buf), buf, &ret_size);
      printf ("   * Version: %s\n", buf);
      clGetDeviceInfo(dev, CL_DEVICE_ADDRESS_BITS, sizeof(ui),  &ui, &ret_size);
      printf ("   * Address Bits: %d\n", ui);
    }

  context = clCreateContext (NULL, 1, p_device_id, NULL, NULL, &ret);
  command_queue = clCreateCommandQueue (context, *p_device_id, CL_QUEUE_PROFILING_ENABLE, &ret);
  *p_context = context;
  *p_command_queue = command_queue;

  return(num_compute_unit);
}

cl_program read_cl_kernel_src(cl_context context, const char* filename)
{
  FILE *fp;
  cl_program program = NULL;
  size_t kernel_code_size;
  char *kernel_src_str;
  cl_int ret;

  fp = fopen(filename, "r");
  kernel_src_str = (char*)malloc(MAX_SOURCE_SIZE);
  kernel_code_size = fread(kernel_src_str, 1, MAX_SOURCE_SIZE, fp);
  program = clCreateProgramWithSource(context, 1, (const char **)&kernel_src_str,
				      (const size_t *)&kernel_code_size, &ret);
  fclose(fp);

  return(program);
}

