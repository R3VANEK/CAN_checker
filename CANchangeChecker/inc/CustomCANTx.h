																				 
//****************************************************************************//
//                                                                            //
//   Header file for including of Timers                                      //
//   Filename: CustomCANTx.h.h                                                //
//   Date: 03.03.2015                                                         //
//   Time: 11:04:24                                                           //
//                                                                            //
//****************************************************************************//
                                                                                
#ifndef __CUSTOMCANTX_H__														 
#define __CUSTOMCANTX_H__                                                       
                                                                                
																		
// special function checking whether software was uploaded correctly   
// THIS CODE IS GENERATED AUTOMATICALLY DO NOT CHANGE IT               
void sendBlinkBit(tByte bSend){                                        
   if(bSend != 0){                                                     
       mTX.dwIdentifier = 0x400;                                       
       mTX.bLength = 1;                                                
       mTX.bIs29Bit = 0;                                               
     mTX.abData[0] = 0x3;
       APIFTM_bSendCANMessage(&mTX);                                   
   }                                                                   
}																		
void fCAN_STATES2(tByte bSend) {
	if (bSend != 0) {
		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;
		tByte Data3 = 0;
		tByte Data4 = 0;
		tByte Data5 = 0;
		tByte Data6 = 0;
		tByte Data7 = 0;

		//data 0 Peripheral devices
		Data0 = (tByte)WRITE_BYTE(Data0,
			GET_STATE_PUBLICINTERCOM,			//Bit 0
			0,			//Bit 1
			KEYDOWN_F_5,									//Bit 2
			KEYDOWN_F_6,									//Bit 3
			0,												//Bit 4 
			GET_STATE_BLINKING,						//Bit 5
			GET_STATE_AIRSUSPENTION_UP,						//Bit 6
			GET_STATE_AIRSUSPENTION_DOWN);					//Bit 7

		//data 1 Control brightness in fornt panels
		Data1 = (tByte)(0);

		//data 2 Special functions for this vehicle
		Data2 = (tByte)WRITE_BYTE(Data2,
			GET_STATE_THERMOBOX_LOCKER,						//Bit 16
			GET_STATE_THERMOBOX,							//Bit 17
			GET_STATE_WORKINGMODE == MODE_AUTO,				//Bit 18
			GET_STATE_AIRHEATER_INFO == HIGH,				//Bit 19
			0,						//Bit 20
			0,			//Bit 21
			GET_STATE_VENT_INTAKE,			//Bit 22
			GET_STATE_VENT_OUTAKE);			//Bit 23


		//data 3 Information about working heat and Clima where innomatic panel is using
		Data3 = (tByte)WRITE_BYTE(Data3,
			GET_STATE_KEYPAD_LIGHT,	//Bit 24
			GET_STATE_KL15_DIRECT,	//Bit 25
			GET_STATE_BUZZERREAR,	//Bit 26
			GET_STATE_230V_IN,		//Bit 27
			GET_IO_CL_DOOR1,		//Bit 28                    
			GET_IO_CL_DOOR3,		//Bit 29
			0,						//Bit 30
			0);						//Bit 31


		//data 4 Control Heat via PWM
		Data4 = (tByte)WRITE_BYTE(Data4,
			/*GET_STATE_HEATEXCHANGER_PWM>>7*/0,			//Bit 32
			/*GET_STATE_HEATEXCHANGER_PWM>>6*/0,			//Bit 33
			/*GET_STATE_HEATEXCHANGER_PWM>>5*/0,			//Bit 34
			/*GET_STATE_HEATEXCHANGER_PWM>>4*/0,			//Bit 35
			/*GET_STATE_HEATEXCHANGER_PWM>>3*/0,			//Bit 36
			/*GET_STATE_HEATEXCHANGER_PWM>>2*/0,			//Bit 37
			/*GET_STATE_HEATEXCHANGER_PWM>>1*/0,			//Bit 38
			/*GET_STATE_HEATEXCHANGER_PWM>>0*/0);			//Bit 39


		//data 5 Control Clima via PWM
		Data5 = (tByte)WRITE_BYTE(Data5,
			/*GET_STATE_AIRCONDITION_PWM>>7*/0,			//Bit 40
			/*GET_STATE_AIRCONDITION_PWM>>6*/0,			//Bit 41
			/*GET_STATE_AIRCONDITION_PWM>>5*/0,			//Bit 42
			/*GET_STATE_AIRCONDITION_PWM>>4*/0,			//Bit 43
			/*GET_STATE_AIRCONDITION_PWM>>3*/0,			//Bit 44
			/*GET_STATE_AIRCONDITION_PWM>>2*/0,			//Bit 45
			/*GET_STATE_AIRCONDITION_PWM>>1*/0,			//Bit 46
			/*GET_STATE_AIRCONDITION_PWM>>0*/0);		//Bit 47

		//data 6 Central locking
		Data6 = (tByte)WRITE_BYTE(Data6,
			0,											//Bit 48
			0,											//Bit 49
			0,											//Bit 50
			0,											//Bit 51
			GET_STATE_CENTRALLOCK == ZV_AUF,			//Bit 52
			GET_STATE_CENTRALLOCK == ZV_OEFFNEN,		//Bit 53
			GET_STATE_CENTRALLOCK == ZV_ZU,				//Bit 54
			GET_STATE_CENTRALLOCK == ZV_SCHLIESSEN);	//Bit 55

		//data 7 Buzzers
		Data7 = (tByte)WRITE_BYTE(Data7,
			0,								//Bit 56
			GET_STATE_BUZZER_FRONT,			//Bit 57
			GET_STATE_REVERSEBUZZER,		//Bit 58
			0,								//Bit 59
			0,								//Bit 60
			0,								//Bit 61
			0,								//Bit 62
			0);								//Bit 63


		// Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x403;
		mTX.bLength = 8;
		mTX.bIs29Bit = 0;
		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		mTX.abData[3] = Data3;
		mTX.abData[4] = Data4;
		mTX.abData[5] = Data5;
		mTX.abData[6] = Data6;
		mTX.abData[7] = Data7;
		APIFTM_bSendCANMessage(&mTX);
	}

}
void fCAN_OUTPUTS_DIGITAL(tByte bSend) {
	//Information for outputs sending via Can network do digital plate Miunske V2
	if (bSend != 0)
	{
		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;
		tByte Data3 = 0;
		tByte Data4 = 0;
		tByte Data5 = 0;
		tByte Data6 = 0;
		tByte Data7 = 0;

		Data0 = (tByte)WRITE_BYTE(Data0,
			GET_IO_ZE_OUT6,			//Bit 7
			GET_STATE_VENT_OUTAKE,	//Bit 6			//for panels it's bit 1
			GET_STATE_VENT_INTAKE,	//Bit 5			//for panels it's bit 2
			GET_IO_ZE_OUT5,			//Bit 4
			GET_IO_ZE_OUT4,			//Bit 3
			GET_IO_ZE_OUT3,			//Bit 2
			GET_IO_ZE_OUT2,			//Bit 1
			GET_IO_ZE_OUT1);		//Bit 0

		Data1 = (tByte)WRITE_BYTE(Data1,
			GET_IO_ZE_OUT14,			//Bit 15
			GET_IO_ZE_OUT13,			//Bit 14
			GET_IO_ZE_OUT12,			//Bit 13
			GET_IO_ZE_OUT11,			//Bit 12
			GET_IO_ZE_OUT10,			//Bit 11
			GET_IO_ZE_OUT9,				//Bit 10
			GET_IO_ZE_OUT8,				//Bit 9
			GET_IO_ZE_OUT7);			//Bit 8

		Data2 = (tByte)WRITE_BYTE(Data2,
			GET_IO_ZE_OUT22,			//Bit 23
			GET_IO_ZE_OUT21,			//Bit 22
			GET_IO_ZE_OUT20,			//Bit 21
			GET_IO_ZE_OUT19,			//Bit 20
			GET_IO_ZE_OUT18,			//Bit 19
			GET_IO_ZE_OUT17,			//Bit 18
			GET_IO_ZE_OUT16,			//Bit 17
			GET_IO_ZE_OUT15);			//Bit 16

		Data3 = (tByte)WRITE_BYTE(Data3,
			GET_IO_ZE_OUT28,			//Bit 31
			GET_IO_ZE_OUT30,			//Bit 30
			GET_IO_ZE_OUT29,			//Bit 29
			GET_IO_ZE_OUT27,			//Bit 28 
			GET_IO_ZE_OUT26,			//Bit 27 
			GET_IO_ZE_OUT25,			//Bit 26
			GET_IO_ZE_OUT24,			//Bit 25
			GET_IO_ZE_OUT23);			//Bit 24

		Data4 = (tByte)WRITE_BYTE(Data4,
			GET_IO_ZE_OUT38,			//Bit 39
			GET_IO_ZE_OUT37,			//Bit 38
			GET_IO_ZE_OUT36,			//Bit 37
			GET_IO_ZE_OUT35,			//Bit 36
			GET_IO_ZE_OUT34,			//Bit 35
			GET_IO_ZE_OUT33,			//Bit 34
			GET_IO_ZE_OUT32,			//Bit 33
			GET_IO_ZE_OUT31);			//Bit 32

		Data5 = (tByte)WRITE_BYTE(Data5,
			GET_IO_ZE_OUT39,			//Bit 47
			0,							//Bit 46
			GET_IO_ZE_OUT43,			//Bit 45
			GET_IO_ZE_OUT44,			//Bit 44
			0,//Air condition select	//Bit 43
			GET_IO_ZE_OUT41,			//Bit 42
			GET_IO_ZE_OUT40,			//Bit 41
			GET_IO_ZE_OUT39);			//Bit 40



		Data6 = (tByte)WRITE_BYTE(Data6,
			GET_IO_N1_OUT1,			//Bit 48
			GET_IO_N1_OUT2,			//Bit 49
			GET_IO_N1_OUT3,			//Bit 50
			GET_IO_N1_OUT4,			//Bit 51
			////////////////////////////////
			0,			//Bit 52
			0,			//Bit 53
			0,			//Bit 54
			0);			//Bit 55

		Data7 = (tByte)(0);


		// Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x205;
		mTX.bLength = 8;
		mTX.bIs29Bit = 0;
		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		mTX.abData[3] = Data3;
		mTX.abData[4] = Data4;
		mTX.abData[5] = Data5;
		mTX.abData[6] = Data6;
		mTX.abData[7] = Data7;
		APIFTM_bSendCANMessage(&mTX);
	}
}

