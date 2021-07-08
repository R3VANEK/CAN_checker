#ifndef _CONFIGFUNCTIONS_H_
#define _CONFIGFUNCTIONS_H_

#include <fstream>
#include <string>











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
                    std::cout << "B£¥D : NIE UDA£O SIÊ ODCZYTAÆ LICZBY KOMPILACJI, CZY NA PEWNO WARTOŒÆ JEST TYPU LICZBOWEGO?";
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
                    std::cout << "B£¥D : NIE UDA£O SIÊ ODCZYTAÆ OBECNEGO BITU, CZY NA PEWNO WARTOŒÆ JEST TYPU LICZBOWEGO Z PRZEDZIA£U 0 ALBO 1?";
                }
            }
        }
        else {
            throw std::runtime_error("Could not open file");
        }
    }
    catch (std::runtime_error e) {
        std::cout << "B£¥D : NIE UDA£O OTWORZYÆ SIÊ PLIKU licznik.txt, CZY PLIK NA PEWNO ZNAJDUJE SIÊ NA TAKIM SAMYM POZIOMIE FOLDERU?";
    }
}




void updateConfig(void) {

    std::fstream configFile(PATH_CONFIG_FILE);
    std::string line;

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
}



/*
bool updateConfig(void) {

    fstream configFile(PATH_CONFIG_FILE);
    string line;



    if (configFile.is_open()) {

        string diodeColor = (BLINK_BIT_NEW == '0') ? "Kolor diody prawid³owo wgranego programu : CZERWONY\n" : "Kolor diody prawid³owego wgranego programu : ZIELONY\n";

        configFile << "Poprzedni stan bitu : " << BLINK_BIT_OLD << "\n";
        configFile << "Obecny stan bitu : " << BLINK_BIT_NEW << "\n";
        configFile << "Liczba kompilacji : " << readCompileNumber() + 1;
        configFile << "\n";
        configFile << "\n";
        configFile << "\n";
        configFile << diodeColor;
        return 1;

    }

    return 0;

}*/

#endif
