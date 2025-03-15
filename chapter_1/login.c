#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_USERS 100000
#define MAX_PWD_LEN 10

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

#define HASH_BIT_LEN 20

unsigned long oaat(const char* key, unsigned long len, unsigned long bits)
{
    unsigned long hash, i;
    for (hash = 0, i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & hashmask(bits);
}

typedef struct node {
    char pwd[MAX_PWD_LEN + 1];
    int count;
    struct node* next;
} node;

node* find_in_table(node* table[], const char* key)
{
    unsigned hash = oaat(key, strlen(key), HASH_BIT_LEN);
    node* entry = table[hash];
    while (entry) {
        if (strcmp(entry->pwd, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

void add_to_table(node* table[], const char* key)
{
    node* entry = find_in_table(table, key);
    if (!entry) {
        unsigned hash = oaat(key, strlen(key), HASH_BIT_LEN);
        entry = malloc(sizeof(node));
        strcpy(entry->pwd, key);
        entry->count = 0;
        entry->next = table[hash];
        table[hash] = entry;
    }
    ++entry->count;
}

bool pwd_in_array(char array[][MAX_PWD_LEN + 1], int max_idx, char* key)
{
    while (max_idx > 0) {
        if (strcmp(array[max_idx - 1], key) == 0) {
            return true;
        }
        --max_idx;
    }
    return false;
}

int main(int argc, char** argv)
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

    static node* users[1 << HASH_BIT_LEN] = { NULL };
    int num_ops, op, op_type;
    char pwd[MAX_PWD_LEN + 1];
    char substr[MAX_PWD_LEN + 1];
    char substr_buff[MAX_PWD_LEN * MAX_PWD_LEN][MAX_PWD_LEN + 1];

    if (fscanf(fp, "%d", &num_ops) == EOF) {
        fclose(fp);
        return 3;
    }

    for (op = 0; op < num_ops; ++op) {
        if (fscanf(fp, "%d %s", &op_type, pwd) == EOF) {
            fclose(fp);
            return 4;
        }

        if (op_type == 1) {
            int pwd_len = strlen(pwd);
            int substr_cnt = 0;

            for (int i = 0; i < pwd_len; ++i) {
                for (int take = 1; take + i - 1 < pwd_len; ++take) {
                    strncpy(substr, pwd + i, take);
                    substr[take] = '\0';
                    if (!pwd_in_array(substr_buff, substr_cnt, substr)) {
                        strcpy(substr_buff[substr_cnt++], substr);
                        add_to_table(users, substr);
                    }
                }
            }
        } else {
            node* user = find_in_table(users, pwd);
            if (user) {
                printf("%d\n", user->count);
            } else {
                printf("0\n");
            }
        }
    }

    return 0;
}
