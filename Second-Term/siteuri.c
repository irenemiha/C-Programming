#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "siteuri.h"

site* baza_date(site *siteuri, int *nr_siteuri){
    FILE *master, *file;
    master = fopen("master.txt", "r");
    char file_name[31];
    int capacitate = 3;

    siteuri = malloc(capacitate * sizeof(site));

    while(fgets(file_name, 31, master)){
        if(file_name[strlen(file_name) - 1] == '\n')
            file_name[strlen(file_name) - 1] = '\0';

        file = fopen(file_name, "r");

        if((*nr_siteuri) == capacitate){
            capacitate += 3;
            siteuri = realloc(siteuri, capacitate * sizeof(site));
        }

        fscanf(file, "%s%d%d%d", siteuri[(*nr_siteuri)].url, &siteuri[(*nr_siteuri)].octeti, &siteuri[(*nr_siteuri)].accesari, &siteuri[(*nr_siteuri)].checksum);

        char *html, nimic;
        int aux_octeti = siteuri[(*nr_siteuri)].octeti;
        html = malloc((aux_octeti+1) * sizeof(char));

        fscanf(file, "%c", &nimic);
        for(int i = 0; i < aux_octeti; i++){
            fscanf(file, "%c", &html[i]);
            if(html[i] == 13)
                i--;
        }
	    html[aux_octeti] = '\0';
        char *first_title = strstr(html, "<title>");
        char *last_title = strstr(html, "</title>");
        int p = first_title - html + 7;
        int q = last_title - html;
        int k = 0;

        for(int i = p; i < q; i++)
            siteuri[(*nr_siteuri)].titlu[k++] = html[i];
        siteuri[(*nr_siteuri)].titlu[k] = '\0';

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
        siteuri[(*nr_siteuri)].paragraf = malloc(dimensiune * sizeof(char));
        for(int i = r; i < s; i++)
            siteuri[(*nr_siteuri)].paragraf[k++] = html[i];
        siteuri[(*nr_siteuri)].paragraf[k] = '\0';
	
	    free(html);
        (*nr_siteuri) ++;
        fclose(file);
    }
    fclose(master);
    return siteuri;
}

void swap (site *unu, site *doi){
    site aux = *unu;
    *unu = *doi;
    *doi = aux;
}

int comparator_2(site unu, site doi){
    if(strcmp(unu.paragraf, doi.paragraf) == 0)
        return unu.accesari < doi.accesari ? 1 : -1;
    return strcmp(unu.paragraf, doi.paragraf) > 0 ? 1 : -1;
}

void sort(site *vector_siteuri, int cate, int (*comparator)(site unu, site doi)){
    for(int i = 0; i < cate - 1; i++)
        for(int j = i + 1; j < cate; j++){
            if(comparator(vector_siteuri[i], vector_siteuri[j]) == 1){
                swap(&vector_siteuri[i], &vector_siteuri[j]);
            }
        }
}

site* filtrare_simpla(site *siteuri, site *vector_siteuri, int nr_siteuri, int *cate){
    char cuvinte_tastatura[1001];
    char **vector_cuvinte;
    char **vector_cuv_paragraf;
    int capacitate = 10;
    int k = 0;
    vector_cuvinte = malloc(capacitate * sizeof(char*));
    scanf("%[^\n]s", cuvinte_tastatura);

    char *token = strtok(cuvinte_tastatura, " ");

    while(token != NULL){
        if(k == capacitate){
            capacitate *= 2;
            vector_cuvinte = realloc(vector_cuvinte, capacitate * sizeof(char*));
        }
        vector_cuvinte[k] = malloc((strlen(token)+1) * sizeof(char));
	    token[strlen(token)] = '\0';
        strcpy(vector_cuvinte[k++], token);
        token = strtok(NULL, " ");
    }

    int capacitate_2 = 1;
    char *cuvant_paragraf;
    char *copie_paragraf;
    (*cate) = 0;
    vector_siteuri = malloc(capacitate_2 * sizeof(site));

    for(int i = 0; i < nr_siteuri; i++){
        int capacitate_1 = 1;
        vector_cuv_paragraf = malloc(capacitate_1 * sizeof(char*));

        int cuv_par = 0;
        copie_paragraf = malloc((strlen(siteuri[i].paragraf) + 1) * sizeof(char));
        strcpy(copie_paragraf, siteuri[i].paragraf);

        for(int j = 0; j < strlen(siteuri[i].paragraf); j++)
            if(copie_paragraf[j] == '\n')
                copie_paragraf[j] = ' ';
                
        copie_paragraf[strlen(siteuri[i].paragraf)] = '\0';

        cuvant_paragraf = strtok(copie_paragraf, " ");       
        while(cuvant_paragraf != NULL){
            if(cuv_par == capacitate_1){
                capacitate_1 *= 2;
                vector_cuv_paragraf = realloc(vector_cuv_paragraf, capacitate_1 * sizeof(char*));
                }
            vector_cuv_paragraf[cuv_par] = malloc((strlen(cuvant_paragraf) + 1) * sizeof(char));
            strcpy(vector_cuv_paragraf[cuv_par++], cuvant_paragraf);
            cuvant_paragraf = strtok(NULL, " ");     
        }
        free(copie_paragraf);
    
        for(int j = 0; j < cuv_par; j++)
            for(int z = 0; z < k; z++)
                if(strcmp(vector_cuv_paragraf[j], vector_cuvinte[z]) == 0){
                    if((*cate) == capacitate_2){
                        capacitate_2 *= 2;
                        vector_siteuri = realloc(vector_siteuri, capacitate_2 * sizeof(site));
                    }
                    vector_siteuri[(*cate)++] = siteuri[i];
                    j = cuv_par;
                    break;
                }

        for(int t = 0; t < cuv_par; t++)
            free(vector_cuv_paragraf[t]);
        free(vector_cuv_paragraf);
    }
    sort(vector_siteuri, (*cate), comparator_2);

    for(int i = 0; i < k ; i++)
        free(vector_cuvinte[i]);
    free(vector_cuvinte);

    return vector_siteuri;
}

