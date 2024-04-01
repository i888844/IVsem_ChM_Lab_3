#include <cstdio>
#include <cmath>
#include <windows.h>

double Eitkin_by_X(double function[2][11], double X)
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

    double L = 0.0;

    for (int i = 0; i < 6; i++)
    {
        double Li = 1.0;
        for (int j = 0; j < 6; j++)
        {
            if (i != j)
            {
                Li *= (X - Eitkin[j][0]) / (Eitkin[i][0] - Eitkin[j][0]);
            }
        }
        L += Eitkin[i][1] * Li;
    }

    printf("Значение функции по интерполяционной формуле Лагранжа: %.2f\n", L);
    printf("\n\n\n");

    return L;
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

    double X[10];
    double Xf[10];
    double Ls[10];

    X[0] = function[0][2] + 0.25 * h;
    printf("\nX = X0 + 0.25h = %.2f\n", X[0]);
    Ls[0] = Eitkin_by_X(function, X[0]);
    Xf[0] = atan(1.0 / 2.0 * X[0]);

    X[1] = function[0][2] - 0.25 * h;
    printf("X = X0 - 0.25h = %.2f\n", X[1]);
    Ls[1] = Eitkin_by_X(function, X[1]);
    Xf[1] = atan(1.0 / 2.0 * X[1]);

    X[2] = function[0][2] + 0.5 * h;
    printf("X = X0 + 0.5h = %.2f\n", X[2]);
    Ls[2] = Eitkin_by_X(function, X[2]);
    Xf[2] = atan(1.0 / 2.0 * X[2]);

    X[3] = function[0][2] - 0.5 * h;
    printf("X = X0 - 0.5h = %.2f\n", X[3]);
    Ls[3] = Eitkin_by_X(function, X[3]);
    Xf[3] = atan(1.0 / 2.0 * X[3]);

    X[4] = function[0][5] + 0.5 * h;
    printf("X = X5 + 0.5h = %.2f\n", X[4]);
    Ls[4] = Eitkin_by_X(function, X[4]);
    Xf[4] = atan(1.0 / 2.0 * X[4]);

    X[5] = function[0][5] - 0.5 * h;
    printf("X = X5 - 0.5h = %.2f\n", X[5]);
    Ls[5] = Eitkin_by_X(function, X[5]);
    Xf[5] = atan(1.0 / 2.0 * X[5]);

    X[6] = function[0][7] + 0.25 * h;
    printf("X = X7 + 0.25h = %.2f\n", X[6]);
    Ls[6] = Eitkin_by_X(function, X[6]);
    Xf[6] = atan(1.0 / 2.0 * X[6]);

    X[7] = function[0][7] - 0.25 * h;
    printf("X = X7 - 0.25h = %.2f\n", X[7]);
    Ls[7] = Eitkin_by_X(function, X[7]);
    Xf[7] = atan(1.0 / 2.0 * X[7]);

    X[8] = function[0][10] + 1.5 * h;
    printf("X = X10 + 1.5h = %.2f\n", X[8]);
    Ls[8] = Eitkin_by_X(function, X[8]);
    Xf[8] = atan(1.0 / 2.0 * X[8]);

    X[9] = function[0][10] - 1.5 * h;
    printf("X = X10 - 1.5h = %.2f\n", X[9]);
    Ls[9] = Eitkin_by_X(function, X[9]);
    Xf[9] = atan(1.0 / 2.0 * X[9]);

    printf("\n\nX      F(x) истин.   F(x) Лагранж   Погрешность\n");
    for (i = 0; i < 10; i++)
    {
        printf("%.2f   %.8f    %.8f     %.8f\n", X[i], Ls[i], Xf[i], fabs(Xf[i] - Ls[i]));
    }
}
