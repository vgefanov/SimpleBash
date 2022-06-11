#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define E 0
#define I 1
#define V 2
#define C 3
#define L 4
#define N 5
#define H 6
#define S 7
#define F 8
#define O 9

typedef struct {
    char *file_name;
    int mached;
    int mached_all;
    int valid;
} file_struct;

typedef struct {
    char *name;
    char *file_name;
    int is_default;
    int is_file;
} template;

void init_templates(template *template, int size);
void get_grep_flags(int argc, char **argv, int *flags, template *template, int *templates_var);
int get_flags_from_argv(char *arg, int *flags);
char *get_template_file_name(int argc, char **argv, int i);
char *get_e_template(int argc, char **argv, int i);
char *get_default_template(int argc, char **argv);
void scan_files(int argc, char **argv, template *template, int templates_var, int *flags);
int var_files(int argc, char **argv, template *template, int *flags);
int is_arg_a_file(int i, char **argv, template *template, int *same, const int *flags);
void init_files(file_struct *files, int size);
void get_files(int argc, char **argv, template *template, file_struct *files, int *flags);
void files_processing(template *template, int templates_var, file_struct *files, int files_var, int *flags);
int is_empty_line_in_templates(template *template, int templates_var);
int is_empty_line(char *name);
int print_all(FILE *fp, int *flags, file_struct *files, int files_var);
void trim_n(char *line);
int seek_in_file(FILE *fp, template *template, int templates_var, int *flags, file_struct *files,
                 int files_var);
void seek_choice(char *line, template *template, file_struct *files, int *flags, int *matching_lines,
                 int files_var, int line_number, int *one_time_print, int *file_name_print);
void seek_file_templates(char *line, template *template, file_struct *files, int *flags, int *matching_lines,
                         int files_var, int line_number, int *one_time_print, int *file_name_print);
void seek_o_template(char *line, template *template, file_struct *files, int *flags, int *maching_lines,
                     int files_var, int line_number, int *file_name_print);
int do_regcomp(regex_t *regex, int *flags, char *template);
void print_o_match(int *file_name_print, file_struct *files, size_t offset, regmatch_t match, char *line,
                   int *flags, int line_number, int files_var);
void seek_template(char *line, template template, file_struct *files, int *flags, int *matching_lines,
                   int files_var, int line_number, int *one_time_print);
void print_match(char *line, int *flags, file_struct *files, int files_var, int line_number,
                 int *one_time_print, int *maching_lines);
void print_files_c(file_struct *files, int files_var, int maching_lines, const int *flags);
void print_files_l(file_struct *files, int maching_lines);

#endif  // SRC_GREP_S21_GREP_H_
