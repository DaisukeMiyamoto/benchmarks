//#define FLOAT float
#define FLOAT double
#define EXP exp

#define HH_DT (0.025)
#define HH_E_K (-77.0)
#define HH_E_NA (50.0)
#define HH_V_REST (-54.3)

#define HH_CM (1.0)
#define HH_CM_INV (1.0)
#define HH_GK_MAX (36.)
#define HH_GNA_MAX (120.)
#define HH_GM (0.3)

#define TABLE_SIZE 201
#define TABLE_MAX_V 100.0f
#define TABLE_MIN_V -100.0f


#define TABLE_N_TAU(x) table[(x)*6 + 0]
#define TABLE_N_INF(x) table[(x)*6 + 1]
#define TABLE_M_TAU(x) table[(x)*6 + 2]
#define TABLE_M_INF(x) table[(x)*6 + 3]
#define TABLE_H_TAU(x) table[(x)*6 + 4]
#define TABLE_H_INF(x) table[(x)*6 + 5]


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
			  __global FLOAT *data_n,
			  __global FLOAT *data_m,
			  __global FLOAT *data_h,
			  __global const FLOAT *table,
			  __global FLOAT *data_v
			  )
{
  int i = get_global_id(0);
  if (i > datasize) return;

  int v_i;
  FLOAT theta;
  FLOAT tau_n, n_inf, tau_m, m_inf, tau_h, h_inf;
  //FLOAT hh_gk_max, hh_gna_max, hh_gm, hh_e_k, hh_e_na, hh_v_rest;
  FLOAT i_inj = 0.0;

  v_i = (int)(data_v[i] -TABLE_MIN_V);
  theta = (data_v[i] - TABLE_MIN_V) - (FLOAT)v_i;

  if(!(v_i >= TABLE_SIZE || v_i<0) )
    {
      ;
    }
  else if(v_i >= TABLE_SIZE)
    {
      v_i=TABLE_SIZE-1; theta=1.0;
    }
  else if(v_i <  0)
    {
      v_i=0; theta=0.0;
    }

  tau_n = TABLE_N_TAU(v_i);
  n_inf = TABLE_N_INF(v_i);
  tau_m = TABLE_M_TAU(v_i);
  m_inf = TABLE_M_INF(v_i);
  tau_h = TABLE_H_TAU(v_i);
  h_inf = TABLE_H_INF(v_i);
	
  tau_n = (tau_n + theta * (TABLE_N_TAU(v_i+1) - tau_n));
  tau_m = (tau_m + theta * (TABLE_M_TAU(v_i+1) - tau_m));
  tau_h = (tau_h + theta * (TABLE_H_TAU(v_i+1) - tau_h));
  n_inf = n_inf + theta * (TABLE_N_INF(v_i+1) - n_inf) - data_n[i];
  m_inf = m_inf + theta * (TABLE_M_INF(v_i+1) - m_inf) - data_m[i];
  h_inf = h_inf + theta * (TABLE_H_INF(v_i+1) - h_inf) - data_h[i];
  
  data_n[i] += (1.0f - EXP(-HH_DT/tau_n)) * n_inf;
  data_m[i] += (1.0f - EXP(-HH_DT/tau_m)) * m_inf;
  data_h[i] += (1.0f - EXP(-HH_DT/tau_h)) * h_inf;
  
  data_v[i] += HH_DT * HH_CM_INV * (HH_GK_MAX * data_n[i] * data_n[i] * data_n[i] * data_n[i] * (HH_E_K - data_v[i]) 
				  + HH_GNA_MAX * data_m[i] * data_m[i] * data_m[i] * data_h[i] * (HH_E_NA - data_v[i])
				  + HH_GM * (HH_V_REST - data_v[i]) + i_inj);

}
