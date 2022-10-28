#include <stdio.h>

//funcția returnează minimul dintre 2 numere x și y
int minim (int x, int y){
    if(x > y)
        return y;
    return x;   
}

void dec_to_bin (int n, char *s){

    /*
    - funcția transformă numărul n din baza 10 în baza 2 și pune fiecare cifră din rezultat în vectorul aux, 
         urmând ca apoi să adăugăm în șirul de caractere s cifrele respective ca și caractere;
    */

    int k = 0, i;
    char aux[8];

    for (i = 0; i < 8; i++)
        aux[i] = '0';

    while (n > 0){
        aux[k++] = n % 2 + (int)'0';
        n /= 2;
    }
    
    for (i = 0; i < 8; i++)
        s[i] = aux[7 - i];
}

int bin_to_dec (char *s){

    /*
    - funcția transformă numărul reprezentat de cifrele din șirul de caractere s din baza 2 în baza 10;
    - vectorul aux păstrează toate puterile lui 2 până la 2^7-1 (adică 128);
    - în variabila x se calculează numărul in baza 10;
    */

    int i, aux[8] = {1, 2, 4, 8, 16, 32, 64, 128}, x = 0;
    for(i = 0; i < 8; i++)
        x = x + ((int)s[i] - (int)'0') * aux[7 - i];
    return x;
}


void inmultire_matrice (int a[8][8], int b[8][8], int c[8][8]){

    /*
    - funcția înmulțește matricele a și b, dând ca rezultat matricea c;
    - apelarea funcției minim are ca motiv diferențierea relației booleene 1+1=1 de relația matematică 1+1=2;
    - pentru a putea avea matricea c formată doar din 0 sau 1, trebuie să alegem minimul dintre 1 
         și rezultatul adunării elementelor înmulțitie linie cu coloană;
    */

    int i, j, k;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            c[i][j] = 0;

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++){
            c[i][j] = 0;
            for (k = 0; k < 8; k++)
                c[i][j] = minim (1, c[i][j] + a[i][k] * b[k][j]);
        }
}
 
//funcția primește matricea a ca parametru și calculează transpusa sa în matricea b
void transpusa (int a[8][8], int b[8][8]){
    int i, j;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            b[i][j] = a[j][i];
}


