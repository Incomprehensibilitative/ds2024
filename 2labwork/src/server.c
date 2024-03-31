#include "filetransfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

send_file_res *send_file_1_svc(send_file_args *arg, struct svc_req *req) {
  /* NOTE: Do not forget to the proper return value */

  send_file_res *res = malloc(sizeof(send_file_res));

  /*
   * Write the file received from the client req
   * */
  FILE *fp = fopen(strcat(arg->fname, "_send_server"), "a");
  if (fp == NULL) {
    perror("fopen failed");
    exit(EXIT_FAILURE);
  }

  printf("Writing: %s\n", arg->fdata);

  int result = fputs(arg->fdata, fp);

  if (result == EOF) {
    perror("fputs failed");
    exit(EXIT_FAILURE);
  }

  if (fclose(fp) != 0) {
    perror("fclose failed");
    exit(EXIT_FAILURE);
  }

  res->errno = 0;

  return res;
}

retreive_file_res *retreive_file_1_svc(char **arg, struct svc_req *req) {
  static retreive_file_res res;

  /* TODO: Add your implementation here */

  return &res;
}
