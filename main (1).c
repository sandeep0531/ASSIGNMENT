#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int height;
    struct node* left;
    struct node* right;
};

int max(int a, int b) {
    return a > b ? a : b;
}

int height(struct node* N) {
    return (N == NULL) ? 0 : N->height;
}

struct node* newNode(int key) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct node* rightRotate(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    struct node* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return y;
}

int getBalance(struct node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

struct node* search(struct node* root, int key, int* path, int* pathIndex) {
    if (root == NULL)
        return NULL;

    path[(*pathIndex)++] = root->key;

    if (key == root->key)
        return root;
    else if (key < root->key)
        return search(root->left, key, path, pathIndex);
    else
        return search(root->right, key, path, pathIndex);
}

void printPath(int* path, int pathIndex) {
    for (int i = 0; i < pathIndex; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int calculateRotations(struct node* root, int key) {
    if (root == NULL)
        return 0;

    int rotations = 0;

    while (root != NULL) {
        if (key < root->key) {
            root = root->left;
            rotations++;
        } else if (key > root->key) {
            root = root->right;
            rotations++;
        } else {
            break;
        }
    }

    return rotations;
}

void rotations(struct node* root, int key) {
    int path[100]; // Assuming a reasonable limit for the path length
    int pathIndex = 0;

    struct node* result = search(root, key, path, &pathIndex);

    if (result == NULL) {
        printf("-1\n");
    } else {
        int leftRotations = calculateRotations(root->left, key);
        int rightRotations = calculateRotations(root->right, key);

        printf("%d %d\n", leftRotations, rightRotations);
    }
}

int main() {
    struct node* root = NULL;
    char operation;
    int key;

    while (1) {
        scanf(" %c", &operation);

        if (operation == 'e') {
            break;
        }

        switch (operation) {
            case 'i':
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 'x':
                scanf("%d", &key);
                rotations(root, key);
                break;
            case 'p':
                preOrder(root);
                printf("\n");
                break;
            case 's':
                scanf("%d", &key);
                rotations(root, key);
                break;
            default:
                break;
        }
    }

    return 0;
}
