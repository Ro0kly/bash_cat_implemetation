#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void number_nonblank(FILE *fptr) {
  char c = ' ';
  char prev = ' ';
  int counter = 1;
  int flag = 0;
  while (c != EOF) {
    prev = c;
    c = fgetc(fptr);
    if (c == EOF) {
      break;
    }
    if (c != '\n' && prev == ' ' && flag == 0) {
      printf("%6d\t%c", counter, c);
      flag = 1;
      counter++;
    } else if (c != '\n' && prev == '\n') {
      printf("%6d\t%c", counter, c);
      counter++;
      flag = 1;
    } else {
      printf("%c", c);
      flag = 1;
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

void number(FILE *fptr) {
  char c = ' ';
  char prev = ' ';
  int counter = 1;
  int flag = 0;
  while (c != EOF) {
    prev = c;
    c = fgetc(fptr);
    if (c == EOF) {
      break;
    }
    if (flag == 0) {
      printf("%6d\t%c", counter, c);
      counter++;
      flag = 1;
    } else if (prev == '\n') {
      printf("%6d\t%c", counter, c);
      counter++;
    } else {
      printf("%c", c);
    }
  }
}

void squeeze_blank(FILE *fptr) {
  char c = ' ';
  int ncounter = 0;
  int flag = 0;
  while (c != EOF) {
    c = fgetc(fptr);
    if (c == EOF) {
      break;
    }
    if (c == '\n') {
      if (flag == 0) {
        if (ncounter < 1) {
          printf("%c", c);
          ncounter++;
        }
      } else {
        if (ncounter < 2) {
        printf("%c",c);
        ncounter++;
      }
      }
    } else {
      printf("%c", c);
      ncounter = 0;
      if (flag == 0) {
        flag = 1;
      }
    }
  }
}

void tabs(FILE *fptr, bool for_GNU) {
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
    } else if (c == '\t') {
      printf("^I");
    } else {
      printf("%c", c);
    }
  }
}

void non_print_symbols(FILE *fptr) {
  char c = 'a';
  while (c != EOF) {
    c = fgetc(fptr);
    if (c == EOF) {
      return;
    }
    if (c < 32 && c != '\n' && c != '\t') {
      printf("^%c", c + 64);
    } else if (c == 127) {
      printf("^?");
    } else if (isascii(c) == 0) {
      printf("M-");
    } else {
      printf("%c", c);
    }
  }
}

void action_long_flag(char *file_name, char *long_flag) {
  FILE *fptr = NULL;
  fptr = fopen(file_name, "r");
  if (fptr == NULL) {
    printf("Can't read the file, file name: %s", file_name);
  } else if (long_flag == NULL) {
    printf("There is no flag");
  } else {
    if (strcmp(long_flag, "--number-nonblank") == 0) {
      number_nonblank(fptr);
    } else if (strcmp(long_flag, "--number") == 0) {
      number(fptr);
    } else if (strcmp(long_flag, "--squeeze-blank") == 0) {
      squeeze_blank(fptr);
    } else {
      printf("There is no such a flag, the flag name: %s", long_flag);
    }
  }
  if (fptr) {
    fclose(fptr);
  }
}

void action_short_flag(char *file_name, char short_flag) {
  FILE *fptr = NULL;
  fptr = fopen(file_name, "r");
  if (fptr == NULL) {
    printf("Can't read the file, file name: %s", file_name);
  } else {
    switch (short_flag) {
    case 'b':
      number_nonblank(fptr);
      break;
    case 'e':
      dlr_sign(fptr, false);
      break;
    case 'E':
      dlr_sign(fptr, true);
      break;
    case 'n':
      number(fptr);
      break;
    case 's':
      squeeze_blank(fptr);
      break;
    case 't':
      tabs(fptr, false);
      break;
    case 'T':
      tabs(fptr, true);
      break;
    case 'v':
      non_print_symbols(fptr);
      break;
    default:
      printf("You use the -flag that do not exist.");
      break;
    }
    fclose(fptr);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("fef");
    return 0;
  }
  (void)argc;
  if (strcmp(argv[0], "./s_cat") == 0) {
    if (argv[1] == NULL) {
      fprintf(stderr, "You do not type a flag.");
    } else if (argv[1][0] == '-' && strlen(argv[1]) == 2) {
      action_short_flag(argv[2], argv[1][1]);
    } else if (argv[1][0] == '-' && argv[1][1] == '-') {
      action_long_flag(argv[2], argv[1]);
    } else {
      fprintf(stderr, "Please, type a correct -flag or file name.");
    }
  } else {
    fprintf(stderr, "There is no such command: %s.", argv[0]);
  }
  return 0;
}