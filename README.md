# Complex Project

### Key Properties of Cartesian Trees

1. Binary Search Tree Property (BST):

- Nodes are ordered by their keys such that for any node _z_:
  - All keys in the left subtree are smaller than _z_'s key.
  - All keys in the right subtree are greater than _z_'s key.

2. Heap Property:

- Nodes are ordered by their priorities such that for any node _z_:
  - _z_'s priority is less than or equal to the priorities of its children.

## 1.c

```c
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
```

## 1.d

```c
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
```

## 2.a

```c
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
```

## 2.b

O(log(n))

## 3.c

```c
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
```

## 4.a

### Steps for Deleting a Node

When you delete a node _z_, the Cartesian tree must preserve the two properties above. Directly removing _z_ might violate the heap property or disconnect parts of the tree. Instead, the following approach is used:

1. Rotations with the Child of Lowest Priority:

- At each step, compare the priorities of _z_'s left and right children.
- Rotate _z_ with its child that has the lowest priority.
- This rotation maintains the BST property because it does not reorder keys.

2. Effect of the Rotation:

- After the rotation:
  - _z_ moves one level deeper in the tree.
  - Its child moves one level higher, reducing the child’s depth by 1.
- This adjustment ensures the Cartesian tree retains the heap property.

3. Repeat Until _z_ Becomes a Leaf:

- Continue the process until _z_ has no children (i.e., it becomes a leaf).
- Once _z_ is a leaf, it can be safely removed without violating any properties.

### Why This Works

- Heap Property Maintenance:
  - By always rotating with the child of the lowest priority, we guarantee that the tree remains a valid heap after each rotation.
- BST Property Maintenance:
  - Rotations do not disrupt the relative order of keys. _z_’s descendants remain in valid positions relative to one another and _z_.
- Efficiency:
  - Each rotation increases _z_’s depth by 1. At worst, _z_ will need `O(h)` rotations to reach the bottom of the tree, where `h` is the height of the tree.

### Conclusion

This method ensures that _z_ is deleted in a way that preserves the Cartesian tree's structure. By always choosing the child with the lowest priority for rotation, we minimize disruptions to the heap property while respecting the BST ordering. The node _z_ gradually sinks to a leaf position, making its removal straightforward.

## 4.b

O(log(n))

## 4.c

```c
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
```

## 5.a

### Relevant Metrics for Evaluating Cartesian Trees

When analyzing the efficiency and balance of a Cartesian tree, the following metrics are significant:

1. Height of the Tree (h):

- Why important: The height of the tree directly affects the time complexity of operations (insertion, deletion, search). Lower height means better performance.
- Cartesian Trees: Random priorities usually keep the height close to O(log(n)), making them efficient for large datasets.
- Comparison to Binary Search Trees (BSTs): For BSTs, height can degenerate to O(n) for specific sequences of insertions.

2. Balance Factor:

- Why important: The balance factor measures the difference in height between left and right subtrees. A balanced tree ensures logarithmic operation costs.
- Cartesian Trees: Priorities enforce randomization, providing better balance compared to a classical BST.

3. Time Complexity of Operations:

- Insertion: Average case O(log(n)), worst case O(h).
- Search and Deletion: Average case O(log(n)), worst case O(h).
- These metrics are compared with classical BSTs and other self-balancing trees (e.g., AVL, Red-Black).

4. Impact of Priority Collisions:

- Priority collisions can affect the Cartesian tree's balance, leading to localized imbalances. This is rare if priorities are chosen uniformly from a large range.
