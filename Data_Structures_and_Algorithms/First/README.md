# **MOD DE IMPLEMENTARE**

### HEADER => functii.h

> constituie rezolvara taskului 1. FORMATUL DATELOR;
> conține structurile **node** pentru nod și **list** pentru listă, precum și antetele funcțiilor necesare pentru rezolvarea temei;**
> structurile și funcțiile corespunzătoare modificărilor unei liste sunt:
```c#
    init_node(int timestamp, double value);
    init_list();
    free_node(NODE *node);
    destroy_list(LIST *list);
    print_list(LIST *list);
    insert_node(LIST *list, int timestamp, double value, int position);
    insert_sorted(LIST *list, int timestamp, double value);
    remove_node(LIST *list, int position);
```

### 2.1 ELIMINARE DE EXCEPȚII FOLOSIND METODE STATISTICE

> în cadrul acestui task, am folosit următoarele funcții:
```c#
    - average(NODE *node);
    - deviation(NODE *node);
    - elimination(LIST *list);
```
> funcțiile **average** și **deviation** calculează media și deviația standard a elementelor din fereastră după formulele din cerință;*
> funcția **elimination** returnează o nouă listă pornind ce le cea inițială, în care se inserează nodurile care se află în intervalul din cerință;

### 2.2.1 FILTRARE MEDIANĂ

> în cadrul acestui task, am folosit funcția **mediana**(LIST *list); 
> această funcție primește ca parametru lista inițială și returnează noua listă creată în urma sortării ferestrei, rezultând la realizearea filtrării prin intermediul medianei

### 2.2.2 FILTRARE FOLOSIND MEDIA ARITMETICĂ

> în cadrul acestui task, am folosit funcția **media_aritmetica**(LIST *list);
> această funcție primește ca parametru lista inițială și returnează noua listă creată prin selectarea ferestrelor de 5 elemente și inserarea nodurilor cu noua valoare reprezentată de media aritmetică a elementelor din fereastră;

### 2.3 UNIFORMIZAREA FRECVENȚEI ÎN TIMP A DATELOR

> în cadrul acestui task, am folosit funcția **uniformizare**(LIST *list);
> această funcție primește ca parametru lista inițială și returnează aceeași listă modificată prin schimbarea timestamp-ului și valorii nodului curent conform formulelor din cerință, în cazul în care diferența de timestamp dintre oricare două noduri este între 100 și 1000;

### 2.4 COMPLETAREA DATELOR

> în cadrul acestui task, am folosit funcțiile:
```c#
    - data_completion(LIST *list);
    - w(int i, int k);
    - f(NODE *left, NODE *right, double C);
```
> funcția **data_completion** primește ca parametru lista inițială și returnează aceeași listă modificată prin adăugarea unor noi noduri între aclealea care au diferența între timestamp-uri mai mare de 1000;
> funcția **w** primește ca parametrii două valori întregi și returnează coeficientul care scade influența valorilor, pe măsură ce ne îndepărtăm de interval, pe baza formulei din cerință;
> funcția **f** calculează valoarea atribuită nodului cu timestamp-ul căutat, primind ca parametrii:
    - **left** = nodul cel mai apropiat de centru, aflat în marginea stângă a listei;
    - **right** = nodul cel mai apropiat de centru, aflat în marginea dreaptă a listei;
    - **C** = raportul dintre diferenta timestamp-urilor nodurilor curent și **left** și diferența timestamp-urilor nodurilor **right** și **left**;
    
### 2.5 STATISTICI

> în cadrul acestui task, am folosit funcția **statistics**(LIST *list, int frequency);
> această funcție primește ca parametru lista inițială și calculează de câte ori apare un nod într-un interval, afișând la final intervalele sortate după marginea inferioară și numărul de elemente regăsite în acel interval;

### MAIN

> funcția **main** primește în linia de comandă argumente corespunzătoare fiecărui task al temei, urmând să se apeleze functiile necesare rezolvării task-urilor respective, în functie de ce nume de cod s-a introdus la tastatură:
- "--e1" => ELIMINARE DE EXCEPȚII FOLOSIND METODE STATISTICE
- "--e2" => FILTRARE MEDIANĂ
- "--e3" => FILTRARE FOLOSIND MEDIA ARITMETICĂ
- "--u" => UNIFORMIZAREA FRECVENȚEI ÎN TIMP A DATELOR
- "--c" => COMPLSTATISTICIETAREA DATELOR
- "st" => STATISTICI