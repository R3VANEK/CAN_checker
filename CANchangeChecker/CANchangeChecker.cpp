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



int main()
{
   
    readConfig();

    updateHeaderFile();

    runCompilator();

    updateConfig();

    printStatusMessage();
       
    return 0;
}

