#ifndef _HEADERFUNCTIONS_H_
#define _HEADERFUNCTIONS_H_


#include <fstream>
#include <string>
#include <cstdlib>




// create string that represents method for sending blinking bit
// updates BLINK_BIT_CURRENT_DECIMAL
std::string constructCANMethod() {


    config_data_container.BLINK_BIT_CURRENT_DECIMAL = (config_data_container.BLINK_BIT_CURRENT_DECIMAL != 255) ? config_data_container.BLINK_BIT_CURRENT_DECIMAL + 1 : 1;
    std::string output;
    char b[32];
    _itoa_s(config_data_container.BLINK_BIT_CURRENT_DECIMAL, b, 16);


    output += CAN_METHOD_BEGINNING;
    output += "     mTX.abData[0] = 0x" + std::string(b) + ";\n";
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

    std::string ProgramMashedContent = BEGINNING_HEADER + constructCANMethod();
    std::string line;

    try {
        if (programFile.is_open()) {

            while (getline(programFile, line)) {

                // identify the first user-written function in header file 
                if (line.substr(0, 4) == "void" && line.rfind("void sendBlinkBit(tByte bSend)") == std::string::npos)
                    startCopying = true;

                if (startCopying) {

                    //////////////////////////////////////////// BUG RISK ////////////////////////////////////////////////
                    //                                                                                                  //
                    // Im assuming that opening curly bracket of function vCAN_Tx_Custom                                //
                    // is in the same line as string 'void vCAN_TX_Custom(void)'                                        //
                    //                                                                                                  //
                    // If it's not, program won't compile properly                                                      //
                    //                                                                                                  //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////

                    if (
                            line.rfind("void vCAN_TX_Custom(void)") == std::string::npos 
                            && line.rfind("// execution of special function sendBlinkBit") == std::string::npos
                            && line.rfind("// THIS CODE IS GENERATED AUTOMATICALLY") == std::string::npos
                            && line.rfind("sendBlinkBit((tByte)(GET_TIMER_CAN == 12));") == std::string::npos
                        ) {
                        ProgramMashedContent += line + "\n";
                    }
                        
                    else if(line.rfind("void vCAN_TX_Custom(void)") != std::string::npos){
                        ProgramMashedContent += "void vCAN_TX_Custom(void){\n";
                        ProgramMashedContent += CAN_METHOD_TIMER;
                    }
                }
                    

            }
            programFile.close();

            try {
                if (startCopying == false)
                    throw std::runtime_error("Could not find function");
            }
            catch (std::runtime_error e) {
                MODIFICATION_ERROR_MESSAGE = "  - COULD NOT MODIFY 'CustomCANTx.h'\n  - COULD NOT FIND ANY USER-WRITTEN FUNCTION OF TYPE void\n  - IS CustomCANtX.h EMPTY?";
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