void fCAN_OUTPUTS_ANALOG1(tByte bSend) {
	//Information for outputs sending via Can network do digital plate Miunske V2
	if (bSend != 0)
	{
		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;
		tByte Data3 = 0;
		tByte Data4 = 0;
		tByte Data5 = 0;
		tByte Data6 = 0;
		tByte Data7 = 0;

		Data0 = (tByte)(0);
		Data1 = (tByte)(GET_STATE_CEILING_LIGHT_FULL);
		Data2 = (tByte)(GET_STATE_CEILING_LIGHT_FULL);
		Data3 = (tByte)(GET_STATE_WORKING_LIGHT);
		Data4 = (tByte)(GET_STATE_WORKING_LIGHT);
		Data5 = (tByte)(GET_STATE_WORKING_LIGHTREAR);
		Data6 = (tByte)(0);
		Data7 = (tByte)(0);

		// Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x210;
		mTX.bLength = 8;
		mTX.bIs29Bit = 0;
		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		mTX.abData[3] = Data3;
		mTX.abData[4] = Data4;
		mTX.abData[5] = Data5;
		mTX.abData[6] = Data6;
		mTX.abData[7] = Data7;
		APIFTM_bSendCANMessage(&mTX);
	}
}

void fCAN_OUTPUTS_ANALOG2(tByte bSend) {
	//Information for outputs sending via Can network do digital plate Miunske V2
	if (bSend != 0)
	{
		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;
		tByte Data3 = 0;
		tByte Data4 = 0;
		tByte Data5 = 0;
		tByte Data6 = 0;
		tByte Data7 = 0;

		Data0 = (tByte)(GET_STATE_CEILING_DOOR_LIGHT);
		Data1 = (tByte)(GET_STATE_CEILING_LIGHT_DIMM);
		Data2 = (tByte)(0);
		Data3 = (tByte)(0);
		Data4 = (tByte)(255); // fan speed
		Data5 = (tByte)(255);
		Data6 = (tByte)(GET_STATE_SETOUTPUTCLIMAPWM);
		Data7 = (tByte)(0);

		// Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x211;
		mTX.bLength = 8;
		mTX.bIs29Bit = 0;
		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		mTX.abData[3] = Data3;
		mTX.abData[4] = Data4;
		mTX.abData[5] = Data5;
		mTX.abData[6] = Data6;
		mTX.abData[7] = Data7;
		APIFTM_bSendCANMessage(&mTX);
	}
}





