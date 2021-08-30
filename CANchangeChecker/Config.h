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

		struct {
			long compile_time = 0;
			unsigned int random_byte1;
			unsigned int random_byte2;
		} data_container;




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
							data_container.compile_time = std::stoi(line.substr(29, std::string::npos)); 
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
				configFileWrite << "Liczba kompilacji projektu : " << data_container.compile_time << "\n";
				configFileWrite << "Losowa liczba wysy³ana na bajcie 1 : " << data_container.random_byte1 << "\n";
				configFileWrite << "Losowa liczba wysy³ana po bajcie 2 : " << data_container.random_byte2 << "\n";
			}
			// handling errors for modifing config file here
			configFileWrite.close();
		}



		int* setConfigData() {
			data_container.random_byte1 = rand() % 255 + 1;
			data_container.random_byte2 = rand() % 255 + 1;
			data_container.compile_time += 1;

			// returning ConfigData struct is not possible in other .h files
			int output[2];
			output[0] = data_container.random_byte1;
			output[1] = data_container.random_byte2;

			return output;
		}

};


#endif
