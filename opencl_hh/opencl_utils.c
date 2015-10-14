#include <stdio.h>

#include "opencl_utils.h"


//cl_uint init_cl(cl_platform_id *p_platform_id, cl_device_id *p_device_id
//	    , cl_context *p_context, cl_command_queue *p_command_queue)

int init_cl(CLInfo *cli, char *kernel_filename)
{
  cl_uint num_devices;
  cl_uint num_platforms;
  cl_int ret;
  size_t ret_size;

  cli->state = 0;

  clGetPlatformIDs(MAX_PLATFORMS, &(cli->platform_id), &num_platforms);
  clGetDeviceIDs(cli->platform_id, CL_DEVICE_TYPE_DEFAULT, MAX_DEVICES, &(cli->device_id), &num_devices);
  if (num_devices == 0)
    {
      return (-1);
    }
  else
    {
      cl_device_id dev = cli->device_id;

      clGetDeviceInfo (dev, CL_DEVICE_VENDOR, sizeof(cli->vender_name), cli->vender_name, &ret_size);
      clGetDeviceInfo (dev, CL_DEVICE_NAME, sizeof(cli->device_name), cli->device_name, &ret_size);
      clGetDeviceInfo (dev, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cli->num_compute_unit), &(cli->num_compute_unit), &ret_size);
      clGetDeviceInfo (dev, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cli->clock_freq), &(cli->clock_freq), &ret_size);
      clGetDeviceInfo (dev, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cli->mem_size),  &(cli->mem_size), &ret_size);
      clGetDeviceInfo (dev, CL_DRIVER_VERSION, sizeof(cli->version), cli->version, &ret_size);
      clGetDeviceInfo(dev, CL_DEVICE_ADDRESS_BITS, sizeof(cli->address_bit),  &(cli->address_bit), &ret_size);
    }

  cli->context = clCreateContext (NULL, 1, &(cli->device_id), NULL, NULL, &ret);
  cli->queue = clCreateCommandQueue (cli->context, cli->device_id, CL_QUEUE_PROFILING_ENABLE, &ret);

  if (kernel_filename != NULL)
    {
      cli->program = read_cl_kernel_src(cli->context, kernel_filename);
      ret = clBuildProgram(cli->program, 1, &(cli->device_id), "", NULL, NULL);
      if (ret != CL_SUCCESS)
	{
	  char buffer[2048];
	  size_t len;
	  clGetProgramBuildInfo(cli->program, cli->device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
	  printf(" [OpenCL Build Error]\n%s\n", buffer);
	  return(cli->state);
	}

    }


  cli->state = 1;
  return(cli->state);
}

int finalize_cl(CLInfo *cli)
{
  clReleaseCommandQueue(cli->queue);
  clReleaseContext(cli->context);
  cli->state = 0;
}

void print_cl_info(CLInfo *cli)
{
  printf (" [OpenCL Information]\n");
  printf ("   * Vendor: %s\n", cli->vender_name);
  printf ("   * Device: %s\n", cli->device_name);
  printf ("   * Compute Units: %d\n", cli->num_compute_unit);
  printf ("   * Clock Frequency: %d [MHz]\n", cli->clock_freq);
  printf ("   * Memory Size: %d [MiB]\n", (int)(cli->mem_size / 1024 / 1024));
  printf ("   * Version: %s\n", cli->version);
  printf ("   * Address Bits: %d\n", cli->address_bit);
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

