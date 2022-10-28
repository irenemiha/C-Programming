#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "siteuri.h"

int main(){

    site *siteuri;
    int nr_siteuri = 0;

    siteuri = baza_date(siteuri, &nr_siteuri);
    
    for(int i = 0; i < nr_siteuri; i++)
        printf("%s %d %s\n", siteuri[i].url, siteuri[i].accesari, siteuri[i].titlu);

    for(int i = 0; i < nr_siteuri; i++)
        free(siteuri[i].paragraf);
    free(siteuri); 
}