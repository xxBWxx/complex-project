#include <stdlib.h>
#include <stdio.h>

typedef struct _Node Node;

struct _Node {
    char key;
    int priority;
    Node* left;
    Node* right;
};


Node* createNode(char key, int priority) {
    Node* newNode = (Node*) malloc(sizeof(Node));

    if (!newNode) {
        perror("Failed to allocate memory for node creation");
        exit(EXIT_FAILURE);
    }

    newNode->key = key;
    newNode->priority = priority;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* createEmptyTree() {
    return NULL;
}

int isTreeEmpty(Node* root) {
    return root == NULL;
}

Node* getLeftChild(Node* node) {
    if (!node) {
        fprintf(stderr, "Error: Cannot get left child of a NULL node.\n");
        return NULL;
    }

    return node->left;
}

Node* getRightChild(Node* node) {
    if (!node) {
        fprintf(stderr, "Error: Cannot get right child of a NULL node.\n");
        return NULL;
    }

    return node->right;
}

Node* findKey(char key, Node* root) {
    if (isTreeEmpty(root)) {
        fprintf(stderr, "Error: Empty tree.\n");
        return NULL;
    }

    Node* iter = root;
    while (iter) {
        if (iter->key == key) {
            return iter;
        }

        else {
            if (key < iter->key) {
                iter = getLeftChild(iter);
            }

            else {
                iter = getRightChild(iter);
            }
        }
    }

    return NULL;
}