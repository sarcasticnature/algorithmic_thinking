#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#define MAX_N 100
#define MAX_K 100
#define MAX_DP 200

typedef struct {
    int count;
    float price;
} deal;

int scan_ints(FILE *fp, int *ints)
{
    char buff[3];
    int i = 0;
    int j = 0;
    char c = (char)fgetc(fp);
    if (c != '\n') {
        return 2;
    }

    while (i < MAX_K) {
        c = (char)fgetc(fp);
        if (c == '\n' || c == EOF) {
            ints[i++] = atoi(buff);
            break;
        }

        if (c == ' ') {
            ints[i++] = atoi(buff);
            for (j = 0; j < 3; ++j) {
                buff[j] = 0;
            }
            j = 0;
        } else {
            buff[j++] = c;
        }
    }
    return i != 0;
}

void collect(float *table, deal *deals, int len)
{
    int i = 1;
    int j = 0;

    while (i < len) {
        if (table[i]) {
            deals[j++] = (deal){ i, table[i] };
        }
        ++i;
    }
    if (j < len) {
        deals[j] = (deal){ 0, 0.0 };
    }
}

void gen_dp(deal *input, float *output)
{
    int input_cnt = 0;
    int prev;
    float min_price, tmp_price;
    while (input_cnt < MAX_N) {
        if (input[input_cnt].count == 0) {
            break;
        }
        ++input_cnt;
    }

    output[0] = 0.0;

    for (int i = 1; i < MAX_DP + 1; ++i) {
        min_price = FLT_MAX;
        for (int j = 0; j < input_cnt; ++j) {
            if ((prev = i - input[j].count) >= 0) {
                tmp_price = output[prev] + input[j].price;
                min_price = min_price < tmp_price ? min_price : tmp_price;
            }
        }
        output[i] = min_price;
    }

    min_price = FLT_MAX;
    for (int i = MAX_DP; i >= 0; --i) {
        min_price = min_price < output[i] ? min_price : output[i];
        output[i] = min_price;
    }
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

    float prices[MAX_N + 1] = {0};
    float dp[MAX_DP + 1] = {0};
    float price;
    int line_cnt, idx;
    int case_cnt = 1;
    int items[MAX_K] = {0};
    deal deals[MAX_N];
    while (fscanf(fp, "%f %d", prices + 1, &line_cnt) != EOF) {
        for (int i = 0; i < line_cnt; ++i) {
            fscanf(fp, "%d %f", &idx, &price);
            if (!prices[idx] || prices[idx] > price) {
                prices[idx] = price;
            }
        }
        if (!scan_ints(fp, items)) {
            fclose(fp);
            return 3;
        }
        collect(prices, deals, MAX_N + 1);
        gen_dp(deals, dp);
        // for (int i = 90; i < 100; ++i) {
        //     printf("%.2f ", dp[i]);
        // }

        printf("Case %d:\n", case_cnt++);
        for (int i = 0; i < MAX_K; ++i) {
            if (items[i] == 0) {
                break;
            }
            printf("Buy %d for $%.2f\n", items[i], dp[items[i]]);
        }

        memset(prices, 0, (MAX_N + 1) * (sizeof (float)));
        memset(items, 0, MAX_K * (sizeof (int)));
        memset(deals, 0, MAX_N * (sizeof (deal)));
    }

    fclose(fp);

    return 0;
}
