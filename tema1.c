#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define K1 5  //K1 - k folosit pentru functiile e1, e2, e3
#define K2 3  //K2 - k folosit pentru functia c

//structura unui nod
typedef struct nod
{
    double value;
    int timestamp;
    struct nod* next;
    struct nod* prev;
} Nod;

//functie ce initializeaza o lista cu timestamp-ul si valoarea primite ca parametri
Nod* initList (int timestamp, double value)
{
    Nod* l =(Nod*)malloc(sizeof(struct nod));
    l->timestamp = timestamp;
    l->value = value;
    l->next = NULL;
    l->prev = NULL;
    return l;
}

//functie ce adauga un nod la finalul listei l cu timestamp-ul si valoarea primite ca parametru
Nod* addLast (Nod* l, int timestamp, double value)
{
    if (l == NULL)
        return initList(timestamp, value);
    Nod* curr = l;
    Nod* nou = initList(timestamp, value);
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = nou;
    nou->prev = curr;
    //nou->next = NULL;
    return l;
}

//functie de sterge urmatorul element din lista l data ca parametru
Nod* deleteItem(Nod* l, int timestamp, double value)
{
    Nod* toDel = l->next;
    if(toDel != NULL)
    {
        l->next = toDel->next;
        if(toDel->next != NULL)
        {
            toDel->next->prev = l;
        }
        free(toDel);
    }
    return l;
}

//functie ce afiseaza lista l primita ca parametru
void printList (Nod* l)
{
    Nod* curr = l;
    while (curr != NULL)
    {
        printf ("%d %.2lf\n", curr->timestamp, curr->value);
        curr = curr->next;
    }
}

//functie ce sterge complet o lista l primita ca parametru
Nod* freeList (Nod* l) 
{ 
   Nod* curr = l; 
   Nod* q; 
   while (curr != NULL)  
   { 
       q = curr->next; 
       free (curr); 
       curr = q; 
   } 
   l = NULL;
   return l; 
}

//functie de interschimbare a valorilor capetelor de lista primite ca parametru
void swap(Nod* l1, Nod* l2)
{
    double temp;
    temp = l1->value;
    l1->value = l2->value;
    l2->value = temp;
}

//functia de sortare Bubble Sort a listei l primita ca parametru
Nod* bubbleSort(Nod* l)
{
    int ok = 1;
    Nod* curr = l;
    Nod* last = NULL;
    do
    {
        ok = 0;
        curr = l;
        while (curr->next != last)
        {
            if (curr->value > curr->next->value)
            {
                swap (curr, curr->next);
                ok = 1;
            }
            curr = curr->next;
        }
        last = curr;
    }
    while (ok == 1);
    return l;
}

//functie de adaugare a unui nod cu timestamp-ul si valoarea date ca parametri pe pozitia pos a listei l
Nod* addItem(Nod* l, int pos, int timestamp, double value)
{
    Nod* curr = l;
    int count = 0;
    while(curr->next != NULL && count != pos-1)
    {
        curr = curr->next;
        count ++;
    }
    Nod* nou = initList(timestamp, value);
    nou->next = curr->next;
    nou->prev = curr;
    curr->next->prev = nou;
    curr->next = nou;
    return l;
}

//functia de eliminare de exceptii folosind metode statistice ce primeste ca parametri capul listei l si un numar de noduri din aceasta
Nod* e1 (Nod* l, int* n)
{
    int i = 0;
    double average = 0, deviation = 0, sum = 0;
    Nod* curr = l;
    for (i = 0; i < (int)(K1 / 2); i ++)
        curr = curr->next;
    Nod* fereastraCurr = curr; //lista auxiliara cu care ne vom deplasa in fereastra
    Nod* toDel = NULL; //lista ce va contine elementele de sters
    while (curr->next->next != NULL)
    {
        sum = 0;
        fereastraCurr = curr->prev->prev;
        //utilizarea unei bucle for pentru calculul lui sumei auxiliare sum
        for (i = 0; i < K1; i ++)
        {
            sum = sum + fereastraCurr->value;
            fereastraCurr = fereastraCurr->next;
        }
        average = sum / K1; //valoarea lui average pentru fereastra curenta
        sum = 0;
        fereastraCurr = curr->prev->prev;
        //utilizarea unei bucle for pentru calculul lui sumei auxiliare sum
        for (i = 0; i < K1; i ++)
        {
            sum = sum + (fereastraCurr->value - average) * (fereastraCurr->value - average);
            fereastraCurr = fereastraCurr->next;
        }
        deviation = sqrt(sum / K1); //valoarea deviatiei pentru fereastra curenta
        //se verifica daca valoarea curenta se afla in intervalul dat si se adauga in lista toDel in caz afirmativ
        if (curr->value < (average - deviation) || curr->value > (average + deviation))
        {
            if (toDel == NULL)
            {
                toDel = initList(curr->timestamp, curr->value);
                (*n)--;
            }
            else
            {
                toDel = addLast(toDel, curr->timestamp, curr->value);
                (*n)--;
            }
        }
        curr = curr->next;
    }
    curr = l->next;
    Nod* toDelCopy = toDel; //copie a listei toDel
    //parcurgerea listelor curr si toDel in paralel si stergerea valorilor din lista curenta
    while (toDel != NULL)
    {
        if (curr->next->value == toDel->value)
        {
            curr = deleteItem (curr, curr->timestamp, curr->value);
            toDel = toDel->next;
        }
        else
            curr = curr->next;
    }
    toDelCopy = freeList(toDelCopy); //stergerea copiei listei toDelCopy
    fereastraCurr = freeList(fereastraCurr); //stergerea copiei listei fereastraCurr
    return l;
}

