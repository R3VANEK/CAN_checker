#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include <string>




#define PATH_HEADER_FILE "./inc/CustomCANTx.h"
//#define PATH_HEADER_FILE "./original.txt"
#define PATH_CONFIG_FILE "./licznik.txt"


char BLINK_BIT_OLD;
char BLINK_BIT_NEW;


struct configurationData {

	int NUMBER_COMPILE;
	unsigned int BLINK_BIT_CURRENT;
} config_data_container;



std::string BEGINNING_HEADER =			"//****************************************************************************//\n"
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


std::string CAN_METHOD_BEGINNING =		"// special function checking whether software was updated correctly    \n"
										"// this code is generated automatically by script, DO NOT CHANGE IT    \n"
										"void sendBlinkBit(tByte bSend){                                        \n"
										"   if(bSend != 0){                                                     \n";
									

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
