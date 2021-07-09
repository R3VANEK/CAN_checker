#include <iostream>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <windows.h>

#include "Variables.h"
#include "ConfigFunctions.h"
#include "HeaderFunctions.h"

using namespace std;



void exec(const char* cmd) {

    // if any previous function didn't executed properly this function is skipped
    if (ERROR_STATUS)
        return;

    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    }
    catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);

    COMPILATION_STATUS = (result.length() > 300) ? 1 : 0;
    //COMPILATION_MESSAGE = (result.length() > 300) ? "SUCCESS" : "ERRORS\n  - PLEASE NOTE THAT 'licznik.txt' WAS MODIFIED NONETHELESS\n  - PLEASE FIX ERRORS AND COMPILE ONCE MORE NOT CHANGING 'licznik.txt'\n";
}



void runCompilator(void) {


    // if any previous function didn't executed properly this function is skipped
    if (ERROR_STATUS)
        return;

    system("make.exe");
}


void printStatusMessage(void) {

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!ERROR_STATUS) {
        cout << "\n\n- PROGRAM MODIFIED WITH ";
        SetConsoleTextAttribute(hConsole, 160);
        cout << "SUCCESS\n";
        SetConsoleTextAttribute(hConsole, 7);

        cout << "- PROGRAM COMPILED WITH ";

        if (COMPILATION_STATUS) {
            SetConsoleTextAttribute(hConsole, 160);
            cout << "SUCCESS\n";
            SetConsoleTextAttribute(hConsole, 7);
        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "ERRORS\n";
            SetConsoleTextAttribute(hConsole, 7);
            cout << "  - PLEASE NOTE THAT 'licznik.txt' WAS MODIFIED NONETHELESS\n";
            cout << "  - PLEASE FIX COMPILATION ERRORS AND NOT CHANGE 'licznik.txt'\n";
        }

        cout << "\n\nCHECK './licznik.txt' ABOUT CORRECT LIGHT COLOR INFORMATION\n\n\n";
    }

}

int main()
{
   
    readConfig();

    updateHeaderFile();

    //runCompilator();
    exec("make.exe");

    updateConfig();


    printStatusMessage();
        
    system("pause");
    return 0;
}

