#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int scanFromFile();
int scanFromStdio(char **matrix, int n, int m);
int randomize(char **matrix, int n, int m);

void output(int **a, int x, int y);

char **allocate(int n, int m);
void drawScreen(char **status, int n, int m);
void refreshLife(char **status, int n, int m);
char ruleOfLife(char status_cell, int neighbours);
void replaceArray(char **array, char **arraytemp, int n, int m);
void lifeCycle(char **status, int n, int m);
int checkEnd(char **status, int n, int m, int error);
int getKey();

int main(void) {
  int n = 25;
  int m = 80;
  int error = 0;
  char **status = allocate(n, m);
  error += scanFromStdio(status, n, m);
  //scanFromFile(status, "preset.txt");
  if (error == 0) {
    lifeCycle(status, n, m);
  } else {
    printf("\nThis is an error message, please do not panic!\nOkay, panic!\n");
  }
  free(status);
  return 0;
}
// allocate memory
char **allocate(int n, int m) {
  char **a = malloc(n * m * sizeof(char) + n * sizeof(char**));
  char *ptr = (char*)(a + n);
  for (int i = 0; i < n; i++) {
    a[i] = ptr + m * i;
  }
  return a;
}
// draw current status
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
// Initialize random status
int randomize(char **matrix, int n, int m) {
  int error = 0;
  srand(time(NULL));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      matrix[i][j] = rand()%2 == 1 ? 'O' : ' ';
  return error;
}
int checkNeighbors(char **status, int index_x, int index_y, int n, int m) {
  int temp_i = 0;
  int temp_j = 0;
  int count_live = 0;
  for (int i = index_x - 1 ; i <= index_x + 1; i++) {
    for (int j = index_y - 1; j <= index_y + 1; j++) {
      if (j == index_y && i == index_x) {
        //do nothing
      } else {
        temp_j = j;
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

char ruleOfLife(char status_cell, int neighbours) {
    int result = status_cell;
    if (status_cell == 'O' && neighbours > 3) //Перенаселение
    result = ' ';
    else if (status_cell == 'O' && neighbours < 2) //Недостаточная населенность
    result = ' ';
    else if (status_cell == ' ' && neighbours == 3) //Воспроизведение
    result = 'O';
    return result;
}

void refreshLife(char **status, int n, int m) {
  char **temp2d = allocate(n, m);
  int neighbours = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      neighbours = checkNeighbors(status, i, j, n, m);
      temp2d[i][j] = ruleOfLife(status[i][j], neighbours);
    }
  }
  replaceArray(status, temp2d, n, m);
  free(temp2d);
}

void replaceArray(char **array, char **arraytemp, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      array[i][j] = arraytemp[i][j];
    }
  }
}

void lifeCycle(char **status, int n, int m) {
  int key = 69;
  drawScreen(status, n, m);
  refreshLife(status, n, m);
  while (key != 666) {
    if (key == 1) {
      drawScreen(status, n, m);
      refreshLife(status, n, m);
    }
    key = getKey();
  }
}
int getKey() {
  int key = 69;
  char what_is_love; // baby don't hurt me
  scanf("%c", &what_is_love);
  if (what_is_love == ' ') {
    key = 1;
  } else if (what_is_love == 'q') {
    key = 666;
  }
  return key;
}

int scanFromFile(char** matrix, char* name, int n, int m) { //отлаживается
  int error = 0;
  char read_char;
  FILE *file = fopen("preset.txt", "r");
  if (file == NULL) {
    error = 1;
  }
  int i = 0, j = 0;
  while (!feof(file)) {
      read_char = fgetc(file);
      printf("%c", read_char);
      if(read_char == 'O' || read_char == ' ') {
        matrix[i][j] = read_char;
        j++;
      } else if (read_char == '\n') {
        j = 0;
        i++;
      }
  }
  fclose(file);
  return error;
}

int scanFromStdio(char **matrix, int n, int m) { //Немножко через жепу работает изза чаров.
  int error = 0;
  char c;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m+1; j++) {
        c = getchar();
        if(c =='\n') {
          //do nothing
        } else {
          matrix[i][j] = c;
        }
      //scanf("%c", &matrix[i][j]);
    }
  }
  return error;
}
/*void output(int **a, int x, int y) {
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
        printf("%d", a[i][j]);
      }
      printf("\n");
    }

}*/


/*int checkEnd(char **status, int n, int m, int error) {
  if (scanDead(status, n, m) == 1) {
    error = 5;
  }
  error +=checkPrevious
  return error;
}*/
