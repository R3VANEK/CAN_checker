#ifndef _HEADERFUNCTIONS_H_
#define _HEADERFUNCTIONS_H_


#include <fstream>
#include <string>




// create string that represents method for sending blinking bit
// automatically inverts previous state of BLINK_BIT_CURRENT
std::string constructCANMethod(unsigned int *BLINK_BIT_CURRENT) {

    *BLINK_BIT_CURRENT = !*BLINK_BIT_CURRENT;

    std::string output;
    
    output += CAN_METHOD_BEGINNING;
    output += "       tByte dataBlink = ";
    output += std::to_string(*BLINK_BIT_CURRENT);
    output += ";\n";
    output += CAN_METHOD_END;

    return output;

}





// insert into CustomCANTx.h custom function to send blink bit by CANID 0x400 made by constructCANMethod()
void updateHeaderFile() {



    // if any previous function didn't executed properly this function is skipped
    if (MODIFICATION_ERROR_STATUS)
        return;



    std::fstream programFile(PATH_HEADER_FILE);
    bool startCopying = false;

    std::string ProgramMashedContent = BEGINNING_HEADER + constructCANMethod(&config_data_container.BLINK_BIT_CURRENT);
    std::string line;

    try {
        if (programFile.is_open()) {

            while (getline(programFile, line)) {

                // identify the first function in header file that isnt CANMethod
                // that first functon must start with letter 'f'
                if (line.substr(0, 6) == "void f")
                    startCopying = true;

                if (startCopying)
                    ProgramMashedContent += line + "\n";

            }
            programFile.close();

            try {
                if (startCopying == false)
                    throw std::runtime_error("Could not find function");
            }
            catch (std::runtime_error e) {
                std::cout << "  - COULD NOT MODIFY 'CustomCANTx.h'\n - COULD NOT FIND FUNCTION THAT STARTS WITH LETTER 'f'\n   - (FIRST SPECIFIED FUNCTION BY USER MUST START WITH LETTER 'f')";
                MODIFICATION_ERROR_STATUS = MODIFICATION_ERROR;
            }

            try {
                std::fstream programFile(PATH_HEADER_FILE);

                if (programFile) {
                    programFile << ProgramMashedContent;
                    programFile.close();
                }
                if (programFile.bad()) {
                    throw std::runtime_error("Could not write to file");
                }
            }
            catch (std::runtime_error e) {
                MODIFICATION_ERROR_MESSAGE = "  - COULD NOT MODIFY FILE './inc/CustomCANTx.h'";
                MODIFICATION_ERROR_STATUS = MODIFICATION_ERROR;
            }
            
        }
        else {
            throw std::runtime_error("Could not open file");
        }
    }

    catch (std::runtime_error e) {
        MODIFICATION_ERROR_MESSAGE = "  - COULD NOT OPEN './inc/CustomCANTx.h'";
        MODIFICATION_ERROR_STATUS = MODIFICATION_ERROR;
    }
    
}



#endif