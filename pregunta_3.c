#include <stdio.h>
#include <omp.h>

int multiplicacion(int a, int b) {
    int result = 0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < b; i++) {
        result += a;
    }

    return result;
}

int division(int a, int b) {
    int result = 0;
    int remainder = a;

    #pragma omp parallel
    {
        #pragma omp single
        {
            while (remainder >= b) {
                #pragma omp task firstprivate(remainder)
                {
                    remainder -= b;
                }
                #pragma omp taskwait
                #pragma omp atomic
                result++;
            }
        }
    }

    return result;
}

int main() {
    int a = 100, b = 10;
    int resuladotMul = multiplicacion(a, b);
    printf("Multiplicacion: %d * %d = %d\n", a, b, resuladotMul);
    int resultadoDiv = division(a, b);
    printf("Division: %d / %d = %d\n", a, b, resultadoDiv);
    return 0;
}