site* filtrare_simpla2(site *siteuri, site *vector_siteuri, int nr_siteuri, int *cate, char *text){
    char cuvinte_tastatura[130];
    char **vector_cuvinte;
    char **vector_cuv_paragraf;
    int capacitate = 10;
    int k = 0;
    vector_cuvinte = malloc(capacitate * sizeof(char*));
    strcpy(cuvinte_tastatura, text);

    char *token = strtok(cuvinte_tastatura, " ");

    while(token != NULL){
        if(k == capacitate){
            capacitate *= 2;
            vector_cuvinte = realloc(vector_cuvinte, capacitate * sizeof(char*));
        }
        vector_cuvinte[k] = malloc((strlen(token)+1) * sizeof(char));
	    token[strlen(token)] = '\0';
        strcpy(vector_cuvinte[k++], token);
        token = strtok(NULL, " ");
    }

    int capacitate_2 = 1;
    char *cuvant_paragraf;
    char *copie_paragraf;
    (*cate) = 0;
    vector_siteuri = malloc(capacitate_2 * sizeof(site));

    for(int i = 0; i < nr_siteuri; i++){
        int capacitate_1 = 1;
        vector_cuv_paragraf = malloc(capacitate_1 * sizeof(char*));

        int cuv_par = 0;
        copie_paragraf = malloc((strlen(siteuri[i].paragraf) + 1) * sizeof(char));
        strcpy(copie_paragraf, siteuri[i].paragraf);

        for(int j = 0; j < strlen(siteuri[i].paragraf); j++)
            if(copie_paragraf[j] == '\n')
                copie_paragraf[j] = ' ';
                
        copie_paragraf[strlen(siteuri[i].paragraf)] = '\0';

        cuvant_paragraf = strtok(copie_paragraf, " ");       
        while(cuvant_paragraf != NULL){
            if(cuv_par == capacitate_1){
                capacitate_1 *= 2;
                vector_cuv_paragraf = realloc(vector_cuv_paragraf, capacitate_1 * sizeof(char*));
                }
            vector_cuv_paragraf[cuv_par] = malloc((strlen(cuvant_paragraf) + 1) * sizeof(char));
            strcpy(vector_cuv_paragraf[cuv_par++], cuvant_paragraf);
            cuvant_paragraf = strtok(NULL, " ");     
        }
        free(copie_paragraf);
    
        for(int j = 0; j < cuv_par; j++)
            for(int z = 0; z < k; z++)
                if(strcmp(vector_cuv_paragraf[j], vector_cuvinte[z]) == 0){
                    if((*cate) == capacitate_2){
                        capacitate_2 *= 2;
                        vector_siteuri = realloc(vector_siteuri, capacitate_2 * sizeof(site));
                    }
                    vector_siteuri[(*cate)++] = siteuri[i];
                    j = cuv_par;
                    break;
                }

        for(int t = 0; t < cuv_par; t++)
            free(vector_cuv_paragraf[t]);
        free(vector_cuv_paragraf);
    }
    sort(vector_siteuri, (*cate), comparator_2);

    for(int i = 0; i < k ; i++)
        free(vector_cuvinte[i]);
    free(vector_cuvinte);

    return vector_siteuri;
}

int comparator_3(site unu, site doi){
    return unu.accesari < doi.accesari ? 1 : -1;
}

