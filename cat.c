#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void number_nonblank(FILE *fptr) {
  const int n_file_str = 260;
  char file_str[n_file_str];
  int count = 1;
  while (fgets(file_str, n_file_str, fptr) != NULL) {
    if (strcmp(file_str, "\n") != 0) {
      printf("%d  %s", count, file_str);
      count++;
    } else {
      printf("\n");
    }
  }
}

void dlr_sign(FILE *fptr, bool for_GNU) {
  char c = 'a';
  while (c != EOF) {
    c = fgetc(fptr);
    if (c == EOF) {
      return;
    }
    if (c < 32 && c != '\n' && c != '\t' && for_GNU == false) {
      printf("^%c", c + 64);
    } else if (c == 127 && for_GNU == false) {
      printf("^?");
    } else if (isascii(c) == 0 && for_GNU == false) {
      printf("M-");
    } else if (c == '\n') {
      printf("$%c", c);
    } else {
      printf("%c", c);
    }
  }
}

void action(char *file_name, char cat_flag) {
  printf("flag: %c\n", cat_flag);
  FILE *fptr = NULL;
  fptr = fopen(file_name, "r");
  if (fptr == NULL) {
    printf("Can't read the file, file name: %s", file_name);
  } else {
    switch (cat_flag) {
      case 'b':
        number_nonblank(fptr);
        break;
      case 'e':
        dlr_sign(fptr, false);
        break;
      default:
        printf("You use the -flag that do not exist.");
        break;
    }
  }
  fclose(fptr);
}

int main(int argc, char **argv) {
  char **words = malloc(sizeof(char *) * argc);

  for (int i = 0; i < argc; i++) {
    words[i] = argv[i];
  }

  for (int i = 0; i < argc; i++) {
    printf("%s ", words[i]);
  }

  if (strcmp(words[1], "cat") == 0) {
    printf("You use bash-cat\n");
    if (words[2] == NULL) {
      printf("You do not type a -flag");
    } else if (words[2][0] == '-' && strlen(words[2]) == 2) {
      printf("make action\n");
      action(words[3], words[2][1]);
    } else {
      printf("Please, type a correct -flag or file name.");
    }
  } else {
    printf("There is no such command: %s.", words[1]);
  }
  free(words);
  return 0;
}