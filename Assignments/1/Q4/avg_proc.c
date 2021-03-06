#include <rpc/rpc.h>
#include "avg.h"
#include <stdio.h>
#include <stdlib.h>

/* run locally on 'server' called by a remote client. */
static double median;

int comparator(const void *a, const void *b) {
  double c = * (double *) a;
  double d = * (double *) b;
  return c > d ? 1 : -1;
}

/* 
 * routine notice the _1 the version number 
 * notice the client handle, not sued here but needs to be 
 * a parameter 
 */
double * average_1(input_data *input, CLIENT *client) 
  {

  /* input is paramters were marshalled by genrated routine */
  /*  a pointer to a double, is set to begining of data array  */
  double *dp = input->input_data.input_data_val;
  int len = input->input_data.input_data_len;
  double doubles[(len)];
  
  int i;
  
  for(i = 0; i < len; i++){
    doubles[i] = *dp;
    dp++;
  }

  qsort(doubles, len, sizeof(double), comparator);

  if(len % 2) {
    median = doubles[(len/2)];
  } else {
    median = (doubles[(len/2) - 1] + doubles[(len/2)]) / 2;
  }

  printf("\n%f\n", median);

  return(&median);
}

/* 
 * server stub 'average_1_svc function handle called in avg_svc that was
 * generated by rpcgen 
 * FYI:
 *   result = (*local)((char *)&argument, rqstp);
 *   where local is (char *(*)(char *, struct svc_req *)) average_1_svc;
 */
 
double * average_1_svc(input_data *input, struct svc_req *svc) 
  {
  CLIENT *client;
  return( average_1( input, client) );
  }
