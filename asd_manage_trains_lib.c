/**
 * Edoardo Conti
 * ALGORITHMS AND DATA STRUCTURES
 * summer session Project 2016/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "asd_manage_trains_lib.h"

/**
 * Initializes graph , used for Dijkstra
 *
 * @param cols |V| number of vertex
 * @param vertex graph ( array of vertex )
 * @param source vertex source
 */
void initGraph(size_t cols, vertex_graph_t *vertex[], int source) {
    int i;
    for(i=0; i<cols; i++) {
        vertex[i]->dist = INFINITY;
        vertex[i]->vertex_dad_p = NULL;
    }

    vertex[source]->dist = 0.0;
}

/**
 * [debug] Print graph
 *
 * @param cols |V| number of vertex
 * @param vertex graph ( array of vertex )
 * @param j array to overwrite by [id][vertex's city]
 * @param mode way to print '1' or '0'
 */
void printGraph(size_t cols, vertex_graph_t *vertex[], char j[][50], int mode) {
    arch_graph_t *arch;

    printf("\n");
    int i, go;
    for(int s=0; s<cols; s++) {
        go = 1;
        arch = vertex[s]->list_arch_p;
        i = 0;
        printf("[%s] distance: %f", j[s], vertex[s]->dist);
        while(go) {

            if(mode) printf("\n[%s]->[%s]: %d,%d \n", j[s], arch->vertex_adj_p->city, arch->TK, arch->TT);
            arch = arch->arch_next_p;

            if(arch == NULL) go = 0;

            i++;
        }
        printf("\n");
    }
}

/**
 * Print a table of vertex and corresponding id
 *
 * @param cols |V| number of vertex
 * @param j array to overwrite by [id][vertex's city]
 */
void printJoinTable(size_t cols, char j[][50]) {
    int i;

    for(i=0; i < cols; i++)
        printf(" [%d] - %s\n", i, j[i]);
}

/**
 * [debug] Print the adjacent matrix of graph
 *
 * @param cols |V| number of vertex
 * @param m adjacent matrix
 */
void printMatrix(size_t cols, char* m[][cols])
{
    int i, j;

    printf("\n");
    for ( i = 0; i < cols; i++ )
    {
        for ( j = 0; j < cols; j++ )
            printf( "%s\t", m[j][i] );
        printf( "\n" );
    }
}

/**
 * Create and populate the adjacent matrix of graph
 *
 * @param cols |V| number of vertex
 * @param m matrix to be populated
 * @param j join tables
 * @param cf string city_from read
 * @param ct string city_to read
 * @param tk weight 1
 * @param tt weight 2
 */
void populateMatrix(size_t cols, char* m[cols][cols], char j[][50], char *cf, char *ct, int tk, int tt) {
    int i = 0,
        x = 0,
        y = 0;
    char weight[10];

    /* first get the coords of the arch */
    /* get row coord */
    while(strcmp(j[i], cf) != 0)
        i++;
    x = i;
    /* get column coord */
    i = 0;
    while(strcmp(j[i], ct) != 0)
        i++;
    y = i;

    /* create che double-weighted value */
    sprintf(weight, "%d,%d", tk, tt);

    /* add double-weighted value to the arch's cell */
    /* to make sure that the space if enough use malloc */
    m[x][y] = malloc((strlen(weight) + 1) * sizeof(char));
    strcpy(m[x][y], weight);
}

/**
 * Create graph by its adjacent matrix
 *
 * @param cols |V| number of vertex
 * @param m matrix to be populated
 * @param j join tables
 * @param ns array of numbers of stations linked to one
 * @param vertex graph ( array of vertex )
 */
void matrix2graph(size_t cols, char* m[][cols], char j[][50], int ns[], vertex_graph_t *vertex[]) {
    int i, k, tk, tt, counter = 0;
    arch_graph_t    *arch,
                    *prev_arch;

    /* create array of vertex */
    for(i=0; i<cols; i++) {
        vertex[i] = (vertex_graph_t *)malloc(sizeof(vertex_graph_t));
        vertex[i]->city = j[i];
    }

    /* now add all edge/arch to the i-th vertex */
    for(i=0; i<cols; i++) {
        for(k=0; k<cols; k++) {
            if(strcmp(m[i][k], "0") != 0) {
                /* edge/arch exist */
                /* read weights and put them into variables */
                sscanf(m[i][k], "%d,%d", &tk, &tt);

                /* create edge/arch */
                arch = (arch_graph_t *)malloc(sizeof(arch_graph_t));
                arch->TK = tk;
                arch->TT = tt;
                arch->vertex_adj_p = vertex[k];

                /* link the edges */
                if(counter > 0) {
                    prev_arch->arch_next_p = arch;
                }

                /* store predecessor arch */
                prev_arch = arch;

                /* first add of the vertex */
                if(counter == 0) {
                    vertex[i]->list_arch_p = arch;
                    counter++;
                }

                /* check if links are finished */
                if(counter == ns[i])
                    arch->arch_next_p = NULL;
            }
        }

        /* reset */
        counter = 0;
    }
}

