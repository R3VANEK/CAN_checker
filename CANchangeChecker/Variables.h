#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include <string>




#define PATH_HEADER_FILE "./inc/CustomCANTx.h"
#define PATH_CONFIG_FILE "./licznik.txt"

#define MODIFICATION_ERROR true
#define COMPILATION_ERROR true


// variable indicating if modifications of 'licznik.txt' or 'CustomCANTx.h' were succesfull
// please note that if error, other functions that modifies and compile are stopped from being executed
// - TRUE if error
// - FALSE if success
bool MODIFICATION_ERROR_STATUS = false;

// variable storing error message if MODIFICATION_ERROR_STATUS is true
std::string MODIFICATION_ERROR_MESSAGE;

// variable storing error message that is printed if COMPILATION_ERROR_STATUS is true
// it is constant becouse actual compilation error from make.exe is printed on top of console and is impossible to store it into variable
const std::string COMPILATION_ERROR_MESSAGE = "  - COMPILATION ERROR CODES ARE DISPLAYED HIGHER (IF MODIFICATION IS SUCCESS)\n  - PLEASE FIX COMPILATION AND/OR MODIFICATION ERRORS\n  - DO NOT CHANGE 'licznik.txt'\n";


// variable indicating if compilation was successfull or not
// please note that if error, function updateConfig() is still executed
// - TRUE if error
// - FALSE if success
bool COMPILATION_ERROR_STATUS = false;


// struct for storing read data from 'licznik.txt' file
struct configurationData {

	int NUMBER_COMPILE;
	unsigned int BLINK_BIT_CURRENT;

} config_data_container;


//string representation of beginning part of 'CustomCANTx.h'
std::string BEGINNING_HEADER =			"																				 \n"
										"//****************************************************************************//\n"
										"//                                                                            //\n"
										"//   Header file for including of Timers                                      //\n"
										"//   Filename: CustomCANTx.h.h                                                //\n"
										"//   Date: 03.03.2015                                                         //\n"
										"//   Time: 11:04:24                                                           //\n"
										"//                                                                            //\n"
										"//****************************************************************************//\n"
										"                                                                                \n"
										"#ifndef __CUSTOMCANTX_H__														 \n"
										"#define __CUSTOMCANTX_H__                                                       \n"
										"                                                                                \n";


// string representation of beginning part of sendBlinkBit() function 
// together with output of constructCANMethod() and CAN_METHOD_END they represent full function
std::string CAN_METHOD_BEGINNING =		"																		\n"
										"// special function checking whether software was updated correctly    \n"
										"// this code is generated automatically by script, DO NOT CHANGE IT    \n"
										"void sendBlinkBit(tByte bSend){                                        \n"
										"   if(bSend != 0){                                                     \n";
									


// string representation of end part of sendBlinkBit() function 
// together with output of constructCANMethod() and CAN_METHOD_BEGINNING they represent full function
std::string CAN_METHOD_END =			"       tByte data0 = 0;                                                \n"
										"                                                                       \n"
										"       mTX.dwIdentifier = 0x400;                                       \n"
										"       mTX.bLength = 1;                                                \n"
										"       mTX.bIs29Bit = 0;                                               \n"
										"       mTX.abData[0] = dataBlink;                                      \n"
										"       APIFTM_bSendCANMessage(&mTX);                                   \n"
										"   }                                                                   \n"
										"} \n";




#endif
