Task 1.1: Parcurg fiecare pas cu o fereastra de 5 elemente. Pentru fiecare calculez o suma auxiliara,
pe care o voi folosi la calcularea mediei si a deviatiei. Verific daca valoarea curenta
se afla in intervalul [average - deviation, average + deviation] si adaug in lista toDel elementul respectiv.
Dupa ce parcurg fiecare lista, reinitializez lista curr pe care o voi folosi sa parcurg element cu element
pentru a verifica daca elementul se afla si in lista toDel.
In caz afirmativ, sterg nodul din lista curr. Folosesc o copie a listei toDel pentru a sterge toate elementele,
apoi intorc lista finala.

Task 1.2.1: Voi folosi o lista mediana vida initial pe care o voi intoarce la final.
Initializez fereastra in care voi lucra, iar apoi sortez toate valorile din aceasta.
Adaug in lista mediana valoarea din centrul ferestrei sortate crescator.
Dupa ce parurg toate ferestrele posibile, sterg complet lista initiala l si intorc lista mediana.

Task 1.2.2: Voi folosi o lista media vida initial pe care o voi intoarce la final.
Calculez o suma auxiliara pentru fereastra curenta pe care o voi folosi in calculul mediei.
Valoarea obtinuta va fi adaugata in lista media.
La finalul parcurgerii ferestrelor se elibereaza memoria ocupata de lista l si se intoarce lista media.

Task 1.3: Se verifica daca diferenta dintre doua noduri consecutive este mai mica decat o secunda.
In caz afirmativ, se adauga in lista un nod intre cele doua ce are timestamp-ul egal cu media aritmetica a celor doua timestamp-uri
si valoarea egala cu media aritmetica a celor doua valori.
Apoi, se sterge elementul nodul urmator valorii adaugate.
Se repeta procesul pana la finalizarea listei si se intoarce noua lista modificata.

Task 1.4: Voi folosi o lista toAdd in care voi pune noile valori ce vor fi adaugate.
Pentru fiecare diferenta dintre doua timestamp-uri mai mare decat 1000,
se vor adauga noduri noi.
Cat timp nu se ajunge la valoarea din dreapta, se vor initializa noi timestamp-uri si valori ale nodului
dupa formula lui f, apoi se va trece la urmatoarele doua noduri.
La final, se afiseaza lista modificata.

Task 1.5: Se va pune intr-o alta lista sorted, lista l sortata cu ajutorul functiei bubbleSort.
Se initializeaza primul cap de interval in functie de cea mai mica valoare.
Apoi, se numara si se afiseaza cate numere sunt in intervalul [startVal, startVal + delta].
Dupa aceea, se modifica capul inferior al intervalului, adaugandu-se valoarea lui delta.
La final, se sterg complet listele sorted si l.