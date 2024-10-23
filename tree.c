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

    newNode->key = key;
    newNode->priority = priority;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void showNode(Node* node) {
    if (node) {
        printf("key: %c, priority: %d\n", node->key, node->priority);
    }
}

void showTree(Node* tree) {
    if (!tree) {
        return;
    }

    showNode(tree);
    
    if (tree->left) {
        printf("left of %c%d\n", tree->key, tree->priority);
        showTree(tree->left);
    }

    if (tree->right) {
        printf("right of %c%d\n", tree->key, tree->priority);
        showTree(tree->right);
    }
}

Node* addNode(Node* tree, Node* child) {
    if (!tree) {
        return NULL;
    } 

    if (!child) {
        return NULL;
    }

    Node* currentNode = tree;
    Node* parent = NULL;
    while (currentNode) {
        if (child->priority < currentNode->priority) {
            currentNode = addNode(child, currentNode);

            if (!parent) {
                return currentNode;
            }

            else {
                if (currentNode->key < parent->key) {
                    parent->left = currentNode;
                }

                else {
                    parent->right = currentNode;
                }

                break;
            }
        }

        if (child->key < currentNode->key) {
            if (currentNode->left == NULL) {
                currentNode->left = child; 
                break;
            }
            
            else {
                parent = currentNode;
                currentNode = currentNode->left;
            }
        } 
        
        else {
            if (currentNode->right == NULL) {
                currentNode->right = child; 
                break;
            }
            
            else {
                parent = currentNode;
                currentNode = currentNode->right;
            }
        }
    }

    return tree;
}

int main() {
    Node* nodeA1 = createNode('A', 1);
    Node* nodeB2 = createNode('B', 2);
    Node* nodeC3 = createNode('C', 3);
    Node* nodeD4 = createNode('D', 4);

    Node* tree = nodeD4;
    showTree(tree);
    printf("\n");

    tree = addNode(tree, nodeB2);
    showTree(tree);
    printf("\n");

    tree = addNode(tree, nodeC3);
    showTree(tree);
    printf("\n");
    
    return 0;
}