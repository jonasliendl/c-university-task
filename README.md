# c-university-task
Task in operating systems lesson programmed in C.

## Task Description
In dieser Arbeit betrachtet man eine große Menge der Daten (z.B. die ganzen Zahlen), die aufsteigend sortiert
werden soll. Zwei Programme sind notwendig: das eine sortiert die Daten sequenziell, das andere ― parallel. Die
dafür benötigten Zeiten werden in log-Dateien protokolliert. Die Daten (etwa 10 000 000 ganze Zahlen) werden in
beiden Programmen gleicherweise vorbereitet (z.B. mittels Zufallsgenerators rand() oder eines anderen
Programms). Ein Sortieralgorithmus kann von den Studierenden selbst ausgewählt und implementiert werden, aber
er gilt für beide Programme. In dem sequenziellen Programm wird die ganze Datenmenge auf einmal sortiert. In
dem parallelen Programm wird diese Datenmenge in mehreren Teilmengen zerteilt. Jede Teilmenge wird von einem
Thread sortiert (die Anzahl Teilmengen ist gleich der Anzahl der Threads). Die schon sortierten Teilmengen werden
vom Haupt-Thread zusammengeführt so, dass Ergebnis auch sortiert wird.


### Requirements:
---
</br> 


- Die Datenmenge und die Teilmengen müssen als doppelt verkettete lineare Listen implementiert werden. 
- Die beiden Zeiger im Knoten, vorwärts und zurück, müssen gepflegt werden [2]. 
- Die beiden Programme (sequenzielles und paralleles) haben jeweils eine eigene log-Dateien. 
- Sequenzielles Programm protokolliert die Anzahl der Knoten und die Dauer der Sortierung
- Jeder Thread im parallelen Programm protokolliert außerdem die Nummer des eigenen Threads
- Die Threads müssen einen Mutex beim Schreiben in die Datei verwenden. 
- Der Haupt-Thread im parallelen Programm protokolliert die Anzahl der Knoten und gesamte Dauer der Sortierung (inkl. die Sortierung der Teilmengen). 
- Der Name der log-Datei sowie die Anzahl der Threads müssen im Programm als Präprozessorvariablen festgelegt werden.
- Die beiden Anwendungen sollten nach dem Schema aus Übungen aufgebaut werden: jeweils eine makefileDatei, Header-Dateien, Dateien  mit main()-Funktionen und eine Datei mit gemeinsamen Funktionen
- Die makefile-Dateien für beide Anwendungen müssen von Studenten selbst geschrieben werden (keine Standard-makefile!), die Befehle make, make run und make clean müssen funktionieren
- Diese Dateien können z.B. seq.make und par.make heißen


</br> 

#### Header-Dateien:
---
- Header-Datei <strong>com.h</strong> ist für die Daten gedacht, die sowohl im sequenziellen als auch im parallelen Programm gemeinsam verwendet werden. Hier müssen alle notwendigen include stehen, globalen
Konstanten und/oder globalen Variablen, Preprozessorvariablen, Datentypen, Prototypen.
- Header-Datei <strong>seq.h</strong> wird für sequenzielles Programm gedacht, hier stehen Inklusion der gemeinsamen HeaderDatei und die Daten, die im sequenziellen Programm verwendet werden, z.B. der Name der logDatei
- Header-Datei <strong>par.h</strong> wird für paralleles Programm gedacht, hier stehen Inklusion der gemeinsamen HeaderDatei und die Daten, die im parallelen

### Summary of Functions
---
</br>

- **Sort()**  
  Sorts the list using its starting address as a parameter, with no return value. Updates the list in place.

- **Gen()**  
  Generates a doubly linked list with a specified number of integer nodes, using `Reserve()` for memory allocation. Returns the starting address of the list.

- **Reserve()**  
  Allocates memory for a node, initializes it with a random integer, and returns the node's address.

- **ListOut()**  
  Displays the entire list or a specified range of nodes. Takes the list's starting address and optional start/end nodes as parameters. If the range is invalid, outputs the whole list without error.

- **ListFree()**  
  Frees memory for all nodes in the list. Takes the list’s starting address as a parameter with no return value.

- **main() (Sequential)**  
  Calls `Gen()` to create the list, records start time, calls `Sort()`, and records end time. Logs these details and frees the list with `ListFree()`.

- **main() (Parallel)**  
  Creates the list with `Gen()`, splits it among threads, and calls `ThrdFunc()` in each thread. After threads finish, merges sorted sublists and logs the process time. Frees the list with `ListFree()`.

- **ThrdFunc()**  
  Executes within each thread. Records start time, calls `Sort()` on its sublist, records end time, and logs timing details.

</br></br>


**Wichtig** Schleifen & Steuerungskonstruktionen strukturiert (z.B. keinen return oder exit aus Schleifen oder Auswahl-Konstruktionen), sonst werden einige Punkte verloren gehen!

### Notizen: 
Zahl erzeugen </br>
Prüfprogramm, dass die Zahl überprüft (freiwillig) 
Threadanzahl anpassbar  

