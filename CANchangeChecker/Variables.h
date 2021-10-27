#ifndef _VARIABLES_H_
#define _VARIABLES_H_




#define PATH_HEADER_FILE "./inc/CustomCANTx.h"
#define PATH_CONFIG_FILE "./licznik.txt"

#define MODIFICATION_ERROR true
#define COMPILATION_ERROR true


bool MODIFICATION_ERROR_STATUS = false;
bool COMPILATION_ERROR_STATUS = false;

HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

std::string MODIFICATION_ERROR_MESSAGE;
#define COMPILATION_ERROR_MESSAGE "  - COMPILATION ERROR CODES ARE DISPLAYED HIGHER (IF MODIFICATION IS SUCCESS)\n  - PLEASE FIX COMPILATION AND/OR MODIFICATION ERRORS\n  - DO NOT CHANGE 'licznik.txt'\n";



// global struct for storing read data from 'licznik.txt' file
struct ConfigData {
	unsigned int compile_time = 0;
	unsigned int random_byte1 = 0;
	unsigned int random_byte2 = 0;
} CONFIG_DATA_CONTAINER;





#define BEGINNINGTEXT	"														\n\
//****************************************************************************//\n\
//                                                                            //\n\
//   Header file for including of Timers                                      //\n\
//   Filename: CustomCANTx.h.h                                                //\n\
//   Date: 03.03.2015                                                         //\n\
//   Time: 11:04:24                                                           //\n\
//                                                                            //\n\
//****************************************************************************//\n\
										                                        \n\
#ifndef __CUSTOMCANTX_H__														\n\
#define __CUSTOMCANTX_H__                                                       \n\
										                                        \n";



#define CUSTOMBLINK_METHOD	"											\n\
// special function checking whether software was uploaded correctly    \n\
// THIS CODE IS GENERATED AUTOMATICALLY DO NOT CHANGE IT                \n\
void sendBlinkBit(tByte bSend){                                         \n\
	if(bSend != 0){                                                     \n\
		mTX.dwIdentifier = 0x400;                                       \n\
		mTX.bLength = 2;                                                \n\
		mTX.bIs29Bit = 0;                                               \n\
		mTX.abData[0] = CUSTOM_BLINK_BYTE1;							    \n\
		mTX.abData[1] = CUSTOM_BLINK_BYTE2;							    \n\
		APIFTM_bSendCANMessage(&mTX);								    \n\
	}																    \n\
}																	    \n";				
									


#define CUSTOMBLINK_TIMER	"											\n\
	// timer for special function sendBlinkBit							\n\
	// THIS CODE IS GENERATED AUTOMATICALLY DO NOT CHANGE IT            \n\
	sendBlinkBit((tByte)(GET_TIMER_CAN == 12));							\n";














#define CAN_METHOD_BEGINNING 			"																		\n\
										// special function checking whether software was uploaded correctly   \n\
										// THIS CODE IS GENERATED AUTOMATICALLY DO NOT CHANGE IT               \n\
										void sendBlinkBit(tByte bSend){                                        \n\
										   if(bSend != 0){                                                     \n\
										       mTX.dwIdentifier = 0x400;                                       \n\
										       mTX.bLength = 1;                                                \n\
										       mTX.bIs29Bit = 0;                                               \n";

// string representation of end part of sendBlinkBit() function 
// together with output of constructCANMethod() and CAN_METHOD_BEGINNING they represent full function
std::string CAN_METHOD_END =			"       APIFTM_bSendCANMessage(&mTX);                                   \n"
										"   }                                                                   \n"
										"}																		\n";


//string representation of executing sendBlinkBit with timer in code
std::string CAN_METHOD_TIMER =			"																		\n"
										"		// execution of special function sendBlinkBit					\n"
										"		// THIS CODE IS GENERATED AUTOMATICALLY							\n"
										"		sendBlinkBit((tByte)(GET_TIMER_CAN == 12));						";

#endif
