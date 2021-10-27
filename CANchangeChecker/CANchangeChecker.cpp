#include <iostream>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <windows.h>
#include <fstream>






#include "Variables.h"
#include "Other.h"
#include "Config.h"
#include "CodeModifier.h"





int main()
{

   
    
        Config config;
        CodeModifier code;
        ConsolePrint p;


        config.readConfig();
        code.updateHeaderFile();
        
        // uruchomienie kompilatora

        config.updateConfig();

        
    
    
    








/*    readConfig();

    updateHeaderFile();

    runCompilator();

    updateConfig();

    printStatusMessage();*/
       
    return 0;
}

