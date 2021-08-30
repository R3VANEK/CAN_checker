#include <iostream>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <windows.h>
#include <fstream>


#include "Variables.h"
#include "Config.h"
#include "CodeModifier.h"


// AKTUALIZACJA WARTOŚCI O ÓSEMKOWE
// TODO : zmodyfikuj constructCANMethod()
// TODO : zmodyfikuj zmienne odpowiadające za znakową reprezentacje funkcji (zrobione ?)
// TODO : zmodyfikuj zapisywanie informacji do licznika.txt, informacje o kolorach i informacje o ostatnim wysłanym bicie
// TODO : zmodyfikuj printowanie informacji do konsoli o kolorze diody
// TODO : zmień zapisywanie do pliku


// TODO : CHANGE CREATECONFIG FUNCTION



int main()
{

   

    Config config;
    CodeModifier code;


    config.readConfig();
    code.updateHeaderFile();








/*    readConfig();

    updateHeaderFile();

    runCompilator();

    updateConfig();

    printStatusMessage();*/
       
    return 0;
}

