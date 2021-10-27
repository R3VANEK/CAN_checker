#ifndef _CODEMODIFIER_H
#define _CODEMODIFIER_H



class CodeModifier : public ConsolePrint{

	private:
		std::ifstream headerFile;
		std::fstream headerFileWrite;


		void setConfigData() {
			srand((unsigned int)time(NULL));
			CONFIG_DATA_CONTAINER.random_byte1 = rand() % 255 + 1;
			CONFIG_DATA_CONTAINER.random_byte2 = rand() % 255 + 1;
			CONFIG_DATA_CONTAINER.compile_time += 1;
		}


		std::string createBlinkBytes() {

			setConfigData();

			std::string output;
			output += "////////////////////////////////////////////////////////\n";
			output += "// THIS CODE IS GENERATED AUTOMATICALLY DO NOT CHANGE IT\n";
			output += "// random values sending through sendBlinkBit\n";
			output += "#define CUSTOM_BLINK_BYTE1  (" + std::to_string(CONFIG_DATA_CONTAINER.random_byte1);
			output += ")\n";
			output += "#define CUSTOM_BLINK_BYTE2  (" + std::to_string(CONFIG_DATA_CONTAINER.random_byte2);
			output += ")\n////////////////////////////////////////////////////////\n";
			return output;
		}


		// do sprawdzenia czy nie wykrzacza siê na funkcjach
		// gdzie otwieraj¹ca klamra jest w nowej linii
		std::string createNewTextContent() {

			std::string line;
			bool startCopying = false;
			std::string newTextContent;

			newTextContent += BEGINNINGTEXT;
			newTextContent += createBlinkBytes();
			newTextContent += CUSTOMBLINK_METHOD;

			headerFile.open(PATH_HEADER_FILE);
			if (!headerFile.is_open()) {
				std::string error_message = "ERROR OPENING HEADER FILE ";
				error_message += PATH_HEADER_FILE;
				printColorMessage(error_message, ConsolePrint::c_ERROR);
			}
			else {
				while (getline(headerFile, line)) {

					// identify the first user-written function in header file 
					if (line.substr(0, 4) == "void" && line.rfind("void sendBlinkBit(tByte bSend)") == std::string::npos && !startCopying)
						startCopying = true;

					if (startCopying) {

						if (
							line.rfind("void vCAN_TX_Custom(void)") == std::string::npos
							&& line.rfind("// execution of special function sendBlinkBit") == std::string::npos
							&& line.rfind("// THIS CODE IS GENERATED AUTOMATICALLY") == std::string::npos
							&& line.rfind("sendBlinkBit((tByte)(GET_TIMER_CAN == 12));") == std::string::npos
							) {
							newTextContent += line + "\n";
						}
						else if (line.rfind("void vCAN_TX_Custom(void)") != std::string::npos) {
							newTextContent += "void vCAN_TX_Custom(void){\n";
							newTextContent += CUSTOMBLINK_TIMER;
						}
					}
				}
			}

			std::string success_message = "MODIFIED HEADER FILE ";
			success_message += PATH_HEADER_FILE;
			success_message += " WITH SUCCESS";
			printColorMessage(success_message, ConsolePrint::c_SUCCESS);
			headerFile.close();
			return newTextContent;
		}



	public:
		~CodeModifier() {}
		CodeModifier() {}

		
		void updateHeaderFile() {

			headerFileWrite.open(PATH_HEADER_FILE);
			if (!headerFileWrite.is_open()) {
				std::string error_message = "ERROR OPENING HEADER FILE ";
				error_message += PATH_HEADER_FILE;
				printColorMessage(error_message, ConsolePrint::c_ERROR);
				
			}
			else {
				headerFileWrite << createNewTextContent();
				headerFileWrite.close();
			}
		}
};



#endif
