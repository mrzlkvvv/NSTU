#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 128

/*
    Лабораторная работа №1 - Вариант 13
    Работу выполнили: Мерзляков К., Енина К.
*/

void get_input(char message[], char str[]);
int get_str_len(char str[]);
void concat_without_spaces(char *src1, char *src2, char *dst);
void replace_first_on_spaces(char str[]);
void replace_specific_chars_if(char str[]);
void replace_specific_chars_switch(char str[]);

int main() {
  // Инициализация переменных для строк, вводимых пользователем
  char str1[STRING_LENGTH];
  char str2[STRING_LENGTH];

  printf("\nПункт 4.1\n");
  get_input("Введите первую строку: ", str1);
  get_input("Введите вторую строку: ", str2);

  printf("\nПункт 4.2\n");
  printf("Длина первой строки \"%s\" = %d\n", str1, get_str_len(str1));
  printf("Длина второй строки \"%s\" = %d\n", str2, get_str_len(str2));

  // Инициализация строки в два раза большего размера,
  // чтобы была возможна конкатенация двух предыдущих строк
  char str[STRING_LENGTH * 2];

  printf("\nПункт 4.3\n");
  concat_without_spaces(str1, str2, str);
  printf("Сконкатенированная без пробелов строка: \"%s\"\n", str);

  printf("\nПункт 4.4.1\n");
  replace_first_on_spaces(str);
  printf("Заменили '%c' на пробелы: \"%s\"\n", str[0], str);

  // Копируем str в strCopy
  char strCopy[STRING_LENGTH * 2];
  strcpy(strCopy, str);

  printf("\nПункт 4.4.2 и 4.5\n");
  replace_specific_chars_if(str);
  printf("Заменили специальные символы (   if-else   ): \"%s\"\n", str);

  printf("\nПункт 4.6\n");
  replace_specific_chars_switch(strCopy);
  printf("Заменили специальные символы ( switch-case ): \"%s\"\n", strCopy);

  return 0;
}

// 4.1
void get_input(char message[], char str[]) {
  // Выводим сообщение (приглашение ко вводу)
  printf("%s", message);

  // Считываем первую строку
  fgets(str, STRING_LENGTH, stdin);

  // Ищем индекс перевода строки (\n) в str
  // на его место вставляем символ конца строки (\0)
  str[strcspn(str, "\n")] = '\0';
}

// 4.2
int get_str_len(char str[]) {
  int c = 0;

  for (int i = 0; i < STRING_LENGTH; i++) {
    if (str[i] != '\0')
      c++;

    else
      break;
  }

  return c;
}

// 4.3
void concat_without_spaces(char *src1, char *src2, char *dst) {
  // Индекс для dst
  int i = 0;

  // Индекс для src1 и src2
  int j = 0;

  while (src1[j] != '\0') {
    if (src1[j] != ' ') {
      dst[i] = src1[j];
      i++;
    }

    j++;
  }

  j = 0;

  while (src2[j] != '\0') {
    if (src2[j] != ' ') {
      dst[i] = src2[j];
      i++;
    }

    j++;
  }

  dst[i] = '\0';
}

// 4.4.1
void replace_first_on_spaces(char str[]) {
  // Сохраняем первый символ
  char c = str[0];

  // Первый символ не заменяем
  int i = 1;
  int changes = 0;

  do {
    if (str[i] == c) {
      str[i] = ' ';
      changes++;
    }

    i++;

  } while (changes < 5 && str[i + 1] != '\0');
}

// 4.4.2
void replace_specific_chars_if(char str[]) {
  int i = 0;
  int changes = 0;

  do {
    if (str[i] == '\\') {
      str[i] = 'q';
      changes++;
    }

    else if (str[i] == '_') {
      str[i] = 'w';
      changes++;
    }

    else if (str[i] == '^') {
      str[i] = 'e';
      changes++;
    }

    else if (str[i] == '~') {
      str[i] = 'r';
      changes++;
    }

    i++;

  } while (changes < 5 && str[i + 1] != '\0');
}

// 4.6 (4.4.2 со switch-case)
void replace_specific_chars_switch(char str[]) {
  int i = 0;
  int changes = 0;

  do {
    switch (str[i]) {
    case '\\':
      str[i] = 'q';
      changes++;
      break;

    case '_':
      str[i] = 'w';
      changes++;
      break;

    case '^':
      str[i] = 'e';
      changes++;
      break;

    case '~':
      str[i] = 'r';
      changes++;
      break;
    }

    i++;

  } while (changes < 5 && str[i + 1] != '\0');
}
