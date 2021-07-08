#ifndef _HEADERFUNCTIONS_H_
#define _HEADERFUNCTIONS_H_


#include <fstream>
#include <string>



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






void updateHeaderFile() {

    if (ERROR_STATUS)
        return;

    std::fstream programFile(PATH_HEADER_FILE);
    bool startCopying = false;

    std::string ProgramMashedContent = BEGINNING_HEADER + constructCANMethod(&config_data_container.BLINK_BIT_CURRENT);
    std::string line;

    try {
        if (programFile.is_open()) {

            while (getline(programFile, line)) {

                //identify the first function in header file that isnt CANMethod
                // that first functon must start with letter 'f'
                if (line.substr(0, 6) == "void f")
                    startCopying = true;

                if (startCopying)
                    ProgramMashedContent += line + "\n";

            }
            programFile.close();

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
                std::cout << "ERROR : COULD NOT MODIFY FILE './inc/CustomCANTx.h' \n\n";
                ERROR_STATUS = true;
            }
        }
        else {
            throw std::runtime_error("Could not open file");
        }
    }

    catch (std::runtime_error e) {
        std::cout << "ERROR : COULD NOT OPEN './inc/CustomCANTx.h'\n\n";
        ERROR_STATUS = true;
    }
    
}



#endif