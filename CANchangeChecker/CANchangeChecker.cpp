#include <iostream>
#include <string>
#include "Variables.h"
#include "ConfigFunctions.h"
#include "HeaderFunctions.h"

using namespace std;



void runCompilator(void) {

    if (ERROR_STATUS)
        return;

    system("start make.exe");
}


int main()
{
   
    readConfig();
    updateHeaderFile();
    //runCompilator();
    updateConfig();

    if (!ERROR_STATUS) {
        cout << "MODIFIED AND COMPILED WITH SUCCESS\n";
        cout << "CHECK './licznik.txt' ABOUT SUCCESFULL UPLOAD LIGHT COLOR INFORMATION\n\n";
    }
        
    system("pause");
    return 0;
}

