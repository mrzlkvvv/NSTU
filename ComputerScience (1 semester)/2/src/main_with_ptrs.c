#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRS_COUNT 5
#define STRS_MAX_LEN 64

/*
    Лабораторная работа №2 - Вариант 13
    Работу выполнили: Мерзляков К., Енина К.
*/

// Объявляем прототипы функций
int inp_str(char *string, int maxlen);
void inp_strings(char **strings);
void out_str(char *string, int length, int number);
void out_strings(char **strings);
int get_spaces_count(char *string);
void sort_strings_by_spaces_count(char **strings, int strings_count);
void free_memory(char **strings);

int main() {
  // Инициализируем массив указателей на строки
  // и запрашиваем их ввод у пользователя
  char *strings[STRS_COUNT];
  inp_strings(strings);

  // Выводим введенные пользователем строки
  printf("\nДо сортировки:\n");
  out_strings(strings);

  // Сортируем их согласно таблице 2.2 вариант 13
  sort_strings_by_spaces_count(strings, STRS_COUNT);

  // Выводим отсортированные строки
  printf("\nПосле сортировки:\n");
  out_strings(strings);

  // Освобождаем выделенную для строк память
  free_memory(strings);

  return 0;
}

// Ввод строки
int inp_str(char *string, int maxlen) {
  /*
    char *string: указатель, куда считать строку
    int maxlen:   максимальная длина вводимой строки
  */

  printf("\nВведите строку: ");

  // Считываем строку
  fgets(string, maxlen, stdin);

  // Ищем индекс перевода строки (\n) в str
  // на его место вставляем символ конца строки (\0)
  string[strcspn(string, "\n")] = '\0';

  return strlen(string);
}

// Ввод STRS_COUNT строк в виде указателей на строки
void inp_strings(char **strings) {
  /*
    char **strings: массив строк
  */

  for (int i = 0; i < STRS_COUNT; i++) {

    // Выделяем память для строки
    strings[i] = (char *)malloc(STRS_MAX_LEN * sizeof(char));
    if (strings[i] == NULL) {
      printf("Ошибка выделения памяти\n");
      exit(1);
    }

    // Считываем ее и выводим в консоль ее длину
    int length = inp_str(strings[i], STRS_MAX_LEN);
    printf("Длина введенной строки: %d\n", length);
  }
}

// Вывод в консоль строки, ее длины и порядкового номера
void out_str(char *string, int length, int number) {
  /*
    char *string: указатель на строку
    int length:   длина строки
    int number:   порядковый номер строки
  */

  printf("%d) [длина строки = %d] \"%s\"\n", number, length, string);
}

// Вывод в консоль всех строк
void out_strings(char **strings) {
  /*
    char **strings: массив строк
  */

  for (int i = 0; i < STRS_COUNT; i++) {
    out_str(strings[i], strlen(strings[i]), i + 1);
  }
}

// Получение количества пробелов в строке
int get_spaces_count(char *string) {
  /*
    char *string: указатель на строку
  */

  int count = 0;

  for (int i = 0; string[i] != '\0'; i++) {
    if (string[i] == ' ') {
      count++;
    }
  }

  return count;
}

// Сортировка строк по возрастанию количества пробелов
// Вывод кол-ва перестановок и наибольшего числа пробелов
void sort_strings_by_spaces_count(char **strings, int strings_count) {
  /*
    char **strings:    массив строк
    int STRS_COUNT: его размерность
  */

  int swaps_count = 0;
  int max_spaces_count = 0;

  for (int i = 0; i < strings_count - 1; i++) {
    for (int j = i + 1; j < strings_count; j++) {

      int str_i_spaces_count = get_spaces_count(strings[i]);
      int str_j_spaces_count = get_spaces_count(strings[j]);

      if (str_i_spaces_count > max_spaces_count) {
        max_spaces_count = str_i_spaces_count;
      }

      if (str_j_spaces_count > max_spaces_count) {
        max_spaces_count = str_i_spaces_count;
      }

      if (str_i_spaces_count > str_j_spaces_count) {
        char *tmp = strings[i];
        strings[i] = strings[j];
        strings[j] = tmp;
        swaps_count++;
      }
    }
  }

  printf("При сортировке было совершено перестановок: %d\n", swaps_count);
  printf("Наибольшее количество пробелов среди строк: %d\n", max_spaces_count);
}

// Освобождаем выделенную для строк память
void free_memory(char **strings) {
  /*
    char **strings: массив строк
  */

  for (int i = 0; i < STRS_COUNT; i++) {
    free(strings[i]);
  }
}
