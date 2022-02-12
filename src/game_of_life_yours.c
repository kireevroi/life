#include<stdio.h>
#include<stdlib.h>

int size1 = 3;
int size2 = 3;

int count_nbr (int grid[size1][size2], int i, int j, int size1, int size2);
int getKey();

int main(void)
{
  int grid[3][3];
  for (int i = 0; i < size1; i++) {
    for (int j = 0; j < size2; j++) {
      scanf("%d", &grid[i][j]);
      printf("%d", grid[i][j]);
    }
  }

  int neighbour_count[size1][size2]; //Задаем матрицу по значению 20 на 20
  int i,j,steps;
  int key = 69;
  while(key != 666)
  {
      key = getKey();
    //system("clear"); // очищаем экран
    for (i = 0; i < size1; ++i)
    {
    printf("\n\n"); // создаем пустое пространство по y
      for (j = 0; j < size2; ++j)
      {
        if (grid[i][j] == 1) // Если в матрице есть 1, то создает *
          printf("\t*");
        else
          printf("\t"); // Если 0, то создает табуляцию
        neighbour_count[i][j] = count_nbr(grid,i,j,size1, size2); // счетчик соседей
      }
    }

    for (i = 0; i < size1; ++i) // движение по оси X
    {
      for (j = 0; j < size2; ++j) // движение по оси y
      {
        if (grid[i][j] >= 1) //
        {
          if (neighbour_count[i][j] <= 1 || neighbour_count[i][j] >=4)
            grid[i][j] = 0;
        }
        else
          if (neighbour_count[i][j] == 3)
            grid[i][j] = 1;
      }
    }
    printf("\n\n");
    //system("sleep 0.2");
  }

  return 0;
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

int count_nbr (int grid[size1][size2], int i, int j, int size1, int size2)
{
  int n_count = 0;
  if (i-1 >= 0 && j-1 >= 0)
  {
    if (grid[i-1][j-1] >= 1)
      n_count++;
  }

  if (i-1 >= 0)
  {
    if(grid[i-1][j] >= 1)
      n_count++;
  }

  if (i-1 >= 0 && j+1 < size2)
  {
    if(grid[i-1][j+1] >= 1)
      n_count++;
  }

  if (j-1 >= 0)
  {
    if(grid[i][j-1] >= 1)
      n_count++;
  }

  if (j+1 < size2)
  {
    if(grid[i][j+1] >= 1)
      n_count++;
  }

  if (i+1 < size1 && j-1 >=0)
  {
    if(grid[i+1][j-1] >= 1)
      n_count++;
  }

  if (i+1 < size1)
  {
    if(grid[i+1][j] >= 1)
      n_count++;
  }

  if (i+1 < size1 && j+1 < size2)
  {
    if(grid[i+1][j+1] >= 1)
      n_count++;
  }

  return n_count;
}

// int napr(int grid[size][size], int i, int j, int size)

// while (i > size)
// i == 1
