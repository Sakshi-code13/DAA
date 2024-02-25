#include <stdio.h>

void strassen(int n, int a[][n], int b[][n], int c[][n]) {
    if (n == 1) {
        c[0][0] = a[0][0] * b[0][0];
        return;
    }

    int i, j;
    int k = n / 2;
    int a11[k][k], a12[k][k], a21[k][k], a22[k][k];
    int b11[k][k], b12[k][k], b21[k][k], b22[k][k];
    int c11[k][k], c12[k][k], c21[k][k], c22[k][k];
    int p1[k][k], p2[k][k], p3[k][k], p4[k][k], p5[k][k], p6[k][k], p7[k][k];

    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + k];
            a21[i][j] = a[i + k][j];
            a22[i][j] = a[i + k][j + k];

            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + k];
            b21[i][j] = b[i + k][j];
            b22[i][j] = b[i + k][j + k];
        }
    }

    strassen(k, a11, b11, p1);
    strassen(k, a12, b21, p2);
    strassen(k, a11, b12, p3);
    strassen(k, a12, b22, p4);
    strassen(k, a21, b11, p5);
    strassen(k, a22, b21, p6);
    strassen(k, a21, b12, p7);
    strassen(k, a22, b22, c11);

    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            c12[i][j] = p1[i][j] + p2[i][j];
            c21[i][j] = p3[i][j] + p4[i][j];
            c22[i][j] = p5[i][j] + p6[i][j];
            c[i][j] = c11[i][j] + c12[i][j];
            c[i][j + k] = c21[i][j] + c22[i][j];
            c[i + k][j] = c12[i][j] - c11[i][j];
            c[i + k][j + k] = c22[i][j] - c21[i][j];
        }
    }
}

int main() {
    int n = 4;
    int a[][4] = {{1, 2, 3, 4}, {4, 3, 2, 1}, {5, 6, 7, 8}, {8, 7, 6, 5}};
    int b[][4] = {{8, 7, 6, 5}, {5, 6, 7, 8}, {4, 3, 2, 1}, {1, 2, 3, 4}};
    int c[n][n];
    int i, j;

    strassen(n, a, b, c);

    printf("Result matrix is \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}

