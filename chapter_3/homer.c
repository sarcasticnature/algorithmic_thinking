#include <stdio.h>
#include <limits.h>

typedef struct {
    int burgers;
    int beer;
} burgers_n_beer;

burgers_n_beer solve(int m, int n, int t)
{
    burgers_n_beer ret = {0, 0};
    if (t < m && t < n) {
        ret.beer = t;
        return ret;
    }

    if (m < n) {
        int tmp = n;
        n = m;
        m = tmp;
    }

    int count = 0;
    int min_count = 0;
    int min = INT_MAX;
    int remainder;
    while (count < m) {
        if ((remainder = (t - count * m) % n)) {
            if (remainder < 0) {
                break;
            }
            if (remainder < min) {
                min = remainder;
                min_count = count;
            }
            ++count;
        } else {
            ret.burgers = count + (t - count * m) / n;
            break;
        }
    }

    if (!ret.burgers) {
        ret.burgers = min_count + (t - min_count * m) / n;
        ret.beer = min;
    }

    return ret;
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
        burgers_n_beer bnb = solve(m, n, t);
        printf("%d", bnb.burgers);
        if (bnb.beer) {
            printf(" %d", bnb.beer);
        }
        printf("\n");
    }

    fclose(fp);

    return 0;
}
