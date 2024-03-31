#include "remtime.h"
#include <rpc/clnt.h>
#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>

#define SERVER "localhost"

int main(void) {
  CLIENT *client;     // client handle - required
  datestr *resstring; // pointer to a datestr to hold result

  /* create a client handle to the specified server, program, version, using the
   * specidied protocol*/
  client = clnt_create(SERVER, REMTIMEPROG, REMTIMEVERS, "udp");

  if (client == NULL) {
    perror("Cannot connect to server\n");
    clnt_pcreateerror(SERVER);
    exit(1);
  }

  /* as our function receives no arguments our first
  argument is a pointer to void, the second a pointer
  to the client handle we wish to use We should really
  error check the return! */
  resstring = getdatestr_1(NULL, client);

  printf("%s\n", *resstring);

  return EXIT_SUCCESS;
}
