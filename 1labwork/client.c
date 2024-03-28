#include <asm-generic/socket.h>
#include <netinet/in.h> // sockaddr_in struct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // socket, setsockopt, bind, listen, accept functions
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080

int main(void) {

  /* ==== Establish the connection  ==== */
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

  /* ==== File Transfer  ==== */
  FILE *fp = fopen("file.txt", "r");
  char *file_name = "file";

  if (fp == NULL) {
    perror("fopen failed");
    exit(EXIT_FAILURE);
  }

  send(server_socket, file_name, strlen(file_name), 0);

  if (recv(server_socket, buffer, 1024, 0) < 0) {
    perror("Filename not received");
    exit(EXIT_FAILURE);
  }

  if (strcmp(buffer, "Filename Received") == 0) {
    printf("Filename Received\n");
    while (fgets(buffer, 1024, fp) != NULL) {
      printf("Sending: %s\n", buffer);
      send(server_socket, buffer, strlen(buffer), 0);
      memset(buffer, 0, 1024);
    }
    // Add a delimiter at the end of the file content
    char delimiter[] = "\0";
    send(server_socket, delimiter, sizeof(delimiter), 0);
  }
  fclose(fp);

  // Send the "File Sent" message
  send(server_socket, "File Sent", strlen("File Sent"), 0);

  close(server_socket);

  return EXIT_SUCCESS;
}
