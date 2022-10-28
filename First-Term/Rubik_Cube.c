#include <stdio.h>
#include <string.h>

int cod (char culori[6][10], char culoare[10]){

    /*
    - funcția primește ca parametrii matricea culori și vectorul culoare și 
         are ca scop codificarea culorilor;

    - funcția compară culoarea de pe indicele i cu locul pe care se găsește 
         aceasta în vectorul culoare;

    - funcția returnează indicele culorii respective, reprezentând codul culorii,
         respectiv -1 dacă nu găsește culoarea în lista de culori;
    */

    int i;
    for (i = 0; i < 6; i++)
        if(strcmp (culori[i], culoare) == 0)
            return i;
    return -1;
}

void F (int cub[18][3]){

    /*
    - funcția F priește ca parametru cubul Rubik și realizează mutarea în sensul acelor de ceasornic a feței frontale;

    - aux_up = vector care reține ultima linie de pe fața de sus;
      aux_down =  vector care reține prima linie de pe fața de sus;
      aux_left = vector care reține ultima coloană de pe fața din stânga;
      aux_right = vector care reține prima coloană de pe fața din dreapta;

      aux = vector care reține toate elementele de pe o față;
    
    - primele 4 for-uri atribuie fiecărui vector auxiliar linia sau coloana corespunzătoare;
    - următoarele 4 for-uri realizează mutarea propriu-zisă, mutând coloana sau linia respectivă pe locul potrivit;

    - cele 8 atribuiri ale elementelor din cub realizează mutarea întregii fețe;
    */

    int i, j;
    int aux_up[3], aux_down[3], aux_left[3], aux_right[3], aux[9], k = 0;

    for (i = 0; i <= 2; i++)
        for (j = 0; j < 3; j++)
            aux[k++] = cub[i][j];

    cub[0][0] = aux[6];
    cub[0][1] = aux[3];
    cub[0][2] = aux[0];
    cub[1][0] = aux[7];
    cub[1][2] = aux[1];
    cub[2][0] = aux[8];
    cub[2][1] = aux[5];
    cub[2][2] = aux[2];


    for (i = 0; i <= 2; i++)
        aux_up[i] = cub[8][i];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_down[j] = cub[9][i];

    for (i = 14, j = 0; i >= 12 && j <= 2; i--, j++)
        aux_left[j] = cub[i][2];  

    for (i = 15, j = 0; i <= 17 && j <= 2; i++, j++)
        aux_right[j] = cub[i][0];



    for (i = 15, j = 0; i <= 17 && j < 3; i++, j++)
            cub[i][0] = aux_up[j];

    for (i = 14, j = 0; i >= 12 && j < 3; i--, j++)
            cub[i][2] = aux_down[j];

    for (j = 0, i = 0; j < 3 && i < 3; j++, i++)
            cub[8][j] = aux_left[i];

    for (j = 2, i = 0; j >= 0 && i < 3; j--, i++)
            cub[9][j] = aux_right[i];

}

