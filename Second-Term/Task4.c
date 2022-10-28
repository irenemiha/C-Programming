#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char url[51];
    int octeti;
    int accesari;
    int checksum;
    char titlu[51];
    char *paragraf;
    char *html;
} site;

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

int rotr(char x, int k){
    int i, j;
    char biti[8];
    dec_to_bin((int)x, biti);
    for(i = 0; i < k; i++){
        int b7 = biti[7];
        for(j = 7; j > 0; j--)
            biti[j] = biti [j - 1];
        biti[0] = b7;          
    }
    return bin_to_dec(biti);
}

int rotl(char x, int k){
    int i, j;
    char biti[8];
    dec_to_bin((int)x, biti);
    for(i = 0; i < k; i++){
        int b0 = biti[0];
        for(j = 0; j < 7; j++)
            biti[j] = biti [j + 1];
        biti[7] = b0;          
    }
    return bin_to_dec(biti);
}

int checksum(char *html){
    int rezultat = (int)html[0];
    for(int i = 1; i < strlen(html); i++){
        if(i % 2 == 0)
            rezultat = rezultat ^ rotl(html[i], i);
        else
            rezultat = rezultat ^ rotr(html[i], i);
    }
    return rezultat;
}

int indice(site *vector_siteuri, char url[51], int nr_siteuri){
    for(int i = 0; i < nr_siteuri; i++)
        if(strcmp(vector_siteuri[i].url, url) == 0)
            return i;
    return -5;
}

int main(){
    FILE *master, *file;
    master = fopen("master.txt", "r");
    char file_name[31];
    site *siteuri;
    int capacitate = 3;
    int nr_siteuri = 0;

    siteuri = malloc(capacitate * sizeof(site));

    while(fgets(file_name, 31, master)){
        if(file_name[strlen(file_name) - 1] == '\n')
            file_name[strlen(file_name) - 1] = '\0';

        file = fopen(file_name, "r");

        if(nr_siteuri == capacitate){
            capacitate += 3;
            siteuri = realloc(siteuri, capacitate * sizeof(site));
        }

        fscanf(file, "%s%d%d%d", siteuri[nr_siteuri].url, &siteuri[nr_siteuri].octeti, &siteuri[nr_siteuri].accesari, &siteuri[nr_siteuri].checksum);
        
        char *html, nimic;
        int aux_octeti = siteuri[nr_siteuri].octeti;
        html = malloc((aux_octeti + 1) * sizeof(char));

        fscanf(file, "%c", &nimic);
        for(int i = 0; i < siteuri[nr_siteuri].octeti; i++){
            fscanf(file, "%c", &html[i]);
            if(html[i] == 13)
                i--;   
        }
        html[aux_octeti] = '\0';

        siteuri[nr_siteuri].html = malloc((aux_octeti + 1) * sizeof(char));
        strcpy(siteuri[nr_siteuri].html, html);
        char *first_title = strstr(html, "<title>");
        char *last_title = strstr(html, "</title>");
        int p = first_title - html + 7;
        int q = last_title - html;
        int k = 0;
        
        for(int i = p; i < q; i++)
            siteuri[nr_siteuri].titlu[k++] = html[i];
        siteuri[nr_siteuri].titlu[k] = '\0';

        char *first_p;
        if(strstr(html, "<p>") != NULL)
            first_p = strstr(html, "<p>");
        else
            first_p = strstr(html, ";\">");
        char *last_p = strstr(html, "</p>");
        int r = first_p - html + 3;
        int s = last_p - html;
        int dimensiune = s - r + 2;
        k = 0;
        siteuri[nr_siteuri].paragraf = malloc(dimensiune * sizeof(char));
        for(int i = r; i < s; i++)
            siteuri[nr_siteuri].paragraf[k++] = html[i];
        siteuri[nr_siteuri].paragraf[k] = '\0';

        nr_siteuri ++;
        free(html);
        fclose(file);
    }
    fclose(master);

    char linie[101];
    while(fgets(linie, 101, stdin)){
        if(linie[strlen(linie) - 1] == '\n')
            linie[strlen(linie) - 1] = '\0';
        int ind = indice(siteuri, linie, nr_siteuri);
        if(ind < 0)
            printf("Website not found!\n");
        else
            if(checksum(siteuri[ind].html) == siteuri[ind].checksum)
                printf("Website safe!\n");
            else
                printf("Malicious website! Official key: %d. Found key: %d\n", siteuri[ind].checksum, checksum(siteuri[ind].html));
    }

    for(int i = 0; i < nr_siteuri; i++){
        free(siteuri[i].paragraf);
        free(siteuri[i].html);
    }
    free(siteuri);

}