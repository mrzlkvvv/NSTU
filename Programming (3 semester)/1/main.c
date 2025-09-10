#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Лабораторная работа №1
 * Вариант: 17
 * Выполнил: Мерзляков К.А.
 */

/*
 * КОДЫ ОШИБОК, ВОЗВРАЩАЕМЫХ ПРОГРАММОЙ
 *  -1: невалидное количество переданных аргументов
 *  -2: невалидный <replaces_count>
 *  -3: не удалось открыть файл <filename> на чтение
 *  -4: не удалось выделить память для имени временного файла
 *  -5: не удалось открыть временный файл на запись
 *  -6: не удалось записать в выходной файл
 *  -8: не удалось переименовать временный файл
 */

void processFile(char *filename, int replacesCount);

int main(int argc, char *argv[]) {
  // Проверяем количество переданных аргументов
  if (argc != 3) {
    printf("Usage: %s <filename> <replaces_count>\n", argv[0]);
    exit(-1);
  }

  // Достаем количество замен из argv
  int replacesCount = atoi(argv[2]);
  if (replacesCount == 0) {
    printf("Error: <replaces_count> is not a number or equals 0\n");
    exit(-2);
  }

  // Обрабатываем файл
  processFile(argv[1], replacesCount);

  // Успешный выход из программы
  return EXIT_SUCCESS;
}

void processFile(char *filename, int replacesCount) {
  // Открываем <filename> на чтение
  int inputHandle = open(filename, O_RDONLY);
  if (inputHandle < 0) {
    printf("Error %d (%s) while open file: %s\n", errno, strerror(errno), filename);
    exit(-3);
  }

  // Формируем имя временного файла ("<filename>.processed")
  size_t len = strlen(filename) + 11;
  char *tempFilename = malloc(len);
  if (tempFilename == NULL) {
    printf("Error allocating memory for tempFilename\n");
    exit(-4);
  }
  snprintf(tempFilename, len, "%s.processed", filename);

  // Открываем временный файл на запись
  int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw - rw - rw - */

  int outputHandle = open(tempFilename, openFlags, filePerms);
  if (outputHandle < 0) {
    printf("Error %d (%s) while open file: %s\n", errno, strerror(errno), filename);
    exit(-5);
  }

  // Посимвольно читаем файл:
  // записываем пробел в выходной файл, если код символа > 47 и количество замен не исчерпано
  // иначе записываем прочитанный символ

  int numRead, numWrite;
  char buf;

  for (;;) {
    numRead = read(inputHandle, &buf, 1);
    if (numRead == 0) {
      break;
    }

    if (buf > 47 && replacesCount > 0) {
      numWrite = write(outputHandle, " ", 1);
      replacesCount--;
    } else {
      numWrite = write(outputHandle, &buf, 1);
    }

    if (numWrite == 0) {
      printf("Error %d (%s) while write to file: %s\n", errno, strerror(errno), filename);
      exit(-6);
    }
  }

  close(outputHandle);
  close(inputHandle);
}
