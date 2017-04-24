#define _BSD_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*
V sliko, dimenzij nxn, vstavi nakljucna stevila v razponu [min,max]
*/
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

/*
Izpise matriko nxn v barvah.
Barve so "mapane":
    0 - rdeca
    1 - zelena
    2 - cyan
    3 - rumena
    4 - magenta
    5 - black
    6 - white

    Tako da so razponi [0,2] - RGB, [2,5] - CMYK, [5,6] - BW.
*/
int *writeMatrixColor(int n, int slika[][n])
{
    printf("\e[1;1H\e[2J"); //cleara konzolo
    int *temp = calloc(7, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[slika[i][j]]++;
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
    return temp;
}

void colorPercent(int *a, int n)
{
    printf("\nBARVA      ST    %%\n");
    printf("Rdeca:   %4d %.2f\n", a[0], (double) a[0]/(n*n));
    printf("Zelena:  %4d %.2f\n", a[1], (double) a[1]/(n*n));
    printf("Modra:   %4d %.2f\n", a[2], (double) a[2]/(n*n));
    printf("Rumena:  %4d %.2f\n", a[3], (double) a[3]/(n*n));
    printf("Magenta: %4d %.2f\n", a[4], (double) a[4]/(n*n));
    printf("Crna:    %4d %.2f\n", a[5], (double) a[5]/(n*n));
    printf("Bela:    %4d %.2f\n", a[6], (double) a[6]/(n*n));
}

/*
Izpise matriko z stevilkami.

!Deluje samo ce so v matriki vrednosti 0-9!
*/
int *writeMatrix(int n, int slika[][n])
{
    int *temp = calloc(7, sizeof(int));
    printf("\e[1;1H\e[2J"); //cleara konzolo
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", slika[i][j]);
            temp[slika[i][j]]++;
        }
        printf("\n");
    }
    return temp;
}

/*
Pomozna funkcija, ki interpretira matriko kot torus.
*/
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

/*
Funkcija, ki nakljucno izbere vrednost nekega sosednjega piksla.
*/
int choose(int n, int slika[][n], int i, int j)
{

    /*##################
    #                  #
    #     -1  0  1  j  #
    #  -1 [0][1][2]    #
    #   0 [3][x][4]    #
    #   1 [5][6][7]    #
    #   i              #
    #                  #
    ###################*/

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
    //Seed za random - time(NULL) res random
    srand(time(NULL));

    const int n = 30;
    int slika[n][n]; /*= {
        {6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6},
        {6, 6, 6, 5, 5, 6, 6, 0, 0, 0, 0, 5, 5, 6, 6, 6},
        {6, 6, 5, 6, 6, 6, 6, 0, 0, 0, 0, 6, 6, 5, 6, 6},
        {6, 5, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 6, 6, 5, 6},
        {6, 5, 6, 6, 6, 0, 0, 6, 6, 6, 6, 0, 0, 6, 5, 6},
        {5, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 0, 0, 0, 5},
        {5, 0, 6, 6, 0, 0, 6, 6, 6, 6, 6, 6, 0, 0, 0, 5},
        {5, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 0, 0, 6, 5},
        {5, 6, 6, 6, 6, 0, 0, 6, 6, 6, 6, 0, 0, 6, 6, 5},
        {5, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 5},
        {5, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 6, 5},
        {6, 5, 5, 5, 6, 6, 5, 6, 6, 5, 6, 6, 5, 5, 5, 6},
        {6, 6, 5, 6, 6, 6, 5, 6, 6, 5, 6, 6, 6, 5, 6, 6},
        {6, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 6, 6},
        {6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 5, 6, 6, 6},
        {6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6}};
        //16x16 gobica*/
        
    int novaSlika[n][n];

    generateRandomMatrix(n, slika, 0, 6);
    colorPercent(writeMatrixColor(n, slika), n);
    usleep(3000000); //spi 3 sekunde, da se nagledas prvotne slike

    //izmenjavanje slika in novaSlika - dela hitreje
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
            colorPercent(writeMatrixColor(n, novaSlika), n);
            usleep(100000);
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
            colorPercent(writeMatrixColor(n, slika), n);
            usleep(100000);
        }
        if (zmaga)
            break; // ce ni bilo spremembe od zadne se zakljuci
    }
    printf("Stevilo iteracij: %d\n", iter); //counter za stevilo zank
}