#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} letters;

void initialization_structure(letters *token);
int pars_full(letters *flags, int argc, char **argv, char **find_str,
              int *find_number, int *count_flags, int *error);
void operation_file(letters *flags, char *file, char **find_str,
                    int find_number, int count_file);
int pars_letters(letters *flags, int argc, char **argv, char *str,
                 int *argv_number, char *find_str, int *find_number,
                 int *count_flags);
void def_file(letters *flags, int count_file, char *file, char *file_name);
int proc_mark(letters *flags, char *line, char **find_str, int find_number,
              char *file_name, int *count_flag_n, int *count_flag_c,
              int *count_flag_l, int *print);
void proc_after(letters *flags, char *file_name, char *file, char last,
                int count_flag_c, int count_flag_l, int print);
int calling_function(letters *flags, char c);
int control_line(letters *flags, char *line, char **find_str, int find_number);

#endif  // SRC_GREP_S21_GREP_H_
