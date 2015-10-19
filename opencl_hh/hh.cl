//#define FLOAT float
#define FLOAT double

__kernel void cl_hh_init (const unsigned long datasize,
			  __global const FLOAT *data1,
			  __global const FLOAT *data2,
			  __global FLOAT *result
			  )
{
  int gid = get_global_id(0);
  if (gid > datasize) return;
  result[gid] = data1[gid] + data2[gid];  
}


__kernel void cl_hh_calc (const unsigned long datasize,
			  __global const FLOAT *data1,
			  __global const FLOAT *data2,
			  __global FLOAT *result
			  )
{
  int gid = get_global_id(0);
  if (gid > datasize) return;
  result[gid] = data1[gid] + data2[gid];  
}
