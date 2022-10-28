#ifndef _list
#define _list

typedef struct node{
    double value;
    int timestamp;
    struct node *prev;
    struct node *next;
}NODE;

typedef struct list{
    NODE *head;
    NODE *tail;
    int len;
}LIST;

//Inițializare nod nou în listă
NODE *init_node(int timestamp, double value);

//Inițializare listă vidă
LIST *init_list();

//Eliberarea memoriei ocupată de un nod
void free_node(NODE *node);

//Eliberarea memoriei ocupată de o listă
void destroy_list(LIST *list);

//Afișarea listei
void print_list(LIST *list);

//Inserarea unui nou nod în listă
int insert_node(LIST *list, int timestamp, double value, int position);

//Inserarea în ordine crescătoare a nodurilor în listă
int insert_sorted(LIST *list, int timestamp, double value);

//Ștergerea unui nod din listă
int remove_node(LIST *list, int position);

//Calculează media valorilor numerice din fereastră
double average(NODE *node);

//Calculează deviatia standard a valorilor din fereastră
double deviation(NODE *node);

//Eliminarea excepțiilor
LIST *elimination(LIST *list);

//Returnează noua listă în funcție de filtrarea mediană
LIST *mediana(LIST *list);

//Returnează noua listă în funcție de media aritmetică
LIST *medie_aritmetica(LIST *list);

//Uniformizează lista actualizând timestamp-ul și valoarea nodului curent 
//în cazul in care nodul următor depășește timestamp-ul primului cu o valoare intre 100 și 1000
LIST *uniformizare(LIST *list);

//Numără de câte ori apare un punct într-un anumit interval
void statistics(LIST *list, int frequency);

//Extrage un număr dintr-un șir de caractere dat
int extragere_nr(char *numar);

//Adaugă în listă noduri cu diferența de timestamp-uri 200
//atunci când diferența timestamp-urilor a două noduri consecutive depășește 1000
LIST *data_completion(LIST *list);

//Calculează coeficientul care scade influența valorilor, pe măsură ce ne îndepărtăm de interval
double w(int i, int k);

//Calculează valoarea atribuită nodului cu timestamp-ul căutat
double f(NODE *left, NODE *right, double C);

#endif