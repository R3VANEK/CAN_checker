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
        runCompilator();

        config.updateConfig();

        std::cout << "\n\n" << "Please upload program to miunske and conect CANFOX to computer\n";
        std::cout << "When you are ready click any button";


        system("pause");
    
    








/*    readConfig();

    updateHeaderFile();

    runCompilator();

    updateConfig();

    printStatusMessage();*/
       
    return 0;
}

