#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX];
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void DFS(Graph* graph, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v); 

    Node* temp = graph->adjLists[v];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void BFS(Graph* graph, int start, int visited[]) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices, edges;
    printf("Nhap so luong dinh: ");
    scanf("%d", &vertices);
    printf("Nhap so luong canh: ");
    scanf("%d", &edges);

   	 Graph* graph = createGraph(vertices);

    printf("Nhap cac cap dinh (src dest):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int visited[MAX] = {0};
    printf("Duyet DFS bat dau tu dinh 0:\n");
    DFS(graph, 0, visited);
    printf("\n");

    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }

    printf("Duyet BFS bat dau tu dinh 0:\n");
    BFS(graph, 0, visited);
    printf("\n");

    return 0;
}
