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
#include "Potentiostat_EC_Tech.h"
#include "Potentiostat_Serial_Com.h"
#include "Potentiostat_SW_PID.h"

#include "MCP_DAC.h" //Using the library in order to use the MCP4921
// URL: https://github.com/RobTillaart/MCP_DAC





/////////////////////////////////////////////////////////////////
//Shield hardware configuration:

//DAC chip
//MCP4921  sh;
MCP4921 DAC_SPI;  // HW SPI

Potentiostat_Shield Pot;
Potentiostat_EC_Tech Tech;
Potentiostat_Serial_Com Communicator(Pot,Tech);
Potentiostat_SW_PID SW_Regulator;

        // incoming serial byte
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////
// SETUP    
void setup() {


Communicator.begin();

    /////Sets the speed to fast if needed)
    
    Serial.println("Ini start");
    Serial.println(F("@ ---------------------------------------------------------"));
    Serial.println("@ ");
    Serial.println("@ ");
    Serial.println(F("@ Initialisation of Potentiostat v1.6"));

    Pot.begin();
    SW_Regulator.begin();
  
    // initialize SPI: DAC

    DAC_SPI.begin(Pot.SPI_chipSelectPin); //
    DAC_SPI.setGain(2);// Gain 2
    DAC_SPI.setBufferedMode(1); //Buffered reference
    DAC_SPI.analogWrite(2048, 0); //start value

  Serial.println("@ ---------------   ------------");
 
  delay(2000);
  
  Serial.println("@ ");
  Serial.println(F("@---------------------------------------------------------"));
  Serial.println(F("@ Initialisation of Potentiostat Done"));
  Serial.println("Ini Done");
  
  Serial.println("@ ---------------------------------------------------------");
  Serial.println("@ Time(ms)\tE(mV)\ti(A)");
  Serial.read();  //clears incoming text.


}


///////////////////////////////////////////////////////////////////////////
///Main
void loop() {

//1. Check for commands
    Communicator.GetCOM(Pot,Tech); // Get commands over the serial port.


//2. Read Analog values

    delay(0);
    Pot.Read_valueRE(); //Reads Potential
    delay(1);
    Pot.Read_valueI();//Reads Current
         
//3. Plot Values
    Communicator.PlotData(Pot);

 
//4. Run Tech
Tech.runECtech();


//5. Run PID regulator
SW_Regulator.PID(Tech.setValue,Pot.Get_Ctrl_Value()); //in mV rel GND
 
//6....//////////////SETS DAC 
    DAC_SPI.analogWrite(SW_Regulator.Output());
   
}
