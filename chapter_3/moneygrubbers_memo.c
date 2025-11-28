#include <stdio.h>
#include <stdlib.h>

#define MAX_SCHEMES 20
#define SIZE 200

int get_number(FILE *fp, int *num)
{
    int ch;
    int ret = 0;
    ch = fgetc(fp);
    while (ch != ' ' && ch != '\n') {
        ret = ret * 10 + ch - '0';
        ch = fgetc(fp);
    }
    *num = ret;
    return ch == ' ';
}

float min(float a, float b)
{
    return a < b ? a : b;
}

float solve_k(int num[], float price[], int num_schemes,
               float unit_price, int num_apples, float memo[])
{
    float best, result;
    int i;
    if (memo[num_apples] != -1) {
        return memo[num_apples];
    }
    if (num_apples == 0) {
        memo[num_apples] = 0;
        return memo[num_apples];
    }

    result = solve_k(num, price, num_schemes, unit_price, num_apples - 1, memo);
    best = result + unit_price;
    for (i = 0; i < num_schemes; ++i) {
        if (num_apples - num[i] >= 0) {
            result = solve_k(num, price, num_schemes, unit_price, num_apples - num[i], memo);
            best = min(best, result + price[i]);
        }
    }
    memo[num_apples] = best;

    return memo[num_apples];
}

float solve(int num[], float price[], int num_schemes,
             float unit_price, int num_apples, float memo[])
{
    float best;
    int i;
    best = solve_k(num, price, num_schemes, unit_price, num_apples, memo);
    for (i = num_apples + 1; i < SIZE; ++i) {
        best = min(best, solve_k(num, price, num_schemes, unit_price, i, memo));
    }
    return best;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("could not open test file\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("could not open test file\n");
        return 2;
    }

    int test_case, num_schemes, num_apples, more, i;
    float unit_price, result;
    int num[MAX_SCHEMES];
    float price[MAX_SCHEMES];
    float memo[SIZE];
    test_case = 0;

    while (fscanf(fp, "%f%d ", &unit_price, &num_schemes) != EOF) {
        ++test_case;
        for (i = 0; i < num_schemes; ++i) {
            fscanf(fp, "%d%f ", &num[i], &price[i]);
        }
        printf("Case %d:\n", test_case);
        for (i = 0; i < SIZE; ++i) {
            memo[i] = -1;
        }
        more = get_number(fp, &num_apples);
        while (more) {
            result = solve(num, price, num_schemes, unit_price, num_apples, memo);
            printf("Buy %d for $%.2f\n", num_apples, result);
            more = get_number(fp, &num_apples);
        }
        result = solve(num, price, num_schemes, unit_price, num_apples, memo);
        printf("Buy %d for $%.2f\n", num_apples, result);
    }

    fclose(fp);

    return 0;
}
