#include <iostream>
#include <fstream>
#include "Variables.h"


using namespace std;



string constructCANMethod(char lastSetBit) {


    string output;
    BLINK_BIT_NEW = (lastSetBit == '0') ? '1' : '0';
    output += CAN_METHOD_BEGINNING;
    output += "       tByte dataBlink = ";
    output += BLINK_BIT_NEW;
    output += ";\n";
    output += CAN_METHOD_END;

    return output;

}

char readCompileNumber(void) {

    fstream configFile(PATH_CONFIG_FILE);
    string line;

    if (configFile.is_open()) {

        while (getline(configFile, line)) {

            if (line.rfind('L', 0) == 0) {

                int index = stoi(line.substr(19, string::npos));
                return index;
            }
        }

    }

    return -1;
}


bool insertMethodInCode(char lastSetBit) {



    fstream programFile(PATH_HEADER_FILE);
    bool startCopying = false;


    string ProgramMashedContent = BEGINNING_HEADER + constructCANMethod(lastSetBit);
    string line;

    
    

    if (programFile.is_open()) {

        while (getline(programFile, line)) {
            
            if (line == "void fCAN_STATES2(tByte bSend) {")
                startCopying = true;
             
            if (startCopying)
                ProgramMashedContent += line + "\n";
            
        }        
        programFile.close();
        
        std::fstream programFile(PATH_HEADER_FILE);
        programFile << ProgramMashedContent;
        programFile.close();

    }
    else {
        return 0;
    }

    return 1;

}



bool updateConfig(void) {

    fstream configFile(PATH_CONFIG_FILE);
    string line;

    

    if (configFile.is_open()) {

        configFile << "Poprzedni stan bitu : " << BLINK_BIT_OLD << "\n";
        configFile << "Liczba kompilacji : " << readCompileNumber() + 1;
        return 1;
        
    }

    return 0;

}


char readLastSetBit(void) {

    fstream configFile(PATH_CONFIG_FILE);
    string line;

    if (configFile.is_open()) {

        while (getline(configFile, line)) {

            if (line.rfind('P', 0) == 0) {
                return line.at(line.length() - 1);
            }
        }
        
    }

    return -1;
}

void runCompilator(void) {
    system("start make.exe");
}



int main()
{
   


    BLINK_BIT_OLD = readLastSetBit();

    if (BLINK_BIT_OLD != '1' && BLINK_BIT_OLD != '0') {
        cout << "BŁĄD ODCZYTU WARTOŚCI OSTATNIEGO USTAWIONEGO BITA Z config.txt, PRZERYWANIE KOMPILACJI...";
        //return -1;
        while (true) {

        }
    }

    if (!insertMethodInCode(BLINK_BIT_OLD)) {
        cout << "BŁĄD MODYFIKACJI PLIKU NAGŁÓWKOWEGO";
        while (true) {

        }
        //return -1;
    }

   runCompilator();


    if (!updateConfig()) {
        cout << "BŁĄD PRZY AKTUALIZACJI licznik.txt";
        while (true) {

        }
        //return -1;
    }


    

        
    
    

    
    return 0;
}

