#include "s21_grep.h"

int main(int argc, char **argv) {
    int kLen = argc;
    template template[kLen];
    init_templates(template, argc);
    int templates_var = 0;
    int flags[10] = {0};
    get_grep_flags(argc, argv, flags, template, &templates_var);
    scan_files(argc, argv, template, templates_var, flags);
    return 0;
}

void init_templates(template *template, int size) {
    for (int i = 0; i < size; i++) {
        template[i].name = NULL;
        template[i].file_name = NULL;
        template[i].is_default = 0;
        template[i].is_file = 0;
    }
}

void get_grep_flags(int argc, char **argv, int *flags, template *template, int *templates_var) {
    int e = 0, f = 0;
    for (int i = 1; i < argc; i++) {
        if (strspn(argv[i], "-")) {
            get_flags_from_argv(argv[i], flags);
            if (strchr(argv[i], 'f')) {
                f++;
                template[*templates_var].file_name = get_template_file_name(argc, argv, i);
                template[*templates_var].is_default = 0;
                template[*templates_var].is_file = 1;
                (*templates_var)++;
            }
            if (strchr(argv[i], 'e')) {
                e++;
                template[*templates_var].name = get_e_template(argc, argv, i);
                template[*templates_var].is_default = 0;
                template[*templates_var].is_file = 0;
                (*templates_var)++;
            }
        }
    }
    if (e == 0 && f == 0) {
        template[*templates_var].name = get_default_template(argc, argv);
        template[*templates_var].is_default = 1;
        template[*templates_var].is_file = 0;
        (*templates_var)++;
    }
}

int get_flags_from_argv(char *arg, int *flags) {
    int fail = 0;
    char *flag;
    if (strlen(arg) == 1 || strlen(arg) != strspn(arg, "-eivclnhsfo")) fail = 1;
    char *e = strchr(arg, 'e');
    char *f = strchr(arg, 'f');
    if (!e) e = arg + strlen(arg);
    if (!f) f = arg + strlen(arg);
    if (e < f) {
        flags[8] = 1;
        f = e;
    }
    if (f < e) {
        flags[0] = 1;
        e = f;
    }
    if ((flag = strchr(arg, 'i')) && (e == NULL || flag < e) && (f == NULL || flag < f)) flags[1] = 1;
    if ((flag = strchr(arg, 'v')) && (e == NULL || flag < e) && (f == NULL || flag < f)) flags[2] = 1;
    if ((flag = strchr(arg, 'c')) && (e == NULL || flag < e) && (f == NULL || flag < f)) flags[3] = 1;
    if ((flag = strchr(arg, 'l')) && (e == NULL || flag < e) && (f == NULL || flag < f)) flags[4] = 1;
    if ((flag = strchr(arg, 'n')) && (e == NULL || flag < e) && (f == NULL || flag < f)) flags[5] = 1;
    if ((flag = strchr(arg, 'h')) && (e == NULL || flag < e) && (f == NULL || flag < f)) flags[6] = 1;
    if ((flag = strchr(arg, 's')) && (e == NULL || flag < e) && (f == NULL || flag < f)) flags[7] = 1;
    if ((flag = strchr(arg, 'o')) && (e == NULL || flag < e) && (f == NULL || flag < f)) flags[9] = 1;
    return fail;
}

char *get_template_file_name(int argc, char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'f') == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc) res = argv[i + 1];
    } else {
        res = strchr(argv[i], 'f') + 1;
    }
    return res;
}

char *get_e_template(int argc, char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'e') == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc) res = argv[i + 1];
    } else {
        res = strchr(argv[i], 'e') + 1;
    }
    return res;
}

char *get_default_template(int argc, char **argv) {
    char *res = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strspn(argv[i], "-")) {
            res = argv[i];
            break;
        }
    }
    return res;
}

void scan_files(int argc, char **argv, template *template, int templates_var, int *flags) {
    int kFiles_variable = var_files(argc, argv, template, flags);
    if (kFiles_variable) {
        file_struct files[kFiles_variable];
        init_files(files, kFiles_variable);
        get_files(argc, argv, template, files, flags);
        files_processing(template, templates_var, files, kFiles_variable, flags);
    }
}

int var_files(int argc, char **argv, template *template, int *flags) {
    int res = 0;
    int same = 0;
    for (int i = 1; i < argc; i++)
        if (is_arg_a_file(i, argv, template, &same, flags)) res++;
    return res;
}

