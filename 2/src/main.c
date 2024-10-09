#include <stdio.h>

#include "consts.h"
#include "funcs.h"

/*
    Лабораторная работа №2 - Вариант 13
    Работу выполнили: Мерзляков К., Енина К.
*/

int main() {
  // Определяем массив указателей на строки и запрашиваем их ввод у пользователя
  char *strings[STRINGS_COUNT];
  inp_strings(strings);

  // Выводим введенные пользователем строки
  printf("\nДо сортировки:\n");
  out_strings(strings);

  // Сортируем их согласно таблице 2.2 вариант 13
  // и сохраняем количество перестановок
  int swaps_count = sort_strings_by_spaces_count(strings, STRINGS_COUNT);

  // Выводим количество перестановок и отсортированные строки
  printf("\nПосле сортировки (кол-во перестановок = %d):\n", swaps_count);
  out_strings(strings);

  // Освобождаем выделенную для строк память
  free_memory(strings);

  return 0;
}
