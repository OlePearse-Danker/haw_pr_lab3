// Praktikumsaufgbabe 3
// Lottozahlen
// Autor: Ole Pearse-Danker
// Datum: 03/11/2022
// Version: 1.0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Prototypes -> Deklaration
short get_short(char text[], short, short); //get_short -> lower snake case 
void print_array(short[], short); // helper function to print the array

int main ()
{   
   //clear system for better UX
    system("clear");


    // Declare constants
    const short MIN = 1;
    const short MAX = 49;


    // Array length
    const int NUMBER_COUNT = 6;

    // Declare array of 6 int
    // Initialize array
    short user_numbers[NUMBER_COUNT] = { 0 };
    short winning_numbers[NUMBER_COUNT] = { 0 };

    // User Interface
    printf("----------------------------------------\n");
    printf("    Willkommen beim Lotto! (6 aus 49)\n");
    printf("Geben Sie beliebige ganze Zahlen zwischen 6 und 49 ein\n");
    printf("----------------------------------------\n");

//----------------------
//Aufgabe 4
//Lottozahlen tippen
//---------------------

  for (int i = 0; i < NUMBER_COUNT; i++)
    {
        user_numbers[i] = get_short("Geben Sie eine Zahl ein: ", MIN, MAX);
    }

    // Print array to console
    printf("--------------------------------\n");
    printf("Sie haben folgende Zahlen getippt:\n");
    print_array(user_numbers, NUMBER_COUNT); // -> NUMBER COUNT ist die Länge des Arrays
    printf("--------------------------------");


//--------------------
// Aufgabe 5
// Random Lottozahlen ziehen 
//--------------------


   printf("\n"); 
   printf("Die heutigen Lottozahlen sind: ");
   srand(time(NULL) ); // Gibt die aktuelle Zeit zurück, weil diese IMMER unterschiedlich ist, wenn das Programm zu unterschiedlichen Zeiten gestartet wird 
                        //NULL -> Konstante mit dem Wert 0 /oder Wert von einem Pointer der nirgends hinzeigt -> wenn die Zahl einen Wert hätte, wären die Zanlen nicht random
                        // srand kann man auch einen konstanten Wert geben, um die Ausgabe der Gewinnquote zu testen -> Zahlen merken die er ausgibt und bei erneutem Durchlauf wieder eingeben -> so kann man die verschiedenen cases testen

   int random_number; // Variable to store the numbers
   bool unique; // keeps track of wether the numbers we've just generated are unique

   for (int i = 0; i < NUMBER_COUNT; i++)
   {

        do 
        
        {
            random_number = (rand () % 49) + 1;// gibt  immer eine Zahl die in der Range von 0-48 liegt zurück; mit der +1 in der Range von 1-49
            unique = true;
            for (int j = 0; j < i; j++) // j ist less than i, because i keeps track of the amount of numbers we've made so far
            if (winning_numbers[j] == random_number) unique = false; // if we can find a number in the array of numbers we've already generated, we know it's not unique


        } while (!unique); //keep generating random number until number is unique -> as long as the number is not unique, keep generating
        winning_numbers[i] = random_number; // once we have found a number that is unique -> we can add it to the numbers array
        //printf("Zahl %d: %d\n", i+1, number);

   }

    printf("\n");
    print_array(winning_numbers, NUMBER_COUNT);
    printf("--------------------------------\n");


//----------------------------
//Aufgabe 6
// Anzahl der richtigen bestimmen
//----------------------------    

short correct_numbers = 0;

    for (int i = 0; i < NUMBER_COUNT; i++)
    {
        for ( int j = 0; j < NUMBER_COUNT; j++)
        {
            if (user_numbers[i] == winning_numbers[j]) 
            {
                correct_numbers++;
            }
        }
    }


    if (correct_numbers == 0)
    
    {
        printf("Sie haben heute leider kein Glück gehabt. (0 Zahlen richtig)\n");
        printf("--------------------------------\n");
    }
    else
    {
    printf("Sie haben %d Zahl(en) richtig getippt!\n", correct_numbers);
    printf("--------------------------------\n");
    }
   
//----------------------------
//Aufgabe 7
//Ausgabe des Gewinns
//----------------------------    

switch (correct_numbers)
{
    case 2: printf ("Sie haben 5€ gewonnen! Glückwunsch!\n");
    break;                                          //break beendet den case, sonst würde jeder case ausgeführt werden
    case 3: printf ("Sie haben 50€ gewonnen! Glückwunsch!\n");
    break;
    case 4: printf ("Sie haben 1,000€ gewonnen! Glückwunsch!\n");
    break;
    case 5: printf ("Sie haben 50,000€ gewonnen! Glückwunsch!\n");
    break;
    case 6: printf ("Sie haben 1,000,000€ gewonnen! Glückwunsch!\n");
    break;
    default: printf("Dafür gibt es leider kein Geld.\n");  //wenn kein Case zutrifft (keine Zahl richtig getippt), wird default ausgeführt
             printf("--------------------------------\n");
}

   return 0;
}

//Definition der Funktion get_short 
short get_short(char text[],short min, short max) // "text[]" ist ein string mit einem array oder auch Zeichenkette mit array genannt; Semikolon nur bei Statements z.B "Führe x aus", sonst Kommata
{   
    //declare working variables 
    short value;
    int finished = 0; //0 für FALSE
    char ch;
    int retVal;


    do
        {   // get user input 

            printf("%s: ", text); //Abkürzung "s" für "string"  / Zeichenkette
            ch = '\0'; // \0 wird als ein Buchstabe gewertet; O ist nicht die Zahl 0 sondern ein "Null Character"; Null Character hat in der Ascii Tabelle auch den Wert 0
            retVal = scanf("%hd%c", &value, &ch); // -> "hd" steht für short -> Adresse ist "Value"; scanf gibt auch einen Wert zurück, diesen speichern wir in retVal 

            // check for valid user input
            if (retVal != 2) printf("Das war keine korrekte Zahl!\n");
            else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");
            else if (value < min) printf("Zahl ist nicht im erlaubten Intervall (1-49)\n");
            else if (value > max) printf("Zahl ist nicht im erlaubten Intervall(1-49)\n");
            else finished = 1;   // Keiner der oberen Fälle trifft zu (alles richtig), also Schleife wird nicht wieder wiederholt, sondern man löscht den Input stream buffer für eine weitere Eingabe
        
        
            //clear input stream buffer
            while (ch != '\n') scanf("%c", &ch); //Variation mit scanf von getchar

        } while (!finished); //repeat if not finished 

//return user input
return value; //wer auch immer die Funktion get_short aufruft bekommt "value" zurück
}

//Definition der Funktion print_array
// helper function to print array inline
void print_array(short array[], short arr_len)
{
    for (int i = 0; i < arr_len; i++)
    {
        printf("%3hd", array[i]);
    }

    printf("\n");

    return;
}


