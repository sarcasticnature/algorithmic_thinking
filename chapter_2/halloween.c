#include <stdlib.h>
#include <stdio.h>

#define NUM_TREES 5
#define MAX_LINE_LEN 255

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct node {
    int candy;
    struct node* left;
    struct node* right;
} node;

typedef struct tree_data {
    int total_candy;
    int path_len;
    int depth;
} tree_data;

node* read_tree_helper(char* line, int* pos)
{
    node* tree = malloc(sizeof(node));

    if (line[*pos] == '(') {
        ++(*pos);
        tree->left = read_tree_helper(line, pos);
        ++(*pos);
        tree->right = read_tree_helper(line, pos);
        ++(*pos);
    } else {
        tree->left = NULL;
        tree->right = NULL;
        tree->candy = line[(*pos)++] - '0';
        char peek = line[*pos];
        if (peek != ' ' && peek != ')' && peek != '\0' && peek != '\n') {
            tree->candy = tree->candy * 10 + (peek - '0');
            ++(*pos);
        }
    }

    return tree;
}

node* read_tree(char* line)
{
    int pos = 0;
    return read_tree_helper(line, &pos);
}

tree_data solve_tree(node* tree)
{
    tree_data data;
    // NOTE: tree is expected to be "full", i.e. no nodes with a single child
    if (!tree->left) {
        data.total_candy = tree->candy;
        data.path_len = 0;
        data.depth = 0;
    } else {
        data = solve_tree(tree->left);
        tree_data tmp_data = solve_tree(tree->right);
        data.total_candy += tmp_data.total_candy;
        data.path_len += tmp_data.path_len + 4;
        data.depth = MAX(tmp_data.depth, data.depth) + 1;
    }
    return data;
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

    char line_buff[MAX_LINE_LEN + 1];

    for (int i = 0; i < NUM_TREES; ++i) {
        fgets(line_buff, MAX_LINE_LEN + 1, fp); // NOTE: may contain a newline before '\0'
        node* tree = read_tree(line_buff);
        tree_data data = solve_tree(tree);
        printf("%d %d\n", data.path_len - data.depth, data.total_candy);
    }

    return 0;
}
