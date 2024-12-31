#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(Node** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
    } else if (value < (*root)->data) {
        insert(&((*root)->left), value);
    } else {
        insert(&((*root)->right), value);
    }
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

void convertTreeToGraph(Node* root, int adjacencyList[MAX][MAX], int* size) {
    if (root == NULL) return;

    int index = root->data;
    if (root->left != NULL) {
        adjacencyList[index][root->left->data] = 1;
        adjacencyList[root->left->data][index] = 1; 
        convertTreeToGraph(root->left, adjacencyList, size);
    }
    if (root->right != NULL) {
        adjacencyList[index][root->right->data] = 1; 
        adjacencyList[root->right->data][index] = 1; 
        convertTreeToGraph(root->right, adjacencyList, size);
    }
}

void DFS(int start, int visited[], int adjacencyList[MAX][MAX], int size) {
    visited[start] = 1;
    printf("%d ", start);
    for (int i = 0; i < size; i++) {
        if (adjacencyList[start][i] && !visited[i]) {
            DFS(i, visited, adjacencyList, size);
        }
    }
}

void BFS(int start, int visited[], int adjacencyList[MAX][MAX], int size) {
    int queue[MAX], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);
        for (int i = 0; i < size; i++) {
            if (adjacencyList[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    Node* root = NULL;
    int n, value;
    int adjacencyList[MAX][MAX] = {0};
    int visited[MAX] = {0};
    int size = MAX;

    printf("Nhap so luong nut trong cay: ");
    scanf("%d", &n);

    printf("Nhap cac gia tri can chen vao cay:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        insert(&root, value);
    }

    printf("Duyet cay theo thu tu pre-order:\n");
    preOrder(root);
    printf("\n");

    printf("Duyet cay theo thu tu in-order:\n");
    inOrder(root);
    printf("\n");

    printf("Duyet cay theo thu tu post-order:\n");
    postOrder(root);
    printf("\n");

    convertTreeToGraph(root, adjacencyList, &size);

    printf("Duyet do thi theo DFS:\n");
    for (int i = 0; i < MAX; i++) visited[i] = 0; 
    DFS(root->data, visited, adjacencyList, size);
    printf("\n");
    for (int i = 0; i < MAX; i++) visited[i] = 0;
    printf("Duyet do thi theo BFS:\n");
    BFS(root->data, visited, adjacencyList, size);
    printf("\n");

    return 0;
}
