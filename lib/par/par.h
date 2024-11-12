#include "../com/com.h"

/*
Diese Funktion führt jeder Thread (außer Haupt-Thread) aus. Sie muss die standardmäßigen
Parameter und Rückgabewert haben, sonst funktioniert sie nicht. Als Parameter bekommt sie die
Anfangsadresse der Liste. Sie merk die Startzeit, ruft die Funktion Sort() auf, übergibt ihr die
Anfangsadresse der Liste. Nach der Sortierung merk sie die Endzeit und schreibt die oben
benannten Daten in die log-Datei
*/
Node* ThrdFunc(Node* head);