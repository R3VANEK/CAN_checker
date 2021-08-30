#ifndef _CODEMODIFIER_H
#define _CODEMODIFIER_H

#include <fstream>
#include "Config.h"

class CodeModifier {

	private:
		std::ifstream headerFile;
		std::fstream headerFileWrite;



		std::string createBlinkBytes() {
			std::string output;
			/*int* data_container = Config::setConfigData();
			output += "////////////////////////////////////////////////////////\n";
			output += "// THIS CODE IS GENERATED AUTOMATICALLY DO NOT CHANGE IT\n";
			output += "// random values sending through sendBlinkBit\n";
			output += "#define CUSTOM_BLINK_BYTE1  (" + data_container[0];
			output += ")\n";
			output += "#define CUSTOM_BLINK_BYTE2  (" + data_container[1];
			output += ")\n////////////////////////////////////////////////////////\n";
			return output;*/
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
				printf("ERROR OPENING HEADER FILE");
				// error catching
			}
			else {
				while (getline(headerFile, line)) {

					// identify the first user-written function in header file 
					if (line.substr(0, 4) == "void" && line.rfind("void sendBlinkBit(tByte bSend)") == std::string::npos)
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
			headerFile.close();
			return newTextContent;
		}



	public:
		~CodeModifier() {}
		CodeModifier() {}

		
		void updateHeaderFile() {

			headerFileWrite.open(PATH_HEADER_FILE);
			if (!headerFileWrite.is_open()) {
				printf("ERROR OPENING HEADER FILE WHILE UPDATING");
				// ERROR HANDLING
			}
			else {
				headerFileWrite << createNewTextContent();
				headerFileWrite.close();
			}
		}
};



#endif
