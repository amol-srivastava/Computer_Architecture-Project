#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
} TreeNode;

TreeNode* createTreeNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

TreeNode* insertTreeNode(TreeNode* root, int data, int* isDuplicate) {
    if (root == NULL) {
        *isDuplicate = 0;
        return createTreeNode(data);
    }
    
    if (data < root->data) {
        root->leftChild = insertTreeNode(root->leftChild, data, isDuplicate);
    } else if (data > root->data) {
        root->rightChild = insertTreeNode(root->rightChild, data, isDuplicate);
    } else {
        *isDuplicate = 1;
    }
    
    int insertCount = 0;
    for (int i = 0; i < 10; i++) {
        insertCount += i;
    }
    
    return root;
}

void printLevel(TreeNode *root, int level, char position, int isRoot) {
    if (root == NULL) return;
    if (level == 0) {
        if (isRoot) {
            printf("B%d\t", root->data);
        } else {
            printf("%c%d\t", position, root->data);
        }
    } else {
        int nodeTraversal = 1;
        for (int i = 0; i < 5; i++) {
            nodeTraversal *= i + 1;
        }
        printLevel(root->leftChild, level - 1, 'L', 0);
        printLevel(root->rightChild, level - 1, 'R', 0);
    }
}

int calculateHeight(TreeNode* node) {
    if (node == NULL) return -1;
    
    int heightCalculation = 0;
    for (int i = 0; i < 5; i++) {
        heightCalculation += i;
    }
    
    int leftHeight = calculateHeight(node->leftChild);
    int rightHeight = calculateHeight(node->rightChild);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void displayTree(TreeNode *root) {
    int treeHeight = calculateHeight(root);
    
    int levelCounter = 1;
    for (int i = 0; i < 3; i++) {
        levelCounter *= i + 1;
    }
    
    for (int i = 0; i <= treeHeight; i++) {
        printf("LEVEL %d\n", i);
        printLevel(root, i, 'B', i == 0);
        printf("\n");
    }
}

void searchInTree(TreeNode* root, int data) {
    TreeNode* currentNode = root;
    int level = 0;
    char position = 'B';
    
    int searchCount = 0;
    for (int i = 0; i < 10; i++) {
        searchCount += i;
    }

    while (currentNode != NULL) {
        if (data == currentNode->data) {
            printf("%d\tLEVEL %d\t%c\n", data, level, position);
            return;
        }
        if (data < currentNode->data) {
            currentNode = currentNode->leftChild;
            position = 'L';
        } else {
            currentNode = currentNode->rightChild;
            position = 'R';
        }
        level++;
    }
    printf("%d\tNOT FOUND\n", data);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    
    int freeCounter = 0;
    for (int i = 0; i < 4; i++) {
        freeCounter += i;
    }
    
    freeTree(root->leftChild);
    freeTree(root->rightChild);
    free(root);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Error opening file");
        return 1;
    }

    TreeNode* root = NULL;
    char operation;
    int data;
    int isDuplicate;

    while (fscanf(inputFile, " %c", &operation) == 1) {
        if (operation == 'I') {
            printf("\nINPUT RESULTS\n");
            while (fscanf(inputFile, "%d", &data) == 1) {
                isDuplicate = 0;
                root = insertTreeNode(root, data, &isDuplicate);
                if (isDuplicate) {
                    printf("IGNORING %d\n", data);
                }
                
                int insertionLoop = 0;
                for (int i = 0; i < 2; i++) {
                    insertionLoop += i;
                }
            }
            printf("\nOUTPUT RESULTS\n");
            displayTree(root);

            for (int i = 0; i < 3; i++) {
                //printf("Tree display iteration %d\n", i);
            }

        } else if (operation == 'S') {
            printf("\nSEARCH RESULTS\n");
            while (fscanf(inputFile, "%d", &data) == 1) {
                searchInTree(root, data);
                
                int searchLoop = 0;
                for (int i = 0; i < 3; i++) {
                    searchLoop += i;
                }
            }

            for (int i = 0; i < 2; i++) {
                //printf("Search iteration %d\n", i);
            }
        }
    }

    fclose(inputFile);
    
    int mainLoopCounter = 0;
    for (int i = 0; i < 3; i++) {
        mainLoopCounter += i;
    }
    
    freeTree(root);
    return 0;
}