int is_arg_a_file(int i, char **argv, template *template, int *same, const int *flags) {
    return (!strspn(argv[i], "-") &&
            !((strchr(argv[i], 'f') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'f' && strspn(argv[i - 1], "-")) ||
              (strchr(argv[i], 'e') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'e' && strspn(argv[i - 1], "-")) ||
              (!(flags[8] || flags[0]) && !strcmp(argv[i], template[0].name) && ((*same)--) >= 0)));
}

void init_files(file_struct *files, int size) {
    for (int i = 0; i < size; i++) {
        files[i].file_name = NULL;
        files[i].mached = 0;
        files[i].mached_all = 0;
        files[i].valid = 0;
    }
}

void get_files(int argc, char **argv, template *template, file_struct *files, int *flags) {
    int same = 0;
    int k = 0;
    for (int i = 1; i < argc; i++) {
        if (is_arg_a_file(i, argv, template, &same, flags)) files[k++].file_name = argv[i];
    }
}

void files_processing(template *template, int templates_var, file_struct *files, int files_var, int *flags) {
    int empty_line = is_empty_line_in_templates(template, templates_var);
    int maching_lines = 0;
    for (int i = 0; i < files_var; i++) {
        FILE *fp = fopen(files[i].file_name, "r");
        if (fp) {
            if (empty_line) {
                if (flags[L] || flags[C] || (flags[O] && !flags[V]) || !(flags[V] && flags[O]))
                    maching_lines = print_all(fp, flags, files + i, files_var);
            } else {
                maching_lines = seek_in_file(fp, template, templates_var, flags, files + i, files_var);
            }
            fclose(fp);
        } else {
            if (!flags[S]) printf("Ошибка ввода, %s такого файла не существует\n", files[i].file_name);
            files[i].valid = 0;
        }
        if (flags[C]) print_files_c(files + i, files_var, maching_lines, flags);
        if (flags[L]) print_files_l(files + i, maching_lines);
    }
}

int is_empty_line_in_templates(template *template, int templates_var) {
    int res = 0;
    for (int i = 0; i < templates_var; i++) {
        if (template[i].is_file) {
            char *line = NULL;
            size_t size = 0;
            FILE *fp = fopen(template[i].file_name, "r");
            if (fp) {
                while (getline(&line, &size, fp) != -1) {
                    if (line && is_empty_line(line)) res = 1;
                }
                fclose(fp);
                free(line);
            }
        } else {
            if (is_empty_line(template[i].name)) res = 1;
        }
    }
    return res;
}

int is_empty_line(char *name) { return (strlen(name) == 1 && name[0] == '\n'); }

int print_all(FILE *fp, int *flags, file_struct *files, int files_var) {
    char *line = NULL;
    int line_number = 0;
    size_t size = 0;
    while (getline(&line, &size, fp) != -1) {
        if (line) {
            trim_n(line);
            line_number++;
            if (!flags[C] && !flags[L]) {
                if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
                if (!flags[H] && files_var > 1) printf("%s:", files->file_name);
                if (flags[N]) printf("%d:", line_number);
                printf("%s\n", line);
            }
        }
    }
    free(line);
    return line_number;
}

void trim_n(char *line) {
    if (strlen(line) == 1 && line[0] == '\n') line[0] = '.';
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
}

int seek_in_file(FILE *fp, template *template, int templates_var, int *flags, file_struct *files,
                 int files_var) {
    int matching_lines = 0;
    int line_number = 0;
    size_t size = 0;
    char *line = NULL;
    while (getline(&line, &size, fp) != -1) {
        if (line) {
            int one_time_print = 1;
            line_number++;
            trim_n(line);
            for (int i = 0; i < templates_var; i++) {
                int file_name_print = 1;
                seek_choice(line, template + i, files, flags, &matching_lines, files_var, line_number,
                            &one_time_print, &file_name_print);
            }
            if (flags[V] && one_time_print == 1) {
                print_match(line, flags, files, files_var, line_number, &one_time_print, &matching_lines);
            }
        }
    }
    free(line);
    return matching_lines;
}

void seek_choice(char *line, template *template, file_struct *files, int *flags, int *matching_lines,
                 int files_var, int line_number, int *one_time_print, int *file_name_print) {
    if (flags[O] && !flags[C] && !flags[V]) {
        if (template->is_file) {
            seek_file_templates(line, template, files, flags, matching_lines, files_var, line_number,
                                one_time_print, file_name_print);
        } else {
            seek_o_template(line, template, files, flags, matching_lines, files_var, line_number,
                            file_name_print);
        }
    } else {
        if (template->is_file) {
            seek_file_templates(line, template, files, flags, matching_lines, files_var, line_number,
                                one_time_print, file_name_print);
        } else {
            seek_template(line, *template, files, flags, matching_lines, files_var, line_number,
                          one_time_print);
        }
    }
}

