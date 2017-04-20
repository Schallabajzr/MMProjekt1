#define _BSD_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

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

void writeMatrixColor(int n, int slika[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            switch (slika[i][j])
            {
            case 0:
                //light rdeca
                printf("\e[101m\e[91m%d \e[0m", slika[i][j]);
                break;
            case 1:
                //light green
                printf("\e[92m\e[102m%d \e[0m", slika[i][j]);
                break;
            case 2:
                //light cyan
                printf("\e[96m\e[106m%d \e[0m", slika[i][j]);
                break;
            case 3:
                //light yellow
                printf("\e[93m\e[103m%d \e[0m", slika[i][j]);
                break;
            case 4:
                //light magenta
                printf("\e[105m\e[95m%d \e[0m", slika[i][j]);
                break;
            case 5:
                //black
                printf("\e[30m\e[40m%d \e[0m", slika[i][j]);
                break;
            case 6:
                //white
                printf("\e[97m\e[107m%d \e[0m", slika[i][j]);
                break;
            default:
                printf("!!");
            }
        }
        printf("\n");
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    usleep(300000);
}

void writeMatrix(int n, int slika[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", slika[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    usleep(200000);
}

int giveColor(int n, int slika[][n], int i, int j)
{ //nism zihr da je prou
    n = n - 1;
    if (i == -1)
        i = n;
    if (j == -1)
        j = n;
    i = i % n;
    j = j % n;
    return slika[i][j];
}

int choose(int n, int slika[][n], int i, int j)
/*###################################
#     -1  0  1  j
#  -1 [0][1][2]
#   0 [3][x][4]
#   1 [5][6][7]
#   i
####################################*/
{
    int temp[8];
    temp[0] = giveColor(n, slika, i - 1, j - 1);
    temp[1] = giveColor(n, slika, i - 1, j);
    temp[2] = giveColor(n, slika, i - 1, j + 1);
    temp[3] = giveColor(n, slika, i, j - 1);
    temp[4] = giveColor(n, slika, i, j + 1);
    temp[5] = giveColor(n, slika, i + 1, j - 1);
    temp[6] = giveColor(n, slika, i + 1, j);
    temp[7] = giveColor(n, slika, i + 1, j + 1);

    return temp[rand() % 8];
}

int main()
{
    srand(time(NULL));

    const int n = 10;
    int slika[n][n];
    /* 
    //Mario gobica
    {
        {6,6,6,6,6,5,5,5,5,5,5,6,6,6,6,6},
        {6,6,6,5,5,6,6,0,0,0,0,5,5,6,6,6},
        {6,6,5,6,6,6,6,0,0,0,0,6,6,5,6,6},
        {6,5,6,6,6,6,0,0,0,0,0,0,6,6,5,6},
        {6,5,6,6,6,0,0,6,6,6,6,0,0,6,5,6},
        {5,0,0,0,0,0,6,6,6,6,6,6,0,0,0,5},
        {5,0,6,6,0,0,6,6,6,6,6,6,0,0,0,5},
        {5,6,6,6,6,0,6,6,6,6,6,6,0,0,6,5},
        {5,6,6,6,6,0,0,6,6,6,6,0,0,6,6,5},
        {5,0,6,6,0,0,0,0,0,0,0,0,0,6,6,5},
        {5,0,0,0,5,5,5,5,5,5,5,5,0,0,6,5},
        {6,5,5,5,6,6,5,6,6,5,6,6,5,5,5,6},
        {6,6,5,6,6,6,5,6,6,5,6,6,6,5,6,6},
        {6,6,5,6,6,6,6,6,6,6,6,6,6,5,6,6},
        {6,6,6,5,6,6,6,6,6,6,6,6,5,6,6,6},
        {6,6,6,6,5,5,5,5,5,5,5,5,6,6,6,6}
        
    };*/
    int novaSlika[n][n];

    generateRandomMatrix(n, slika, 0, 6);
    writeMatrixColor(n, slika);
    usleep(3000000);

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
                    novaSlika[i][j] = choose(n, slika, i, j);
                    if (novaSlika[i][j] != barva)
                        zmaga = 0;
                }
            }
            writeMatrixColor(n, novaSlika);
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    slika[i][j] = choose(n, novaSlika, i, j);
                    if (slika[i][j] != barva)
                        zmaga = 0;
                }
            }
            writeMatrixColor(n, slika);
        }
        if (zmaga)
            break;
    }
    //printf("%d", iter);
}