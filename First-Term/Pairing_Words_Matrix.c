#include <stdio.h>
#include <string.h>

int is_anagram (char *s1, char *s2){ 

    /* 
    - funcția verifică dacă cele două cuvinte, reprezentate prin șirurile de caractere s1 și s2, sunt anagrame;

    - vectorii de frecvență a și b numără aparițiile fiecărui caracter din cele două cuvinte;

    - dacă numărul de apariții ale unui caracter din vectorul a coincide cu numărul de apariții 
        ale aceluiași caracter în vectorul b, arunci funcția returează valoarea 1;
        
    - în caz contrar, funcția returnează valoarea 0;
    */

    int a[26] = {0}, b[26] = {0}, i, x;

    for (i = 0; i < strlen(s1); i++)
        a[(int)s1[i] - (int)('a')]++;

    for (i = 0; i < strlen(s2); i++)
        b[(int)s2[i] - (int)('a')]++;

    int ok = 1;

    for (x = 0; x < 26; x++)
        if (a[x] != b[x])
            ok = 0;

    return ok;
}

double compute_grade (char *s1, char *s2){

    /*
    - funcția calculează gradul anagramei formate din cuvintele reprezentate de șirurile de caractere s1 și s2;

    - dacă cele două cuvinte nu formează o anagramă, funcția returnează valoarea -1;

    - în caz contrar, este evident că cele două cuvinte au număr identic de caractere;

    - în continuare, funcția verifică dacă caracterele aflate pe aceleași poziții în cele două cuvinte sunt identice,
        contorizând în variabila k cazurile contrare;

    - variabila gr returnează raportul dintre variabila k și lungimea șirurilor (care este identică), 
        reprezentând, de fapt, gradul anagramei;
    */

    int i, k = 0;
    double gr;

    if (is_anagram (s1, s2) == 0)
        return -1;

    for (i = 0; i < strlen(s1); i++)
        if (s1[i] != s2[i])
            k++;     

    gr = (double)k/strlen(s1);

    return gr;   
}

void sortare (double grad[], char cuv1[][52], char cuv2[][52], int n){

    /*
    - funcția sortează atât vectorul de grade în ordine descrescătoare, cât și anagramele corespunzătoare gradelor, 
        tot în ordine descrescătoare;

    - cuv1 și cuv2 sunt două matrici cu n linii 52 de coloane, reprezentând cele două liste de cuvinte;

    - cuv1 conține pe fiecare linie primele cuvinte din fiecare pereche, iar cuv2 conține pe 
        fiecare linie celelalte cuvinte;

    - dacă gradele a mai multe anagrame sunt identice, acestea vor fi ordonate în ordine 
        lexicografică descrescătoare;
    */

    int i, j;
    double aux;
    char aux_cuv[52];

    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++){
            if (grad[i] < grad [j]){
                aux = grad[i];
                grad[i] = grad[j];
                grad[j] = aux;
                strcpy(aux_cuv, cuv1[i]);
                strcpy(cuv1[i], cuv1[j]);
                strcpy(cuv1[j], aux_cuv);
                strcpy(aux_cuv, cuv2[i]);
                strcpy(cuv2[i], cuv2[j]);
                strcpy(cuv2[j], aux_cuv);
            }
            if (grad[i] == grad[j])
                if (strcmp(cuv1[i], cuv1[j]) < 0){
                    aux = grad[i];
                    grad[i] = grad[j];
                    grad[j] = aux;
                    strcpy(aux_cuv, cuv1[i]);
                    strcpy(cuv1[i], cuv1[j]);
                    strcpy(cuv1[j], aux_cuv);
                    strcpy(aux_cuv, cuv2[i]);
                    strcpy(cuv2[i], cuv2[j]);
                    strcpy(cuv2[j], aux_cuv);
                }
        }              
}

//funcția main
int main (){
    int n, i;
    scanf ("%d", &n);
    char cuv1[n][52], cuv2[n][52];
    double grad[n];

    //citim cele două matrici de cuvinte
    for (i = 0; i < n; i++)
        scanf ("%s%s", cuv1[i], cuv2[i]); 

    //calculăm gradele fiecărei perechi de cuvinte de pe fiecare linie a matricelor
    for (i = 0; i < n; i++)
        grad[i] = compute_grade(cuv1[i], cuv2[i]);

    //sortăm atât vectorul de grade, cât și anagramele corespunzătoare acestora, in ordine descrescătoare
    sortare (grad, cuv1, cuv2, n);

    //afișăm noile matrici de cuvinte, respectiv anagramele ordonate corespunzător
    for (i = 0; i < n; i++)
        printf("%s %s\n", cuv1[i], cuv2[i]);
}