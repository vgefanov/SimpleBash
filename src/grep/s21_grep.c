#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char **find_str;
  find_str = (char **)malloc(1024 * sizeof(char *));
  for (int i = 0; i < 1024; i++)
    *(find_str + i) = (char *)malloc(1024 * sizeof(char));
  letters flags;
  initialization_structure(&flags);
  int find_number = 0, count_flags = 0, error = 0, count_file;
  if (argc > 1) {
    count_file = pars_full(&flags, argc, argv, find_str, &find_number,
                           &count_flags, &error);
  } else {
    error = 1;
  }
  if (!error) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-')
        operation_file(&flags, argv[i], find_str, find_number, count_file);
    }
  }
  for (int i = 0; i < 1024; i++) free(*(find_str + i));
  free(find_str);
  return 0;
}

void initialization_structure(letters *token) {
  token->e = 0;
  token->i = 0;
  token->v = 0;
  token->c = 0;
  token->l = 0;
  token->n = 0;
  token->h = 0;
  token->s = 0;
  token->f = 0;
  token->o = 0;
}

int pars_full(letters *flags, int argc, char **argv, char **find_str,
              int *find_number, int *count_flags, int *error) {
  int count_file = 0, i = 1;
  while (i < argc) {
    if (argv[i][0] == '-') {
      if (pars_letters(flags, argc, argv, argv[i], &i, find_str[*find_number],
                       find_number, count_flags)) {
        *error = 1;
        break;
      }
    }
    i++;
  }
  if (!*count_flags) {
    snprintf(find_str[*find_number], strlen(argv[1]) + 1, "%s", argv[1]);
    argv[1][0] = '-';
    *find_number += 1;
  } else if (flags->e == 0) {
    i = 1;
    while (i < argc) {
      if (argv[i][0] != '-') {
        snprintf(find_str[*find_number], strlen(argv[i]) + 1, "%s", argv[i]);
        argv[i][0] = '-';
        *find_number += 1;
        break;
      }
      i++;
    }
    if (*find_number == 0) *error = 1;
  }
  for (int j = 1; j < argc; j++) {
    if (argv[j][0] != '-') count_file += 1;
  }
  return count_file;
}

int pars_letters(letters *flags, int argc, char **argv, char *str,
                 int *argv_number, char *find_str, int *find_number,
                 int *count_flags) {
  int error = 0, i = 1;
  while (str[i] != '\0') {
    if (calling_function(flags, str[i])) {
      error = 1;
      break;
    } else {
      *count_flags += 1;
      if (str[i] == 'e') {
        if (str[i + 1] != '\0') {
          memmove(find_str, str + i + 1, strlen(str) - i);
        } else if (*argv_number + 1 < argc) {
          snprintf(find_str, strlen(argv[*argv_number + 1]) + 1, "%s",
                   argv[*argv_number + 1]);
          argv[*argv_number + 1][0] = '-';
          *argv_number += 1;
        } else {
          printf("Ошибка ввода. Введите './s21_grep -q' для помощи\n");
          error = 1;
          break;
        }
        *find_number += 1;
        break;
      }
    }
    i++;
  }
  return error;
}

int calling_function(letters *flags, char c) {
  int error = 0;
  switch (c) {
    case 'e':
      flags->e = 1;
      break;
    case 'i':
      flags->i = 1;
      break;
    case 'v':
      flags->v = 1;
      break;
    case 'c':
      flags->c = 1;
      break;
    case 'l':
      flags->l = 1;
      break;
    case 'n':
      flags->n = 1;
      break;
    case 'h':
      flags->h = 1;
      break;
    case 's':
      flags->s = 1;
      break;
    case 'f':
      flags->f = 1;
      break;
    case 'o':
      flags->o = 1;
      break;
    case 'q':
      printf(
          "Формат ввода:\n./s21_grep [-флаг] [шаблон] [название файла]\nСписок "
          "доступных флагов:\n-е шаблон\n-i игнорирует различия регистра\n-v "
          "инвертирует смысл поиска соответствий\n-c выводит только количество "
          "совпадающих строк\n-l выводит только совпадающие файлы\n-n "
          "предваряет каждую строку вывода номером строки из файла ввода\n-h "
          "выводит совпадающие строки, не предваряя их именами файлов\n-s "
          "подавляет сообщения об ошибках о несуществующих или нечитаемых "
          "файлах\n-f [file] получает регулярные выражения из файла\n-o "
          "печатает только совпадающие (непустые) части совпавшей строки\n");
      break;
    default:
      printf("Ошибка ввода. Введите './s21_grep -q' для помощи\n");
      error = 1;
  }
  return error;
}

