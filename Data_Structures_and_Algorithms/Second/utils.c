#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define INF 99999;

// TASK 1

void floydWarshall(int n, double **graph, double **min_costs, double **next){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(graph[i][j] != 0){
                min_costs[i][j] = graph[i][j];
                next[i][j] = j;
            }
    for(int i = 0; i < n; i++){
        min_costs[i][i] = 0;
        next[i][i] = i;
    }
    for(int t = 0; t < n; t++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(min_costs[i][t] + min_costs[t][j] < min_costs[i][j]){
                    min_costs[i][j] = min_costs[i][t] + min_costs[t][j];
                    next[i][j] = next[i][t];
                }
}

// TASK 2

void dfs_graph_1(int n, int x, int **s, double **graph){
    if(x != 0)
        (*s)[x] = 1;
    for(int i = 0; i < n; i++){
        if((*s)[i] == 0 && graph[x][i] != 0)
            dfs_graph_1(n, i, &(*s), graph);
    }
}

void dfs_graph_transpus_1(int n, int x, int **p, double **graph_transpus){
    if(x != 0)
        (*p)[x] = 1;
    for(int i = 0; i < n; i++){
        if((*p)[i] == 0 && graph_transpus[x][i] != 0)
            dfs_graph_transpus_1(n, i, &(*p), graph_transpus);
    }
}

