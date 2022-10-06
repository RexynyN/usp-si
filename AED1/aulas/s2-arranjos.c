#include <stdio.h>
#include <stdlib.h>

// Exemplo 1
// int main()
// {
//     int x[3];

//     x[0] = 1;
//     x[1] = 2;
//     x[2] = 7;

//     imprimir(x);

//     printf("x0: %i, x1: %i, x2: %i\n", x[0], x[1], x[2]);
//     printf("&x: %p, x: %p, *x: %p\n", &x, x, *x);
//     return 0;
// }

// void imprimir(int *w)
// {
//     printf("w0: %i, w1: %i, w2: %i\n", w[0], w[1], w[2]);
//     printf("&w: %p, w: %p, *w: %p\n", &w, w, *w);

//     w[0] = 21;
//     w[1] = 22;
//     w[2] = 27;
// }

// ===============================================================================
// ===============================================================================

// Exemplo 2
int main()
{
    int x[3];
    int *y = (int *)malloc(sizeof(int) * 3);

    y[0] = 4;
    y[1] = 5;
    y[2] = 6;

    *y = *x;
    free(y);
    y = (int *) x;

    printf("y0: %i, y1: %i, y2: %i\n", y[0], y[1], y[2]);
    printf("&y: %p, y: %p, *y: %p\n", &y, y, *y);
}