void seek_file_templates(char *line, template *template, file_struct *files, int *flags, int *matching_lines,
                         int files_var, int line_number, int *one_time_print, int *file_name_print) {
    FILE *fp = fopen(template->file_name, "r");
    if (fp) {
        char *file_line = NULL;
        size_t file_line_size = 0;
        while (getline(&file_line, &file_line_size, fp) != -1) {
            if (line) {
                template->name = file_line;
                if (flags[O] && !flags[C] && !flags[V]) {
                    seek_o_template(line, template, files, flags, matching_lines, files_var, line_number,
                                    file_name_print);
                } else {
                    seek_template(line, *template, files, flags, matching_lines, files_var, line_number,
                                  one_time_print);
                }
            }
        }
        free(file_line);
        fclose(fp);
    } else {
        if (!flags[S]) printf("Ошибка ввода, %s такого файла не существует\n", template->file_name);
    }
}

void seek_o_template(char *line, template *template, file_struct *files, int *flags, int *maching_lines,
                     int files_var, int line_number, int *file_name_print) {
    regex_t regex;
    trim_n(template->name);
    int comp_val = do_regcomp(&regex, flags, template->name);
    if (!comp_val) {
        regmatch_t match;
        size_t offset = 0;
        size_t len = strlen(line);
        int eflags = 0;
        while (regexec(&regex, line + offset, 1, &match, eflags) == 0) {
            if (*file_name_print) (*maching_lines)++;
            eflags = REG_NOTBOL;
            print_o_match(file_name_print, files, offset, match, line, flags, line_number, files_var);
            offset += match.rm_eo;
            if (match.rm_so == match.rm_eo) offset += 1;
            if (offset > len) break;
        }
    }
    regfree(&regex);
}

int do_regcomp(regex_t *regex, int *flags, char *template) {
    int comp_val;
    if (flags[1])
        comp_val = regcomp(regex, template, REG_ICASE);
    else
        comp_val = regcomp(regex, template, 0);
    return comp_val;
}

void print_o_match(int *file_name_print, file_struct *files, size_t offset, regmatch_t match, char *line,
                   int *flags, int line_number, int files_var) {
    if (!flags[C] && !flags[L]) {
        if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
        if (*file_name_print) {
            if (!flags[H] && files_var > 1) printf("%s:", files->file_name);
            if (flags[N]) printf("%d:", line_number);
        }
        for (size_t i = offset + match.rm_so; i < offset + match.rm_eo; i++) printf("%c", line[i]);
        printf("\n");
        *file_name_print = 0;
    }
}

void seek_template(char *line, template template, file_struct *files, int *flags, int *matching_lines,
                   int files_var, int line_number, int *one_time_print) {
    regex_t regex;
    trim_n(template.name);
    int comp_val = do_regcomp(&regex, flags, template.name);
    if (!comp_val) {
        int exec_val = regexec(&regex, line, 0, NULL, 0);
        if (exec_val == 0) {
            if (!flags[V]) {
                print_match(line, flags, files, files_var, line_number, one_time_print, matching_lines);
            }
            *one_time_print = 0;
        }
    } else {
        printf("Ошибка ввода, введите корректные данные\n");
    }
    regfree(&regex);
}

void print_match(char *line, int *flags, file_struct *files, int files_var, int line_number,
                 int *one_time_print, int *maching_lines) {
    if (!flags[C] && !flags[L] && *one_time_print) {
        if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
        if (!flags[H] && files_var > 1) printf("%s:", files->file_name);
        if (flags[N]) printf("%d:", line_number);
        printf("%s\n", line);
    }
    if (*one_time_print) (*maching_lines)++;
}

void print_files_c(file_struct *files, int files_var, int maching_lines, const int *flags) {
    if (!flags[H] && files_var > 1) printf("%s:", files->file_name);
    if (!flags[L])
        printf("%d\n", maching_lines);
    else
        printf("%d\n", maching_lines > 0 ? 1 : 0);
}

void print_files_l(file_struct *files, int maching_lines) {
    if (maching_lines > 0) printf("%s\n", files->file_name);
}