//functie de eliminare de zgomot folosind filtrarea mediana ce intoarce o lista auxiliara mediana
Nod* e2 (Nod* l, int* n)
{
    int i = 0;
    (*n) = 0;
    Nod* curr = l;
    Nod* fereastra = NULL;
    Nod* fereastraCurr;
    Nod* mediana = NULL; //lista in care vom pune valorile mediane
    curr = curr->next->next;
    while (curr->next->next != NULL)
    {
        fereastraCurr = curr->prev->prev;
        //initializare fereastra
        for (i = 0; i < K1 - 1; i ++)
        {
            if(fereastra != NULL)
            {
                fereastra = addLast(fereastra, fereastraCurr->timestamp, fereastraCurr->value);
                fereastraCurr = fereastraCurr->next;
            }
            else
            {
                fereastra = initList(fereastraCurr->timestamp, fereastraCurr->value);
                fereastraCurr = fereastraCurr->next;
            }
        }
        fereastra = addLast(fereastra, fereastraCurr->timestamp, fereastraCurr->value);
        fereastra = bubbleSort(fereastra); //sortare fereastra
        //adaugarea valorii din mijlocul ferestrei in lista mediana
        if (mediana != NULL)
        {
            mediana = addLast(mediana, fereastra->next->next->timestamp, fereastra->next->next->value);
            (*n) ++;
        }
        else
        {
            mediana = initList(fereastra->next->next->timestamp, fereastra->next->next->value);
            (*n) ++;
        }
        fereastra = freeList(fereastra); //stergerea ferestrei curente
        curr = curr->next;
    }
    l = freeList(l); //stergerea completa a listei l
    return mediana;
}

//functie de eliminare de zgomot folosind filtrare utilizand media aritmetica ce intoarce o lista media
Nod* e3 (Nod* l, int* n)
{
    int i = 0;
    double average = 0, sum = 0;
    (*n) = 0;
    Nod* media = NULL; //lista ce va fi intoarsa de catre functie
    Nod* curr = l->next->next;
    Nod* fereastraCurr = curr;
    while (curr->next->next != NULL)
    {
        sum = 0;
        fereastraCurr = curr->prev->prev;
        //utilizarea unei bucle for pentru calculul lui sumei auxiliare sum
        for (i = 0; i < K1; i ++)
        {
            sum = sum + fereastraCurr->value;
            fereastraCurr = fereastraCurr->next;
        }
        average = sum / K1; //media aritmetica a nodurilor din fereastra
        fereastraCurr = curr->prev->prev;
        //contruirea listei media
        if (media != NULL)
        {
            media = addLast(media, curr->timestamp, average);
            (*n) ++;
        }
        else
        {
            media = initList(curr->timestamp, average);
            (*n) ++;
        }
        curr = curr->next;
    }
    l = freeList(l); //stergerea completa a listei l
    return media;
}

//functie de uniformizare a frecventei in timp a datelor
Nod* u (Nod* l, int* n)
{
    Nod* curr = l;
    while (curr->next != NULL)
    {
        //verificam daca diferenta dintre noduri se afla in intervalul [100, 1000]
        if ((curr->next->timestamp - curr->timestamp) >= 100 && (curr->next->timestamp - curr->timestamp) <= 1000)
        {
            //adaugarea unui nod nod cu timestamp egal cu media aritmetica a timestamp-urilor si cu valoare egala cu media aritmetica a timestamp-urilor
            curr = addItem(curr, 1, (curr->timestamp + curr->next->timestamp) / 2, (curr->value + curr->next->value) / 2);
            curr = curr->next;
            //stergerea elementului vechi din lista
            if(curr->next->next != NULL)
                curr = deleteItem(curr, curr->next->timestamp, curr->next->value);
            else
            {
                Nod* toDel = curr->next;
                curr->next = NULL;
                free(toDel);
            }
        }
        else
            curr = curr->next;
    }
    return l;
}

//functie de calcul a valorii w in functie de i
double w (double i)
{
    double val = 0, sum = 0, j = 0;
    for (j = 0; j < K2; j ++)
        sum = sum + (j / (K2 - 1)) * (j / (K2 - 1)) * 0.9 + 0.1;
    val = ((i / (K2 - 1)) * (i / (K2 - 1)) * 0.9 + 0.1) / sum;
    return val;
}

