#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

typedef struct {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
} letters;

void initialization_structure(letters *token);
int pars_letters(letters *flags, char *str);
int calling_function(letters *flags, char *c);
int operation_file(letters *flags, char *file, int course, int *step);
int check_flags(letters *flags);
void let_n(letters *flags, int empl, int step, int *course);
void let_e(letters *flags, int *empl, int *step, int *number_empl);
void let_b(letters *flags, int empl, int step, int *course);
void let_t_or_v(letters *flags, char tmp);
void proc_after(letters *flags, char tmp, int *step, int count_flags);

#endif  // SRC_CAT_S21_CAT_H_
