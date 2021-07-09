#include <iostream>
#include <string>
#include "Variables.h"
#include "ConfigFunctions.h"
#include "HeaderFunctions.h"

using namespace std;



void runCompilator(void) {


    // if any previous function didn't executed properly this function is skipped
    if (ERROR_STATUS)
        return;

    system("make.exe");
}


int main()
{
   
    readConfig();

    updateHeaderFile();

    runCompilator();

    updateConfig();

    if (!ERROR_STATUS) {
        cout << "\n\nPROGRAM MODIFIED AND COMPILED WITH SUCCESS\n";
        cout << "CHECK './licznik.txt' ABOUT SUCCESFULL UPLOAD LIGHT COLOR INFORMATION\n\n";
    }
        
    system("pause");
    return 0;
}

