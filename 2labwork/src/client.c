#include "filetransfer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tirpc/rpc/clnt.h>

#define SERVER "localhost"
int main(void) {
  CLIENT *client;

  /*
   * Set up the connection to the server
   * */
  client = clnt_create(SERVER, FILETRANSFER_PROG, FILETRANSFER_VERS, "udp");

  if (client == NULL) {
    perror("Cannot connect to server\n");
    clnt_pcreateerror(SERVER);
    exit(1);
  }

  char *filename = "text";
  send_file_res *send_res;
  send_res = send_file_1(&filename, client);

  if (send_res->errno != 0)
    printf("%s\n", send_res->send_file_res_u.errmsg);
  else
    printf("Send File Successfully\n");

  /*
   * ====================================
   * Read a file from server
   * ====================================
   * */

  retreive_file_res *ret_res;
  char *request_filename = "server_text";

  ret_res = retreive_file_1(&request_filename, client);

  if (ret_res->errno != 0)
    printf("%s\n", ret_res->retreive_file_res_u.errmsg);
  else
    printf("Retreieve File Successfully");

  FILE *fp = fopen("server_text_recv", "w");
  if (fp == NULL) {
    perror("fopen failed");
    exit(EXIT_FAILURE);
  }

  fputs(ret_res->retreive_file_res_u.data, fp);

  if (fclose(fp) != 0) {
    perror("fclose failed");
    exit(EXIT_FAILURE);
  }

  clnt_destroy(client);

  return EXIT_SUCCESS;
}