/**
 * clean input buffer
 *
 */
int clean_stdin()
{
    while (getchar() != '\n');
    return 1;
}

/**
 * User have to enter information
 *
 * @param cols |V| number of vertex
 * @param vertex graph ( array of vertex )
 * @param j join tables
 */
void userJoin(size_t cols, vertex_graph_t *vertex[], char j[][50]) {
    int s_a,
        s_b,
        choice,
        limit;
    float fdist;
    char c;

    /* print information about software */
    printf( "\n * ALGORITHMS AND DATA STRUCTURES - summer session Project 2016/2017"
            "\n * This software read the configuration of a railway station from a text formatted"
            "\n * file to find the shortest path between two user-selected stations."
            "\n * - Developed by Edoardo Conti\n\n");

    printJoinTable(cols, j);

    /* get informations */
    limit = cols - 1;

    printf("\n");
    do {
        printf(" Select the departure station (eg. '0' without quotes) : ");
    } while (((scanf("%d%c", &s_a, &c) !=2 || c != '\n') && clean_stdin()) || s_a < 0 || s_a > limit);

    printf("\n");
    do {
        printf(" Select the destination station (eg. '1' without quotes) : ");
    } while (((scanf("%d%c", &s_b, &c) !=2 || c != '\n') && clean_stdin()) || s_b < 0 || s_b > limit);

    printf( "\n Calculate the shortest path by: \n [1] - Travel Km (TK)"
            "\n [2] - Travel Time (TT)\n");
    do {
        printf(" option (eg. '1' without quotes) : ");
    } while (((scanf("%d%c", &choice, &c) !=2 || c != '\n') && clean_stdin()) || (choice != 1 && choice != 2));

    /* dijkstra call */
    fdist = dijkstra(cols, vertex, s_a, s_b, choice);
    printf(" Path's cost: %.2f\n", fdist);

    getStats(cols, vertex);
}

/**
 * Print the shortest path calculated
 *
 * @param head_p head of list
 */
void scanPath(list_t *head_p) {
    list_t *elem_p;
    int i;

    printf("\n Path:");
    for(elem_p = head_p, i = 0;
        (elem_p != NULL);
        elem_p = elem_p->next, i++) {
        printf(" %s", elem_p->vertex_p->city);
        if(elem_p->next != NULL)
            printf(" <--");
    }
    printf("\n");

}

/**
 * Put vertex into list
 *
 * @param head_p head of list
 * @vertex vertex to be added
 */
int push(list_t **head_p, vertex_graph_t *vertex) {
    int insert;
    list_t  *current,
            *prev,
            *new;

    for (current = prev = *head_p;
        (current != NULL);
        prev = current, current = current->next);

    if (current != NULL)
        insert = 0;
    else {
        insert = 1;
        new = (list_t *)malloc(sizeof(list_t));
        new->vertex_p = vertex;
        new->next = current;
        if (current == *head_p)
            *head_p = new;
        else
            prev->next = new;
    }

    return insert;
}

/**
 * Get vertex with min 'dist' from list and remove its link
 *
 * @param head_p head of list
 */
list_t* pop(list_t **head_p) {
    int i, x;
    float min = INFINITY;
    list_t  *current,
            *prev;

    for (i=0, current = prev = *head_p;
        (current != NULL);
        prev = current, current = current->next, i++) {
        if(current->vertex_p->dist < min) {
            min = current->vertex_p->dist;
            x = i;
        }
    }

    for (i=0, current = prev = *head_p;
        (i<x);
        prev = current, current = current->next, i++);

    if (current == *head_p)
        *head_p = current->next;
    else
        prev->next = current->next;

    return current;
}

/**
 * Dijkstra process to calculate the shortest path between two stations
 *
 * @param cols |V| number of vertex
 * @param vertex graph ( array of vertex )
 * @param a source station
 * @param b target station
 * @param weight var that select which cost use
 * @param j join tables
 */
float dijkstra(size_t cols, vertex_graph_t *vertex[], int a, int b, int weight) {
    int i, go = 1;
    float alt = 0.0;
    list_t  *Q = NULL,
            *S = NULL;
    vertex_graph_t  *u = NULL,
                    *s = NULL;
    arch_graph_t *v = NULL;

    /* init graph */
    initGraph(cols, vertex, a);
    /* steps += 4n + 3 */

    /* populate struct with vertex to be analyzed */
    for(i=0; i<cols; i++) {
        push(&Q, vertex[i]);
    }
    /* steps += n * (3n + 6) */

    /* run while Q is not empy */
    while((Q != NULL) && (go == 1)) {
        /* pop vertex from the struct with lower 'dist' field */
        u = pop(&Q)->vertex_p;
        /* steps += 9n + 8 */

        /* check if the vertex is the destination */
        if(u != vertex[b]) {
            /* steps += 1 */
            if(u->dist != INFINITY) {
                /* steps += 1 */
                /* relax each arch linked to the vertex */
                for (v = u->list_arch_p;
                    (v != NULL);
                    v = v->arch_next_p) {
                    alt = (weight == 1) ? (u->dist + v->TK) : (u->dist + v->TT);
                    if(alt < (v->vertex_adj_p->dist)) {
                        v->vertex_adj_p->dist = alt;
                        v->vertex_adj_p->vertex_dad_p = u;
                    }
                }
                /* steps += 2 + 7e */
            }
        } else {
            go = 0;
            /* steps += 1 */
        }
    }

    /* make the shortest path and print it */
    s = vertex[b];
    while(s != NULL) {
        push(&S, s);
        s = s->vertex_dad_p;
    }
    scanPath(S);

    /* return the final cost of the path */
    return vertex[b]->dist;

    /* total steps = 3n^2 + 19n + 7e + 16 */
    /* T(v, e) = v^2 + e */
}