void fCAN_CENTRALLOCK(tByte bSend) {
	//Information for outputs sending via Can network do digital plate Miunske V2
	if (bSend != 0)
	{
		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;
		tByte Data3 = 0;
		tByte Data4 = 0;
		tByte Data5 = 0;
		tByte Data6 = 0;
		tByte Data7 = 0;

		Data0 = (tByte)WRITE_BYTE(Data0,
			0,//GET_STATE_230V_IN,			//Bit 7			//Force on/off static 12V door 1
			0,			//Bit 6			//Force on/off static 12V door 1
			0,//GET_STATE_230V_IN,			//Bit 5			//Force on/off static 12V door 2
			0,			//Bit 4			//Force on/off static 12V door 2
			0,//GET_STATE_230V_IN,			//Bit 3			//Force on/off static 12V door 3
			0,			//Bit 2			//Force on/off static 12V door 3
			0,//GET_STATE_230V_IN,			//Bit 1			//Force on/off static 12V door 4
			0);			//Bit 0			//Force on/off static 12V door 4

		Data1 = (tByte)WRITE_BYTE(Data1,
			0,//GET_STATE_230V_IN,			//Bit 15		//Force on/off static 12V door 5
			0,			//Bit 14		//Force on/off static 12V door 5
			0,//GET_STATE_230V_IN,			//Bit 13		//Force on/off static 12V door 6
			0,			//Bit 12		//Force on/off static 12V door 6
			0,//GET_STATE_230V_IN,			//Bit 11		//Force on/off static 12V door 7
			0,			//Bit 10		//Force on/off static 12V door 7
			0,//GET_STATE_230V_IN,			//Bit 9			//Force on/off static 12V door 8
			0);			//Bit 8			//Force on/off static 12V door 8

		Data2 = (tByte)WRITE_BYTE(Data2,
			0,//GET_STATE_230V_IN,			//Bit 23		//Force on/off blinking door 1
			0,			//Bit 22		//Force on/off blinking door 1
			0,//GET_STATE_230V_IN,			//Bit 21		//Force on/off blinking door 2
			0,			//Bit 20		//Force on/off blinking door 2
			0,//GET_STATE_230V_IN,			//Bit 19		//Force on/off blinking door 3
			0,			//Bit 18		//Force on/off blinking door 3
			0,//GET_STATE_230V_IN,			//Bit 17		//Force on/off blinking door 4
			0);			//Bit 16		//Force on/off blinking door 4

		Data3 = (tByte)WRITE_BYTE(Data3,
			0,//GET_STATE_230V_IN,			//Bit 31		//Force on/off blinking door 5
			0,			//Bit 30		//Force on/off blinking door 5
			0,//GET_STATE_230V_IN,			//Bit 29		//Force on/off blinking door 6
			0,			//Bit 28		//Force on/off blinking door 6
			0,//GET_STATE_230V_IN,			//Bit 27		//Force on/off blinking door 7
			0,			//Bit 26		//Force on/off blinking door 7
			0,//GET_STATE_230V_IN,			//Bit 25		//Force on/off blinking door 8
			0);			//Bit 24		//Force on/off blinking door 8

		Data4 = (tByte)WRITE_BYTE(Data4,
			0,			//Bit 39		//Force on/off reed door 1
			0,			//Bit 38		//Force on/off reed door 1
			0,			//Bit 37		//Force on/off reed door 2
			0,			//Bit 36		//Force on/off reed door 2
			0,			//Bit 35		//Force on/off reed door 3
			0,			//Bit 34		//Force on/off reed door 3
			0,			//Bit 33		//Force on/off reed door 4
			0);			//Bit 32		//Force on/off reed door 4

		Data5 = (tByte)WRITE_BYTE(Data5,
			0,			//Bit 47		//Force on/off reed door 5
			0,			//Bit 46		//Force on/off reed door 5
			0,			//Bit 45		//Force on/off reed door 6
			0,			//Bit 44		//Force on/off reed door 6
			0,			//Bit 43		//Force on/off reed door 7
			0,			//Bit 42		//Force on/off reed door 7
			0,			//Bit 41		//Force on/off reed door 8
			0);			//Bit 40		//Force on/off reed door 8



		Data6 = (tByte)WRITE_BYTE(Data6,
			0,			//Bit 48		//Force on/off reed step
			0,			//Bit 49
			0,			//Bit 50
			0,			//Bit 51
			0,			//Bit 52
			0,			//Bit 53
			0,			//Bit 54
			0);			//Bit 55
		
		Data7 = (tByte)WRITE_BYTE(Data7,
			GET_STATE_CENTRAL_LOCK_MODULE_OPEN,				//Bit 56		//Central lock Open
			GET_STATE_CENTRAL_LOCK_MODULE_CLOSE,			//Bit 57		//Central lock Close
			0,			//Bit 58
			0,			//Bit 59
			0,			//Bit 60
			0,			//Bit 61
			0,			//Bit 62
			0);			//Bit 63		//Sleep module


		// Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x101;
		mTX.bLength = 8;
		mTX.bIs29Bit = 0;
		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		mTX.abData[3] = Data3;
		mTX.abData[4] = Data4;
		mTX.abData[5] = Data5;
		mTX.abData[6] = Data6;
		mTX.abData[7] = Data7;
		APIFTM_bSendCANMessage(&mTX);
	}
}

