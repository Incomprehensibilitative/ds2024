#include <asm-generic/socket.h>
#include <netinet/in.h> // sockaddr_in struct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // socket, setsockopt, bind, listen, accept functions
#include <sys/types.h>

#define PORT 8080

int main(void) {
  struct sockaddr_in server_address;
  int server_socket;
  char buffer[1024] = {0};
  char *message = "Hello from client";
  int option = 1;

  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option,
                 sizeof(option))) {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);
  server_address.sin_zero[7] = 0;

  if (connect(server_socket, (struct sockaddr *)&server_address,
              sizeof(server_address)) < 0) {
    perror("connect failed");
    exit(EXIT_FAILURE);
  }

  send(server_socket, message, strlen(message), 0);
  printf("Message sent\n");

  recv(server_socket, buffer, 1024, 0);
  printf("Message received: %s\n", buffer);

  shutdown(server_socket, SHUT_RDWR);

  return EXIT_SUCCESS;
}
