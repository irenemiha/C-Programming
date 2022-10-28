#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "siteuri.h"

int main(){
    
    site *siteuri, *vector_cautare;

    int nr_siteuri = 0, cate = 0;

    siteuri = baza_date(siteuri, &nr_siteuri);

    vector_cautare = filtrare_avansata(siteuri, vector_cautare, nr_siteuri, &cate);

    for(int i = 0; i < cate; i++)
        printf("%s\n", vector_cautare[i].url);

    for(int i = 0; i < nr_siteuri; i++)
        free(siteuri[i].paragraf);
    free(siteuri);

    free(vector_cautare);
}