#include <stdio.h>
#include <stdlib.h>

#define FILENAME "text.txt"

typedef struct _Node {
  char *key;
  int val;
  struct _Node *next;
} Node;

typedef struct _List {
  int size;
  Node *head;
} List;

void initList(List *I) {
  I->size = 0;
  I->head = NULL;
}

Node *initNode(char *key, int val) {
  Node *node = malloc(sizeof(Node));
  node->key = key;
  node->val = val;
  node->next = NULL;

  return node;
}

int main(void) {
  FILE *fp = fopen(FILENAME, "r");

  fclose(fp);

  return EXIT_SUCCESS;
}
