#ifndef _siteuri_
#define _siteuri_ 

typedef struct{
    char url[51];
    int octeti;
    int accesari;
    int checksum;
    char titlu[51];
    char *paragraf;
} site;

site* baza_date(site *siteuri, int *nr_siteuri);
void swap (site *unu, site *doi);
int comparator_2(site unu, site doi);
int comparator_3(site unu, site doi);
void sort(site *vector_siteuri, int cate, int (*comparator)(site unu, site doi));
site* filtrare_simpla(site *siteuri, site *vector_siteuri, int nr_siteuri, int *cate);
site* filtrare_simpla2(site *siteuri, site *vector_siteuri, int nr_siteuri, int *cate, char *text);
site* filtrare_avansata(site *siteuri, site *vector_cautare, int nr_siteuri, int *cate);
site* filtrare_avansata2(site *siteuri, site *vector_cautare, int nr_siteuri, int *cate, char *text);

#endif