void B (int cub[18][3]){

    /*
    - funcția B priește ca parametru cubul Rubik și realizează mutarea în sensul acelor de ceasornic a feței din spate;

    - aux_up = vector care reține prima linie de pe fața de sus;
      aux_down =  vector care reține ultima linie de pe fața de sus;
      aux_left = vector care reține ultima coloană de pe fața din dreapta;
      aux_right = vector care reține prima coloană de pe fața din stânga;

      aux = vector care reține toate elementele de pe o față;
    
    - primele 4 for-uri atribuie fiecărui vector auxiliar linia sau coloana corespunzătoare;
    - următoarele 4 for-uri realizează mutarea propriu-zisă, mutând coloana sau linia respectivă pe locul potrivit;

    - cele 8 atribuiri ale elementelor din cub realizează mutarea întregii fețe;
    */

    int i, j;
    int aux_up[3], aux_down[3], aux_left[3], aux_right[3], aux[9], k = 0;

    for (i = 3; i <= 5; i++)
        for (j = 0; j < 3; j++)
            aux[k++] = cub[i][j];

    cub[3][0] = aux[6];
    cub[3][1] = aux[3];
    cub[3][2] = aux[0];
    cub[4][0] = aux[7];
    cub[4][2] = aux[1];
    cub[5][0] = aux[8];
    cub[5][1] = aux[5];
    cub[5][2] = aux[2];

    for (j = 2, i = 0; j >= 0 && i < 3; j--, i++)
        aux_up[j] = cub[6][i];

    for (i = 0, j = 0; i <= 2 && j <= 2; i++, j++)
        aux_down[j] = cub[11][i];

    for (i = 17, j = 0; i >= 15 && j <= 2; i--, j++)
        aux_left[j] = cub[i][2];  

    for (i = 12, j = 0; i <= 14 && j <= 2; i++, j++)
        aux_right[j] = cub[i][0];


    
    for (i = 12, j = 0; i <= 14 && j < 3; i++, j++)
            cub[i][0] = aux_up[j];

    for (i = 17, j = 0; i >= 15 && j < 3; i--, j++)
            cub[i][2] = aux_down[j];

    for (j = 2, i = 0; j >= 0 && i < 3; j--, i++)
            cub[6][j] = aux_left[i];

    for (j = 0, i = 0; j <= 2 && i < 3; j++, i++)
            cub[11][j] = aux_right[i];

}

void U (int cub[18][3]){

    /*
    - funcția U priește ca parametru cubul Rubik și realizează mutarea în sensul acelor de ceasornic a feței de sus;

    - aux_back = vector care reține prima linie de pe fața din spate;
      aux_front =  vector care reține prima linie de pe fața frontală;
      aux_left = vector care reține prima linie de pe fața din stânga;
      aux_right = vector care reține prima linie de pe fața din dreapta;

      aux = vector care reține toate elementele de pe o față;
    
    - primele 4 for-uri atribuie fiecărui vector auxiliar linia sau coloana corespunzătoare;
    - următoarele 4 for-uri realizează mutarea propriu-zisă, mutând coloana sau linia respectivă pe locul potrivit;

    - cele 8 atribuiri ale elementelor din cub realizează mutarea întregii fețe
    */

    int i, j;
    int aux_back[3], aux_front[3], aux_left[3], aux_right[3], aux[9], k = 0;

    for (i = 6; i <= 8; i++)
        for (j = 0; j < 3; j++)
            aux[k++] = cub[i][j];

    cub[6][0] = aux[6];
    cub[6][1] = aux[3];
    cub[6][2] = aux[0];
    cub[7][0] = aux[7];
    cub[7][2] = aux[1];
    cub[8][0] = aux[8];
    cub[8][1] = aux[5];
    cub[8][2] = aux[2];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_back[j] = cub[3][i];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_front[j] = cub[0][i];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_left[j] = cub[12][i];  

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_right[j] = cub[15][i];



    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[15][i] = aux_back[j];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[12][i] = aux_front[j];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[3][i] = aux_left[j];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[0][i] = aux_right[j];

}

void D (int cub[18][3]){

    /*
    - funcția D priește ca parametru cubul Rubik și realizează mutarea în sensul acelor de ceasornic a feței de jos;

    - aux_back = vector care reține ultima linie de pe fața din spate;
      aux_front =  vector care reține ultima linie de pe fața frontală;
      aux_left = vector care reține ultima linie de pe fața din stânga;
      aux_right = vector care reține ultima linie de pe fața din dreapta;

      aux = vector care reține toate elementele de pe o față;
    
    - primele 4 for-uri atribuie fiecărui vector auxiliar linia sau coloana corespunzătoare;
    - următoarele 4 for-uri realizează mutarea propriu-zisă, mutând coloana sau linia respectivă pe locul potrivit;

    - cele 8 atribuiri ale elementelor din cub realizează mutarea întregii fețe
    */

    int i, j;
    int aux_back[3], aux_front[3], aux_left[3], aux_right[3], aux[9], k = 0;

    for (i = 9; i <= 11; i++)
        for (j = 0; j < 3; j++)
            aux[k++] = cub[i][j];

    cub[9][0] = aux[6];
    cub[9][1] = aux[3];
    cub[9][2] = aux[0];
    cub[10][0] = aux[7];
    cub[10][2] = aux[1];
    cub[11][0] = aux[8];
    cub[11][1] = aux[5];
    cub[11][2] = aux[2];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_back[j] = cub[5][i];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_front[j] = cub[2][i];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_left[j] = cub[14][i];  

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_right[j] = cub[17][i];


    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[14][i] = aux_back[j];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[17][i] = aux_front[j];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[2][i] = aux_left[j];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[5][i] = aux_right[j];

}

