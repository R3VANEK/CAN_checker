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




Run CAN_Checker on your Visual Studio project and after completion upload software to the miunsketoolchain app normally. How to determine if we uploaded correctly? Just [plug](#Comments-and-adnotations) to the Main CAN Module small CAN I/O Module with diode that blinks red if it recives 0 via CANId 400 and blinks green if it detects 1 also via CANId. Becouse of alternating beetwen sending bit 1 and 0, if you happen to see no change in color of diode you have certainty something went wrong in the uploading procedure


## How it works

```C
void sendBlinkBit(tByte bSend){                                        
   if(bSend != 0){                                                     
       tByte dataBlink = 0; // each run of CAN_checker alternates this value 
       tByte data0 = 0;                                                
                                                                       
       mTX.dwIdentifier = 0x400;                                       
       mTX.bLength = 1;                                                
       mTX.bIs29Bit = 0;                                               
       mTX.abData[0] = dataBlink;                                      
       APIFTM_bSendCANMessage(&mTX);                                   
   }                                                                   
}


```

Upon running, application inserts into ./inc/CustomCANTx.h special function sendBlinkingBit that alternates beetwen sending 0 bit and 1 bit.
It then invokes COSMOS compiler and outputs compiled code into ./out folder


## Software required

* COSMOS compiler with compilation key in the project directory (make.exe)
* CustomCANTx.h file in the ./inc folder
* [Configured CAN I/O diode module](#Comments-and-adnotations)
* [Windows 7/8/10](#Comments-and-adnotations)





## Licznik.txt

![Licznik.txt](https://github.com/R3VANEK/CAN_checker/blob/main/README_images/licznik.png)

This file serves as config/information file. It holds : 
* Information about current set bit (0 or 1) in the sendBlinkingBit function
* Number of compilations of current project
* Proper upload diode color


## Error handling

**If any compilation error occurs its code is prompted on top of console**



![example error 1](https://github.com/R3VANEK/CAN_checker/blob/main/README_images/error1.png)

Program is tested for these errors :

* **Non-existing licznik.txt** : warning is prompted and new licznik.txt is created
* **Corrupted data in licznik.txt** : fatal error is raised, program outputs error and stop compilation
* **Non-existing CustomCANTx.h** : fatal error is raised, program ouputs error and stop compilation
* **Corrupted CustomCANTx.h (lack of user defined functions)** : fatal error is raised, program outputs error and stop compilation
* **Could not update licznik.txt** : warning is prompted, compilation was success, please modify licznik.txt manually
* **Could not read licznik.txt or CustomCANTx.h** : fatal error is raised, program outputs error and stop compilation






## Comments and adnotations

* This program was written special for specific projects architecture in B.A.U.S AT sp.z.o.o company, therefore it is not compatible/intended for use in any other project
* Becouse of use standard library Windows.h for coloring text in console, application is only runnable on Windows system
* Testing uploads as a whole require some preconfigured CAN I/O Module that register incoming bits via CANId 400 and blink diode accordingly. If you don't have this, you can
simply use some software that detects CAN signals like [CANexplorer 4](https://www.sontheim-industrie-elektronik.de/en/automation/visualization-and-monitoring/canexplorer-4/)



## Licence

All rights reserved



## Authors
Jan Napieralski  [R3VANEK](https://github.com/R3VANEK)



