#include <iostream>
#include "Variables.h"


using namespace std;



void insertMethodInCode() {


    string ProgramMashedContent = beginningOfProgramFile + CANmethod;
    string line;

    bool startCopying = false;

    if (programFile.is_open()) {

        while (std::getline(programFile, line)) {
            
            if (line == "void fCAN_STATES2(tByte bSend) {")
                startCopying = true;
             
            if (startCopying)
                ProgramMashedContent += line + "\n";
            
        }        
        programFile.close();
        
        std::fstream programFile("./original.txt");
        programFile << ProgramMashedContent;
        programFile.close();

    }
    else {
        cout << "error";
    }

}




int main()
{
    


    insertMethodInCode();
    

    
    return 0;
}