site* filtrare_avansata(site *siteuri, site *vector_cautare, int nr_siteuri, int *cate){
    char cuvinte_tastatura[1001];
    char **vector_cuvinte;
    int capacitate = 1;
    int k = 0;
    vector_cuvinte = malloc(capacitate * sizeof(char*));
    scanf("%[^\n]s", cuvinte_tastatura);

    char *token = strtok(cuvinte_tastatura, " ");

    while(token != NULL){
        if(k == capacitate){
            capacitate *= 2;
        }
        vector_cuvinte = realloc(vector_cuvinte, capacitate * sizeof(char*));
        vector_cuvinte[k] = malloc((strlen(token) + 1) * sizeof(char));
        token[strlen(token)] = '\0';

        strcpy(vector_cuvinte[k++], token);
        token = strtok(NULL, " ");
    }

    int ok = 0, pas = 0;
    
    for(int i = 0; i < k; i++)
        if(vector_cuvinte[i][0] == '"'){
            pas = 0;
            ok = 1; 
            int ci = i;
            for(int j = i + 1; j < k && ok == 1; j++){
                vector_cuvinte[j][strlen(vector_cuvinte[j])] = '\0';
                vector_cuvinte[i] = realloc(vector_cuvinte[i], strlen(vector_cuvinte[i]) + strlen(vector_cuvinte[j])+2);
                strcat(vector_cuvinte[i], " ");
                strcat(vector_cuvinte[i], vector_cuvinte[j]);
                pas++;
                if(vector_cuvinte[j][strlen(vector_cuvinte[j]) - 1] == '"'){
                    ok = 0;
                }
            }
            for(int z = ci + pas + 1; z < k; z++){
                    vector_cuvinte[z][strlen(vector_cuvinte[z])] = '\0';
                    strcpy(vector_cuvinte[z - pas], vector_cuvinte[z]);
            }
            k -= pas;          
        }
    
    for(int i = 0; i < k; i++)
        if(vector_cuvinte[i][0] == '"'){
            vector_cuvinte[i][strlen(vector_cuvinte[i]) - 1] = '\0';
        }

    capacitate = 1;
    vector_cautare = malloc(capacitate * sizeof(site));
    (*cate) = 0;
    
    for(int i = 0; i < nr_siteuri; i++){
        int nr = 0;
        char *copie_paragraf = malloc((strlen(siteuri[i].paragraf) + 1) * sizeof(char));
        ok = 0;
        int cap = 1;

        strcpy(copie_paragraf, siteuri[i].paragraf);
        for(int j = 0; j < strlen(siteuri[i].paragraf); j++)
            if(copie_paragraf[j] == '\n')
                copie_paragraf[j] = ' ';

        copie_paragraf[strlen(siteuri[i].paragraf)] = '\0';   
        char *cuvant = strtok(copie_paragraf, " ");
        char **lista_cuvinte;
        lista_cuvinte = malloc(cap * sizeof(char*));

        while(cuvant != NULL){
            if(cap == nr){
                cap *= 2;
                lista_cuvinte = realloc(lista_cuvinte, cap * sizeof(char*));
            }
            lista_cuvinte[nr] = malloc((strlen(cuvant) + 1) * sizeof(char));
            cuvant[strlen(cuvant)] = '\0';
            strcpy(lista_cuvinte[nr++], cuvant);
            cuvant = strtok(NULL, " ");
        }

        for(int j = 0; j < k; j++)
            if(vector_cuvinte[j][0] == '"')
                if(strstr(siteuri[i].paragraf, vector_cuvinte[j] + 1)){
                    ok = 1;
                    break;
                }

        for(int j = 0; j < nr; j++)
            for(int t = 0; t < k; t++)
                if(strcmp(lista_cuvinte[j], vector_cuvinte[t]) == 0){
                    ok = 1;
                    j = nr;
                    break;
                }

        for(int j = 0; j < nr; j++)
            for(int t = 0; t < k; t++)
                if(vector_cuvinte[t][0] == '-')
                    if(strcmp(lista_cuvinte[j], vector_cuvinte[t] + 1) == 0){
                        ok = 0;
                        j = nr;
                        break;
                    }

        if((*cate) == capacitate){
            capacitate *= 2;
            vector_cautare = realloc(vector_cautare, capacitate * sizeof(site));
        }
        if(ok == 1)
            vector_cautare[(*cate)++] = siteuri[i];
        
        free(copie_paragraf);
        for(int i = 0; i < nr; i++)
            free(lista_cuvinte[i]);
        free(lista_cuvinte);
    }
    sort(vector_cautare, (*cate), comparator_3);

    for(int i = 0; i < k ; i++)
        free(vector_cuvinte[i]);
    free(vector_cuvinte);
    
    return vector_cautare;
}

