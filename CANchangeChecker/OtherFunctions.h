#ifndef _OTHERFUNCTIONS_H_
#define _OTHERFUNCTIONS_H_

#include <string>
#include <stdexcept>
#include <stdio.h>
#include <windows.h>


// prints all necessary informaton to the console
// includes modification messages, compilation messages
void printStatusMessage(void) {

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout << "\n\n- FILES MODIFIED/READ WITH ";

    if (!MODIFICATION_ERROR_STATUS) {
        SetConsoleTextAttribute(hConsole, 160);
        std::cout << "SUCCESS";
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << "\n";
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "ERRORS\n";
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << MODIFICATION_ERROR_MESSAGE;
        std::cout << "\n";
    }

    std::cout << "\n- PROGRAM COMPILED WITH ";
    if (!COMPILATION_ERROR_STATUS) {
        SetConsoleTextAttribute(hConsole, 160);
        std::cout << "SUCCESS\n";
        SetConsoleTextAttribute(hConsole, 7);
    }
    else {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "ERRORS\n";
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << COMPILATION_ERROR_MESSAGE;
        std::cout << "\n\n";
    }


    if (!MODIFICATION_ERROR_STATUS && !COMPILATION_ERROR_STATUS) {

        std::cout << "\n\nSUCCESSFULL UPLOAD DIODE COLOR IS ";
        if (config_data_container.BLINK_BIT_CURRENT_DECIMAL) {
            SetConsoleTextAttribute(hConsole, 160);
            std::cout << "WHAT COLOR MAREK";
            SetConsoleTextAttribute(hConsole, 7);
        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
            std::cout << "RED";
            SetConsoleTextAttribute(hConsole, 7);
        }
        std::cout << "\nTHIS INFORMATION IS ALSO STORED IN './licznik.txt'\n\n";
    }

    system("pause");
}






// attempts to run COSMOS compilator on modified project
void runCompilator(void) {

    // if any previous function didn't executed properly this function is skipped
    if (MODIFICATION_ERROR_STATUS) {
        COMPILATION_ERROR_STATUS = COMPILATION_ERROR;
        return;
    }
    const char* cmd = "make.exe";

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

    // brak klucza kompilacji - length() ok. 1540
    // zamieniona b³êdnie kolejnoœæ nag³ówków - length() ok. 1540
    // je¿eli wiadomoœæ d³u¿sza ni¿ 1600 znaków - kompiacja bez b³êdów (?) TODO : sprawdzic dok³adniej
    COMPILATION_ERROR_STATUS = (result.length() > 1600) ? 0 : COMPILATION_ERROR;
}






#endif
