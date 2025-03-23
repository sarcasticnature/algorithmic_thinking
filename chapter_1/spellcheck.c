#include <stdio.h>
#include <string.h>

#define MAX_WORD_SIZE 1000000

size_t find_prefix(char* str_1, char* str_2)
{
    size_t i = 0;
    while (str_1[i] == str_2[i]) {
        ++i;
    }

    return i;
}

size_t find_suffix(char* str_short, char* str_long)
{
    size_t i = strlen(str_long) - 1;
    while (i > 0 && str_short[i - 1] == str_long[i]) {
        --i;
    }

    return i;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("incorrect number of arguments\n");
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("could not open test file\n");
        return 2;
    }

    static char str_1[MAX_WORD_SIZE + 3], str_2[MAX_WORD_SIZE + 3];

    if (fgets(str_1, sizeof str_1, fp) == NULL || fgets(str_2, sizeof str_2, fp) == NULL) {
        fclose(fp);
        return 3;
    }

    size_t len_1 = strlen(str_1) - 1;
    size_t len_2 = strlen(str_2) - 1;
    str_1[len_1] = '\0';
    str_2[len_2] = '\0';

    size_t prefix_end = find_prefix(str_1, str_2);
    size_t suffix_start;
    if (len_1 < len_2) {
        suffix_start = find_suffix(str_1, str_2);
    } else {
        suffix_start = find_suffix(str_2, str_1);
    }

    int diff = ((int)prefix_end - (int)suffix_start);
    if (diff < 0) {
        printf("%d\n", 0);
    } else {
        printf("%d\n", diff + 1);
        for (size_t i = suffix_start + 1; i <= prefix_end + 1; ++i) {
            printf("%lu", i);
            if (i < prefix_end + 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
