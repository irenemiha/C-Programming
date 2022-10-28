#ifndef _graph
#define _graph

void floydWarshall(int n, double **graph, double **min_costs, double **next);

void dfs_graph_1(int n, int x, int **s, double **graph);

void dfs_graph_transpus_1(int n, int x, int **p, double **graph_transpus);

#endif