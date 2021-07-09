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
    if (MODIFICATION_ERROR_STATUS)
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

    COMPILATION_ERROR_STATUS = (result.length() > 300) ? 0 : COMPILATION_ERROR;
}






void printStatusMessage(void) {

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "\n\n- PROGRAM MODIFIED WITH ";

    if (!MODIFICATION_ERROR_STATUS) {
        SetConsoleTextAttribute(hConsole, 160);
        cout << "SUCCESS\n";
        SetConsoleTextAttribute(hConsole, 7);
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "ERRORS\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << MODIFICATION_ERROR_MESSAGE;
    }

    cout << "\n- PROGRAM COMPILED WITH ";
    if (!COMPILATION_ERROR_STATUS) {
        SetConsoleTextAttribute(hConsole, 160);
        cout << "SUCCESS\n";
        SetConsoleTextAttribute(hConsole, 7);
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        cout << "ERRORS\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << COMPILATION_ERROR_MESSAGE;
    }

    cout << "\n\n";
    system("pause");
}

int main()
{
   
    readConfig();

    updateHeaderFile();

    
    exec("make.exe");

    updateConfig();


    printStatusMessage();
       

    return 0;
}

