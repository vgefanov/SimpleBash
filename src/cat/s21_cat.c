#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int error = 0;
  letters flags;
  initialization_structure(&flags);
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (pars_letters(&flags, argv[i])) {
        error = 1;
        break;
      }
    }
  }
  if (!error) {
    int step = 1;
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        int string_number = 1;
        operation_file(&flags, argv[i], string_number, &step);
      }
    }
  }
  return 0;
}

void initialization_structure(letters *token) {
  token->b = 0;
  token->e = 0;
  token->n = 0;
  token->s = 0;
  token->t = 0;
  token->v = 0;
}

int pars_letters(letters *flags, char *str) {
  int error = 0;
  while (*str != '\0') {
    if (calling_function(flags, str)) {
      error = 1;
    }
    break;
  }
  return error;
}

int calling_function(letters *flags, char *c) {
  int error = 0;
  if ((strcmp(c, "-b") == 0) || (strcmp(c, "--number-nonblank") == 0)) {
    flags->b = 1;
  } else if ((strcmp(c, "-e") == 0) || (strcmp(c, "-E") == 0)) {
    flags->e = 1;
  } else if ((strcmp(c, "-n") == 0) || (strcmp(c, "--number") == 0)) {
    flags->n = 1;
  } else if ((strcmp(c, "-s") == 0) || (strcmp(c, "--squeeze-blank") == 0)) {
    flags->s = 1;
  } else if ((strcmp(c, "-t") == 0) || (strcmp(c, "-T") == 0)) {
    flags->t = 1;
  } else if (strcmp(c, "-v") == 0) {
    flags->v = 1;
  } else if (strcmp(c, "-q") == 0) {
    printf(
        "Формат ввода:\n./s21_cat [-флаг] [название файла]\nСписок доступных "
        "флагов:\n-b (GNU: --number-nonblank) нумерует только непустые "
        "строки\n-e предполагает и -v (GNU only: -E то же самое, но без "
        "применения -v) также отображает символы конца строки как $\n-n (GNU: "
        "--number) нумерует все выходные строки\n-s (GNU: --squeeze-blank) "
        "сжимает несколько смежных пустых строк\n-t предполагает и -v (GNU: -T "
        "то же самое, но без применения -v) также отображает табы как ^I\n-h "
        "Помощь\n");
    error = 1;
  } else {
    printf("Ошибка ввода. Введите './s21_cat -q' для помощи\n");
    error = 1;
  }
  return error;
}

int operation_file(letters *flags, char *file, int string_number, int *step) {
  if (flags->e || flags->t) flags->v = 1;
  if (flags->b) flags->n = 0;
  char tmp;
  FILE *fp;
  fp = fopen(file, "r");
  if (fp == NULL) {
    printf("Ошибка ввода. '%s' такого файла не существует\n", file);
  } else {
    int empl = 0, num_empl = 0, count_flags = check_flags(flags);
    while (fscanf(fp, "%c", &tmp) != EOF) {
      if (tmp == '\n' && (empl == 0 && num_empl != 0 && flags->s == 1))
        continue;
      let_n(flags, empl, *step, &string_number);
      if (tmp == '\n') {
        let_e(flags, &empl, step, &num_empl);
      } else {
        num_empl = 0;
        let_b(flags, empl, *step, &string_number);
        let_t_or_v(flags, tmp);
        empl++;
      }
    }
    proc_after(flags, tmp, step, count_flags);
    fclose(fp);
  }
  return string_number;
}

int check_flags(letters *flags) {
  int count = 0;
  count = flags->b + flags->e + flags->n + flags->s + flags->t + flags->v;
  return count;
}

void let_n(letters *flags, int empl, int step, int *string_number) {
  if (flags->n == 1 && empl == 0) {
    if (step) {
      printf("%6d\t", *string_number);
      *string_number += 1;
    }
  }
}

void let_e(letters *flags, int *empl, int *step, int *num_empl) {
  if (flags->e) printf("$");
  if (*empl == 0) *num_empl += 1;
  printf("\n");
  *empl = 0;
  *step = 1;
}

void let_b(letters *flags, int empl, int step, int *string_number) {
  if (flags->b == 1 && empl == 0) {
    if (step) {
      printf("%6d\t", *string_number);
      *string_number += 1;
    }
  }
}

void let_t_or_v(letters *flags, char tmp) {
  if (tmp == '\t') {
    if (flags->t) {
      printf("^I");
    } else {
      printf("%c", tmp);
    }
  } else if (((tmp < ' ' && tmp >= '0') || tmp == 127) && flags->v) {
    printf("^%c", tmp + 64);
  } else {
    printf("%c", tmp);
  }
}

void proc_after(letters *flags, char tmp, int *step, int count_flags) {
  if (tmp != '\n') {
    *step = 0;
    if ((flags->b || flags->n) && count_flags == 1) {
      *step = 1;
    }
  } else {
    *step = 1;
  }
}
