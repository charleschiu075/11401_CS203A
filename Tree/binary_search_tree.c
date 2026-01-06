#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* bst_create_node(int key) {
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

Node* bst_insert(Node* root, int key) {
    if (!root) return bst_create_node(key);
    if (key < root->key) root->left = bst_insert(root->left, key);
    else if (key > root->key) root->right = bst_insert(root->right, key);
    return root;
}

Node* bst_search(Node* root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return bst_search(root->left, key);
    return bst_search(root->right, key);
}

static Node* bst_min_node(Node* node) {
    Node* current = node;
    while (current && current->left) current = current->left;
    return current;
}

Node* bst_delete(Node* root, int key) {
    if (!root) return NULL;
    if (key < root->key) {
        root->left = bst_delete(root->left, key);
    } else if (key > root->key) {
        root->right = bst_delete(root->right, key);
    } else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            Node* successor = bst_min_node(root->right);
            root->key = successor->key;
            root->right = bst_delete(root->right, successor->key);
        }
    }
    return root;
}

void bst_inorder(Node* root) {
    if (!root) return;
    bst_inorder(root->left);
    printf("%d ", root->key);
    bst_inorder(root->right);
}

void bst_print(Node* root, const char* label) {
    if (label) printf("%s: ", label);
    bst_inorder(root);
    printf("\n");
}

void bst_destroy(Node* root) {
    if (!root) return;
    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root);
}
