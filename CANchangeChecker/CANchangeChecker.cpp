#include <iostream>
#include <fstream>
#include "Variables.h"


using namespace std;



string constructCANMethod(char lastSetBit) {


    string output;

    output += CAN_METHOD_BEGINNING;
    output += "       tByte dataBlink = ";
    output += lastSetBit;
    output += "\n";
    output += CAN_METHOD_END;

    return output;

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



void updateConfig(void) {



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
   


    char lastSetBit = readLastSetBit();

    if (lastSetBit != '1' && lastSetBit != '0') {
        cout << "BŁĄD ODCZYTU WARTOŚCI OSTATNIEGO USTAWIONEGO BITA Z config.txt, PRZERYWANIE KOMPILACJI...";
        return -1;
    }

    if (insertMethodInCode(lastSetBit)) {

    }
    else {
        cout << "BŁĄD MODYFIKACJI PLIKU NAGŁÓWKOWEGO";
    }

        
    
    

    
    return 0;
}

