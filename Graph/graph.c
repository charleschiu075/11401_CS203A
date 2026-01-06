#include <stdio.h>
#include <stdlib.h>

typedef struct EdgeNode {
    int to;
    struct EdgeNode* next;
} EdgeNode;

typedef struct {
    EdgeNode** adj;
    size_t vertex_count;
} Graph;

Graph* graph_create(size_t vertices) {
    Graph* g = malloc(sizeof(Graph));
    if (!g) return NULL;
    g->vertex_count = vertices;
    g->adj = calloc(vertices, sizeof(EdgeNode*));
    if (!g->adj) {
        free(g);
        return NULL;
    }
    return g;
}

void graph_destroy(Graph* g) {
    if (!g) return;
    for (size_t i = 0; i < g->vertex_count; ++i) {
        EdgeNode* cur = g->adj[i];
        while (cur) {
            EdgeNode* next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(g->adj);
    free(g);
}

int graph_add_edge(Graph* g, int u, int v, int bidirectional) {
    if (u >= (int)g->vertex_count || v >= (int)g->vertex_count) return 0;
    EdgeNode* edge = malloc(sizeof(EdgeNode));
    if (!edge) return 0;
    edge->to = v;
    edge->next = g->adj[u];
    g->adj[u] = edge;
    if (bidirectional) {
        EdgeNode* back = malloc(sizeof(EdgeNode));
        if (!back) return 0;
        back->to = u;
        back->next = g->adj[v];
        g->adj[v] = back;
    }
    return 1;
}

void graph_bfs(Graph* g, int start) {
    int* visited = calloc(g->vertex_count, sizeof(int));
    int* queue = malloc(g->vertex_count * sizeof(int));
    size_t head = 0, tail = 0;
    visited[start] = 1;
    queue[tail++] = start;
    while (head < tail) {
        int node = queue[head++];
        printf("%d ", node);
        for (EdgeNode* e = g->adj[node]; e; e = e->next) {
            if (!visited[e->to]) {
                visited[e->to] = 1;
                queue[tail++] = e->to;
            }
        }
    }
    printf("\\n");
    free(queue);
    free(visited);
}

static void graph_dfs_util(Graph* g, int node, int* visited) {
    visited[node] = 1;
    printf("%d ", node);
    for (EdgeNode* e = g->adj[node]; e; e = e->next) {
        if (!visited[e->to]) graph_dfs_util(g, e->to, visited);
    }
}

void graph_dfs(Graph* g, int start) {
    int* visited = calloc(g->vertex_count, sizeof(int));
    graph_dfs_util(g, start, visited);
    printf("\\n");
    free(visited);
}

void graph_print(Graph* g) {
    printf("Adjacency list:\\n");
    for (size_t i = 0; i < g->vertex_count; ++i) {
        printf("%zu: ", i);
        for (EdgeNode* e = g->adj[i]; e; e = e->next) {
            printf("%d ", e->to);
        }
        printf("\\n");
    }
}
