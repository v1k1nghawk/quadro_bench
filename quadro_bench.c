#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#define EPSILON 1e-9
#define IS_ZERO(x) (fabs(x) < EPSILON)
#define IS_GT_ZERO(x) ((x) >= EPSILON)
#define IS_LT_ZERO(x) ((x) <= -EPSILON)


double epsilon = 1e-9;
bool is_zero(double x) { return fabs(x) < epsilon; }
bool is_gt_zero(double x) { return x >= epsilon; }
bool is_lt_zero(double x) { return x <= -epsilon; }


typedef struct
{
    double root1;
    double root2;
    char roots_quantity;
} roots;


roots quadratic_equation_using_macro(double a, double b, double c) {

    double discriminant;
    roots res;

    if (IS_ZERO(a)) {
        if (!IS_ZERO(b)) {
            res.root1 = -c / b;
            res.roots_quantity = 1;
        } else {
            if (IS_ZERO(c)) res.roots_quantity = 254;
            else res.roots_quantity = 0;
        }
        return res;
    }

    discriminant = pow(b, 2.) - 4. * a * c;
    double doubledA = 2. * a;

    if (IS_GT_ZERO(discriminant)) {
        double sqrtD = sqrt(discriminant);
        res.root1 = (-b + sqrtD) / doubledA;
        res.root2 = (-b - sqrtD) / doubledA;
        res.roots_quantity = 2;
    }
    else if (IS_ZERO(discriminant)) {
        res.root1 = -b / doubledA;
        res.roots_quantity = 1;
    }
    else // Complex roots
        res.roots_quantity = 0;

    return res;
}



roots quadratic_equation_using_funcs(double a, double b, double c) {

    double discriminant;
    roots res;

    if (is_zero(a)) {
        if (!is_zero(b)) {
            res.root1 = -c / b;
            res.roots_quantity = 1;
        } else {
            if (is_zero(c)) res.roots_quantity = 254;
            else res.roots_quantity = 0;
        }
        return res;
    }

    discriminant = pow(b, 2.) - 4. * a * c;
    double doubledA = 2. * a;

    if (is_gt_zero(discriminant)) {
        double sqrtD = sqrt(discriminant);
        res.root1 = (-b + sqrtD) / doubledA;
        res.root2 = (-b - sqrtD) / doubledA;
        res.roots_quantity = 2;
    }
    else if (is_zero(discriminant)) {
        res.root1 = -b / doubledA;
        res.roots_quantity = 1;
    }
    else // Complex roots
        res.roots_quantity = 0;

    return res;
}


int main() {

    unsigned int iterations = 1000000000; // 1Bln

    // Allocate mem on the heap
    double *a = malloc(iterations * sizeof(double));
    double *b = malloc(iterations * sizeof(double));
    double *c = malloc(iterations * sizeof(double));

    // Check if allocation failed
    if (a == NULL || b == NULL || c ==NULL) {
        fprintf(stderr, "Mem allocation failed!\n");
        return 1;
    }

    srand(time(0));

    for (unsigned int i = 0; i < iterations; ++i) {
        a[i] = (double)rand() / RAND_MAX;
        b[i] = (double)rand() / RAND_MAX;
        c[i] = (double)rand() / RAND_MAX;
    }

    ///////
    // TEST MACRO
    ///////

    clock_t start = clock();

    volatile roots sink; // Use volatile to prevent complier for optimizing out the loop
    // Benchmark loop
    for (unsigned int i = 0; i < iterations; ++i) {
        sink = quadratic_equation_using_macro(a[i], b[i], c[i]);
    }

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MACRO Total time for %d iterations: %f seconds\n", iterations, time_spent);
    printf("MACRO Average time per call: %f nanoseconds\n", (time_spent / iterations) * 1e9);

    ///////
    // TEST FUNCS
    ///////
    start = clock();

    // Benchmark loop
    for (unsigned int i = 0; i < iterations; ++i) {
        sink = quadratic_equation_using_funcs(a[i], b[i], c[i]);
    }

    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("FUNCS Total time for %d iterations: %f seconds\n", iterations, time_spent);
    printf("FUNCS Average time per call: %f nanoseconds\n", (time_spent / iterations) * 1e9);

    free(a);
    free(b);
    free(c);

    return 0;
}
