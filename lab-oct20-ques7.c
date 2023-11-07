#include <stdio.h>
#include <stdlib.h>

// A BTree node
struct BTreeNode {
    int *keys;      // An array of keys
    int t;          // Minimum degree (defines the range for the number of keys)
    struct BTreeNode **C; // An array of child pointers
    int n;          // Current number of keys
    int leaf;       // Is true when the node is a leaf; otherwise, false
};

// A BTree
struct BTree {
    struct BTreeNode *root; // Pointer to the root node
    int t; // Minimum degree
};

// Function prototypes
struct BTreeNode* createBTreeNode(int t, int leaf);
struct BTree* createBTree(int t);
void traverse(struct BTreeNode* root);
struct BTreeNode* search(struct BTreeNode* root, int k);
void insert(struct BTree* tree, int k);
void insertNonFull(struct BTreeNode* x, int k);
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y);

// Constructor for BTreeNode structure
struct BTreeNode* createBTreeNode(int t, int leaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->t = t;
    newNode->leaf = leaf;
    newNode->keys = (int*)malloc(sizeof(int) * (2 * t - 1));
    newNode->C = (struct BTreeNode**)malloc(sizeof(struct BTreeNode*) * (2 * t));
    newNode->n = 0;
    return newNode;
}

// Constructor for BTree structure
struct BTree* createBTree(int t) {
    struct BTree* newBTree = (struct BTree*)malloc(sizeof(struct BTree));
    newBTree->root = NULL;
    newBTree->t = t;
    return newBTree;
}

// Function to traverse all nodes in a subtree rooted with the given node
void traverse(struct BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (root->leaf == 0)
            traverse(root->C[i]);
        printf(" %d", root->keys[i]);
    }
    if (root->leaf == 0)
        traverse(root->C[i]);
}

// Function to search for a key in the subtree rooted with the given node
struct BTreeNode* search(struct BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (root->keys[i] == k)
        return root;
    if (root->leaf == 1)
        return NULL;
    return search(root->C[i], k);
}

// Function to insert a new key into the B-Tree
void insert(struct BTree* tree, int k) {
    struct BTreeNode* root = tree->root;
    if (root == NULL) {
        root = createBTreeNode(tree->t, 1);
        root->keys[0] = k;
        root->n = 1;
        tree->root = root;
    } else {
        if (root->n == (2 * tree->t - 1)) {
            struct BTreeNode* s = createBTreeNode(tree->t, 0);
            s->C[0] = root;
            splitChild(s, 0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            insertNonFull(s->C[i], k);
            tree->root = s;
        } else {
            insertNonFull(root, k);
        }
    }
}

// Function to insert a new key into a non-full node
void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf == 1) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;
        i++;
        if (x->C[i]->n == (2 * x->t - 1)) {
            splitChild(x, i, x->C[i]);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->C[i], k);
    }
}

// Function to split the child y of this node
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y) {
    struct BTreeNode* z = createBTreeNode(y->t, y->leaf);
    z->n = x->t - 1;
    for (int j = 0; j < x->t - 1; j++)
        z->keys[j] = y->keys[j + x->t];
    if (y->leaf == 0) {
        for (int j = 0; j < x->t; j++)
            z->C[j] = y->C[j + x->t];
    }
    y->n = x->t - 1;
    for (int j = x->n; j >= i + 1; j--)
        x->C[j + 1] = x->C[j];
    x->C[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[x->t - 1];
    x->n = x->n + 1;
}

int main()
{
    struct BTree* tree = createBTree(4); // Create a B-Tree with minimum degree 3

    char keys[] = {'F', 'S', 'Q', 'K', 'C', 'L', 'H', 'T', 'V', 'W', 'M', 'R', 'N', 'P', 'A', 'B', 'X', 'Y', 'D', 'Z', 'E'};
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < numKeys; i++) {
        insert(tree, keys[i]);
    }

    printf("Traversal of the constructed tree is:");
    traverse(tree->root);
    return 0;
}
