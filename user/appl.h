/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Application class defines the (only) application for OOStuBS.         */
/*****************************************************************************/
//Großteil des Codes basierend auf https://github.com/LikeAnShadow/oostubs_changed/tree/master


#ifndef __application_include__ //ueberprueft, ob das Makro __application_include__ noch nicht definiert ist. Wenn es nicht definiert ist, geht der Präprozessor in den folgenden Codeblock
#define __application_include__ //Makro wird definiert Makro ==> Sequenz von Anweisungen/Ausdrücken, die vor dem Kompilieren durch den Präprozessor ersetzt wird

#define BUFFERSIZE 2048

#include "syscall/thread.h"

class Application : public Thread
{
private:
	Application(const Application &copy); //Kopierkonstruktor: nimmt ein Objekt von Application als Parameter und erstellt ein neues Objekt , das eine Kopie des übergebenen Objekts ist
	//int i = 0;
	void commandParser (char* buffer); //Interpretiert die Eingaben in der Shell
	char buffer[BUFFERSIZE];
	unsigned int argc; //argument count, wie in stdlib
	char argv[8][16]; // argument vector, nicht wie in stdlib, 2 dimensionales Array, 8 Zeilen à 15 Zeichen plus Nullzeichen \0
	int row; //Zeile
	int bufferpos = 0; //Index des Buffers
	int x,y; //Position auf Bildschirm?
	bool printshell = true; //soll am Zeilenbeginn Information zur Shell geprinted werden?
public:
	//Application(const Application &copy) = delete; // prevent copying
	Application(void *tos, int row) : Thread(tos), row(row) {} //Konstruktor der Klasse Application mit Initialisierungsliste
	// Thread (tos) ruft Konstruktor der Basis-/Vaterklasse (Thread) auf und übergibt Zeiger auf Top of Stack (tos, oberes Ende des untypisierten Speicherstapels) als Argument
	//row(row): Initialisiert das Member row mit dem Wert des Parameters row
	void action();

};

void checkForSpaces(char* buffer, unsigned int* argc, char (* argv)[16]); //Pruefung auf Leerzeichen

#endif //Schließt den Codeblock ab. Wenn das Header-File an anderer Stelle im Programm wieder eingefügt wird, wird der Code innerhalb des #ifndef-Blocks übersprungen, weil __application_include__ bereits definiert ist
