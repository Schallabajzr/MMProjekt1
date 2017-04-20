#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void generateRandomMatrix(int n, int slika[n][n], int min, int max)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            slika[i][j] = rand() % (max + 1 - min) + min;
        }
    }
}

void write(int n, int slika[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", slika[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int giveColor(int n, int slika[][n], int i, int j)
{
    if (i == -1)
        i = n;
    if (j == -1)
        j = n;
    i = i % n;
    j = j % n;
    return slika[i][j];
}

int choose(int n, int slika[][n], int i, int j)
{
    int temp[8];
    temp[0] = giveColor(n, slika, i - 1, j + 1);
    temp[1] = giveColor(n, slika, i, j - 1);
    temp[2] = giveColor(n, slika, i - 1, j);
    temp[3] = giveColor(n, slika, i + 1, j - 1);
    temp[4] = giveColor(n, slika, i - 1, j - 1);
    temp[5] = giveColor(n, slika, i, j + 1);
    temp[6] = giveColor(n, slika, i + 1, j);
    temp[7] = giveColor(n, slika, i + 1, j + 1);

    return temp[rand() % 8];
}

int main()
{
    srand(time(NULL));

    int slika[50][50]; 
        /*={ 
            {1,2,3,4,5},
            {5,4,3,2,1},
            {1,3,5,7,9},
            {0,2,4,6,8},
            {5,6,7,8,9}
        };*/
    generateRandomMatrix(50,slika, 0, 9);

    int novaSlika[50][50];
    int n = 50;

    write(n, slika);
    int iter = 0;
    for (int count = 0; 1; count++)
    {
        iter++;
        int barva = slika[0][0];
        int zmaga = 1;
        if (count % 2 == 0)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    novaSlika[i][j] = choose(n - 1, slika, i, j);
                    if (novaSlika[i][j] != barva)
                    {
                        zmaga = 0;
                    }
                }
            }
            write(n,novaSlika);
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    slika[i][j] = choose(n - 1, novaSlika, i, j);
                    if (slika[i][j] != barva)
                    {
                        zmaga = 0;
                    }
                }
            }
            write(n,slika);
        }
        if (zmaga)
        {
            break;
        }
    }
    //printf("%d", iter);
}