# Turing-Machine

Implementarea porneste de la structura Band prin intermediul careia se pot
accesa lista dublu inlantuita cu santinela, ale carei noduri arata valorile
de pe banda, si pozitia degetului (simbolul curent). De asemenea, pentru
retinerea operatiilor am utilizat o coada declarata sub forma unei liste
simplu inlantuite, iar pentru realizarea operatiilor de undo si redo am folosit
doua stive, tot de forma unei liste simplu inlantuite.

Pornind de la aceste structuri si de la operatiile clasice cu acestea am definit
cate o functie pentru realizarea fiecarei instructiuni, cu exceptia intsructiunii
"EXECUTE", a carei utilizare este implementata in functia "main".

## Descrierea functiilor:
1. MOVE_LEFT: se verifica intai daca pozita curenta a degetului corespunde cu
prima pozitie din banda. In caz afirmativ, inseamna ca nu exista o pozitie
disponibila mai la stanga, prin urmare mutarea nu se poate realiza. In caz
contrar, pozitia degetului se actualizeaza corespunzator.
2. MOVE_RIGHT: se verifica daca pozitia curenta a degetului este pe ultimul
element din banda. In acest caz, se realizeaza inserarea la final a
caracterului "#", prin crearea unui nou nod, atribuirea pozitiei aferente si
actualizarea corespunzatoare a legaturilor. Altfel, se actualizeaza pozitia
degetului.
3. MOVE_LEFT_CHAR: initial se verifica daca pe pozitia degetului se regaseste
valoarea dorita. Astfel, in aceasta circumstanta, nu se va modifica nimic. Se
incepe apoi cautarea elementului dorit. Daca acesta a fost intalnit, se
actualizeaza pozitia degetului, iar in caz negativ se afiseaza mesajul aferent.
4. MOVE_RIGHT_CHAR: initial se verifica daca pe pozitia degetului se regaseste
valoarea dorita. Astfel, in aceasta circumstanta, nu va modifica nimic. Se
incepe apoi cautarea elementului dorit. Daca acesta a fost intalnit, se
actualizeaza pozitia degetului, iar in caz negativ se insereaza caracterul "#"
la final.
5. WRITE: se actualizeaza valoarea de la pozitia degetului.
6. INSERT_LEFT: asemanator cu functia "MOVE_LEFT", se verifica intai daca
pozita curenta a degetului corespunde cu prima pozitie din banda. In caz
afirmativ, se afiseaza mesajul aferent, altfel, se realizeaza o inserare in
interior, la stanga degetului, prin crearea unui nod, atribuirea pozitiei
corecte, refacerea legaturilor, precum si actualizarea pozitiilor elementelor
ce succed nodul nou inserat.
7. INSERT_RIGHT: mai intai se verifica daca degetul se afla pe ultima pozitie
disponibila. Atunci se va realiza o inserare la final, altfel inserarea se va
face in interiorul benzii, asemanator ca in functia "INSERT_LEFT".
8. SHOW_CURRENT: se afiseaza in fisier valoarea de la pozitia degetului.
9. SHOW: se realizeaza parcurgerea iterativa a benzii si afisarea valorilor,
tinand cont de evidentierea valorii de pe pozitia degetului.
10. UNDO: stiva pentru realizarea operatiei "UNDO" este construita in functia
"main", in aceasta adaugandu-se pozitiile curente din momentul intalnirii uneia
dintre operatiile "MOVE_LEFT" sau "MOVE_RIGHT". La apelarea functiei "UNDO",
se adauga in stiva pentru operatia "REDO" elementul de la pozitia curenta si,
totodata, se actualizeaza varful stivei de undo, eliminandu-se elementul
necesar operatiei.
11. REDO: stiva pentru realizarea operatiei "REDO" este construita in momentul
apelarii functiei "UNDO". Operatia de "REDO" presupune o noua adaugare in stiva
pentru "UNDO", anume a elementului curent, o actualizare a pozitiei degetului
si eliminarea elementului folosit din stiva.
12. MAIN: se realizeaza citirea din fisier a datelor si apelarea functiilor
descrise anterior. In functie de operatia citita se apeleaza functia
corespunzatoare sau, in cazul operatiilor de tip "UPDATE", se actualizeaza
coada de instructiuni, ca mai apoi, la intalnirea operatiei "EXECUTE" sa se
apeleze operatia regasita in varful cozii. Dupa fiecare efectuare a unei
operatii se scade numarul de instructiuni si se elimina din coada operatia
realizata. La final, se inchid fisierele folosite si se elibereaza memoria
alocata.
