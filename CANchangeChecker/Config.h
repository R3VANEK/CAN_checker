#ifndef _CONFIG_H
#define _CONFIG_H







class Config : public ConsolePrint{

	private:
		std::ifstream configFile;
		std::ofstream configFileWrite;


	public :
		~Config() {}
		Config() {}


		void readConfig() {

			std::string line;
			configFile.open(PATH_CONFIG_FILE);

			if (!configFile.is_open()) {
				// there is no point trying to create new file as function updateConfig do this anyway
				printColorMessage("ERROR OPENING licznik.txt FILE, IT WILL BE CREATED FROM SCRATCH", ConsolePrint::c_WARNING);
			}
			else {
				while (getline(configFile, line)) {

					if (line.rfind("Liczba kompilacji projektu") != std::string::npos) {
						try
						{ 
							CONFIG_DATA_CONTAINER.compile_time = std::stoi(line.substr(29, std::string::npos));
						}
						catch (std::invalid_argument a) {
							printColorMessage("- ERROR READING COMPILE NUMBER, IT WILL BE 0", ConsolePrint::c_WARNING);
							// NOT A CRITICAL ERROR, MOVE ON;
						}		
						break;
					}
				}

				printColorMessage("READ licznik.txt FILE SUCCESS", ConsolePrint::c_SUCCESS);
			}

			configFile.close();
		}



		void updateConfig() {

			configFileWrite.open(PATH_CONFIG_FILE);

			if (!configFileWrite.is_open()) {
				printColorMessage("ERROR OPENING licnzik.txt FILE AFTER MODIFICATIONS, PLEASE UPDATE IT MANUALLY", ConsolePrint::c_WARNING);
			}
			else {
				configFileWrite << "Liczba kompilacji projektu : " << CONFIG_DATA_CONTAINER.compile_time << "\n";
				configFileWrite << "Losowa liczba wysy³ana na bajcie 1 : " << CONFIG_DATA_CONTAINER.random_byte1 << "\n";
				configFileWrite << "Losowa liczba wysy³ana po bajcie 2 : " << CONFIG_DATA_CONTAINER.random_byte2 << "\n";
			}

			printColorMessage("UPDATING licznik.txt WITH SUCCESS", ConsolePrint::c_SUCCESS);
			configFileWrite.close();
		}

};


#endif
