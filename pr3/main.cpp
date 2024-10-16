#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZEOF_ID 32

struct Node {
    char id[SIZEOF_ID];
    struct Node *left = nullptr, *right = nullptr;
};

/* 
 * A / B \ C ; 
 * recursively reaches the bottom of a tree and adds a node to it.
 * @return which way the node was added. -1 is left; 1 is right
 */
short int insertNode(struct Node *c_node, struct Node *node) {
    if (strcmp(c_node->id, node->id) > 0) { // Go left
        if (c_node->left == nullptr) // if nullptr, add to left
            c_node->left = node;
        else // if not nullptr, explore left
            insertNode(c_node->left, node);
        return -1;
    } else { // Go right
        if (c_node->right == nullptr) // if nullptr, add to right
            c_node->right = node;
        else // if not nullptr, explore right
            insertNode(c_node->right, node);
        return 1;
    }
}

struct Node *balanceTree(struct Node *tree) {
    return NULL;
}

bool findNode(struct Node *c_node, char* id) {
    int cmp = strcmp(c_node->id, id);
    if (cmp == 0) { // Found the node.
        return 1;
    } else if (cmp > 0) { // Look left
        printf("Going left\n");
        if (c_node->left == nullptr) { // if nullptr, didn't find the node.
            return 0;
        } else {
            return findNode(c_node->left, id);
        }
    } else { // Look right
        printf("Going right\n");
        if (c_node->right == nullptr) { // if nullptr, didn't find the node.
            return 0;
        } else {
            return findNode(c_node->right, id);
        }
    }
}


void readString(char *string) {
    char buffer = 0;
    short int index = 0;
    fread(&buffer, 1, 1, stdin);
    while (buffer != 0 && buffer != ' ' && buffer != '\n')
    {
        *(string + index) = buffer;
        index++;
        fread(&buffer, 1, 1, stdin);
    }
    *(string + index) = '\0';
}

/* Simple, stdin, line-by-line reader.
 * Gets first line, gets N more lines.
 */
static inline void readSetA(struct Node *set, int set_size) {
    readString(set->id);
    for (int i = 0; i < set_size; ++i) {
        struct Node *node = new struct Node;
        node->left = nullptr;
        node->right = nullptr;
        readString(node->id);
        insertNode(set, node);
    }
}

static inline void findOnSetAFromSetB(struct Node *set, int set_size) {
    char id[SIZEOF_ID];
    for (int i = 0; i < set_size; ++i) {
        readString(id);
        printf("Node: %s\n", id);
        if (!findNode(set, id)) {
            printf("0\n");
            return;
        }
    }
    printf("1\n");
}

void printTree(struct Node *set) {
    bool left = 0, right = 0;
    printf("N: %s ; ", set->id);
    if (set->left != nullptr) {
        printf("L: %s", set->left->id);
        left = 1;
    }
    printf(" ; ");
    if (set->right != nullptr) {
        printf("R: %s", set->right->id);
        right = 1;
    }
    printf("\n");
    if (left) {
        printf("Going left\n");
        printTree(set->left);
    }
    if (right) {
        printf("Going right\n");
        printTree(set->right);
    }
}

int main()
{
    int size_a, size_b;
    scanf("%d", &size_a);  // Read the size of set A
    printf("Set A size: %d\n", size_a);
    struct Node *set_a = new struct Node;
    set_a->left = nullptr;
    set_a->right = nullptr;
    readSetA(set_a, size_a);
    scanf("%d", &size_b);  // Read the size of set B
    printf("Set B size: %d\n", size_b);
    findOnSetAFromSetB(set_a, size_b);
    //printTree(set_a);

    return 0;
}