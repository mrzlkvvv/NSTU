#include <stdio.h>
#include <string.h>

#define STRS_COUNT 5
#define STRS_MAX_LEN 64

/*
    Лабораторная работа №2 - Вариант 13
    Работу выполнили: Мерзляков К., Енина К.
*/

// Объявляем прототипы функций
int inp_str(char string[STRS_MAX_LEN], int maxlen);
void inp_strings(char strings[STRS_COUNT][STRS_MAX_LEN]);
void out_str(char string[STRS_MAX_LEN], int length, int number);
void out_strings(char strings[STRS_COUNT][STRS_MAX_LEN]);
int get_spaces_count(char string[STRS_MAX_LEN]);
void sort(char strings[STRS_COUNT][STRS_MAX_LEN], int strings_count);

int main() {
  // Инициализируем массив строк
  char strings[STRS_COUNT][STRS_MAX_LEN];
  inp_strings(strings);

  // Выводим введенные пользователем строки
  printf("\nДо сортировки:\n");
  out_strings(strings);

  // Сортируем их по возрастанию количества пробелов
  // согласно таблице 2.2, вариант 13
  sort(strings, STRS_COUNT);

  // Выводим отсортированные строки
  printf("\nПосле сортировки:\n");
  out_strings(strings);

  return 0;
}

// Ввод строки
int inp_str(char string[STRS_MAX_LEN], int maxlen) {
  printf("\nВведите строку: ");

  // Считываем строку
  fgets(string, maxlen, stdin);

  // Ищем индекс перевода строки (\n) в str
  // на его место вставляем символ конца строки (\0)
  string[strcspn(string, "\n")] = '\0';

  return strlen(string);
}

// Ввод STRS_COUNT строк
void inp_strings(char strings[STRS_COUNT][STRS_MAX_LEN]) {
  for (int i = 0; i < STRS_COUNT; i++) {
    int length = inp_str(strings[i], STRS_MAX_LEN);
    printf("Длина введенной строки: %d\n", length);
  }
}

// Вывод в консоль строки, ее длины и порядкового номера
void out_str(char string[STRS_MAX_LEN], int length, int number) {
  printf("%d) [длина строки = %d] \"%s\"\n", number, length, string);
}

// Вывод в консоль всех строк
void out_strings(char strings[STRS_COUNT][STRS_MAX_LEN]) {
  for (int i = 0; i < STRS_COUNT; i++) {
    out_str(strings[i], strlen(strings[i]), i + 1);
  }
}

// Получение количества пробелов в строке
int get_spaces_count(char string[STRS_MAX_LEN]) {
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
void sort(char strings[STRS_COUNT][STRS_MAX_LEN], int strings_count) {
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
        max_spaces_count = str_j_spaces_count;
      }

      if (str_i_spaces_count > str_j_spaces_count) {
        char tmp[STRS_MAX_LEN];
        strcpy(tmp, strings[i]);
        strcpy(strings[i], strings[j]);
        strcpy(strings[j], tmp);
        swaps_count++;
      }
    }
  }

  printf("При сортировке было совершено перестановок: %d\n", swaps_count);
  printf("Наибольшее количество пробелов среди строк: %d\n", max_spaces_count);
}