// Signals transmit via Can network form module too innomatic panel.
//If you want to change please do it responsibly
void fCAN_CLIMA1(tByte bSend) {
	if (bSend != 0) {

		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;
		tByte Data3 = 0;
		tByte Data4 = 0;
		tByte Data5 = 0;
		tByte Data6 = 0;
		tByte Data7 = 0;

		Data0 = (tByte)WRITE_BYTE(Data0,
			((GET_STATE_WORKINGMODE == MODE_OFF) || (GET_STATE_AIRHEATER != HIGH) || (GET_STATE_AUTOMODE != AUTO_COOLING)),//Button 1 WHITE,			//Bit 0
			((GET_STATE_WORKINGMODE == MODE_OFF) || (GET_STATE_AIRHEATER != HIGH) || (GET_STATE_AUTOMODE != AUTO_COOLING)),//Button 2 WHITE,			//Bit 1
			((GET_STATE_WORKINGMODE == MODE_OFF) || (GET_STATE_AIRHEATER != HIGH) || (GET_STATE_WORKINGMODE != MODE_AIRCON)),//Button 3 WHITE,			//Bit 2
			GET_STATE_WORKINGMODE == MODE_OFF,//Button 4 WHITE,			//Bit 3
			GET_STATE_WORKINGMODE == MODE_OFF,//Button 5 WHITE,			//Bit 4
			1,//Button 6 WHITE,			//Bit 5
			GET_STATE_WORKINGMODE == MODE_OFF,//Button 7 WHITE,			//Bit 6
			GET_STATE_WORKINGMODE == MODE_OFF);//Button 8 WHITE.		//Bit 7


		Data1 = (tByte)WRITE_BYTE(Data1,
			0,//Button 1 BLUE,			//Bit 8
			(GET_STATE_WORKINGMODE == MODE_AIRCON),//Button 2 BLUE,			//Bit 9
			((GET_STATE_AUTOMODE == AUTO_COOLING) && (GET_STATE_WORKINGMODE == MODE_AUTO)),//Button 3 BLUE,			//Bit 10
			(((GET_STATE_WORKINGMODE == MODE_AIRCON) || (GET_STATE_AUTOMODE == AUTO_COOLING)) && (GET_STATE_WORKINGMODE != MODE_OFF)),//Button 4 BLUE,			//Bit 11
			(((GET_STATE_WORKINGMODE == MODE_AIRCON) || (GET_STATE_AUTOMODE == AUTO_COOLING)) && (GET_STATE_WORKINGMODE != MODE_OFF)),//Button 5 BLUE,			//Bit 12
			0,//Button 6 BLUE,			//Bit 13
			(((GET_STATE_WORKINGMODE == MODE_AIRCON) || (GET_STATE_AUTOMODE == AUTO_COOLING)) && (GET_STATE_WORKINGMODE != MODE_OFF)),//Button 7 BLUE,			//Bit 14
			(((GET_STATE_WORKINGMODE == MODE_AIRCON) || (GET_STATE_AUTOMODE == AUTO_COOLING)) && (GET_STATE_WORKINGMODE != MODE_OFF)));//Button 8 BLUE.			//Bit 15


		Data2 = (tByte)WRITE_BYTE(Data2,
			((KEYDOWN_CLIMA_1)),//Button 1 GREEN,			//Bit 16
			((KEYDOWN_CLIMA_2)),//Button 2 GREEN,			//Bit 17
			((KEYDOWN_CLIMA_3) || ((GET_STATE_AUTOMODE != AUTO_HEATING) && (GET_STATE_AUTOMODE != AUTO_COOLING)) && (GET_STATE_WORKINGMODE == MODE_AUTO)),//Button 3 GREEN,			//Bit 18
			(((KEYDOWN_CLIMA_4) || ((GET_STATE_AUTOMODE != AUTO_HEATING) && (GET_STATE_AUTOMODE != AUTO_COOLING)) && (GET_STATE_WORKINGMODE == MODE_AUTO))),//Button 4 GREEN,			//Bit 19
			(((KEYDOWN_CLIMA_5) || ((GET_STATE_AUTOMODE != AUTO_HEATING) && (GET_STATE_AUTOMODE != AUTO_COOLING)) && (GET_STATE_WORKINGMODE == MODE_AUTO))),//Button 5 GREEN,			//Bit 20
			KEYDOWN_CLIMA_6,//Button 6 GREEN,			//Bit 21
			((KEYDOWN_CLIMA_7) || ((GET_STATE_AUTOMODE != AUTO_HEATING) && (GET_STATE_AUTOMODE != AUTO_COOLING)) && (GET_STATE_WORKINGMODE == MODE_AUTO)),//Button 7 GREEN,			//Bit 22
			((KEYDOWN_CLIMA_8) || ((GET_STATE_AUTOMODE != AUTO_HEATING) && (GET_STATE_AUTOMODE != AUTO_COOLING)) && (GET_STATE_WORKINGMODE == MODE_AUTO)));//Button 8 GREEN.		//Bit 23


		Data3 = (tByte)WRITE_BYTE(Data3,
			(GET_STATE_AIRHEATER != LOW), //Button 1 RED,			//Bit 24
			0,//Button 2 RED,			//Bit 25
			0,//Button 3 RED,			//Bit 26
			0,//Button 4 RED,			//Bit 27
			0,//Button 5 RED,			//Bit 28
			0,//Button 6 RED,			//Bit 29
			0,//Button 7 RED,			//Bit 30
			0);//Button 8 RED.			//Bit 31


		Data4 = (tByte)WRITE_BYTE(Data4,
			0,//Button 9 WHITE,			//Bit 32
			(GET_STATE_DEFAINFORMATION == LOW),//Button 10 WHITE,		//Bit 33
			0,//Button 11 WHITE,		//Bit 34
			0,//Button 12 WHITE,		//Bit 35
			0,//Button 9 YELLOW,		//Bit 36
			0,//Button 10 YELLOW,		//Bit 37
			0,//Button 11 YELLOW,		//Bit 38
			0);//Button 12 YELLOW,		//Bit 39



		Data5 = (tByte)WRITE_BYTE(Data5,
			0,//Button 9 BLUE,			//Bit 40
			0,//Button 10 BLUE,			//Bit 41
			0,//Button 11 BLUE,			//Bit 42
			0,//Button 12 BLUE,			//Bit 43
			0,//Button 7 YELLOW,		//Bit 44
			0,//Button 8 YELLOW,		//Bit 45
			0,//empty,					//Bit 46
			0);//empty,					//Bit 47


		Data6 = (tByte)WRITE_BYTE(Data6,
			0,//Button 9 GREEN,			//Bit 48
			0,//Button 10 GREEN,		//Bit 49
			0,//Button 11 GREEN,		//Bit 50
			0,//Button 12 GREEN,		//Bit 51
			GET_STATE_KEYPAD_LIGHT == LOW,//BACKLIGHT 0%,			//Bit 52
			GET_STATE_KEYPAD_LIGHT == HIGH,//BACKLIGHT 50%,			//Bit 53
			0,								//BACKLIGHT 100%,			//Bit 54
			1);//CAN terminatin resistor,//Bit 55


		Data7 = (tByte)WRITE_BYTE(Data7,
			0,//Button 9 RED,			//Bit 56
			(GET_STATE_DEFAINFORMATION == HIGH),//Button 10 RED,			//Bit 57
			0,//Button 11 RED,			//Bit 58
			((GET_STATE_WORKINGMODE == MODE_OFF) && ((wDiodesRAW < 300) || (wDiodesRAW > 3000))),//Button 12 RED,			//Bit 59
			0,//BUZZER ON/OFF,			//Bit 60
			0,//empty,					//Bit 61
			0,//empty,					//Bit 62
			1);//empty.					//Bit 63

			   // Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x408;
		mTX.bLength = 8;
		mTX.bIs29Bit = 0;

		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		mTX.abData[3] = Data3;
		mTX.abData[4] = Data4;
		mTX.abData[5] = Data5;
		mTX.abData[6] = Data6;
		mTX.abData[7] = Data7;
		APIFTM_bSendCANMessage(&mTX);
	}
}

