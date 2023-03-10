#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

short get_short(char text[], short MIN, short MAX);
bool is_unique(int n, int *numbers, size_t count);

int main (int argc, char** argv)
{

    system("clear");

    int number_to_check = 0;
    int unique_numbers[6];

    bool unique;


    for (size_t i = 0; i < 5; i++)
    {
        do
        {
            number_to_check = get_short("Enter a value between 1 and 49", 1, 49);
        } while (!is_unique(number_to_check, unique_numbers, 6));

        unique_numbers[i] = number_to_check;
    }


    // returns current time
    srand(time(NULL));

    int winning_numbers[6];
    int random_number;

    for (size_t i = 0; i < 6; i++)
    {

            do 
            
            {
                random_number = (rand () % 49) + 1;// gibt  immer eine Zahl die in der Range von 0-48 liegt zurück; mit der +1 in der Range von 1-49
                unique = true;
                for (int j = 0; j < 6; j++) // j ist less than i, because i keeps track of the amount of numbers we've made so far
                if (winning_numbers[j] == random_number) unique = false; // if we can find a number in the array of numbers we've already generated, we know it's not unique


            } while (!unique); //keep generating random number until number is unique -> as long as the number is not unique, keep generating
            winning_numbers[i] = random_number; // once we have found a number that is unique -> we can add it to the numbers array
            //printf("Zahl %d: %d\n", i+1, number);

    }

    printf("------------------------\n");
    printf("Todays lotto numbers are\n");
    printf("------------------------\n");

    for ( size_t i = 0; i < 6; i++)
    {
        printf("%d ", winning_numbers[i]);
    }
    printf("\n");


    // compare the user numbers to the winning numbers

    int matches = 0;

    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            if (unique_numbers[i] == winning_numbers[j])
            {
                matches++;
            }
            
        }
    }
    
    printf("You guessed %d numbers correctly!\n", matches);
    
    switch (matches)
    {
    case 1:
        printf("Unfortunately you did not win anything today.\n");
        break;
    case 2:
        printf("You have won 5€!\n");
        break;
    case 3:
        printf("You have won 50€!\n");
        break;
    case 4:
        printf("You have won 1.000€!\n");
        break;
    case 5:
        printf("You have won 50.000€!\n");
        break;
    case 6:
        printf("You have won 1.000.000€!\n");
        break;
    
    default:

        printf("Unfortunately you did not win anything today.\n");
        break;
    }

}

short get_short(char text[], short MIN, short MAX)
{
    //declare working variables 
    short value;
    int finished = 0; //0 f�r FALSE
    char ch;
    int retVal;

    do
    {
        printf("%s: ", text); //Abk�rzung "s" f�r "string" / Zeichenkette

        ch = '\0'; // \0 wird als ein Buchstabe gewertet; O ist nicht die Zahl 0 sondern ein "Null Character"; Null Character hat in der Ascii Tabelle auch den Wert 0

        retVal = scanf("%hd%c", &value, &ch); // -> "hd" steht f�r short -> Adresse ist "Value"; scanf gibt auch einen Wert zur�ck, diesen speichern wir in retVal 

        // check for valid user input
        if (retVal != 2) printf("Das war keine korrekte Zahl!\n");
        else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");
        else if (value < MIN) printf("Zahl ist zu klein (MIN: %hd)\n", MIN);
        else if (value > MAX) printf("Zahl ist zu gro%c (MAX: %hd)\n", 225, MAX);
        else finished = 1; // falls die Variable tats�chlich 2 ist; und der character ein newline, ist alles richtig und die loop wird beendet

        //Variable finished wird auf 1 gesetzt -> weil 1 f�r TRUE

        //clear input stream buffer
        while (ch != '\n') scanf("%c", &ch); //Variation mit scanf von getchar

    } while (!finished); //repeat if not finished 

    //return user input
    return value; //wer auch immer die Funktion get_short aufruft bekomm "value" zur�ck
}

bool is_unique(int n, int *numbers, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (n == numbers[i]) return false;
    }
    
    return true;
}
