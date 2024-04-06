#include "filetransfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

send_file_res *send_file_1_svc(char **filename, struct svc_req *req) {
  /* NOTE: Do not forget to the proper return value */

  send_file_res *res = malloc(sizeof(send_file_res));

  /*
   * Write the file received from the client req
   * */

  FILE *fp_client_read = fopen(*filename, "r");
  FILE *fp_server_write = fopen(strcat(*filename, "_send_server"), "w");

  if (fp_client_read == NULL) {
    res->errno = 1;
    res->send_file_res_u.errmsg = strdup("fopen failed");
    return res;
  }

  fseek(fp_client_read, 0, SEEK_END);
  long fsize = ftell(fp_client_read);
  fseek(fp_client_read, 0, SEEK_SET);

  char *buffer = malloc(fsize + 1);
  fread(buffer, 1, fsize, fp_client_read);
  buffer[fsize] = 0;

  fwrite(buffer, 1, fsize, fp_server_write);

  fclose(fp_server_write);
  fclose(fp_client_read);

  res->errno = 0;

  return res;
}

retreive_file_res *retreive_file_1_svc(char **filename, struct svc_req *req) {
  retreive_file_res *res = malloc(sizeof(send_file_res));
  FILE *fp = fopen(*filename, "r");

  if (fp == NULL) {
    res->errno = 1;
    res->retreive_file_res_u.errmsg = strdup("fopen failed");
    return res;
  }

  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  printf("File size: %ld\n", fsize);

  char *buffer = malloc(fsize + 1);
  fread(buffer, 1, fsize, fp);
  buffer[fsize] = 0;

  fclose(fp);

  res->errno = 0;
  res->retreive_file_res_u.data = buffer;

  return res;
}
