# CAN_checker

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/powered-by-electricity.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/fixed-bugs.svg)](https://forthebadge.com)

## Table of Contents
* [How it works](#How-it-works)
* [Software required](#Software-required)
* [Licznik.txt](#Licznik.txt)
* [Error handling](#Error-handling)
* [Comments and adnotations](#Comments-and-adnotations)
* [Licence](#Licence)
* [Authors](#Authors)



## How it works

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