site* filtrare_avansata2(site *siteuri, site *vector_cautare, int nr_siteuri, int *cate, char *text){
    char cuvinte_tastatura[130];
    char **vector_cuvinte;
    int capacitate = 1;
    int k = 0;
    vector_cuvinte = malloc(capacitate * sizeof(char*));
    strcpy(cuvinte_tastatura, text);

    char *token = strtok(cuvinte_tastatura, " ");

    while(token != NULL){
        if(k == capacitate){
            capacitate *= 2;
        }
        vector_cuvinte = realloc(vector_cuvinte, capacitate * sizeof(char*));
        vector_cuvinte[k] = malloc((strlen(token) + 1) * sizeof(char));
        token[strlen(token)] = '\0';

        strcpy(vector_cuvinte[k++], token);
        token = strtok(NULL, " ");
    }

    int ok = 0, pas = 0;
    
    for(int i = 0; i < k; i++)
        if(vector_cuvinte[i][0] == '"'){
            pas = 0;
            ok = 1; 
            int ci = i;
            for(int j = i + 1; j < k && ok == 1; j++){
                vector_cuvinte[j][strlen(vector_cuvinte[j])] = '\0';
                vector_cuvinte[i] = realloc(vector_cuvinte[i], strlen(vector_cuvinte[i]) + strlen(vector_cuvinte[j])+2);
                strcat(vector_cuvinte[i], " ");
                strcat(vector_cuvinte[i], vector_cuvinte[j]);
                pas++;
                if(vector_cuvinte[j][strlen(vector_cuvinte[j]) - 1] == '"'){
                    ok = 0;
                }
            }
            for(int z = ci + pas + 1; z < k; z++){
                    vector_cuvinte[z][strlen(vector_cuvinte[z])] = '\0';
                    strcpy(vector_cuvinte[z - pas], vector_cuvinte[z]);
            }
            k -= pas;          
        }
    
    for(int i = 0; i < k; i++)
        if(vector_cuvinte[i][0] == '"'){
            vector_cuvinte[i][strlen(vector_cuvinte[i]) - 1] = '\0';
        }

    capacitate = 1;
    vector_cautare = malloc(capacitate * sizeof(site));
    (*cate) = 0;
    
    for(int i = 0; i < nr_siteuri; i++){
        int nr = 0;
        char *copie_paragraf = malloc((strlen(siteuri[i].paragraf) + 1) * sizeof(char));
        ok = 0;
        int cap = 1;

        strcpy(copie_paragraf, siteuri[i].paragraf);
        for(int j = 0; j < strlen(siteuri[i].paragraf); j++)
            if(copie_paragraf[j] == '\n')
                copie_paragraf[j] = ' ';

        copie_paragraf[strlen(siteuri[i].paragraf)] = '\0';   
        char *cuvant = strtok(copie_paragraf, " ");
        char **lista_cuvinte;
        lista_cuvinte = malloc(cap * sizeof(char*));

        while(cuvant != NULL){
            if(cap == nr){
                cap *= 2;
                lista_cuvinte = realloc(lista_cuvinte, cap * sizeof(char*));
            }
            lista_cuvinte[nr] = malloc((strlen(cuvant) + 1) * sizeof(char));
            cuvant[strlen(cuvant)] = '\0';
            strcpy(lista_cuvinte[nr++], cuvant);
            cuvant = strtok(NULL, " ");
        }

        for(int j = 0; j < k; j++)
            if(vector_cuvinte[j][0] == '"')
                if(strstr(siteuri[i].paragraf, vector_cuvinte[j] + 1)){
                    ok = 1;
                    break;
                }

        for(int j = 0; j < nr; j++)
            for(int t = 0; t < k; t++)
                if(strcmp(lista_cuvinte[j], vector_cuvinte[t]) == 0){
                    ok = 1;
                    j = nr;
                    break;
                }

        for(int j = 0; j < nr; j++)
            for(int t = 0; t < k; t++)
                if(vector_cuvinte[t][0] == '-')
                    if(strcmp(lista_cuvinte[j], vector_cuvinte[t] + 1) == 0){
                        ok = 0;
                        j = nr;
                        break;
                    }

        if((*cate) == capacitate){
            capacitate *= 2;
            vector_cautare = realloc(vector_cautare, capacitate * sizeof(site));
        }
        if(ok == 1)
            vector_cautare[(*cate)++] = siteuri[i];
        
        free(copie_paragraf);
        for(int i = 0; i < nr; i++)
            free(lista_cuvinte[i]);
        free(lista_cuvinte);
    }
    sort(vector_cautare, (*cate), comparator_3);

    for(int i = 0; i < k ; i++)
        free(vector_cuvinte[i]);
    free(vector_cuvinte);

    return vector_cautare;
}