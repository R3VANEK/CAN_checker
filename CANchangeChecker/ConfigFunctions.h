#ifndef _CONFIGFUNCTIONS_H_
#define _CONFIGFUNCTIONS_H_

#include <fstream>
#include <string>
#include <windows.h>



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
            // if no : BLINK_BIT_CURRENT value becomes 0
            while (std::getline(headerFile, line)) {

                if (line.rfind("dataBlink") != std::string::npos) {
                    int comaIndex = line.rfind(';');
                    config_data_container.BLINK_BIT_CURRENT = std::stoi( line.substr(comaIndex-2, comaIndex-1) );
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

            while (getline(configFile, line)) {

                try {
                    if (line.rfind('L', 0) == 0)
                        config_data_container.NUMBER_COMPILE = std::stoi(line.substr(19, std::string::npos));
                }
                catch (std::invalid_argument a) {
                    MODIFICATION_ERROR_MESSAGE = "  - COULD NOT READ COMPILE NUMBER FROM './licznik.txt' \n  - NOT A NUMERIC VALUE\n  - PLEASE SET THIS VALUE MANUALLY IN 'licznik.txt' OR DELETE 'licznik.txt'";
                    MODIFICATION_ERROR_STATUS = MODIFICATION_ERROR;
                }

                try {
                    if (line.rfind('O', 0) == 0) {

                        //additional check whether number is valid
                        //becouse default behavior of std::stoi and bit field BLINK_BIT_CURRENT is silencing this error
                        std::string check = line.substr(19, std::string::npos);
                        if (check != "1" && check != "0")
                            throw std::invalid_argument("Invalid number");

                        config_data_container.BLINK_BIT_CURRENT = std::stoi(check);
                    }
                        
                }
                catch (std::invalid_argument a) {

                    // TO MO¯NA JESZCZE ODCZYTAÆ JEŒLI PRZY TAKIM B£ÊDZIE CHCEMY ZRESETOWAÆ LICZBÊ KOMPILACJI
                    MODIFICATION_ERROR_MESSAGE =  "  - COULD NOT READ CURRENT BIT FROM './licznik.txt' \n  - NOT A NUMERIC VALUE 0 OR 1\n  - PLEASE SET THIS VALUE MANUALLY IN 'licznik.txt OR DELETE 'licznik.txt'\n  - TO SET IT MANUALLY COPY THE VALUE OF VAR dataBlink IN 'CustomCANTx.h'";
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



// Updates 'licznik.txt' file about new BLINK_BIT_CURRENT state, compilation number and diode color
void updateConfig(void) {


    // if any previous function that modifies files didn't executed properly this function is skipped
    if (MODIFICATION_ERROR_STATUS)
        return;

    std::ofstream configFile(PATH_CONFIG_FILE);
    std::string line;

    try {
        if (configFile.is_open()) {

            std::string diodeColor = (config_data_container.BLINK_BIT_CURRENT == 0) ? "Kolor diody prawid³owo wgranego programu : CZERWONY\n" : "Kolor diody prawid³owo wgranego programu : ZIELONY\n";

            //BLINK_BIT_CURRENT state is updated in constructCANMethod
            configFile << "Obecny stan bitu : " << config_data_container.BLINK_BIT_CURRENT << "\n";
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