int sum_X_0 (int m[][8]){

    /*
    - funcția calculează punctajului la X și O pentru matricea dată;
    - variabila k adună pentru fiecare submatrice punctajul;
    */

    //submatricea stânga-sus
    int i, j, k = 0, ok;
    for (i = 0; i <= 3; i++){
        ok = 1;
        for(j = 0; j <= 3 && ok == 1; j++)
            if (m[i][j] != 1) //elementele luate pe linii
                ok = 0;
        k = k + ok;
    }

    for (j = 0; j <= 3; j++){
        ok = 1;
        for(i = 0; i <= 3 && ok == 1; i++)
            if (m[i][j] != 1) //elementele luate pe coloane
                ok = 0;
        k = k + ok;
    }

    ok = 1;
    for (i = 0; i <= 3; i++)
        if (m[i][i] != 1) //elementele diagonalei principale a submatricei
                ok = 0;
    k = k + ok;

    ok = 1;
    for (i = 0; i <= 3; i++)
        if (m[i][3 - i] != 1) //elementele diagonalei secundare a submatricei
                ok = 0;
    k = k + ok;

            
    //submatricea dreapta-sus
    for (i = 0; i <= 3; i++){
        ok = 1;
        for(j = 4; j <= 7 && ok == 1; j++)
            if (m[i][j] != 1) //elementele luate pe linii
                ok = 0;
        k = k + ok;
    }

    for (j = 4; j <= 7; j++){
        ok = 1;
        for(i = 0; i <= 3 && ok == 1; i++)
            if (m[i][j] != 1) //elementele luate pe coloane
                ok = 0;
        k = k + ok;
    }

    ok = 1;
    for (i = 0; i <= 3; i++)
        if (m[i][i + 4] != 1) //elementele diagonalei principale a submatricei
                ok = 0;
    k = k + ok;

    ok = 1;
    for (i = 0; i <= 3; i++)
        if (m[i][7 - i] != 1) //elementele diagonalei secundare a submatricei
                ok = 0;
    k = k + ok;


    //submatricea stânga-jos
    for (i = 4; i <= 7; i++){
        ok = 1;
        for(j = 0; j <= 3 && ok == 1; j++)
            if (m[i][j] != 1) //elementele luate pe linii
                ok = 0;
        k = k + ok;
    }

    for (j = 0; j <= 3; j++){
        ok = 1;
        for(i = 4; i <= 7 && ok == 1; i++)
            if (m[i][j] != 1) //elementele luate pe coloane
                ok = 0;
        k = k + ok;
    }

    ok = 1;
    for (i = 4; i <= 7; i++)
        if (m[i][i - 4] != 1) //elementele diagonalei principale a submatricei
                ok = 0;
    k = k + ok;

    ok = 1;
    for (i = 4; i <= 7; i++)
        if (m[i][7 - i] != 1) //elementele diagonalei secundare a submatricei
                ok = 0;
    k = k + ok;


    //submatricea dreapta-jos
    for (i = 4; i <= 7; i++){
        ok = 1;
        for(j = 4; j <= 7 && ok == 1; j++)
            if (m[i][j] != 1) //elementele luate pe linii 
                ok = 0;
        k = k + ok;
    }

    for (j = 4; j <= 7; j++){
        ok = 1;
        for(i = 4; i <= 7 && ok == 1; i++)
            if (m[i][j] != 1) //elementele luate pe coloane
                ok = 0;
        k = k + ok;
    }

    ok = 1;
    for (i = 4; i <= 7; i++)
        if (m[i][i] != 1) //elementele diagonalei principale a submatricei
                ok = 0;
    k = k + ok;

    ok = 1;
    for (i = 4; i <= 7; i++)
        if (m[i][11 - i] != 1) //elementele diagonalei secundare a submatricei
                ok = 0;
    k = k + ok;

    return k; //funcția returnează scorul obținut
}

//funcția main
int main(){
    int x, a[8][8], i, j;
    char s[8];

    //citire numerele care urmează să fie transformate în matricea de biți
    for(i = 0; i < 8; i++){
        scanf("%d", &x);
        dec_to_bin(x,s);
        for (j = 0; j < 8; j++)
            a[i][j] = (int)s[j] - (int)'0';
    }

    //inițializarea variabilelor coespunzătoare matricei a transpuse, pătratului matricei a și transpusei pătratului matricei a
    int a_transpus[8][8], a_patrat[8][8], a_ori_a_transpus[8][8];

    //apelarea funcțiilor pentru matrice
    transpusa (a, a_transpus);
    inmultire_matrice (a, a_transpus, a_ori_a_transpus);
    inmultire_matrice (a, a, a_patrat);

    //pentru fiecar tip de matrice calcuată, calculăm scorul în 3 variabile diferite
    int p = sum_X_0 (a);
    int q = sum_X_0 (a_ori_a_transpus);
    int r = sum_X_0 (a_patrat);

    //afișarea numerelor de pe fiecare linie din matricea câștigătoare
    if((p >= q) && (p >= r))
        for (i = 0; i < 8; i++){
            char s[8];
            for(j = 0; j < 8; j++)
                s[j] = a[i][j] + (int)'0';
            printf("%d\n", bin_to_dec(s));
        }
    
    else if((q >= p) && (q >= r))
        for (i = 0; i < 8; i++){
            char s[8];
            for(j = 0; j < 8; j++)
                s[j] = a_ori_a_transpus[i][j] + (int)'0';
            printf("%d\n", bin_to_dec(s));
        }

    else if((r >= q) && (r >= p))
        for (i = 0; i < 8; i++){
            char s[8];
            for(j = 0; j < 8; j++)
                s[j] = a_patrat[i][j] + (int)'0';
            printf("%d\n", bin_to_dec(s));
        }
}