void R (int cub[18][3]){

    /*
    - funcția R priește ca parametru cubul Rubik și realizează mutarea în sensul acelor de ceasornic a feței din dreapta;

    - aux_up = vector care reține ultima coloană de pe fața de sus;
      aux_down =  vector care reține ultima coloană de pe fața de jos;
      aux_back = vector care reține prima coloană de pe fața din spate;
      aux_front = vector care reține ultima coloană de pe fața frontală;

      aux = vector care reține toate elementele de pe o față;
    
    - primele 4 for-uri atribuie fiecărui vector auxiliar linia sau coloana corespunzătoare;
    - următoarele 4 for-uri realizează mutarea propriu-zisă, mutând coloana sau linia respectivă pe locul potrivit;

    - cele 8 atribuiri ale elementelor din cub realizează mutarea întregii fețe
    */

    int i, j;
    int aux_back[3], aux_front[3], aux_up[3], aux_down[3], aux[9], k = 0;

    for (i = 15; i <= 17; i++)
        for (j = 0; j < 3; j++)
            aux[k++] = cub[i][j];

    cub[15][0] = aux[6];
    cub[15][1] = aux[3];
    cub[15][2] = aux[0];
    cub[16][0] = aux[7];
    cub[16][2] = aux[1];
    cub[17][0] = aux[8];
    cub[17][1] = aux[5];
    cub[17][2] = aux[2];

    for (i = 3, j = 0; i <= 5 && j <= 2; i++, j++)
        aux_back[j] = cub[i][0];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
        aux_front[j] = cub[i][2];

    for (i = 8, j = 0; i >= 6 && j <= 2; i--, j++)
        aux_up[j] = cub[i][2];  

    for (i = 11, j = 0; i >= 9 && j <= 2; i--, j++)
        aux_down[j] = cub[i][2];



    for (i = 11, j = 0; i >= 9 && j <= 2; i--, j++)
            cub[i][2] = aux_back[j];

    for (i = 2, j = 0; i >= 0 && j <= 2; i--, j++)
            cub[i][2] = aux_down[j];

    for (i = 8, j = 0; i >= 6 && j <= 2; i--, j++)
            cub[i][2] = aux_front[j];

    for (i = 3, j = 0; i <= 5 && j <= 2; i++, j++)
            cub[i][0] = aux_up[j];

}

void L (int cub[18][3]){

    /*
    - funcția L priește ca parametru cubul Rubik și realizează mutarea în sensul acelor de ceasornic a feței din stânga;

    - aux_up = vector care reține prima coloană de pe fața de sus;
      aux_down =  vector care reține prima coloană de pe fața de jos;
      aux_back = vector care reține ultima coloană de pe fața din spate;
      aux_front = vector care reține prima coloană de pe fața frontală;

      aux = vector care reține toate elementele de pe o față;
    
    - primele 4 for-uri atribuie fiecărui vector auxiliar linia sau coloana corespunzătoare;
    - următoarele 4 for-uri realizează mutarea propriu-zisă, mutând coloana sau linia respectivă pe locul potrivit;

    - cele 8 atribuiri ale elementelor din cub realizează mutarea întregii fețe
    */

    int i, j;
    int aux_back[3], aux_front[3], aux_up[3], aux_down[3], aux[9], k = 0;

    for (i = 12; i <= 14; i++)
        for (j = 0; j < 3; j++)
            aux[k++] = cub[i][j];

    cub[12][0] = aux[6];
    cub[12][1] = aux[3];
    cub[12][2] = aux[0];
    cub[13][0] = aux[7];
    cub[13][2] = aux[1];
    cub[14][0] = aux[8];
    cub[14][1] = aux[5];
    cub[14][2] = aux[2];

    for (i = 5, j = 0; i >= 3 && j <= 2; i--, j++)
        aux_back[j] = cub[i][2];

    for (i = 0, j = 0; i <= 2 && j <= 2; i++, j++)
        aux_front[j] = cub[i][0];

    for (i = 6, j = 0; i <= 8 && j <= 2; i++, j++)
        aux_up[j] = cub[i][0];  

    for (i = 9, j = 0; i <= 11 && j <= 2; i++, j++)
        aux_down[j] = cub[i][0];



    for (i = 6, j = 0; i <= 8 && j <= 2; i++, j++)
            cub[i][0] = aux_back[j];

    for (i = 5, j = 0; i >= 3 && j <= 2; i--, j++)
            cub[i][2] = aux_down[j];

    for (i = 9, j = 0; i <= 11 && j <= 2; i++, j++)
            cub[i][0] = aux_front[j];

    for (i = 0, j = 0; i <= 2 && j <= 2; i++, j++)
            cub[i][0] = aux_up[j];

}

