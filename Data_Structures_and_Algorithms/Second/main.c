#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"


int main(){
    int n, m, d, u, v, depozit, nr_cerinte, s, k;
    double w, **graph, **graph_transpus;
    int *depozite, *magazine_aprovizionate, *zona;
    char task[3];

    // Citesc numărul de noduri, muchii, depozite
    scanf("%d%d%d", &n, &m, &d);

    graph = malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++)
        graph[i] = malloc(n * sizeof(double));
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            graph[i][j] = 0;

    graph_transpus = malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++)
        graph_transpus[i] = malloc(n * sizeof(double));
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            graph_transpus[i][j] = 0;

    // Citesc muchiile și creez cele două matrici de adiacență
    for(int i = 0; i < m; i++){
        scanf("%d%d%lf", &u, &v, &w);
        graph[u][v] = w;
        graph_transpus[v][u] = w;
    }

    depozite = malloc(d * sizeof(int));
    
    // Citesc depozitele
    for(int i = 0; i < d; i++)
        scanf("%d", &depozite[i]);
    
    // Citesc numărul de cerințe
    scanf("%d", &nr_cerinte);
    for(int i = 0; i < nr_cerinte; i++){
        // Citesc codul task-ului
        scanf("%s", task);
        if(strcmp(task, "e1") == 0){
            // Citesc depozitul din care plec
            scanf("%d", &s);
            // Citesc numărul de magazine aprovizoinate
            scanf("%d", &k);
            magazine_aprovizionate = malloc(k * sizeof(int));
            for(int i = 0; i < k; i++)
                // Citesc magazinele aprovizionate
                scanf("%d", &magazine_aprovizionate[i]);
            task1(n, s, k, graph, magazine_aprovizionate);
            if(i < nr_cerinte - 1)
            printf("\n");
            free(magazine_aprovizionate);
        }
        
        if(strcmp(task, "e2") == 0){
            for(int i = 0; i < d; i++)
                for(int j = 0; j < n; j++){
                    // Transform în 0 existența muchiilor dintre depozute și restul nodurilor
                    graph[depozite[i]][j] = graph[j][depozite[i]] = 0;
                    graph_transpus[depozite[i]][j] = graph_transpus[j][depozite[i]] = 0;
                }
            task2(n, graph, graph_transpus, d, depozite); 
        }  
    }

    for(int i = 0; i < n; i++)
        free(graph[i]);
    free(graph);

    for(int i = 0; i < n; i++)
        free(graph_transpus[i]);
    free(graph_transpus);

    free(depozite);
    

}