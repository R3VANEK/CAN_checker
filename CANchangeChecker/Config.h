#ifndef _CONFIG_H
#define _CONFIG_H


#include <fstream>
#include "Variables.h"
#include <windows.h>




// zrobiæ parenta z metodami na wypisywanie b³êdów
class Config {

	private:
		std::ifstream configFile;
		std::ofstream configFileWrite;
		bool is_BlinkingBit = false;


	public :
		~Config() {}
		Config() {}


		void readConfig() {

			std::string line;
			configFile.open(PATH_CONFIG_FILE);

			if (!configFile.is_open()) {
				// there is no point trying to create new file as function updateConfig do this anyway
				printf("ERROR OPENING CONFIG FILE, CREATING NEW ONE...");
			}
			else {
				while (getline(configFile, line)) {

					if (line.rfind("Liczba kompilacji projektu") != std::string::npos) {
						try
						{ 
							CONFIG_DATA_CONTAINER.compile_time = std::stoi(line.substr(29, std::string::npos));
						}
						catch (std::invalid_argument a) {
							printf("ERROR READING COMPILE NUMBER, IT WILL BE 0");
							// NOT A CRITICAL ERROR, MOVE ON;
						}		
						break;
					}
				}
			}
			configFile.close();
		}



		void updateConfig() {

			configFileWrite.open(PATH_CONFIG_FILE);

			if (!configFileWrite.is_open()) {
				printf("ERROR OPENING FILE AFTER MODIFICATIONS, PLEASE MODIFY IT MANUALLY");
				// NOT A FATAL ERROR
			}
			else {
				configFileWrite << "Liczba kompilacji projektu : " << CONFIG_DATA_CONTAINER.compile_time << "\n";
				configFileWrite << "Losowa liczba wysy³ana na bajcie 1 : " << CONFIG_DATA_CONTAINER.random_byte1 << "\n";
				configFileWrite << "Losowa liczba wysy³ana po bajcie 2 : " << CONFIG_DATA_CONTAINER.random_byte2 << "\n";
			}
			configFileWrite.close();
		}

};


#endif