//funcția main
int main(){

    /*
    - vectorul culori reține lista de culori citite;
    - vectorul mutare reține șirul de caractere care compun numele unei mutări;
    - vectorul aux folosește la citirea fiecărei linii din matricea tuturor fețelor;
    */

    char culori[6][10], aux[33], mutare[3];
    int cub[18][3], i, j, m;

    //citim culorile date
    for(i = 0; i < 6; i++)
        scanf ("%s", culori[i]);

    for(i = 0; i < 18; i++){

    /* 
    - reținem în pointerul *p coloarea întâlnită până la punct,
         după care atribuie codul acesteia în matricea cub, pe poziția corespunzătoare;

    - acest proces se întâmplă pentru fiecare linie în parte a matricei cub;
    */
   
        scanf("%s", aux);
        char *p = strtok (aux, ".");
        cub[i][0] = cod (culori, p);
        p = strtok(NULL, ".");
        cub[i][1] = cod (culori, p);
        p = strtok (NULL, ".");
        cub[i][2] = cod (culori, p);
    }

    //citim numărul de mutări
    scanf("%d", &m);

    for(i = 0; i < m; i++){

    /*
    - citim fiecare mutare în parte;
    - verificăm dacă mutările citite sunt cele reținute de vectorul mutare;
    - în caz afirmativ, se apelează funcțiile corespunzătoare mutărilor citite;
    - în cazul mutărilor în sens trigonometric, este suficient să apelăm funcția corespunzătoare
        mutărilor în sensul acelor de ceasornic de 3 ori pentru a realiza mutarea;
    */

        scanf("%s", mutare);

        if (strcmp("F", mutare) == 0)
            F(cub);
        if (strcmp("F'", mutare) == 0){
            F(cub);F(cub);F(cub);
        }

        if (strcmp("B", mutare) == 0)
            B(cub);
        if (strcmp("B'", mutare) == 0){
            B(cub);B(cub);B(cub);
        }

        if (strcmp("U", mutare) == 0)
            U(cub);
        if (strcmp("U'", mutare) == 0){
            U(cub);U(cub);U(cub);
        }

        if (strcmp("D", mutare) == 0)
            D(cub);
        if (strcmp("D'", mutare) == 0){
            D(cub);D(cub);D(cub);
        }

        if (strcmp("R", mutare) == 0)
            R(cub);
        if (strcmp("R'", mutare) == 0){
            R(cub);R(cub);R(cub);
        }

        if (strcmp("L", mutare) == 0)
            L(cub);
        if (strcmp("L'", mutare) == 0){
            L(cub);L(cub);L(cub);
        }

    }

   
    /* 
    afișarea matricei cub, înlocuind codurile culorilor cu culorile corespunzătoare
    și introducănd caracterul "." între acestea pe lnie;
    */
    
    for (i = 0; i < 18; i++){
        for (j = 0; j < 3; j++){
            printf("%s", culori[cub[i][j]]);
            if(j < 2)
                printf(".");
        }
        printf("\n");
    }

}