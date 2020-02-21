#include <rpc/rpc.h>
#include "avg.h"
#include <stdio.h>
#include <stdlib.h>

static echoed_input_data echo;
 
echoed_input_data * echo_1_svc(input_data *input, struct svc_req *svc) {
  strncpy(echo.text, input->text, strlen(input->text) + 1);
  return &echo;
  }
