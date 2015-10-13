#ifndef __OPENCL_UTILS_H__
#define __OPENCL_UTILS_H__

#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)
#define MAX_PLATFORMS (1)
#define MAX_DEVICES (1)
#define MAX_BUFFER_SIZE 1024


cl_uint init_cl(cl_platform_id *p_platform_id, cl_device_id *p_device_id
		, cl_context *p_context, cl_command_queue *p_command_queue);
cl_program read_cl_kernel_src(cl_context context, const char* filename);

#endif
