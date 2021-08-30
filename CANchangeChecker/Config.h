#ifndef _CONFIG_H
#define _CONFIG_H


#include <fstream>
#include "Variables.h"
#include <windows.h>




// zrobiæ parenta z metodami na wypisywanie b³êdów
class Config {

	private:
		std::ifstream headerFile;
		std::ofstream configFile;
		bool is_BlinkingBit = false;

		struct ConfigData {
			long compile_time;
			unsigned int random_byte1;
			unsigned int random_byte2;
		} data_container;




	public :
		~Config(){}
		Config() {
			configFile.open(PATH_CONFIG_FILE);

			if (!configFile.is_open()) {
				printf("ERROR OPENING CONFIG FILE, CREATING NEW ONE...");
				// tworzenie nowego licznik.txt a potem i tak losowanie nowych wartoœci itp.
			}
			else {
				// odczyt wartoœci z licznik.txt
				// odczyt tylko liczby kompilacji, wartoœci wysy³ane i tak bêd¹ losowane od pocz¹tku
			}

		}


		void updateConfig() {
			configFile.open(PATH_CONFIG_FILE);
			if (!configFile.is_open()) {
				printf("ERROR OPENING FILE AFTER MODIFICATIONS, PLEASE MODIFY IT MANUALLY");
				// NOT A FATAL ERROR
			}
			else {
				configFile << "Liczba kompilacji projektu : " << data_container.compile_time << "\n";
				configFile << "Losowa liczba wysy³ana na bajcie 1 : " << data_container.random_byte1 << "\n";
				configFile << "Losowa liczba wysy³ana po bajcie 2 : " << data_container.random_byte2 << "\n";
			}
			// handling errors for modifing config file here
		}


		ConfigData getConfigData() {
			return data_container;
		}

		void setConfigData() {
			data_container.random_byte1 = rand() % 255 + 1;
			data_container.random_byte2 = rand() % 255 + 1;
			data_container.compile_time += 1;
		}

		

};




#endif
