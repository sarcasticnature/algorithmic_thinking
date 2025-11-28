#include <stdio.h>

#define SIZE 10000

void solve(int m, int n, int t)
{
    int i, first, second;
    int dp[SIZE];
    dp[0] = 0;

    for (i = 1; i <= t; ++i) {
        if (i >= m) {
            first = dp[i - m];
        } else {
            first = -1;
        }
        if (i >= n) {
            second = dp[i - n];
        } else {
            second = -1;
        }

        if (first == -1  && second == -1) {
            dp[i] = -1;
        } else {
            dp[i] = 1 + (first > second ? first : second);
        }
    }

    for (i = t; dp[i] == -1 && i > 0; --i);
    printf("%d", dp[i]);
    if (i != t) {
        printf(" %d", t - i);
    }
    printf("\n");
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

    int m, n, t;
    while (fscanf(fp, "%d %d %d", &m, &n, &t) != EOF) {
        solve(m, n, t);
    }

    fclose(fp);

    return 0;
}