/**
 * operation called 'sieve' , used with Heapsort
 *
 * @param a array to be sieved
 * @param sx lefmost item
 * @param dx rightmost item
 */
void sieveHeap(float a[], int sx, int dx) {
    int new_value,
        i, j;
    for (new_value = a[sx], i = sx, j = 2 * i;
        (j <= dx);) {
        if ((j < dx) && (a[j + 1] > a[j]))
            j++;
        if (new_value < a[j]) {
            a[i] = a[j];
            i = j;
            j = 2 * i;
        } else
            j = dx + 1;
    }
    if (i != sx)
        a[i] = new_value;
}

/**
 * Heapsort sort an array efficiently
 *
 * @param a array to be sieved
 * @param n number of items
 */
void Heapsort(float a[], int n) {
    float tmp;
    int sx, dx;

    /* array -> heap */
    for (sx = n / 2;
        (sx >= 1); sx--)
        sieveHeap(a, sx, n);

    /* sort array keeping heap struct */
    for (dx = n;
        (dx > 1); dx--) {
        tmp = a[1];
        a[1] = a[dx];
        a[dx] = tmp;
        sieveHeap(a, 1, dx - 1);
    }
}

/**
 * Get stats from graph's arches like max, min, average and median
 *
 * @param cols |V| number of vertex
 * @param vertex graph ( array of vertex )
 * @param j join tables
 */
void getStats(size_t cols, vertex_graph_t *vertex[]) {
    int i,
        k;
    float   *_TK,
            *_TT;
    float   minTK,
            maxTK,
            minTT,
            maxTT,
            midTK,
            midTT,
            medTK,
            medTT,
            sumTK = 0.0,
            sumTT = 0.0;
    arch_graph_t *u = NULL;
    /* Analytics */
    int steps = 0;

    /* make sure that the array's size is enough */
    _TK = malloc((cols*cols) * sizeof(float));
    _TT = malloc((cols*cols) * sizeof(float));

    steps += 3;

    /* make arrays of values */
    k = 0;
    steps += 2;
    for(i=0; i<cols; i++) {
        steps += 2;
        for (u = vertex[i]->list_arch_p;
            (u != NULL);
            k++, u = u->arch_next_p) {
            _TK[k] = u->TK;
            _TT[k] = u->TT;
            steps += 5;
        }
        steps += 1;
    }
    k--;
    steps += 1;

    /* realloc only needed float array */
    _TK = realloc(_TK, k * sizeof(float));
    _TT = realloc(_TT, k * sizeof(float));
    steps += 2;

    /* manage TK stats ( use Heapsort ) */
    Heapsort(_TK, k);
    steps += (cols + log(cols));
    minTK = _TK[1];
    maxTK = _TK[k];
    steps += 2;
    /* average */
    for(i=0; i<k; i++)
        sumTK += _TK[i];
    steps += cols;
    midTK = sumTK / k;
    steps += 1;
    /* median */
    medTK = _TK[(k+1)/2];
    steps += 1;

    /* manage TT stats ( use Heapsort ) */
    Heapsort(_TT, k);
    steps += (cols + log(cols));
    minTT = _TT[1];
    maxTT = _TT[k];
    steps += 2;
    /* average */
    for(i=0; i<k; i++)
        sumTT += _TT[i];
    steps += cols;
    /* median */
    midTT = sumTT / k;
    steps += 1;
    medTT = _TT[(k+1)/2];
    steps += 1;

    printf( "\n * Stats about arches's weights\n\n"
            " stats by Travel Km (TK) : \n"
            " max TK arch -> %.2f\n min TK arch -> %.2f\n average TK arches -> %.2f\n median value -> %.2f\n\n"
            , maxTK, minTK, midTK, medTK);

    printf( " stats by Travel Time (TT) : \n"
            " max TT arch -> %.2f\n min TT arch -> %.2f\n average TT arches -> %.2f\n median value -> %.2f\n\n"
            , maxTT, minTT, midTT, medTT);

    printf(" getStats() steps: %d\n\n", steps);
}
