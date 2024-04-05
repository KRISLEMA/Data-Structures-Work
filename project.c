#include <stdio.h>
#include <stdlib.h>

// Node structure for Binary Search Tree
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new Node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new Node into BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// Function to delete a node with given key from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find the height of BST
int height(struct Node* root) {
    if (root == NULL) return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to find the level of a node in BST
int level(struct Node* root, int data, int lvl) {
    if (root == NULL) return 0;
    if (root->data == data) return lvl;

    int downlevel = level(root->left, data, lvl + 1);
    if (downlevel != 0) return downlevel;

    downlevel = level(root->right, data, lvl + 1);
    return downlevel;
}

// Function to print the level and height of a node in BST
void printLevelAndHeight(struct Node* root, int data) {
    int lvl = level(root, data, 1);
    int h = height(root);
    if (lvl != 0) {
        printf("Level of node %d: %d\n", data, lvl);
        printf("Height of BST: %d\n", h);
    } else {
        printf("Node not found in BST\n");
    }
}

// Function to print the inorder traversal of BST
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Creating BST
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertNode(root, arr[i]);
    }

    printf("Inorder traversal of BST: ");
    inorder(root);
    printf("\n");

    // Deleting a node
    int keyToDelete = 25;
    root = deleteNode(root, keyToDelete);
    printf("Inorder traversal after deleting %d: ", keyToDelete);
    inorder(root);
    printf("\n");

    // Printing height of BST
    printf("Height of BST: %d\n", height(root));

    // Printing level and height of any node
    int nodeToFind = 40;
    printLevelAndHeight(root, nodeToFind);

    return 0;
}
