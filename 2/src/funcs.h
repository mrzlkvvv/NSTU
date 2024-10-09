#ifndef FUNCS_H
#define FUNCS_H

void out_str(char *string, int length, int number);
void out_strings(char **strings);
int get_spaces_count(char *string);
int sort_strings_by_spaces_count(char **strings, int strings_count);
int inp_str(char *string, int maxlen);
void inp_strings(char **strings);
void free_memory(char **strings);

#endif
