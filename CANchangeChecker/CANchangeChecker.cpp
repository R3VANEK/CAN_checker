#include <iostream>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <windows.h>

#include "Variables.h"
#include "ConfigFunctions.h"
#include "HeaderFunctions.h"
#include "OtherFunctions.h"

using namespace std;



// AKTUALIZACJA WARTOŚCI O ÓSEMKOWE
// TODO : zmodyfikuj constructCANMethod()
// TODO : zmodyfikuj zmienne odpowiadające za znakową reprezentacje funkcji (zrobione ?)
// TODO : zmodyfikuj zapisywanie informacji do licznika.txt, informacje o kolorach i informacje o ostatnim wysłanym bicie
// TODO : zmodyfikuj printowanie informacji do konsoli o kolorze diody
// TODO : zmień zapisywanie do pliku


// TODO : CHANGE CREATECONFIG FUNCTION



int main()
{
   
    readConfig();

    updateHeaderFile();

    runCompilator();

    updateConfig();

    printStatusMessage();
       
    return 0;
}

