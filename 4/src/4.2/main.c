#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Лабораторная работа №4 - Вариант 13
    Работу выполнили: Мерзляков К., Енина К.
*/

int main(int argc, char *argv[]) {
  /*
    argv[0] - имя запускаемого файла
    argv[1] - первый параметр (имя входного файла)
    argv[2] - символы, которые нужно заменить на "#@"
  */

  // Проверяем количество аргументов на корректность
  if (argc != 3) {
    printf("Использование: ./main input.txt s\n");
    exit(0);
  }

  // Открываем входной файл на чтение
  FILE *f_in = fopen(argv[1], "rt");

  // Проверяем, что файл успешно открылся
  if (f_in == NULL) {
    fprintf(stderr, "Ошибка: Не удалось открыть файл \"%s\" на чтение\n", argv[1]);
    exit(1);
  }

  // Собираем имя выходного файла
  // "input.txt" + ".out" -> "input.txt.out"
  char f_out_name[strlen(argv[1]) + 5];
  snprintf(f_out_name, sizeof(f_out_name), "%s.out", argv[1]);

  // Открываем выходной файл на запись
  FILE *f_out = fopen(f_out_name, "wt");

  // Проверяем, что файл успешно открылся
  if (f_out == NULL) {
    fprintf(stderr, "Ошибка: Не удалось открыть файл \"%s\" на запись\n", f_out_name);
    exit(1);
  }

  // Достаем из аргумента символы,
  // которые нужно заменить
  const char replace_1 = argv[2][0];
  const char replace_2 = argv[2][1];

  // Замена последовательности двух введенных выше символов на "#@"
  int prev_c = EOF;
  char cur_c;

  while ((cur_c = fgetc(f_in)) != EOF) {

    if (prev_c == replace_1 && cur_c == replace_2) {
      fputc('#', f_out);
      fputc('@', f_out);
      prev_c = EOF;

    } else {
      if (prev_c != EOF) {
        fputc(prev_c, f_out);
      }

      prev_c = cur_c;
    }
  }

  if (prev_c != EOF) {
    fputc(prev_c, f_out);
  }

  // Закрываем файлы
  fclose(f_in);
  fclose(f_out);

  printf("Обработанные данные были записаны в файл \"%s\"\n", f_out_name);

  return 0;
}
