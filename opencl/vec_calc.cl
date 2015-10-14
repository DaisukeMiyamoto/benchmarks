
//#define FLOAT float
#define FLOAT double

__kernel void vec_add (const int datasize, __global const FLOAT *data1, __global const FLOAT *data2, __global FLOAT *result)
{
  int gid = get_global_id(0);

  if (gid > datasize)
    {
      return;
    }

  result[gid] = data1[gid] + data2[gid];  
}

__kernel void vec_exp_add (const int datasize, __global const FLOAT *data1, __global const FLOAT *data2, __global FLOAT *result)
{
  int gid = get_global_id(0);

  if (gid > datasize)
    {
      return;
    }

  result[gid] = exp(data1[gid]) + data2[gid];  
}

