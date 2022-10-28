#include <stdio.h>         

int atacat(int x, int y, int i_x, int i_y, int tabla[100][100], int M){

    /*
    - funcția verifică dacă poziția dată de coordonatele x și y este atacată de vreun nebun;

    - matricea tabla reprezintă tabla de sah, iar M reprezită dimensiunile acesteia;

    - funcția parcurge cele 4 diagonale care pleacă din poziția (x, y) prin intermediul variabilelor I și J,
        care se plimbă prin fiecare element de pe diagonale și returnează valoarea 1 dacă găsește pe parcurs un nebun;

    - pentru a nu se lua în considerare nebunul de pe pozițiile i_x și i_y, 
         determinăm for-ul să sară peste acel nebun în parcurgere, executând o instrucțiune
         care nu afectează cu nimic programul (în cazul nostru, incrementarea lui b);
    
    - funcția returnează 0 dacă nu găsește pe parcurs un nebun;
    */

    int I, J, b;
    b = 0;
    for (I = x + 1, J = y + 1; I < M && J < M; I++, J++)
        if (I == i_x && J == i_y){
		b++;
	}
	else if(tabla[I][J] == 1)
            return 1;

    for (I = x - 1, J = y - 1; I >= 0 && J >= 0; I--, J--)
        if (I == i_x && J == i_y){
		b++;
	}
	else if(tabla[I][J] == 1)
            return 1;

    for (I = x + 1, J = y - 1; I < M && J >= 0; I++, J--)
        if (I == i_x && J == i_y){
		b++;
	}
	else if(tabla[I][J] == 1)
            return 1;

    for (I = x - 1, J = y + 1; I >= 0 && J < M; I--, J++)
        if (I == i_x && J == i_y){
		b++;
	}
	else if(tabla[I][J] == 1)
            return 1;

    return 0;
}

int liber (int i_x, int i_y, int tabla[100][100], int M){

    /*
    - funcția verifică dacă se poate găsi un loc liber pentru nebunul de coordonate i_x și i_y, 
        astfel încât să nu atace sau să fie atacat de alți nebuni de pe tablă;

    - funcția parcurge tabla prin intermediul variabilelor I și J și verifică dacă un element poate fi atacat la un moment dat;

    - dacă elementul poate fi atacat, înseamnnă că nu putem muta nebunul de coordonate (i_x, i_y) în locul elementului găsit,
        întrucât va fi atacat de alți nebuni, lucru care noi nu ne dorim să se întâmple;

    - variabila ok păstrează valoarea returnată de funcție, în funcție de efectul verificării;

    - ok capătă valoarea 1 dacă nebunul de coordonate (i_x, i_y) poate fi mutat pe o altă poziție, 
        astfel încât să nu mai existe nebuni care să se atace pe tablă; 
    */

    int ok, I, J;
    ok = 0;
    for (I = 0; I < M; I++){
        for (J = 0; J < M; J++)
	    if(tabla[I][J] == 0)
            if (atacat (I, J, i_x, i_y, tabla, M) == 0)
		        ok = 1;
    }
    return ok;
}

int nebuni (int i, int j, int tabla[100][100], int M){

    /*
    - funcția ia ca parametrii coordonatele nebunului la care ne referim, acestea fiind i și y, 
        și parcurge diagonalele care pleacă din acesta pentru a verifica dacă există nebuni pe acestea;
    
    - cu alte cuvinte, funcția calculează în variabila s numărul de nebuni care pot fi atacați de nebunul de coordonate (i, j);
    */

    int I, J, s = 0;
    
    for (I = i + 1, J = j + 1; I < M && J < M; I++, J++)
        if (tabla[I][J] != 0)
            s++;
    
    for (I = i - 1, J = j - 1; I >= 0 && J >= 0; I--, J--)
        if (tabla[I][J] != 0)
            s++;
    
    for (I = i + 1, J = j - 1; I < M && J >= 0; I++, J--)
        if (tabla[I][J] != 0)
            s++;
    
    for (I = i - 1, J = j + 1; I >= 0 && J < M; I--, J++)
        if (tabla[I][J] != 0)
            s++;
    
    return s;
}

void printM(int tabla[100][100], int M){
	for(int i = 0 ; i < M; i++){
		for(int j = 0; j < M; j++)
			printf("%d ", tabla[i][j]);
		printf("\n");
	}
}


//funcția main
int main(){
    int N, M, i, j, x, y, perechi = 0, i_x = -1, j_x = -1, i_y = -1, j_y = -1, tabla[100][100];
    scanf ("%d%d", &M, &N);

    //transforăm în zero toate elementele matricei tabla
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            tabla[i][j] = 0;

    //citim perechile de coordonate și așează valoarea 1 pe pozițiile din matrice reprezentate de cele 2 coordonate
    for (i = 0; i < N; i++){
        scanf("%d%d", &x, &y);
        tabla[x][y] = 1;
    }

    //calculăm în variabila perechi numărul pe perechi de nebuni care se atacă reciproc;
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            if (tabla[i][j] == 1)
                perechi += nebuni(i, j, tabla, M);

    /*
    - deoarece funcția nebuni consideră cazurile în care nebunul x îl atacă pe nebunul y și invers ca fiind diferite,
        output-ul va returna un număr dublu de perechi;
    - de aceea, vom atribui variabilei perechi valoarea sa înjumătățită, urând să o afișăm apoi;
    */
    perechi /= 2;
    printf("%d\n", perechi);

    //căutăm pe tabla de șah nebuni care atacă un singur alt nebun și salvăm poziția lor pe tabla de șah
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            if (tabla[i][j] == 1)
                if (nebuni(i, j, tabla, M) == 1){
                    if (i_x == -1){
                        i_x = i;
                        j_x = j;
                    }
                    else{
                        i_y = i;
                        j_y = j;
                    }
                }

    //dacă nu există doar o pereche de nebuni care se atacă, afișăm mesajul "NU";
    if (perechi != 1)
        printf("NU\n");

    /*
    - dacă am găsit o singură pereche de nebuni care se atacă, verificăm dacă există
        poziții libere pe care îi putem muta pe oricare dintre aceștia, astfel încât să nu mai existe 
        nicio pereche de nebuni care se atacă;

    - în caz afirmativ, afișâm mesajul "DA", iar, în caz contrar, afișăm mesajul "NU";
    */
    else{
        if (liber (i_x, j_x, tabla, M) || liber (i_y, j_y, tabla, M))
            printf("DA\n");
        else
            printf("NU\n");
    }
}