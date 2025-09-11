#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Лабораторная работа №2
 * Вариант: 17
 * Выполнил: Мерзляков К.А.
 */

/*
 * КОДЫ ОШИБОК, ВОЗВРАЩАЕМЫХ БИБЛИОТЕКОЙ
 *  -20: не удалось открыть файл <filename> на чтение
 *  -21: не удалось выделить память для имени временного файла
 *  -22: не удалось открыть временный файл на запись
 *  -23: не удалось записать в временный файл
 */

void process_File(const char *filename, int replacesCount) {
  // Открываем <filename> на чтение
  int inputHandle = open(filename, O_RDONLY);
  if (inputHandle < 0) {
    printf("Error %d (%s) while open file: %s\n", errno, strerror(errno), filename);
    exit(-20);
  }

  // Формируем имя временного файла ("<filename>.processed")
  size_t len = strlen(filename) + 11;
  char *outputFilename = malloc(len);
  if (outputFilename == NULL) {
    printf("Error allocating memory for outputFilename\n");
    exit(-21);
  }
  snprintf(outputFilename, len, "%s.processed", filename);

  // Открываем временный файл на запись
  int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw - rw - rw - */

  int outputHandle = open(outputFilename, openFlags, filePerms);
  if (outputHandle < 0) {
    printf("Error %d (%s) while open file: %s\n", errno, strerror(errno), filename);
    exit(-22);
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
      exit(-23);
    }
  }

  if (close(outputHandle) == -1) {
      printf("Error %d (%s) while closing file: %s\n", errno, strerror(errno), outputFilename);
  }

  if (close(inputHandle) == -1) {
      printf("Error %d (%s) while closing file: %s\n", errno, strerror(errno), filename);
  }
}
