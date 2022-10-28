# TEMA 3 - GRAFURI

## TASK 1

> acest task constă în găsirea celui mai scurt drum de la depozitele date la 
fiecare magazin din lista de magazine ce trebuie aprovizionate, și înapoi;

> m-am folosit de algoritmul Floyd-Warshall pentru a determina cel mai scurt drum de la un nod la altul
și l-am aplicat de două ori, pentru a determina distanța minimă totală, și dus, și întors;

> la final, am afișat pentru fiecare magazin, nodurile prin care se trece începând cu depozitul dat, 
urmând ca apoi să afișez șî costul total pentru acel drum;

## TASK 2

> acest task constă în determinarea componentelor tare conexe, din care nu au voie să aparțină însă și depozitele;

> m-am folosit de algoritmul Plus-Minus pentru a determina componentele tare conexe ale grafului, 
iar pentru a elimina depozitele din calcul, am transformat în 0 muchiile dintre depozite și celelalte noduri
din cadrul celor două matrici de adiacență utilizate (cea normală și cea transpusă);

> la final, am afișat numărul componentelor conexe, urmat de nodurile din componența fiecăreia;

## TASK 3

> din păcate, n-am reușit să duc la capăt acest task, întrucât mă apucasem de el sâmbată noaptea (adica ieri, 21 mai) 
și n-am apucat să-l termin :))

> PS: am șters încercările de cod pentru acest task, pentru a nu primi erori sau warning-uri.