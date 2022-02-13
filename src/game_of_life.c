/*Copyright 2022 kireevroi*/

#include <stdio.h>
#include <stdlib.h>

/*Заранее извиняюсь за явное усложнение структуры...
  Я думал получится проще, но Школа явно берет своё
  И ставит препоны на каждом шагу. Чтоб её) */

// Считывание из терминала или из pipeline
int scanFromStdio(char **matrix, int n, int m);
// Хеширование статуса алгоритмом sdbm
long int hashing(char **status, int n, int m);
// Проверка, что достигнута стабильность или повторяемость или смехть
int checkEnd(char **status, long int *hash_array, int hash_len, int n, int m);
// Проверка всех на живость - для checkEnd
int scanDead(char **status, int n, int m);
// Аллоцирование памяти
char **allocate(int n, int m);
// Рисуем нашу колонию красивенько
void drawScreen(char **status, int n, int m);
// Обновляем состояние нашей колонии
void refreshLife(char **status, int n, int m);
// Проверка по соседям
char ruleOfLife(char status_cell, int neighbours);
// Переписываем состояние колонии
void replaceArray(char **array, char **arraytemp, int n, int m);
// Собственно цикл нашей программы
void lifeCycle(char **status, int n, int m);
// Считывание клавиши на выход
int getKey();

int main(void) {
  int n = 25; // Размеры нашего поля
  int m = 80;
  int error = 0; //Ошибки при считывании
  char **status = allocate(n, m);
  if (status == NULL)
    error = 1;
  error += scanFromStdio(status, n, m);
  if (error == 0) { // Если ошибок не было, запускаемся
    lifeCycle(status, n, m);
  } else {
    printf("\nThis is an error message, please do not panic!\nOkay, panic!\n");
  }
  free(status);
  return 0;
}
// Аллоцируем память и возвращаем на нее указатель
char **allocate(int n, int m) {
  char **a = malloc(n * m * sizeof(char) + n * sizeof(char**));
  char *ptr = (char*)(a + n);
  for (int i = 0; i < n; i++) {
    a[i] = ptr + m * i;
  }
  return a;
}
// Красивенько рисуем
void drawScreen(char **a, int n, int m) {
  for(int i = 0; i < m; i++)
    printf("#");
  printf("\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%c", a[i][j]);
    }
    printf("\n");
  }
  for(int i = 0; i < m; i++)
    printf("#");
  printf("\n");
}
// Проверяем наших соседушек
int checkNeighbors(char **status, int index_x, int index_y, int n, int m) {
  int temp_i = 0;
  int temp_j = 0;
  int count_live = 0;
  for (int i = index_x - 1 ; i <= index_x + 1; i++) {
    for (int j = index_y - 1; j <= index_y + 1; j++) {
      if (j == index_y && i == index_x) {
        //do nothing
      } else {
        temp_j = j; // Если вдруг мы у края, то перескакиваем куда нужно
        temp_i = i;
        if (temp_j < 0) {
          temp_j = m - 1;
        } else if (temp_j > m - 1) {
          temp_j = 0;
        }
        if (temp_i < 0) {
          temp_i = n - 1;
        } else if (temp_i > n - 1) {
          temp_i = 0;
        }
        if (status[temp_i][temp_j] == 'O') {
          count_live++;
        }
      }
    }
  }
  return count_live;
}
// Меняем состояние в зависимости от количества соседей
char ruleOfLife(char status_cell, int neighbours) {
    int result = status_cell;
    if (status_cell == 'O' && neighbours > 3) // Перенаселение
    result = ' ';
    else if (status_cell == 'O' && neighbours < 2) // Недостаточная населенность
    result = ' ';
    else if (status_cell == ' ' && neighbours == 3) // Воспроизведение
    result = 'O';
    return result;
}
// Переписываем нашу колонию по правилам
void refreshLife(char **status, int n, int m) {
  char **temp2d = allocate(n, m);
  if (temp2d != NULL) { // Если вдруг фигово аллоцировалось, не пишем туда ничего
    int neighbours = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        neighbours = checkNeighbors(status, i, j, n, m);
        temp2d[i][j] = ruleOfLife(status[i][j], neighbours);
      }
    }
    replaceArray(status, temp2d, n, m);
  }
  free(temp2d);
}
// Физическое перемещение состояния колонии, никаких передач указателей
void replaceArray(char **array, char **arraytemp, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      array[i][j] = arraytemp[i][j];
    }
  }
}
// Наш замечательный жизненный цикл
void lifeCycle(char **status, int n, int m) {
  int key = 69; // Хе-хе
  long int *hash_array = malloc(2*sizeof(long int));
  if (hash_array == NULL) // Не подмажешь, не поедешь
    key = 666;
  int hash_len = 1;
  drawScreen(status, n, m); // Инициализируем и отрисовываем
  hash_array[hash_len-1] = hashing(status, n, m); // Записываем старое состояние
  refreshLife(status, n, m); // Обновляем колонию
  freopen("/dev/tty", "rw", stdin); // Перезапускаем нафиг stdin после pipeline (костыль)
  while (key != 666) {
    if (key == 1) { // Если пробел, работаем.
      drawScreen(status, n, m);
      hash_len++;
      // Больше памяти - богу памяти
      hash_array = realloc(hash_array, hash_len * 2 * sizeof(long int));
      hash_array[hash_len-1] = hashing(status, n, m);
      // Проверка на конец
      if (checkEnd(status, hash_array, hash_len-1, n, m) == 1)
	      break;
      refreshLife(status, n, m);
    }
    // Считываем клавишку
    key = getKey();
  }
  free(hash_array);
}
// Считывание клавиш, само-собой.
int getKey() {
  int key = 69;
  char what_is_love; // baby don't hurt me
  what_is_love = getchar();
  if (what_is_love == EOF) {
	  printf("!");
  }
  if (what_is_love == ' ') {
    key = 1;
  } else if (what_is_love == 'q') {
    key = 666;
  }
  return key;
}
// Считываем таки всё из пайплайна или консоли. Ненавижу считывать чары.
int scanFromStdio(char **matrix, int n, int m) { 
  int error = 0;
  char c;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m+1; j++) {
        c = getchar();
        if(c =='\n') {
          // do nothing как говорится, сэлф экспланатори
        } else {
          matrix[i][j] = c;
        }
    }
  }
  // Ну вот почему вечно EOF забивает всё...
  return error;
}
// Хешируем всё нафиг по sdbm. Реально крутая идея, спасибо добрым людям.
long int hashing(char **status, int n, int m) {
	long int hash = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			hash = (hash << 6) + (hash << 16) -hash + status[i][j];
		}
	}
	return hash;
}
// Проверка на финита
int checkEnd(char **status, long int *hash_array, int hash_len, int n, int m) {
  int error = 0;
  if (scanDead(status, n, m) == 1) { // Вдруг все мертвы?
    error = 1;
  }
  for (int i = 0; i < hash_len; i++){
	if (hashing(status, n, m) == hash_array[i]) { // А вдруг такое уже было?
		error = 1;
		break;
	}
  }
  return error;
}
// Точно не мертвы?
int scanDead(char **status, int n, int m) {
	int count = n*m + 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (status[i][j] == ' ') {
				count--;
			}
		}
	}
	return count;
}
