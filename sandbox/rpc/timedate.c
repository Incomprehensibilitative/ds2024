#include <stdio.h> //include headers
#include <string.h>
#include <time.h>
char *getdatestr_1(void) // returns string
{                        // i.e. pointer to char
  static char buf[80];   // to hold string
  static char *cp;       // to hold pointer
  time_t secs;
  secs = time(NULL); // get current time
  strcpy(buf, ctime(&secs));
  // convert to string
  cp = buf;
  return (cp); // return pointer to static buf
}
int main() {
  char *p;
  p = getdatestr_1();
  printf("The date is %s\n", p);
}
