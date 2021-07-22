/**************************************************************************/
/*!
    @file     Potentiostat_Shield.cpp
    @author   Gustav Wiberg
    @license  BSD (see license.txt)

    This is a  software to control a Potentiostat Shield.

    ----> http://www.nordicec.com/Product/Potentiostat_Shield

    created 2021
  by Gustav Wiberg

    @section  HISTORY

    v1.0  - First release

*/
/**************************************************************************/





#include "Potentiostat_Shield.h"

Potentiostat_Shield::Potentiostat_Shield()
{};

void Potentiostat_Shield::begin()
{

Communicator.begin();

    /////Sets the speed to fast if needed)
    
     delay(2000);

    Serial.println(F("@ ---------------------------------------------------------"));
    Serial.println("Ini start");
    Serial.println(F("@ ---------------------------------------------------------"));
    Serial.println(F("@ Initialisation of Potentiostat Shield v1.6"));
    Serial.println("@ ");
    Serial.print("@ Library version");
    Serial.println(Potentiostat_Shield_LIB_VERSION);
      
    PotState.begin();
    Tech.begin();
    
    SW_Regulator.begin();
  
    // initialize SPI: DAC

    DAC_SPI.begin(PotState.SPI_chipSelectPin); //
    DAC_SPI.setGain(2);// Gain 2
    DAC_SPI.setBufferedMode(1); //Buffered reference
    DAC_SPI.analogWrite(2048, 0); //start value

  Serial.println(F("@---------------------------------------------------------"));
  
  delay(2000);
  
  Serial.println("@ ");
  Serial.println(F("@---------------------------------------------------------"));
  Serial.println(F("@ Initialisation of Potentiostat Done"));
  Serial.println("Ini Done");
  
  Serial.println("@ ---------------------------------------------------------");
  Serial.println("@ Time(ms)\tE(mV)\ti(A)");
  Serial.read();  //clears incoming text.

}


void Potentiostat_Shield::GetCOM()
{
    Communicator.GetCOM(PotState,Tech); // Get commands over the serial port.
}


void Potentiostat_Shield::Read_Analog_Values()
{
    
    delay(0);
    PotState.Read_valueRE(); //Reads Potential
    delay(1);
    PotState.Read_valueI();//Reads Current
    
}

void Potentiostat_Shield::PlotData()
{
    Communicator.PlotData(PotState);
}


void Potentiostat_Shield::runECtech()
{   
    Tech.runECtech();
}

void Potentiostat_Shield::PID_Regulator()
{   
    SW_Regulator.PID(Tech.setValue,PotState.Get_Ctrl_Value()); //in mV rel GND
}

void Potentiostat_Shield::Analog_Write()
{   
    DAC_SPI.analogWrite(SW_Regulator.Output());
}
