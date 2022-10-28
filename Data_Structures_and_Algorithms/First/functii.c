#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functii.h"


double square(double x){
    return x * x;
}

NODE *init_node(int timestamp, double value){
    NODE *new_node = malloc(sizeof(NODE));
    new_node->timestamp = timestamp;
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

LIST *init_list(){
    LIST *new_list = malloc(sizeof(LIST));
    new_list->head = new_list->tail = NULL;
    new_list->len = 0;

    return new_list;
}

void free_node(NODE *node){
    free(node);
}

void destroy_list(LIST *list){
    NODE *aux;
    
    while(list->len > 0){
        aux =list->tail;
        list->tail = list->tail->prev;
        free_node(aux);
        --list->len;
    }

    free(list);
}

void print_list(LIST *list){
    NODE *aux = list->head;

    printf("%d\n", list->len);

    if(aux == NULL){
        printf("NULL\n");
        return;
    }

    while(aux != list->tail){
        printf("%d %0.2lf\n", aux->timestamp, aux->value);
        aux = aux->next;
    }

    printf("%d %0.2lf\n", aux->timestamp, aux->value);
}

int insert_node(LIST *list, int timestamp, double value, int position){
    if(position < 0 || position > list->len)
        return -1;

    if(list->head == NULL){
        NODE *node = init_node(timestamp, value);
        list->head = list->tail = node;
        list->len++;
        return 0;
    }

    if(position == 0){
        NODE *node = init_node(timestamp, value);
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
        list->len++;
        return 0;
    }

    if(position == list->len){
        NODE *node = init_node(timestamp, value);
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        list->len++;
        return 0;
    }

    NODE *aux = list->head;
    for(int i = 0; i < position -1; i++)
        aux = aux->next;

    NODE *node = init_node(timestamp, value);
    node->next = aux->next;
    node->prev = aux;
    aux->next->prev = node;
    aux->next = node;
    list->len++;
    return 0;
}

int insert_sorted(LIST *list, int timestamp, double value){
    if(list->head == NULL){
        NODE *node = init_node(timestamp, value);
        list->head = list->tail = node;
        list->len++;
        return 0;
    }

    if(value <= list->head->value){
        NODE *node = init_node(timestamp, value);
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
        list->len++;
        return 0;
    }

    if(value >= list->tail->value){
        NODE *node = init_node(timestamp, value);
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
        list->len++;
        return 0;
    }

    NODE *aux = list->head;
    while(aux->value < value)
        aux = aux->next;
    
    NODE *node = init_node(timestamp, value);
    node->next = aux;
    node->prev = aux->prev;
    aux->prev->next = node;
    aux->prev = node;
    list->len++;
    return 0;
}

int remove_node(LIST *list, int position){
    if(position < 0 || position > list->len - 1)    
        return -1;
    
    if(position == 0){
        NODE *aux = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free_node(aux);
        list->len--;
        return 0;
    }

    if(position == list->len - 1){
        NODE *aux = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free_node(aux);
        list->len--;
        return 0;
    }

    NODE *aux = list->head;
    for(int i = 0; i < position; i++)  
        aux = aux->next;

    aux->next->prev = aux->prev;
    aux->prev->next = aux->next;
    free_node(aux);
    list->len--;
    return 0;
}

double average(NODE *node){
    NODE *primu = node->prev->prev;
    NODE *doilea = node->prev;
    NODE *patrulea = node->next;
    NODE *cincilea = node->next->next;
    return (primu->value + doilea->value + node->value + patrulea->value + cincilea->value) / 5;
}

double deviation(NODE *node){
    double medie = average(node);
    double suma = 0;
    NODE *primu = node->prev->prev;
    NODE *doilea = node->prev;
    NODE *patrulea = node->next;
    NODE *cincilea = node->next->next;
    suma = square(primu->value - medie) + square(doilea->value - medie) + square(node->value - medie) + square(patrulea->value - medie) + square(cincilea->value - medie);    
    return sqrt(suma / 5);
}

LIST *elimination(LIST *list){
    LIST *new_list = init_list();
    NODE *nod = list->head->next->next;
    insert_node(new_list, list->head->timestamp, list->head->value, new_list->len);
    insert_node(new_list, list->head->next->timestamp, list->head->next->value, new_list->len);
    while(nod != list->tail->prev){
        double medie = average(nod);
        double deviatie = deviation(nod);
        if((medie - deviatie) <= nod->value && nod->value <= (medie + deviatie))
            insert_node(new_list, nod->timestamp, nod->value, new_list->len);
        nod = nod->next;
    }
    insert_node(new_list, list->tail->prev->timestamp, list->tail->prev->value, new_list->len);
    insert_node(new_list, list->tail->timestamp, list->tail->value, new_list->len);
    destroy_list(list);
    return new_list;
}

LIST *mediana(LIST *list){
    LIST *new_list = init_list();
    NODE *nod = list->head->next->next;
    while(nod != list->tail->prev){
        int aux = nod->timestamp;
        LIST *ordered = init_list();
        insert_sorted(ordered, nod->timestamp, nod->value);
        insert_sorted(ordered, nod->prev->timestamp, nod->prev->value);
        insert_sorted(ordered, nod->prev->prev->timestamp, nod->prev->prev->value);
        insert_sorted(ordered, nod->next->timestamp, nod->next->value);
        insert_sorted(ordered, nod->next->next->timestamp, nod->next->next->value);
        insert_node(new_list, aux, ordered->head->next->next->value, new_list->len);
        destroy_list(ordered);
        nod = nod->next;
    }
    destroy_list(list);
    return new_list;
}

LIST *medie_aritmetica(LIST *list){
    LIST *new_list = init_list();
    NODE *nod = list->head->next->next;
    while(nod != list->tail->prev){
        int aux = nod->timestamp;
        insert_node(new_list, aux, average(nod), new_list->len);
        nod = nod->next;
    }
    destroy_list(list);
    return new_list;
}

LIST *uniformizare(LIST *list){
    NODE *nod = list->head->next;
    while(nod != NULL){
        if(nod->timestamp - nod->prev->timestamp >= 100 && nod->timestamp - nod->prev->timestamp <= 1000){
            nod->timestamp = (nod->timestamp + nod->prev->timestamp) / 2;
            nod->value = (nod->value + nod->prev->value) / 2;
        }
        nod = nod->next;
    }
    return list;
}

void statistics(LIST *list, int frequency){
    LIST *ordered = init_list();
    NODE *nod = list->head;
    while(nod != NULL){
        insert_sorted(ordered, nod->timestamp, nod->value);
        nod = nod->next;
    }
    double left = floor(ordered->head->value);
    double right = left + frequency;
    nod = ordered->head;
    int k = 0;
    while(nod != NULL){
        if(nod->value >= left && nod->value <= right)
            k++;
        else{
            if(k != 0)
                printf("[%0.0lf, %0.0lf] %d\n", left, right, k);
            while(nod->value < left || nod->value > right){
                left = right;
                right = left + frequency;
            }
            k = 1;
        }
        nod = nod->next;
    }
    if(k != 0)
        printf("[%0.0lf, %0.0lf] %d\n", left, right, k);

    destroy_list(ordered);
    
}

int extragere_nr(char *numar){
    int rezultat = 0;
    for(int i = 0; i < strlen(numar); i++)
        rezultat = rezultat * 10 + (numar[i] - '0');
    return rezultat;
}

LIST *data_completion(LIST *list){
    NODE *nod = list->head->next->next;
    NODE *right;
    NODE *left;
    int index = 3;
    while(nod != list->tail->prev->prev){
        NODE *aux = nod->next;
        if(nod->next->timestamp - nod->timestamp > 1000){
            right = nod->next;
            left = nod;
            int time = nod->timestamp + 200;
            while(time < aux->timestamp){
                double C = (double)(time - left->timestamp) / (right->timestamp - left->timestamp);
                insert_node(list, time, f(left, right, C), index);
                index++;
                time += 200;
            }
        }
        index++;
        nod = aux;
    }
    return list;
}

double w(int i, int k){
    double numarator = square((double)i / 2) * 0.9 + 0.1;
    double numitor = 0;
    for(int j = 0 ; j < 3; j++)
        numitor += square((double)j / 2) * 0.9 + 0.1;
    return numarator / numitor;
}

double f(NODE *left, NODE *right, double C){
    double suma1 = 0;
    double suma2 = 0;
    NODE *node_l, *node_r;
    node_l = left->prev->prev;
    node_r = right->next->next;
    for(int i = 0; i < 3; i++){
        suma1 += node_l->value * w(i, 3);
        suma2 += node_r->value * w(i, 3);
        node_l = node_l->next;
        node_r = node_r->prev;
    }
    return (1 - C) * suma1 + C * suma2;
}