void operation_file(letters *flags, char *file, char **find_str,
                    int find_number, int count_file) {
  char *line = NULL;
  size_t len = 0;
  char *name_f = (char *)malloc(1024 * sizeof(char));
  FILE *fp;
  fp = fopen(file, "r");
  int print = 0;
  if (fp == NULL) {
    if (!flags->s)
      printf("Ошибка ввода. '%s' такого файла не существует\n", file);
  } else {
    def_file(flags, count_file, file, name_f);
    int count_flag_c = 0, count_flag_n = 0, count_flag_l = 0;
    char last = ' ';
    while (getline(&line, &len, fp) != EOF) {
      last = proc_mark(flags, line, find_str, find_number, name_f,
                       &count_flag_n, &count_flag_c, &count_flag_l, &print);
    }
    proc_after(flags, name_f, file, last, count_flag_c, count_flag_l, print);
    fclose(fp);
  }
  free(line);
  free(name_f);
}

void def_file(letters *flags, int count_file, char *file, char *file_name) {
  if (count_file > 1 && flags->h == 0) {
    snprintf(file_name, strlen(file) + 1, "%s", file);
    file_name[strlen(file)] = ':';
    file_name[strlen(file) + 1] = '\0';
  } else {
    file_name[0] = '\0';
  }
}

int proc_mark(letters *flags, char *line, char **find_str, int find_number,
              char *file_name, int *count_flag_n, int *count_flag_c,
              int *count_flag_l, int *print) {
  char last;
  *print = 0;
  *count_flag_n += 1;
  if (control_line(flags, line, find_str, find_number)) {
    if (flags->l) *count_flag_l += 1;
    if (flags->c) *count_flag_c += 1;
    if (!flags->c && !flags->l) {
      if (flags->n)
        printf("%s%d:%s", file_name, *count_flag_n, line);
      else
        printf("%s%s", file_name, line);
    }
    *print += 1;
  }
  last = line[strlen(line) - 1];
  return last;
}

int control_line(letters *flags, char *line, char **find_str, int find_number) {
  int success = 0;
  regex_t regex;
  for (int i = 0; i < find_number; i++) {
    if (flags->i) {
      regcomp(&regex, find_str[i], REG_ICASE);
    } else {
      regcomp(&regex, find_str[i], 0);
    }
    if ((regexec(&regex, line, 0, NULL, 0)) == 0) {
      success = 1;
      break;
    }
  }
  if (flags->v) {
    if (success)
      success = 0;
    else
      success = 1;
  }
  regfree(&regex);
  return success;
}

void proc_after(letters *flags, char *file_name, char *file, char last,
                int count_flag_c, int count_flag_l, int print) {
  if (flags->c) {
    if (!count_flag_l) {
      printf("%s%d\n", file_name, count_flag_c);
    } else if (!count_flag_c) {
      printf("%s%d\n", file_name, count_flag_c);
    } else {
      printf("%s\n", file);
    }
  } else if (count_flag_l) {
    printf("%s\n", file);
  } else if (flags->o) {
printf("%s%d");
  }
  if (last != '\n' && print != 0 && flags->c == 0 && flags->l == 0)
    printf("\n");
}
