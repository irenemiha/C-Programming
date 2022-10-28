#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void task1(int n, int s, int k, double **graph, int *magazine_aprovizionate){
    int depozit, magazin;
    
    double **min_costs, **next, cost_total = 0, drum_dus, drum_intors;
    
    min_costs = malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++)
        min_costs[i] = malloc(n * sizeof(double));

    next = malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++)
        next[i] = malloc(n * sizeof(double));
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            if(graph[i][j] != 0)
                min_costs[i][j] = graph[i][j];
            else
                min_costs[i][j] = 100000;
        }

    floydWarshall(n, graph, min_costs, next);

    for(int i = 0; i < k; i++){
        printf("%d\n", magazine_aprovizionate[i]);
        drum_dus = min_costs[s][magazine_aprovizionate[i]];
        drum_intors = min_costs[magazine_aprovizionate[i]][s];
        printf("%0.1lf %0.1lf\n", drum_dus, drum_intors);
        cost_total += drum_dus + drum_intors;
        printf("%d", s);
        depozit = s;
        while(depozit != magazine_aprovizionate[i]){
            printf(" ");
            depozit = next[depozit][magazine_aprovizionate[i]];
            printf("%d", depozit);
        }
        magazin = magazine_aprovizionate[i];
        while(magazin != s){
            printf(" ");
            magazin = next[magazin][s];
            printf("%d", magazin);
        }
        printf("\n");
    }
    printf("%0.1lf", cost_total);

    for(int i = 0; i < n; i++)
        free(min_costs[i]);
    free(min_costs);

    for(int i = 0; i < n; i++)
        free(next[i]);
    free(next);
}

void task2(int n, double **graph, double **graph_transpus, int d, int *depozite){
    int *s, *p, *componente_conexe, nrc = 0;
    s = malloc(n * sizeof(int));
    p = malloc(n * sizeof(int));
    componente_conexe = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
        componente_conexe[i] = 0;

    for(int i = 0; i < n; i++){
        if(componente_conexe[i] == 0){
            int ok = 1;
            for(int j = 0; j < d; j++)
                if(i == depozite[j])
                    ok = 0;
            if(ok == 1){
                for(int j = 0; j < n; j++)
                    s[j] = p[j] = 0;
                nrc++;
                dfs_graph_1(n, i, &s, graph);
                dfs_graph_transpus_1(n, i, &p, graph_transpus);
                for(int j = 0; j < n; j++) 
                    if(s[j] == 1 && p[j] == 1)
                        componente_conexe[j] = nrc; 
            }    
        }
    }
    printf("%d\n", nrc);

    for(int j = 1; j <= nrc; j++){
        int ok = 0;
        for(int i = 0; i < n; i++){
            if(componente_conexe[i] == j)
                if(ok == 0){
                    printf("%d", i);
                    ok = 1;
                }
                else if(ok == 1)
                    printf(" %d", i);
        }
        if(j < nrc)
            printf("\n");
    }

    free(s);
    free(p);
    free(componente_conexe);
}