//functie de completare a datelor
Nod* c (Nod* l, int* n)
{
    int time = 0, i = 0;
    double C = 0, sumLeft = 0, sumRight = 0, f = 0;
    Nod* left = l->next->next;
    Nod* right = left->next;
    Nod* leftCurr = left;
    Nod* rightCurr = right;
    Nod* toAdd; //lista cu valorile ce se vor adauga
    while (right->next->next != NULL)
    {
        //verificare daca diferenta dintre timestamp-uri este mai mare decat 1000
        if (right->timestamp - left->timestamp >= 1000)
        {
            time = left->timestamp + 200; //initializarea noului timestamp ce va fi adaugat
            leftCurr = left;
            rightCurr = right;
            toAdd = left; //initializarea listei toAdd cu valoarea din stanga
            while (time < right->timestamp)
            {
                sumLeft = 0;
                sumRight = 0;
                C = (double)(time - left->timestamp) / (double)(right->timestamp - left->timestamp);
                for (i = K2 - 1; i >= 0; i --)
                {
                    sumLeft = sumLeft + leftCurr->value * w(i);
                    leftCurr = leftCurr->prev;
                }
                for (i = K2 - 1; i >= 0; i --)
                {
                    sumRight = sumRight + rightCurr->value * w(i);
                    rightCurr = rightCurr->next;
                }
                f = (1 - C) * sumLeft + C * sumRight; //calcularea valorii f folosindu-se sumele auxiliare sumLeft si sumRight
                toAdd = addItem(toAdd, 1, time, f); //adaugarea unei noi valori
                toAdd = toAdd->next;
                time = time + 200; //noul timestamp
                leftCurr = left;
                rightCurr = right;
                (*n) ++;
            }
            left = right;
            right = right->next;
        }
        else
        {
            left = right;
            right = right->next;
        }
    }
    return l;
}

//functie ce afiseaza statistici: cate valori ale nodurilor se afle in diferite intervale de lungime delta, primit ca parametru
void st (Nod* l, int delta)
{
    Nod* sorted = bubbleSort(l); //lista ce va avea valorile din l, in ordine crescatoare
    int startVal = 0, count = 0;
    //initializarea primului cap de interval
    if (sorted->value < 0)
        startVal = (int) sorted->value - 1;
    else
        startVal = (int) sorted->value;
    while (sorted != NULL)
    {
        //numararea nodurilor din intervalul [startVal, startVal + delta]
        if (sorted->value >= startVal && sorted->value < startVal + delta)
        {
            count ++;
            sorted = sorted->next;
        }
        else
        {
            //afisarea numarului de elemente din interval daca acesta este diferit de 0
            if (count != 0)
                printf ("[%d, %d] %d\n", startVal, startVal + delta, count);
            count = 0; //reinitializarea numaratorului
            startVal = startVal + delta; //reinitializarea valorii de start
        }
    }
    printf ("[%d, %d] %d\n", startVal, startVal + delta, count); //afisarea ultimului interval
    sorted = freeList(sorted); //stergerea completa a listei sorted
    l = freeList(l); //stergerea completa a listei l
    return;
}

//functie de extragere a unui numar dintr-un sir primit ca parametru
int extract (char *s)
{
    int n = 0, i = 0;
    for (i = 0; i < strlen(s); i++)
        if(*(s + i) >= '0' && *(s + i) <= '9')
            n = n * 10 + *(s + i) - '0';
    return n;
}

int main (int argc, char *argv[])
{
    int n = 0, i = 0, timestamp = 0, delta = 0;
    double value = 0;
    scanf("%d", &n); //citirea numarului de noduri
    scanf("%d%lf", &timestamp, &value); //citirea primului nod
    Nod* l = initList(timestamp, value); //initializarea primului element al listei
    //citirea si initializarea celorlalte valori din lista
    for (i = 1; i < n; i ++)
    {
        scanf("%d%lf",&timestamp, &value);
        l = addLast(l, timestamp, value);
    }
    //compararea cu argumentele in linia de comanda si executarea funtiilor respective acestora
    for (i = 1; i < argc; i ++)
    {
        if (strcmp (argv[i], "--e1") == 0)
            l = e1(l, &n);
        if (strcmp (argv[i], "--e2") == 0)
            l = e2(l, &n);
        if (strcmp (argv[i], "--e3") == 0)
            l = e3(l, &n);
        if (strcmp (argv[i], "--u") == 0)
            l = u(l, &n);
        if (strcmp (argv[i], "--c") == 0)
            l = c(l, &n);
        if (strstr(argv[i], "--st") != NULL)
        {
            delta = extract(argv[i]);
            st(l, delta);
            return 0;
        }
    }
    printf("%d\n", n); //afisarea numarului de noduri din output
    printList(l); //afisarea listei finale
    l = freeList(l); //stergerea completa a listei
    return 0;
}