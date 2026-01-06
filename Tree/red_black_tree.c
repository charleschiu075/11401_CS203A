#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

static RBNode* rb_create_node(int key) {
    RBNode* node = malloc(sizeof(RBNode));
    if (!node) return NULL;
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

static RBNode* grandparent(RBNode* n) { return n && n->parent ? n->parent->parent : NULL; }
static RBNode* uncle(RBNode* n) {
    RBNode* g = grandparent(n);
    if (!g) return NULL;
    return n->parent == g->left ? g->right : g->left;
}

static void rotate_left(RBNode** root, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

static void rotate_right(RBNode** root, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) *root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

static void insert_fixup(RBNode** root, RBNode* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == grandparent(z)->left) {
            RBNode* y = uncle(z);
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                grandparent(z)->color = RED;
                z = grandparent(z);
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(root, z);
                }
                z->parent->color = BLACK;
                grandparent(z)->color = RED;
                rotate_right(root, grandparent(z));
            }
        } else {
            RBNode* y = uncle(z);
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                grandparent(z)->color = RED;
                z = grandparent(z);
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(root, z);
                }
                z->parent->color = BLACK;
                grandparent(z)->color = RED;
                rotate_left(root, grandparent(z));
            }
        }
    }
    (*root)->color = BLACK;
}

RBNode* rbt_insert(RBNode* root, int key) {
    RBNode* z = rb_create_node(key);
    if (!z) return root;
    RBNode* y = NULL;
    RBNode* x = root;
    while (x) {
        y = x;
        if (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else { free(z); return root; } /* ignore duplicates */
    }
    z->parent = y;
    if (!y) root = z;
    else if (key < y->key) y->left = z;
    else y->right = z;
    insert_fixup(&root, z);
    return root;
}

RBNode* rbt_search(RBNode* root, int key) {
    RBNode* cur = root;
    while (cur) {
        if (key == cur->key) return cur;
        cur = key < cur->key ? cur->left : cur->right;
    }
    return NULL;
}

void rbt_inorder(RBNode* root) {
    if (!root) return;
    rbt_inorder(root->left);
    printf("%d(%c) ", root->key, root->color == RED ? 'R' : 'B');
    rbt_inorder(root->right);
}

void rbt_print(RBNode* root, const char* label) {
    if (label) printf("%s: ", label);
    rbt_inorder(root);
    printf("\n");
}

void rbt_destroy(RBNode* root) {
    if (!root) return;
    rbt_destroy(root->left);
    rbt_destroy(root->right);
    free(root);
}
