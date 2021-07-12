# CAN_checker

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/powered-by-electricity.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/fixed-bugs.svg)](https://forthebadge.com)

## Table of Contents
* [Description](#Description)
* [How it works](#How-it-works)
* [Software required](#Software-required)
* [Licznik.txt](#Licznik.txt)
* [Error handling](#Error-handling)
* [Comments and adnotations](#Comments-and-adnotations)
* [Licence](#Licence)
* [Authors](#Authors)



## Description

Updating software in Miunske CAN Modules can sometimes be a little tricky. You wrote a good, working code, open miunsketoolchain app to upload it, progress bar goes up to 100% 
and says "done". You are happy and ready to test it out, but appearently it just don't work as you would except. It may be the case that despite no warnings, in reality you 
didn't update software on module. So with that in mind, how to tell if you really uploaded your program correctly? There comes CAN_checker! 


**CAN_checker works as .exe in your Visual Studio project. When you are done writting code just run CAN_checker and wait for validation**


* The application inserts special generated function sendBlinkingBit() into the CustomCanTx.h. What this function do is constantly send 0 or 1 to the CANId 400


* Program then run COSMOS compilator and outputs information about success or 
errors

The next step is to simply upload software to the miunsketoolchain app normally. How to determine if we uploaded correctly? Just plug to the Main CAN Module small CAN I/O Module with diode
that blinks red if it recives 0 via CANId 400 and blinks green if it detects 1 also via CANId.

Becouse of alternating beetwen sending bit 1 and 0, if you happen to see no change in color of diode you have certainty something went wrong in the uploading procedure


## How it works

When run, CAN_checker checks 2 things. It searches for licznik.txt and CustomCANTx.h If everything is ok, it inserts sendBlinkingBit() function definiton and declaration to the user's code

```C
void sendBlinkBit(tByte bSend){                                        
   if(bSend != 0){                                                     
       tByte dataBlink = 0;
       tByte data0 = 0;                                                
                                                                       
       mTX.dwIdentifier = 0x400;                                       
       mTX.bLength = 1;                                                
       mTX.bIs29Bit = 0;                                               
       mTX.abData[0] = dataBlink;                                      
       APIFTM_bSendCANMessage(&mTX);                                   
   }                                                                   
}


```


```C

void vCAN_TX_Custom(void){

  sendBlinkBit((tByte)(GET_TIMER_CAN == 12));	
  // other user code goes here unmodified by program
}

```

After modifying CustomCANtx.h, program the runs COSMOS compilator on the whole Visual Studio project and if successful outputs compiled files in ./out folder

