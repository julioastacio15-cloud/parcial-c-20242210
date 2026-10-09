/***********************************************************/
/*           Programación para mecatrónicos               */
/*  Nombre:    Julio Peguero Astacio                                  */
/*  Matricula: 20242210                                               */
/*  Seccion:   Sabados                                              */
/*  Practica:  Primer parcial individual - Reto 08                                     */
/*  Fecha:     9/10/2026                                              */                       
/* Link Practica: https://github.com/julioastacio15-cloud/parcial-c-20242210          */
/***********************************************************/

#include <stdio.h>

int main(void) {
    int n, m, l, u;
    int inventario[30][30];
    int eventos_columna[30] = {0};
    int i, j;

    if (scanf("%d %d %d %d", &n, &m, &l, &u) != 4) {
        printf("ERROR\n");
        return 0;
    }

    /* Validar dimensiones y límites antes de leer la matriz. */
    if (n < 1 || n > 30 || m < 1 || m > 30 ||
        l < 0 || u > 1000 || l > u) {
        printf("ERROR\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (scanf("%d", &inventario[i][j]) != 1 ||
                inventario[i][j] < 0 || inventario[i][j] > 1000) {
                printf("ERROR\n");
                return 0;
            }
        }
    }

    {
        int fila_prioritaria = 0;
        int mayor_racha = 0;
        int mayor_impacto = 0;
        int mayor_cantidad = 0;
        int total_eventos = 0;

        for (i = 0; i < n; i++) {
            int cantidad = 0;
            int impacto_total = 0;
            int racha_actual = 0;
            int inicio_actual = 0;
            int racha_maxima = 0;
            int inicio_racha_maxima = 0;

            for (j = 0; j < m; j++) {
                int evento = (j >= 1 &&
                              inventario[i][j - 1] > u &&
                              inventario[i][j] <= l);
                int impacto = evento
                    ? inventario[i][j - 1] - inventario[i][j]
                    : 0;

                if (evento) {
                    cantidad++;
                    impacto_total += impacto;
                    eventos_columna[j]++;
                    total_eventos++;

                    if (racha_actual == 0) {
                        inicio_actual = j + 1;
                    }
                    racha_actual++;

                    /* El inicio solo cambia al superar la racha máxima.
                       Así se conserva el inicio más temprano en caso de empate. */
                    if (racha_actual > racha_maxima) {
                        racha_maxima = racha_actual;
                        inicio_racha_maxima = inicio_actual;
                    }
                } else {
                    racha_actual = 0;
                }
            }

            printf("FILA %d EVENTOS %d IMPACTO %d RACHA %d INICIO %d\n",
                   i + 1, cantidad, impacto_total,
                   racha_maxima, inicio_racha_maxima);

            /* El recorrido ascendente conserva la fila menor en los empates finales. */
            if (cantidad > 0 &&
                (fila_prioritaria == 0 ||
                 racha_maxima > mayor_racha ||
                 (racha_maxima == mayor_racha &&
                  impacto_total > mayor_impacto) ||
                 (racha_maxima == mayor_racha &&
                  impacto_total == mayor_impacto &&
                  cantidad > mayor_cantidad))) {
                fila_prioritaria = i + 1;
                mayor_racha = racha_maxima;
                mayor_impacto = impacto_total;
                mayor_cantidad = cantidad;
            }
        }

        printf("COLUMNAS");
        for (j = 0; j < m; j++) {
            printf(" %d", eventos_columna[j]);
        }
        printf("\n");

        if (total_eventos == 0) {
            printf("PRIORIDAD 0\n");
            printf("COLUMNA 0\n");
        } else {
            int columna_destacada = 0;

            /* El uso de > conserva la columna menor en caso de empate. */
            for (j = 1; j < m; j++) {
                if (eventos_columna[j] >
                    eventos_columna[columna_destacada]) {
                    columna_destacada = j;
                }
            }

            printf("PRIORIDAD %d\n", fila_prioritaria);
            printf("COLUMNA %d\n", columna_destacada + 1);
        }
    }

    return 0;
}