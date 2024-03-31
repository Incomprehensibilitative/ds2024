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

  /*
   * Read the file that user want to send
   * Then send it to server line by line
   * */

  char *filename = "text";
  FILE *fp = fopen(filename, "r");
  char buffer[MAXLEN] = {0};

  send_file_res *res;

  if (fp == NULL) {
    perror("fopen failed");
    exit(EXIT_FAILURE);
  }

  send_file_args *arg = malloc(sizeof(send_file_args));
  if (arg == NULL) {
    printf("Memory allocation failed\n");
    return EXIT_FAILURE;
  }

  while (fgets(buffer, MAXLEN, fp) != NULL) {
    printf("Reading: %s", buffer);

    arg->fdata = strdup(buffer);
    arg->fname = filename;

    res = send_file_1(arg, client);
    if (res->errno != 0) {
      printf("%s\n", res->send_file_res_u.errmsg);
    } else {
      printf("Sent Successfully\n");
    }

    free(arg->fdata);
    memset(buffer, 0, MAXLEN);
  }

  free(arg);

  if (fclose(fp) != 0) {
    perror("fclose failed");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