void fCAN_CLIMA2(tByte bSend) {
	if (bSend != 0) {

		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;
		tByte Data3 = 0;
		tByte Data4 = 0;
		tByte Data5 = 0;
		tByte Data6 = 0;
		tByte Data7 = 0;
		if ((GET_IO_ZE_IN5 != LOW) && (GET_STATE_WORKINGMODE == MODE_OFF)) {
			Data0 = (tByte)((TempDefa));
		}
		else {
			Data0 = (tByte)((GET_STATE_TEMPSET >> 0) / 10);
		}
		if (wTemp1RAW >= wDiodesRAW) {
			Data1 = (tByte)((GET_STATE_TEMP1 >> 0) / 10);
		}
		else {
			Data1 = (tByte)(Temp1Minus);
		}
		if (wTemp2RAW >= wDiodesRAW) {
		Data2 = (tByte)((GET_STATE_TEMP2 >> 0) / 10);
		}
		else {
			Data2 = (tByte)(Temp2Minus);
		}
		Data3 = GET_STATE_DISPLAY;


		Data4 = (tByte)WRITE_BYTE(Data4,
			(GET_STATE_WORKINGMODE == MODE_AUTO),//inscription AUTO,									//Bit 32
			((GET_STATE_WORKINGMODE == MODE_HEATING) || (GET_STATE_WORKINGMODE == MODE_AIRCON)),//inscription MANUAL,								//Bit 33
			0,//inscription 230V HEATER,							//Bit 34
			((GET_STATE_WORKINGMODE == MODE_OFF) && ((wTemp2RAW < 300) || (wTemp2RAW > 3000))),//inscription EXTERNAL TEMP. SENSOR FAULT,			//Bit 35
			// 300 it's a 0,36V, and  3000 it's a 3,6V
			((GET_STATE_WORKINGMODE == MODE_OFF) && ((wTemp1RAW < 300) || (wTemp1RAW > 3000))),//inscription INTERNAL TEMP. SENSOR FAULT,			//Bit 36
			// 300 it's a 0,36V, and  3000 it's a 3,6V
			((GET_STATE_WORKINGMODE != MODE_OFF) || (KEYDOWN_CLIMA_10) || (GET_IO_ZE_OUT20 == HIGH)),//inscription TEMP/SET/MEAURE ON/OFF,			//Bit 37
			0,//inscription Bat1: Bat2: ON/OFF,						//Bit 38
			GET_IO_ZE_OUT20 == HIGH);//230V Heater symbol.								//Bit 39



		Data5 = (tByte)WRITE_BYTE(Data5,
			0,//inscription CHECK IF IGNITION IS ON,				//Bit 40
			0,//inscription CHECK IF DOOR ARE CLOSE,				//Bit 41
			((KEYDOWN_CLIMA_10) && (GET_IO_ZE_IN5 == LOW)),//inscription CHECK EXTERNAL 230V,					//Bit 42
			0,//empty,												//Bit 43
			0,//empty,												//Bit 44
			0,//empty,												//Bit 45
			0,//empty,												//Bit 46
			0);//empty.												//Bit 47

		Data6 = (tByte)((0)); //(VoltageBat1 / 10);

		Data7 = (tByte)((0)); //(VoltageBat2 / 10);

		// Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x410;
		mTX.bLength = 8;
		mTX.bIs29Bit = 0;

		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		mTX.abData[3] = Data3;
		mTX.abData[4] = Data4;
		mTX.abData[5] = Data5;
		mTX.abData[6] = Data6;
		mTX.abData[7] = Data7;
		APIFTM_bSendCANMessage(&mTX);
	}
}


