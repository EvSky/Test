#include <stdio.h>

#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

/*

- Беззнаковая целочисленная длинная арифметика
- с использованием массивов.
- Ввод:
- 2 длинных числа в виде массивов до 100 элементов.
- В один элемент массива нельзя вводить число > 9.
- Вывод:
- Результат сложения и разности чисел-массивов.
- Пример:
- 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
- 2 9
- 
- 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
- 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
  */

int main() {
int buff1[LEN], buff2[LEN];
int len1 = 0, len2 = 0;
int result[LEN + 1];
int result_length = 0;
int c;
int error = 0;

```
// Читаем первое число
while ((c = getchar()) != '\n' && c != EOF) {
    if (c == ' ') continue;
    if (c < '0' || c > '9' || len1 >= LEN) {
        error = 1;
        break;
    }
    buff1[len1++] = c - '0';
}
if (c == EOF || len1 == 0) error = 1;

// Читаем второе число
if (!error) {
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == ' ') continue;
        if (c < '0' || c > '9' || len2 >= LEN) {
            error = 1;
            break;
        }
        buff2[len2++] = c - '0';
    }
    if (len2 == 0) error = 1;
}

if (error) {
    printf("n/a\n");
    return 0;
}

// Убираем ведущие нули у первого числа
int start1 = 0;
while (start1 < len1 - 1 && buff1[start1] == 0) start1++;
if (start1 > 0) {
    int new_len = len1 - start1;
    for (int i = 0; i < new_len; i++) buff1[i] = buff1[i + start1];
    len1 = new_len;
}

// Убираем ведущие нули у второго числа
int start2 = 0;
while (start2 < len2 - 1 && buff2[start2] == 0) start2++;
if (start2 > 0) {
    int new_len = len2 - start2;
    for (int i = 0; i < new_len; i++) buff2[i] = buff2[i + start2];
    len2 = new_len;
}

// Сложение
sum(buff1, len1, buff2, len2, result, &result_length);
for (int i = 0; i < result_length; i++) {
    if (i > 0) printf(" ");
    printf("%d", result[i]);
}
printf("\n");

// Вычитание
sub(buff1, len1, buff2, len2, result, &result_length);
if (result_length == -1) {
    printf("n/a\n");
} else {
    for (int i = 0; i < result_length; i++) {
        if (i > 0) printf(" ");
        printf("%d", result[i]);
    }
    printf("\n");
}

return 0;
```

}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
int i = len1 - 1;
int j = len2 - 1;
int carry = 0;
*result_length = 0;

```
while (i >= 0 || j >= 0 || carry) {
    int s = carry;
    if (i >= 0) s += buff1[i--];
    if (j >= 0) s += buff2[j--];
    result[(*result_length)++] = s % 10;
    carry = s / 10;
}

// Разворачиваем результат
for (int k = 0; k < *result_length / 2; k++) {
    int tmp = result[k];
    result[k] = result[*result_length - 1 - k];
    result[*result_length - 1 - k] = tmp;
}
```

}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
// Проверяем: buff1 >= buff2?
int less = 0;
if (len1 < len2) {
less = 1;
} else if (len1 == len2) {
for (int i = 0; i < len1; i++) {
if (buff1[i] < buff2[i]) { less = 1; break; }
if (buff1[i] > buff2[i]) break;
}
}

```
if (less) {
    *result_length = -1;
    return;
}

int i = len1 - 1;
int j = len2 - 1;
int borrow = 0;
*result_length = 0;

while (i >= 0) {
    int d = buff1[i--] - borrow;
    if (j >= 0) d -= buff2[j--];
    if (d < 0) {
        d += 10;
        borrow = 1;
    } else {
        borrow = 0;
    }
    result[(*result_length)++] = d;
}

// Разворачиваем результат
for (int k = 0; k < *result_length / 2; k++) {
    int tmp = result[k];
    result[k] = result[*result_length - 1 - k];
    result[*result_length - 1 - k] = tmp;
}

// Убираем ведущие нули
int start = 0;
while (start < *result_length - 1 && result[start] == 0) start++;
if (start > 0) {
    int new_len = *result_length - start;
    for (int k = 0; k < new_len; k++) result[k] = result[k + start];
    *result_length = new_len;
}
```

}