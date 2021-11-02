#ifndef _OTHER_H_
#define _OTHER_H_




class ConsolePrint {

public:
	static const unsigned int c_ERROR = 12;
	static const unsigned int c_WARNING = 14;
	static const unsigned int c_SUCCESS = 160;

	ConsolePrint() {}
	~ConsolePrint() {};

	static void printColorMessage(std::string message, std::string description, unsigned int color) {
		SetConsoleTextAttribute(CONSOLE_HANDLE, color);
		std::cout << message << "\n";
		SetConsoleTextAttribute(CONSOLE_HANDLE, 7);

        if (description != "") {
            std::cout << '\n';
            std::cout <<description << '\n';
        }
           

		if (color == ConsolePrint::c_ERROR) {
            system("pause");
			exit(-1);
		}
	}
};






// attempts to run COSMOS compilator on modified project
void runCompilator(void) {

    std::cout << "running COSMOS compilator : ";
    const char* cmd = "make.exe 2>&1";

    char buffer[128];
    std::string result = "";
    FILE* pipe;
    try {
        pipe = _popen(cmd, "r");
        if (!pipe) {
            ConsolePrint::printColorMessage("ERROR", "could not open or find ./make.exe", ConsolePrint::c_ERROR);
        }
    }
    catch (...) {
        ConsolePrint::printColorMessage("ERROR", "could not open or find ./make.exe", ConsolePrint::c_ERROR);
    }
    
    
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    }
    catch (...) {
        _pclose(pipe);
        throw;
    }
    auto status = _pclose(pipe);

    if (status != 0)
        ConsolePrint::printColorMessage("ERROR", result, ConsolePrint::c_ERROR);
    else
        ConsolePrint::printColorMessage("SUCCESS", "", ConsolePrint::c_SUCCESS);

}



#endif