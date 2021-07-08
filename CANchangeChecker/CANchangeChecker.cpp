#include <iostream>
#include <string>
#include "Variables.h"
#include "ConfigFunctions.h"
#include "HeaderFunctions.h"


using namespace std;

















void runCompilator(void) {
    system("start make.exe");
}



int main()
{
   
    readConfig();
    updateHeaderFile();
    //runCompilator();
    updateConfig();

    
    return 0;
}