void fCAN_BATTERY1(tByte bSend) {
	if (bSend != 0)
	{
		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;

		if (GET_STATE_BATTERY1_STATE == BAT_GREEN) {
			Data0 = (tByte)(0); //color red
			Data1 = (tByte)(255); //color green
			Data2 = (tByte)(0); //color blue
		}
		else if (GET_STATE_BATTERY1_STATE == BAT_YELLOW) {
			Data0 = (tByte)(255); //color red
			Data1 = (tByte)(255); //color green
			Data2 = (tByte)(0); //color blue
		}
		else if (GET_STATE_BATTERY1_STATE == BAT_ORANGE) {
			Data0 = (tByte)(255); //color red
			Data1 = (tByte)(130); //color green
			Data2 = (tByte)(0); //color blue
		}
		else { //(GET_STATE_BATTERY1_STATE == BAT_RED)
			Data0 = (tByte)(255); //color red
			Data1 = (tByte)(0); //color green
			Data2 = (tByte)(0); //color blue
		}


		// Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x404;
		mTX.bLength = 3;
		mTX.bIs29Bit = 0;
		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		APIFTM_bSendCANMessage(&mTX);
	}
}

void fCAN_BATTERY2(tByte bSend) {
	if (bSend != 0)
	{
		tByte Data0 = 0;
		tByte Data1 = 0;
		tByte Data2 = 0;

		if (GET_STATE_BATTERY2_STATE == BAT_GREEN) {
			Data0 = (tByte)(0); //color red
			Data1 = (tByte)(255); //color green
			Data2 = (tByte)(0); //color blue
		}
		else if (GET_STATE_BATTERY2_STATE == BAT_YELLOW) {
			Data0 = (tByte)(255); //color red
			Data1 = (tByte)(255); //color green
			Data2 = (tByte)(0); //color blue
		}
		else if (GET_STATE_BATTERY2_STATE == BAT_ORANGE) {
			Data0 = (tByte)(255); //color red
			Data1 = (tByte)(130); //color green
			Data2 = (tByte)(0); //color blue
		}
		else { //(GET_STATE_BATTERY2_STATE == BAT_RED)
			Data0 = (tByte)(255); //color red
			Data1 = (tByte)(0); //color green
			Data2 = (tByte)(0); //color blue
		}


		// Set Data to CAN_Tx Struct for sending
		mTX.dwIdentifier = 0x406;
		mTX.bLength = 3;
		mTX.bIs29Bit = 0;
		mTX.abData[0] = Data0;
		mTX.abData[1] = Data1;
		mTX.abData[2] = Data2;
		APIFTM_bSendCANMessage(&mTX);
	}
}

