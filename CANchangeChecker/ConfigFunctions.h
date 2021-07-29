#ifndef _CONFIGFUNCTIONS_H_
#define _CONFIGFUNCTIONS_H_

#include <fstream>
#include <string>
#include <windows.h>
#include <bitset>



// Creates new 'licznik.txt' file
void createConfig(void) {

    std::ifstream headerFile(PATH_HEADER_FILE);
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string line;
    bool find_BLINK_BIT = false;

    SetConsoleTextAttribute(hConsole, 14);
    std::cout << "FILE 'licznik.txt' NOT FOUND, ATTEMPTING ON CREATING NEW ONE...";
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << "\n";

    try {
        if (headerFile.is_open()) {

            // When there is no 'licznik.txt' file we must check if CANMethod is already inserted in code
            // if yes : BLINK_BIT_CURRENT value becomes value read
            // if no : BLINK_BIT_CURRENT value becomes 1
            while (std::getline(headerFile, line)) {

                if (line.rfind("dataBlink") != std::string::npos) {
                    int comaIndex = line.rfind(';');
                    config_data_container.BLINK_BIT_CURRENT_DECIMAL = std::stoi( line.substr(comaIndex-2, comaIndex-1) );
                    break;
                }
            }

            config_data_container.NUMBER_COMPILE = 0;
            SetConsoleTextAttribute(hConsole, 160);
            std::cout << "NEW 'licznik.txt' CREATED WITH SUCCESS";
            SetConsoleTextAttribute(hConsole, 7);
            std::cout << "\n\n";

        }
        else {
            throw std::runtime_error("Could not open file");
        }
    }
    catch (std::runtime_error e) {
        MODIFICATION_ERROR_MESSAGE = "  - COULD NOT OPEN './inc/CustomCANTx.h'\n  - COULD NOT CREATE NEW 'licznik.txt'\n";
        MODIFICATION_ERROR_STATUS = MODIFICATION_ERROR;
    }
}





// Reads data from existing 'licznik.txt' file
// If it could not find it, it invokes createConfig() function
void readConfig(void) {

    std::fstream configFile(PATH_CONFIG_FILE);
    std::string line;


    try {
        if (configFile.is_open()) {


            // odczytywanie wartoœci z licznik.txt (bez reprezentacji binarnej bo w przetwarzaniu jest wykorzystywana tylko decymalna)
            // wartosæ binarna jest dopisywana dopiero przy modyfikacji licnzik.txt przez przekonwertowanie decymalnej
            while (getline(configFile, line)) {

                try {
                    // COMPILE NUMBER
                    if (line.rfind('L', 0) == 0)
                        config_data_container.NUMBER_COMPILE = std::stoi(line.substr(19, std::string::npos));
                }
                catch (std::invalid_argument a) {
                    MODIFICATION_ERROR_MESSAGE = "  - COULD NOT READ COMPILE NUMBER FROM './licznik.txt' \n  - NOT A NUMERIC VALUE\n  - PLEASE SET THIS VALUE MANUALLY IN 'licznik.txt' OR DELETE 'licznik.txt'";
                    MODIFICATION_ERROR_STATUS = MODIFICATION_ERROR;
                }

                try {
                    // DECIMAL SENDING VALUE
                    if (line.rfind('D', 0) == 0) {
                        int check = std::stoi(line.substr(36, std::string::npos));
                        config_data_container.BLINK_BIT_CURRENT_DECIMAL = check;
                    }
                        
                }
                catch (std::invalid_argument a) {
                    MODIFICATION_ERROR_MESSAGE =  "  - COULD NOT READ CURRENT DECIMAL SENDING NUMBER FROM './licznik.txt' \n  - NOT A NUMERIC VALUE\n  - PLEASE SET THIS VALUE MANUALLY IN 'licznik.txt OR DELETE 'licznik.txt'\n  - TO SET IT MANUALLY COPY AND PARSE TO DECIMAL SENDING VALUES IN dataBlink IN 'CustomCANTx.h'";
                    MODIFICATION_ERROR_STATUS = MODIFICATION_ERROR;
                }
            }
        }
        else {
            throw std::runtime_error("Could not open file");
        }
    }
    catch (std::runtime_error e) {
        // not a critical error so MODIFICATION_ERROR_STATUS is not changed
        createConfig();
    }
}



// Updates 'licznik.txt' file about : 
// - new BLINK_BIT_CURRENT_DECIMAL
// - binary representation of BLINK_BIT_CURRENT_DECIMAL
// - compilation number and diode color
void updateConfig(void) {


    // if any previous function that modifies files didn't executed properly this function is skipped
    if (MODIFICATION_ERROR_STATUS)
        return;

    std::ofstream configFile(PATH_CONFIG_FILE);
    std::string line;

    try {
        if (configFile.is_open()) {

            // TODO : JAK TO INTERPRETOWAÆ?
            //std::string diodeColor = (config_data_container.BLINK_BIT_CURRENT_DECIMAL == 0) ? "Kolor diody prawid³owo wgranego programu : CZERWONY\n" : "Kolor diody prawid³owo wgranego programu : ZIELONY\n";

            std::string diodeColor = "JAK TO INTERPRETOWAÆ MAREK?";

            //BLINK_BIT_CURRENT state is updated in constructCANMethod
            configFile << "Decymalna obecna wartoœæ wysy³ana : " << config_data_container.BLINK_BIT_CURRENT_DECIMAL << "\n";
            configFile << "Binarna obecna wartoœæ wysy³ana : " << std::bitset<8>(config_data_container.BLINK_BIT_CURRENT_DECIMAL).to_string() << "\n";
            configFile << "Liczba kompilacji : " << config_data_container.NUMBER_COMPILE + 1;
            configFile << "\n";
            configFile << "\n";
            configFile << "\n";
            configFile << diodeColor;
        }
        else {
            throw std::runtime_error("Cannot write to file");
        }
    }
    catch (std::runtime_error e) {
        MODIFICATION_ERROR_MESSAGE = "  - COULD NOT MODIFY FILE 'licznik.txt'\n  - DESPITE THAT './inc/CustomCANTx.h' WAS MODIFIED AND COMPILED WITH SUCCESS\n  - PLEASE UPDATE 'licznik.txt' MANUALLY";
        MODIFICATION_ERROR_STATUS = MODIFICATION_ERROR;
    }
    
}



#endif
