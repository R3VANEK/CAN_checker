#ifndef _OTHER_H_
#define _OTHER_H_




class ConsolePrint {

public:
	static const unsigned int c_ERROR = 12;
	static const unsigned int c_WARNING = 14;
	static const unsigned int c_SUCCESS = 160;

	ConsolePrint() {}
	~ConsolePrint() {};

	static void printColorMessage(std::string message, unsigned int color) {
		SetConsoleTextAttribute(CONSOLE_HANDLE, color);
		std::cout << message << "\n";
		SetConsoleTextAttribute(CONSOLE_HANDLE, 7);

		if (color == ConsolePrint::c_ERROR) {
			exit(-1);
		}
	}
};



#endif