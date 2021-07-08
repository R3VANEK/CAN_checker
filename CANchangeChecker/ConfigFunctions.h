#ifndef _CONFIGFUNCTIONS_H_
#define _CONFIGFUNCTIONS_H_

#include <fstream>
#include <string>




// TODO : metoda tworz¹ca podstawowy licznik.txt






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
                    std::cout << "ERROR : COULD NOT READ COMPILE NUMBER FROM './licznik.txt' \n - NOT A NUMERIC VALUE\n\n";
                    ERROR_STATUS = true;
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
                    std::cout << "ERROR : COULD NOT READ CURRENT BIT FROM './licznik.txt' \n - NOT A NUMERIC VALUE 0 OR 1\n\n";
                    ERROR_STATUS = true;
                }
            }
        }
        else {
            throw std::runtime_error("Could not open file");
        }
    }
    catch (std::runtime_error e) {
        std::cout << "COULD NOT OPEN FILE './licznik.txt' \n - DOES IT EXIST ON THE SAME LEVEL AS THIS .EXE?\n\n";
        ERROR_STATUS = true;
    }
}




void updateConfig(void) {

    if (ERROR_STATUS)
        return;

    std::fstream configFile(PATH_CONFIG_FILE);
    std::string line;

    try {
        if (configFile.is_open()) {

            std::string diodeColor = (config_data_container.BLINK_BIT_CURRENT == 0) ? "Kolor diody prawid³owo wgranego programu : CZERWONY\n" : "Kolor diody prawid³owego wgranego programu : ZIELONY\n";

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
        std::cout << "ERROR : COULD NOT MODIFY FILE 'licznik.txt'\n - DESPITE THAT './inc/CustomCANTx.h' WAS MODIFIED AND COMPILED WITH SUCCESS\n\n";
        ERROR_STATUS = true;
    }
    
}



#endif
