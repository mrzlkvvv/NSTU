#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Лабораторная работа №2
 * Вариант: 17
 * Выполнил: Мерзляков К.А.
 */

/*
 * КОДЫ ОШИБОК, ВОЗВРАЩАЕМЫХ ПРОГРАММОЙ
 *  -10: невалидное количество переданных аргументов
 *  -11: невалидный <replaces_count>
 *  -12: не удалось загрузить библиотеку
 *  -13: не удалось получить указатель на функцию
 *  -2*: ошибки, возвращаемые библиотекой (см. fileprocessor.c)
 */

int main(int argc, char *argv[]) {
  // Проверяем количество переданных аргументов
  if (argc != 3) {
    printf("Usage: %s <filename> <replaces_count>\n", argv[0]);
    exit(-10);
  }

  // Достаем количество замен из argv
  int replacesCount = atoi(argv[2]);
  if (replacesCount == 0) {
    printf("Error: <replaces_count> is not a number or equals 0\n");
    exit(-11);
  }

  // Загружаем библиотеку
  void *handle = dlopen("./bin/fileprocessor.so", RTLD_LAZY);
  if (!handle) {
    printf("Error loading library: %s\n", dlerror());
    exit(-12);
  }

  // Получаем указатель на функцию processFile
  void (*processFile)(const char *, int);
  processFile = dlsym(handle, "processFile");
  const char *dlsym_error = dlerror();
  if (dlsym_error) {
    printf("Error finding symbol 'process_file': %s\n", dlsym_error);
    dlclose(handle);
    exit(-13);
  }

  // Обрабатываем файл
  processFile(argv[1], replacesCount);

  // Выгружаем библиотеку
  dlclose(handle);

  // Успешный выход из программы
  return EXIT_SUCCESS;
}
