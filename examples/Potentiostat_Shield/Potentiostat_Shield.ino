/**************************************************************************/
/*!
    @file     Potentiostat_Shield.ino
    @author   Gustav Wiberg
    @license  BSD (see license.txt)

    This is example code to use the Potentiostat Shield.

    ----> http://www.nordicec.com/Product/Potentiostat_Shield

    created 2021
  by Gustav Wiberg
*/
/**************************************************************************/
/*

  This example code is in the public domain.

*/

#include <Arduino.h>


#include "Potentiostat_Shield.h"

Potentiostat_Shield PotShield;


// SETUP    
void setup() {

PotShield.begin();

}


///////////////////////////////////////////////////////////////////////////
///Main
void loop() {

//1. Check for commands
    PotShield.GetCOM(); // Get commands over the serial port.

//2. Read Analog values
    PotShield.Read_Analog_Values();
//3. Plot Values
    PotShield.PlotData();
 
//4. Run Tech
    PotShield.runECtech();

//5. Run PID regulator
    PotShield.PID_Regulator(); //in mV rel GND
 
//6..SETS DAC 
    PotShield.Analog_Write();
   
}
