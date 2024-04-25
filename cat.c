#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input(char *text) {
  char c = ' ';
  int size = 0;
  int value_flag = 1;
  while (c != '\n') {
    c = getchar();
    if (c != ' ' && c != '\n' && c != '\t') {
      value_flag = 0;
    }
    if (c != '\n') {
      printf("i:%d, c:%c\n", size, c);
      text[size] = c;
      size++;
    }
  }

  printf("text:%s, text_size:%d\n", text, size);
  return value_flag;
}

int main() {
  char text[100] = {'\0'};
  int inp = input(text);
  if (inp == 1) {
    printf("You type nothing.");
    return 0;
  }
}