import binarytree
import random
import time
import numpy as np
import matplotlib.pyplot as plt

# --------------------------------------------------------------------------- #
# CODE FOR EXERCISE 1      (STRUCTURE AND PROPERTIES)                         #
# Class and visualisation functions, for the Cartesian Tree data structure    #
# --------------------------------------------------------------------------- #

class Node:
    def __init__(self, key, priority, left=None, right=None):
        self.key = key
        self.priority = priority
        self.left = left
        self.right = right
    
    def __str__(self):
        return f'Node({self.key}, {self.priority})'
    
    def copy(self):
        return Node(self.key, self.priority, self.left, self.right)

def nodes_from_string(nodes_str):
    nodes = []
    for node_str in nodes_str.split(','):
        key, priority = node_str.strip('()').split(' : ')
        nodes.append(Node(key, int(priority)))
    return nodes

def print_nodes(nodes):
    for node in nodes:
        print(node)
        
def copy_nodeslist(nodes):
    return [node.copy() for node in nodes]

def convert_to_printable(root, highlighted_node=None):
    if root is None:
        return None
    if highlighted_node is not None and root.key == highlighted_node.key:
        return binarytree.Node('**(' + root.key + ', ' + str(root.priority) + ')**', convert_to_printable(root.left, highlighted_node), convert_to_printable(root.right, highlighted_node))
    return binarytree.Node('(' + root.key + ', ' + str(root.priority) + ')', convert_to_printable(root.left, highlighted_node), convert_to_printable(root.right, highlighted_node))

def print_tree(root, highlighted_node=None):
    print(convert_to_printable(root, highlighted_node=highlighted_node))
    
def get_depth(root):
    if root is None:
        return 0
    return 1 + max(get_depth(root.left), get_depth(root.right))

def get_depth_of_node(root, node):
    if root == node:
        return get_depth(root)
    if root is None:
        return 0
    if root.key == node.key:
        return 1
    if node.key < root.key:
        return 1 + get_depth_of_node(root.left, node)
    return 1 + get_depth_of_node(root.right, node)


# ------------------------------------------------- #
# CODE FOR EXERCISE 2      (FIND NODE)              #
# ------------------------------------------------- #

def find_node(root, key):
    if root is None:
        return None
    if root.key == key:
        return root
    if key < root.key:
        return find_node(root.left, key)
    return find_node(root.right, key)



# ------------------------------------------------- #
# CODE FOR EXERCISE 3      (INSERT NODE)            #
# ------------------------------------------------- #

def BST_insert(root, node, verbose=False):
    if node.key < root.key:
        if root.left is None:
            root.left = node
            if verbose:
                print(f"Added node to left of root ({root.key}.left = {node.key})")
            return root
        if verbose:
            print(f"\tGoing one layer down on the left from {root.key} for {node.key}")
        root.left = BST_insert(root.left, node, verbose=verbose)
        return root
    if root.right is None:
        root.right = node
        if verbose:
            print(f"Added node to right of root ({root.key}.right = {node.key})")
        return root
    if verbose:
        print(f"\tGoing one layer down on the right from {root.key} for {node.key}")
    root.right = BST_insert(root.right, node, verbose=verbose)
    return root

def create_tree_BST(nodes, verbose=False):
    root = nodes[0]
    for node in nodes[1:]:
        root = BST_insert(root, node, verbose=verbose)
    return root


def rotate_tree_right(root):
    new_root = root.left
    root.left = new_root.right
    new_root.right = root
    return new_root

def rotate_tree_left(root):
    new_root = root.right
    root.right = new_root.left
    new_root.left = root
    return new_root


def insert_node(root, node, verbose=False):
    if root is None:
        if verbose:
            print(f"Inserting {node.key}")
        return node
    
    # Continue the tree until we find a leaf
    if node.key < root.key:
        if verbose:
            if root.left is not None:
                print(f"Going one layer down on the left from {root.key} to {root.left.key} for {node.key}")
            else:
                print(f"Going one layer down to add {node.key} to the left of {root.key}")
        root.left = insert_node(root.left, node, verbose=verbose)
    elif node.key > root.key:
        if verbose:
            if root.right is not None:
                print(f"Going one layer down on the right from {root.key} to {root.right.key} for {node.key}")
            else:
                print(f"Going one layer down to add {node.key} to the right of {root.key}")
        root.right = insert_node(root.right, node, verbose=verbose)
    else:
        if verbose:
            print(f"Node {node.key} already exists in the tree")
        return root
    
    
    # Rotate the tree if the priority of the node is lower than the priority of the root
    if node.priority < root.priority:
        if node.key < root.key:
            if verbose:
                print(f"Rotating right at {root.key} for {node.key}")
            return rotate_tree_right(root)
        if verbose:
            print(f"Rotating left at {root.key} for {node.key}")
        return rotate_tree_left(root)
    
    # If a rotation is not needed, return the root for the recursive calls
    return root
        
    
