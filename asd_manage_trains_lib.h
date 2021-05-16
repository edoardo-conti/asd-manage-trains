/**
 * Edoardo Conti
 * ALGORITHMS AND DATA STRUCTURES
 * summer session Project 2016/2017
 */

#ifndef TRAINS_LIB
#define TRAINS_LIB

typedef struct vertex_graph
{
    char *city;
    struct vertex_graph *vertex_dad_p;
    struct arch_graph *list_arch_p;
    double dist;
} vertex_graph_t;

typedef struct arch_graph
{
    int TK; /* Travel Km */
    int TT; /* Travel Time */
    struct vertex_graph *vertex_adj_p;
    struct arch_graph *arch_next_p;
} arch_graph_t;

typedef struct list
{
    struct vertex_graph *vertex_p;
    struct list *next;
} list_t;

void initGraph(size_t cols, vertex_graph_t *vertex[], int);
void printGraph(size_t cols, vertex_graph_t *vertex[], char j[][50], int);
void printJoinTable(size_t cols, char j[][50]);
void printMatrix(size_t cols, char* m[][cols]);
void populateMatrix(size_t cols, char* m[cols][cols], char j[][50], char *, char *, int, int);
void matrix2graph(size_t cols, char* m[][cols], char j[][50], int ns[], vertex_graph_t *vertex[]);
void userJoin(size_t cols, vertex_graph_t *vertex[], char j[][50]);
float dijkstra(size_t cols, vertex_graph_t *vertex[], int, int, int);
void getStats(size_t cols, vertex_graph_t *vertex[]);

void scanPath(list_t *);
int push(list_t **, vertex_graph_t *);
list_t* pop(list_t **);

void sieveHeap(float a[], int sx, int dx);
void Heapsort(float a[], int n);


#endif