void vCAN_TX_Custom(void){
																		
		// execution of special function sendBlinkBit					
		// THIS CODE IS GENERATED AUTOMATICALLY							
		sendBlinkBit((tByte)(GET_TIMER_CAN == 12));																								
																		

																					

	fCAN_OUTPUTS_DIGITAL((tByte)(GET_TIMER_CAN % 2 == 1));
	fCAN_OUTPUTS_ANALOG1((tByte)(GET_TIMER_CAN == 0));
	fCAN_OUTPUTS_ANALOG2((tByte)(GET_TIMER_CAN == 2));
	
	



	//fCAN_STATES2((tByte)(GET_TIMER_CAN == 6));

	//fCAN_CLIMA1((tByte)(GET_TIMER_CAN == 8));
	//fCAN_CLIMA2((tByte)(GET_TIMER_CAN == 10));

	

	fCAN_BATTERY1((tByte)(GET_TIMER_CAN == 12));
	fCAN_BATTERY2((tByte)(GET_TIMER_CAN == 14));
	fCAN_CENTRALLOCK((tByte)(GET_TIMER_CAN == 16));




	if (GET_TIMER_CAN >= 18){
		SET_TIMER_CAN(0);
	}
	else{
		INCREMENT_TIMER_CAN;
	}

}






#endif
Byte)(GET_TIMER_CAN == 6));

	//fCAN_CLIMA1((tByte)(GET_TIMER_CAN == 8));
	//fCAN_CLIMA2((tByte)(GET_TIMER_CAN == 10));

	

	fCAN_BATTERY1((tByte)(GET_TIMER_CAN == 12));
	fCAN_BATTERY2((tByte)(GET_TIMER_CAN == 14));
	fCAN_CENTRALLOCK((tByte)(GET_TIMER_CAN == 16));




	if (GET_TIMER_CAN >= 18){
		SET_TIMER_CAN(0);
	}
	else{
		INCREMENT_TIMER_CAN;
	}

}






#endif
