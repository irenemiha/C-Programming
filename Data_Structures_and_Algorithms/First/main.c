#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int main(int argc, char **argv){
    LIST *list = init_list();
    int n, timestamp;
    double value;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %lf", &timestamp, &value);
        insert_node(list, timestamp, value, list->len);
    }
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--e1") == 0)
            list = elimination(list);
        if(strcmp(argv[i], "--e2") == 0)
            list = mediana(list);
        if(strcmp(argv[i], "--e3") == 0)
            list = medie_aritmetica(list);
        if(strcmp(argv[i], "--u") == 0)
            list = uniformizare(list);
        if(strcmp(argv[i], "--c") == 0)
            list = data_completion(list);   
        if(strstr(argv[i], "st") != NULL){
            int frecventa = extragere_nr(argv[i] + 4);
            statistics(list, frecventa);
            destroy_list(list);
            return 0;
        }
    }

    print_list(list);
    destroy_list(list);
    return 0;
}