def create_tree(nodes, verbose=False):
    root = nodes[0]
    for node in nodes[1:]:
        root = insert_node(root, node, verbose=verbose)
    return root


# ------------------------------------------------- #
# CODE FOR EXERCISE 4      (REMOVE NODE)            #
# ------------------------------------------------- #


def remove_node(root, node, verbose=False):
    if root is None:
        if verbose:
            print(f"Node {node.key} not found in the tree")
        return None
    
    # Search for the node to remove
    if node.key < root.key:
        if verbose:
            print(f"-SEARCHING {node.key}- Going one layer down on the left from {root.key} for {node.key}")
        root.left = remove_node(root.left, node, verbose=verbose)
        return root
    if node.key > root.key:
        if verbose:
            print(f"-SEARCHING {node.key}- Going one layer down on the right from {root.key} for {node.key}")
        root.right = remove_node(root.right, node, verbose=verbose)
        return root
    
    # Case 1: Node is a leaf
    if root.left is None and root.right is None:
        if verbose:
            print(f"{node.key} is a leaf node, removing it")
        return None
    
    # Case 2: Node has one child
    elif root.left is None:
        # Case 2.1: Node has a right child
        if verbose:
            print(f"{node.key} has only a right child, removing it and replacing it with the right child")
        return root.right
    
    elif root.right is None:
        # Case 2.2: Node has a left child
        if verbose:
            print(f"{node.key} has only a left child, removing it and replacing it with the left child")
        return root.left
    
    # Case 3: Node has two children
    # Rotate with the child that has the lower priority
    if root.left.priority < root.right.priority:
        if verbose:
            print(f"{node.key} has two children, left child has lower priority, rotating right")
        root = rotate_tree_right(root)
        if verbose:
            print(f"Rotated tree, new root is {root.key}, continuing with remove_node({root.right.key}, {node.key})")
            print_tree(root)
        root.right = remove_node(root.right, node, verbose=verbose)
    else:
        if verbose:
            print(f"{node.key} has two children, right child has lower priority, rotating left")
        root = rotate_tree_left(root)
        if verbose:
            print(f"Rotated tree, new root is {root.key}, continuing with remove_node({root.left.key}, {node.key})")
            print_tree(root)
        root.left = remove_node(root.left, node, verbose=verbose)
    
    return root

def remove_key(root, key, verbose=False):
    return remove_node(root, find_node(root, key), verbose=verbose)



# ------------------------------------------------- #
# CODE FOR EXERCISE 5      (RANDOM TREES)           #
# ------------------------------------------------- #


ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

def create_random_tree(n):
    key_size = len(str(n)) + 1
    priority_range = (1, n*10)
    nodes = []
    for i in range(n):
        key = ''.join(random.choices(ALPHABET, k=key_size))
        priority = random.randint(*priority_range)
        nodes.append(Node(key, priority))
    return create_tree(nodes)

def create_random_node(n):
    key_size = len(str(n)) + 1
    priority_range = (1, n*10)
    key = ''.join(random.choices(ALPHABET, k=key_size))
    priority = random.randint(*priority_range)
    return Node(key, priority)

def create_random_nodes_linspace(n, max_priority=-1):
    if max_priority == -1:
        max_priority = n * 10
    key_size = len(str(n)) + 1
    priorities = np.linspace(1, max_priority, n, dtype=int)
    nodes = []
    for i in range(n):
        key = ''.join(random.choices(ALPHABET, k=key_size))
        priority = priorities[i]
        nodes.append(Node(key, priority))
    return nodes




# ------------------------------------------------- #
# CODE FOR EXERCISE 6      (THEORETICAL ASPECT)     #
# ------------------------------------------------- #

def root_to_nodelist(root):
    if root is None:
        return []
    return [root] + root_to_nodelist(root.left) + root_to_nodelist(root.right)

def get_keylist(nodelist):
    return [node.key for node in nodelist]

def get_prioritylist(nodelist):
    return [node.priority for node in nodelist]

def get_kth_node(root, k):
    nodelist = root_to_nodelist(root)
    keylist = get_keylist(nodelist)
    sorted_keys = sorted(keylist)
    kth_key = sorted_keys[k-1]
    return find_node(root, kth_key)

def get_kth_node_depth(root, k):
    return get_depth_of_node(root, get_kth_node(root, k))