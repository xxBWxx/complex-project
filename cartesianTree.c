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

Node* insertNode(Node* root, Node* node) {
    if (isTreeEmpty(root)) {
        return node;
    }

    if (node->priority < root->priority) {
        if (node->key < root->key) {
            node->right = root;

            if ((root->left) && (root->left->key < node->key)) {
                node->left = root->left;
                root->left = NULL;
            }

            return node;
        }

        else {
            node->left = root;

            if ((root->right) && (root->right->key > node->key)) {
                node->right = root->right;
                root->right = NULL;
            }

            return node;
        }
    }

    if (node->key < root->key) {
        if (!root->left) {
            root->left = node;
            return root;
        }

        root->left = insertNode(root->left, node);
        
        return root;
    }

    if (!root->right) {
        root->right = node;
        return root;
    }

    root->right = insertNode(root->right, node);
    
    return root;
}


void showNode(Node* node) {
    if (node) {
        printf("key: %c, priority: %d\n", node->key, node->priority);
    }
}

void showTree(Node* root) {
    if (!root) {
        return;
    }

    showNode(root);
    
    if (root->left) {
        printf("-left of %c%d\n", root->key, root->priority);
        showTree(root->left);
    }

    if (root->right) {
        printf("-right of %c%d\n", root->key, root->priority);
        showTree(root->right);
    }
}
