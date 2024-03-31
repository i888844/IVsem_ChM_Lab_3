#include <cstdio>
#include <cmath>
#include <windows.h>

void Eitkin_by_X(double function[2][11], double X)
{
    int i = 0;
    int j = 0;

    double Eitkin[6][10];

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 10; j++)
        {
            Eitkin[i][j] = 0.0;
        }
    }

    Eitkin[0][2] = function[0][0];
    Eitkin[0][3] = function[0][2];
    Eitkin[0][4] = function[0][5];
    Eitkin[0][5] = function[0][7];
    Eitkin[0][6] = function[0][10];

    Eitkin[1][0] = function[0][0];
    Eitkin[1][1] = function[1][0];

    Eitkin[2][0] = function[0][2];
    Eitkin[2][1] = function[1][2];

    Eitkin[3][0] = function[0][5];
    Eitkin[3][1] = function[1][5];

    Eitkin[4][0] = function[0][7];
    Eitkin[4][1] = function[1][7];

    Eitkin[5][0] = function[0][10];
    Eitkin[5][1] = function[1][10];

    double P = 1.0;

    for (i = 1; i < 6; i++)
    {
        for (j = 2; j < 7; j++)
        {
            if (i == j - 1)
            {
                Eitkin[i][j] = X - Eitkin[i][0];
                P *= Eitkin[i][j];
                continue;
            }
            Eitkin[i][j] = Eitkin[i][0] - Eitkin[0][j];
        }
    }

    for (i = 1; i < 6; i++)
    {
        Eitkin[i][7] = 1;
    }

    double S = 0.0;

    for (i = 1; i < 6; i++)
    {
        for (j = 2; j < 7; j++)
        {
            Eitkin[i][7] *= Eitkin[i][j];
        }
        Eitkin[i][8] = Eitkin[i][1] / Eitkin[i][7];
        S += Eitkin[i][8];
    }

    printf("X     Y     t1       t2       t3       t4       t5       Di       Yi       Yi / Di\n");
    printf("        %8.2f %8.2f %8.2f %8.2f %8.2f\n", Eitkin[0][2], Eitkin[0][3], Eitkin[0][4], Eitkin[0][5], Eitkin[0][6]);
    for (i = 1; i < 6; i++)
    {
        printf("%.2f  %.2f  %.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n", Eitkin[i][0], Eitkin[i][1], Eitkin[i][2], Eitkin[i][3], Eitkin[i][4], Eitkin[i][5], Eitkin[i][6], Eitkin[i][7], Eitkin[i][1], Eitkin[i][8]);
    }
    printf("%79.2f\n", S);
    printf("Произведение диагонали: %.2f\n", P);
    printf("\n\n\n");
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int i = 0;
    double x = 1.0;
    const double h = 0.4;

    double function[2][11];

    for (i = 0; i < 2; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            function[i][j] = 0.0;
        }
    }

    i = 0;
    printf("X     Y\n");
    for (x = 1.0; x < 5.05; x += h)
    {
        function[0][i] = x;
        function[1][i] = atan(1.0 / 2.0 * x);
        printf("%.2f  %.2f\n", function[0][i], function[1][i]);
        i++;
    }
    printf("\n");

    double X = 0.0;

    X = function[0][2] + 0.25 * h;
    printf("X = X0 + 0.25h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][2] - 0.25 * h;
    printf("X = X0 - 0.25h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][2] + 0.5 * h;
    printf("X = X0 + 0.5h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][2] - 0.5 * h;
    printf("X = X0 - 0.5h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][5] + 0.5 * h;
    printf("X = X5 + 0.5h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][5] - 0.5 * h;
    printf("X = X5 - 0.5h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][7] + 0.25 * h;
    printf("X = X7 + 0.25h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][7] - 0.25 * h;
    printf("X = X7 - 0.25h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][10] + 1.5 * h;
    printf("X = X10 + 1.5h = %.2f\n", X);
    Eitkin_by_X(function, X);

    X = function[0][10] - 1.5 * h;
    printf("X = X10 - 1.5h = %.2f\n", X);
    Eitkin_by_X(function, X);
}
