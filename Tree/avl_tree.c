#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

static int height(AVLNode* n) { return n ? n->height : 0; }
static int max(int a, int b) { return a > b ? a : b; }

static AVLNode* avl_create_node(int key) {
    AVLNode* node = malloc(sizeof(AVLNode));
    if (!node) return NULL;
    node->key = key;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

static AVLNode* rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

static AVLNode* rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

static int get_balance(AVLNode* n) { return n ? height(n->left) - height(n->right) : 0; }

AVLNode* avl_insert(AVLNode* node, int key) {
    if (!node) return avl_create_node(key);
    if (key < node->key) node->left = avl_insert(node->left, key);
    else if (key > node->key) node->right = avl_insert(node->right, key);
    else return node; /* duplicates ignored */

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = get_balance(node);

    if (balance > 1 && key < node->left->key) return rotate_right(node);            /* LL */
    if (balance < -1 && key > node->right->key) return rotate_left(node);           /* RR */
    if (balance > 1 && key > node->left->key) {                                     /* LR */
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (balance < -1 && key < node->right->key) {                                   /* RL */
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

static AVLNode* min_node(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left) current = current->left;
    return current;
}

AVLNode* avl_delete(AVLNode* root, int key) {
    if (!root) return NULL;
    if (key < root->key) root->left = avl_delete(root->left, key);
    else if (key > root->key) root->right = avl_delete(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            AVLNode* succ = min_node(root->right);
            root->key = succ->key;
            root->right = avl_delete(root->right, succ->key);
        }
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0) return rotate_right(root);     /* LL */
    if (balance > 1 && get_balance(root->left) < 0) {                               /* LR */
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0) return rotate_left(root);    /* RR */
    if (balance < -1 && get_balance(root->right) > 0) {                             /* RL */
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

void avl_inorder(AVLNode* root) {
    if (!root) return;
    avl_inorder(root->left);
    printf("%d ", root->key);
    avl_inorder(root->right);
}

void avl_print(AVLNode* root, const char* label) {
    if (label) printf("%s: ", label);
    avl_inorder(root);
    printf("\n");
}

void avl_destroy(AVLNode* root) {
    if (!root) return;
    avl_destroy(root->left);
    avl_destroy(root->right);
    free(root);
}
