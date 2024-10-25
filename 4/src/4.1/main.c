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
    argv[2] - символ, строки, начинающиеся с которого, нужно исключить
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
    printf("Ошибка: Не удалось открыть файл \"%s\" на чтение\n", argv[1]);
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
    printf("Ошибка: Не удалось открыть файл \"%s\" на запись\n", f_out_name);
    exit(1);
  }

  // Достаем из аргумента символ,
  // строки, начинающиеся с которого, нужно исключить
  char exclude_char = argv[2][0];

  // Создаем строку, в которую будем считывать каждую из строк файла
  char line[128];

  // Считываем строки, пока удается считать:    fscanf() == 1
  // когда не удастся:                          fscanf() == 0
  while (fscanf(f_in, "%127s\n", line) == 1) {
    // если строка начинается или заканчивается на exclude_char,
    // то переходим к следующей (не записываем в выходной файл)
    if (line[0] == exclude_char || line[strlen(line) - 1] == exclude_char) {
      continue;
    }

    fprintf(f_out, "%s\n", line);
  }

  // закрываем файлы
  fclose(f_in);
  fclose(f_out);

  printf("Обработанные данные были записаны в файл \"%s\"\n", f_out_name);

  return 0;
}
