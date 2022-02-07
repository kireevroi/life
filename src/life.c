/*Copyright 2022 liviador*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init();
void start(int edgeX, int edgeY);
void drawField(int edgeX, int edgeY, char *status[]);
void end(int edgeX, char *status[]);
void initField(int edgeX, int edgeY, char *status[]);
void refresh(int edgeX, int edgeY, char *status[]);
int checkDeath(int posX, int posY, int edgeX, int edgeY, char *status[], char *status_new[]);
void swapArray(int edgeX, int edgeY, char *first[], char *second[]);
int scanChar();
int main (void) {
  init();
  return 0;
}
// Проверка на смерть
int checkDeath(int posX, int posY, int edgeX, int edgeY, char *status[], char *status_new[]) {
  int ticker = 0;
  for (int i = posX-1; i < posX+1; i++) {
    for (int j = posY-1; j < posX+1; j++) {
      if ((i > 0 || j > 0) && (posX < edgeX || posY < edgeY)) {
        if (status[i][j] == '@' && (i != posX && j!= posY)) {
          ticker++;
        }
      }
    }
  }
  if (status[posX][posY] == '@') {
    if (ticker <= 3 && ticker >= 2) {
      status_new[posX][posY] = ' ';
      return 0;
    }
    else {
      status_new[posX][posY] = '@';
      return 0;
    }
  } else if (status[posX][posY] == ' ') {
    if (ticker == 3) {
      status_new[posX][posY] = '@';
      return 0;
    }
    else {
      status_new[posX][posY] = ' ';
      return 0;
    }
  }
  return 0;
}
// Инициализация
void init() {
  srand(time(NULL));
  int x, y;
  scanf("%d %d", &x, &y);
  start(x, y);
}
// Считывание клавиши
int scanChar() {
  char get;
  scanf("%c", &get);
  if(get == ' ') {
    return 1;
  } else return 0;
  return 0;
}
// Аллоцируем память, задаем случайные исходные и запускаем
void start(int edgeX, int edgeY) {
  char **array = (char**)malloc(edgeX *sizeof(char*));
  for (int i = 0; i < edgeX; i++) {
    array[i] = (char*)malloc(edgeY * sizeof(char));
  }

  initField(edgeX, edgeY, array);
  refresh(edgeX, edgeY, array);
}
//Рисуем поле
void drawField(int edgeX, int edgeY, char *status[]) {
  for(int i = 0; i < edgeX; i++) {
    for(int j = 0; j < edgeY; j++) {
      printf("%c", status[i][j]);
    }
    printf("\n");
  }
}
//Освобождаем память
void end(int edgeX, char *status[]) {
  for(int i = 0; i< edgeX; i++) {
    free(status[i]);
  }
  free(status);
}
//инициализируем поле рандомными точками
void initField(int edgeX, int edgeY, char *status[]) {
  for (int i = 0; i < edgeX; i++) {
    for (int j = 0; j < edgeY; j++) {
      if (rand()%2 == 0) status[i][j] = '@';
      else status[i][j] = ' ';
    }
  }
}
//обновляем поле
void refresh(int edgeX, int edgeY, char *status[]) {
  char **status_new = (char**)malloc(edgeX *sizeof(char*));
  for (int i = 0; i < edgeX; i++) {
    status_new[i] = (char*)malloc(edgeY * sizeof(char));
  }
  int key = scanChar();
  while (1) {

    drawField(edgeX, edgeY, status);
    if (key == 1){
    for (int i = 0; i < edgeX; i++) {
      for (int j = 0; j < edgeY; j++) {
        checkDeath(i, j, edgeX, edgeY, status, status_new);
      }
    }
    swapArray(edgeX, edgeY, status, status_new);
  }
    key = scanChar();
  }
}
void swapArray(int edgeX, int edgeY,char *first[], char *second[])
{
    for (int i = 0; i < edgeX; i++) {
      for (int j = 0; j < edgeY; j++) {
        first[i][j] = second[i][j];
      }
    }
}
