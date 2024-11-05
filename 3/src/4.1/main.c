#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 100

// Определение структуры для хранения данных о пользователе
typedef struct {
  int count;
  char name[MAX_STRING_LEN];

  char customer_name[MAX_STRING_LEN];
  char manager_surname[MAX_STRING_LEN];
} product;

int main() {
  int products_count;
  printf("Введите количество товаров: ");
  scanf("%d", &products_count);

  // Выделение памяти для массива структур
  product *products = (product *)malloc(products_count * sizeof(product));

  if (products == NULL) {
    printf("Ошибка выделения памяти\n");
    return 1;
  }

  // Последовательный ввод данных
  for (int i = 0; i < products_count; i++) {
    printf("\nВведите название товара %d: ", i + 1);
    scanf("%s", products[i].name);

    printf("Введите количество товара %d: ", i + 1);
    scanf("%d", &products[i].count);

    printf("Введите наименование заказчика %d: ", i + 1);
    scanf("%s", products[i].customer_name);

    printf("Введите фамилию менеджера %d: ", i + 1);
    scanf("%s", products[i].manager_surname);
  }

  // Распечатка содержимого массива
  printf("\nТовары:\n");
  for (int i = 0; i < products_count; i++) {
    printf("Название товара: %s, Наименование заказчика: %s, Количество товара: %d, Фамилия менеджера: %s\n",
           products[i].name, products[i].customer_name, products[i].count, products[i].manager_surname);
  }

  // Освобождение памяти
  free(products);

  return 0;
}
