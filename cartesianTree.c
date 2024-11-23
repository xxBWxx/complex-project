#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

Node* rotateLeft(Node* root) {
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    
    return newRoot;
}

Node* rotateRight(Node* root) {
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    
    return newRoot;
}

Node* deleteNode(Node* root, Node* node) {
    if (!root) {
        fprintf(stderr, "Error: Node not found.\n");
        return NULL;
    }

    // Search for the node to delete
    if (node->key < root->key) {
        root->left = deleteNode(root->left, node);
        return root;
    }
    if (node->key > root->key) {
        root->right = deleteNode(root->right, node);
        return root;
    }

    // Node to delete is found
    if (!root->left && !root->right) {
        // Case 1: Node is a leaf
        free(root);
        return NULL;
    }
    
    else if (!root->left) {
        // Case 2: Node has only a right child
        Node* temp = root->right;
        free(root);
        return temp;
    }
    
    else if (!root->right) {
        // Case 3: Node has only a left child
        Node* temp = root->left;
        free(root);
        return temp;
    }

    // Case 4: Node has two children
    // Rotate with the child that has the lowest priority
    if (root->left->priority < root->right->priority) {
        root = rotateRight(root);
        root->right = deleteNode(root->right, node);
    } else {
        root = rotateLeft(root);
        root->left = deleteNode(root->left, node);
    }

    return root;
}


int main() {
    // Create nodes
    Node* nodeA = createNode('A', 5);
    Node* nodeB = createNode('B', 3);
    Node* nodeC = createNode('C', 8);
    Node* nodeD = createNode('D', 2);
    Node* nodeE = createNode('E', 6);
    Node* nodeF = createNode('F', 7);
    Node* nodeG = createNode('G', 9);
    Node* nodeH = createNode('H', 1);
    Node* nodeI = createNode('I', 10);
    Node* nodeJ = createNode('J', 12);

    // Create empty tree
    Node* tree = createEmptyTree();
    
    // Insertion
    tree = insertNode(tree, nodeA);
    tree = insertNode(tree, nodeB);
    tree = insertNode(tree, nodeC);
    tree = insertNode(tree, nodeD);
    tree = insertNode(tree, nodeE);
    tree = insertNode(tree, nodeF);
    tree = insertNode(tree, nodeG);
    tree = insertNode(tree, nodeH);
    tree = insertNode(tree, nodeI);
    tree = insertNode(tree, nodeJ);
    
    // Deletion
    tree = deleteNode(tree, nodeA);
    tree = deleteNode(tree, nodeJ);
    tree = deleteNode(tree, nodeI);
    showTree(tree);
    
    return 0;
}
