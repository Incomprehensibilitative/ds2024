#include <netinet/in.h> // sockaddr_in struct
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // socket, setsockopt, bind, listen, accept functions
#include <sys/types.h>
#include <unistd.h>
#define PORT 8080

int main(void) {
  int server_socket, client_socket; // file descriptors
  char buffer[1024] = {0};          // buffer to store messages
  int length_of_address;
  struct sockaddr_in server_address,
      client_address; // client and server address we don't need a separate
                      // variable for the connection address because
                      // the communication is between the server and a single
                      // the client
  char *message = "Hello from server";

  // Create a socket: IPv4, TCP, default protocol
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Check if the socket was created successfully
  if (server_socket == -1) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Set the server socket options
  int option = 1;

  // Server socket: TCP, IPv4
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option,
                 sizeof(option))) {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }

  // Set the server address
  server_address.sin_family = AF_INET;         // IPv4
  server_address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
  // use htons to convert from host byte order to network byte order
  server_address.sin_port = htons(PORT); // port number
  server_address.sin_zero[7] = 0;        // padding

  // Bind the server socket to the server address
  if (bind(server_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_socket, 3) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  length_of_address = sizeof(client_address);

  // Accept the incoming connection
  client_socket = accept(server_socket, (struct sockaddr *)&client_address,
                         (socklen_t *)&length_of_address);

  if (client_socket < 0) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }

  // Read the file name from the client
  recv(client_socket, buffer, 1024, 0);
  char *file_name = buffer;
  printf("File name received: %s\n", file_name);

  // Append the server to the file name
  strcat(file_name, "_server.txt");
  printf("File name appended: %s\n", file_name);

  send(client_socket, "Filename Received", strlen("Filename Received"), 0);

  // Open the file
  FILE *fp = fopen(file_name, "w");

  if (fp == NULL) {
    perror("fopen failed");
    exit(EXIT_FAILURE);
  }

  while (recv(client_socket, buffer, sizeof(buffer) - 1, 0) > 0) {
    if (strcmp(buffer, "File Sent\n") == 0) {
      printf("File received successfully\n");
      break;
    }
    fputs(buffer, fp);
    printf("Receiving: %s\n", buffer);
    memset(buffer, 0, sizeof(buffer));
  }

  fclose(fp);

  close(client_socket);
  close(server_socket);

  return EXIT_SUCCESS;
}
