# Complex Project

### Key Properties of Cartesian Trees

1. Binary Search Tree Property (BST):

- Nodes are ordered by their keys such that for any node _z_:
  - All keys in the left subtree are smaller than _z_'s key.
  - All keys in the right subtree are greater than _z_'s key.

2. Heap Property:

- Nodes are ordered by their priorities such that for any node _z_:
  - _z_'s priority is less than or equal to the priorities of its children.

## 1.a

<img width="439" alt="image" src="https://github.com/user-attachments/assets/4036bd4e-afc3-4ec5-95c2-4bce683444fb">

## 1.b

Changing the order of the nodes won't change the tree because they will be inserted in their correct place regardless

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

Complexity of the search algorithm as a function of the depth of the searched node:

**O(log(n))**

## 3.a

If we try to insert a node to the 1.a tree without doing for the rotation that might be required, the resulting tree might not verify the properties anymore. For example:

### Original 1.a Tree

<img width="439" alt="image" src="https://github.com/user-attachments/assets/4036bd4e-afc3-4ec5-95c2-4bce683444fb">

### Step 1: Insert (M, 20), no problem so far

<img width="479" alt="image" src="https://github.com/user-attachments/assets/6e680549-5747-49f2-877a-e3e44ad29021">

### Step 2: Insert (K, 15), also no problem

<img width="529" alt="image" src="https://github.com/user-attachments/assets/53e5acfe-2dc6-4f09-a5e1-87192172b028">

### Step 3: Insert (L, 14), here we see a problem, the (M, 20) node ends up being on the left branch of the new (L, 14) when M is later in the alphabet so it is supposed to be on the right

<img width="611" alt="image" src="https://github.com/user-attachments/assets/6baf82cd-1721-4020-a448-f54bac55fb78">

This problem occurs because the algorithm tries to add (L, 14) on top of the (K, 15) node due to the priorities, but since it doesn't check the child nodes of K, it doesn't know the M node underneath is also supposed to be moved.

### == FIXED ALGORITHM == 
### Same 3 nodes added using the fixed algorithm that does a rotation if needed while inserting new nodes

<img width="581" alt="image" src="https://github.com/user-attachments/assets/c843da33-6014-4570-9104-0c79c896e794">


## 3.b

Complexity of the insert algorithm as a function of the depth of its predecessor:

**O(log(n))**??

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

Complexity of the remove algorithm:

**O(log(n))**

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

## 4.d

### Removing the nodes (A : 5), (J : 12) and (H : 1) in order from the example tree from question 1.a

Visualizing the trees using python

### Initial Tree (From 1.a)

<img width="457" alt="image" src="https://github.com/user-attachments/assets/cc6f0415-b798-423b-ac48-d8286b8fdb74">

### Step 1: Remove Node (A : 5)

<img width="399" alt="image" src="https://github.com/user-attachments/assets/f0803382-375f-46f0-8888-778a52fdb639">

### Step 2: Remove Node (J : 12)

<img width="347" alt="image" src="https://github.com/user-attachments/assets/15a14bd2-6590-4361-a798-d96e06c184d7">

### Step 3: Remove Node (H : 1)

<img width="299" alt="image" src="https://github.com/user-attachments/assets/23ba6e14-2bc2-461f-96a5-14d4e43153b7">

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
