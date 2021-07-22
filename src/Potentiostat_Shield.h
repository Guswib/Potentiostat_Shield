/**************************************************************************/
/*!
    @file     Potentiostat_Shield.h
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






#include <Arduino.h>


#include "Potentiostat_State.h"
#include "Potentiostat_EC_Tech.h"
#include "Potentiostat_Serial_Com.h"
#include "Potentiostat_SW_PID.h"


#include "MCP_DAC.h" //Using the library in order to use the MCP4921


#ifndef _Potentiostat_Shield_H_
#define _Potentiostat_Shield_H_

#define Potentiostat_Shield_LIB_VERSION       (F("1.0.0"))




class Potentiostat_Shield
{

    public:
    Potentiostat_Shield();
    void begin();
    void GetCOM();
    void Read_Analog_Values();
    void PlotData();
    void runECtech();
    void PID_Regulator();
    void Analog_Write();

    Potentiostat_State PotState;
    Potentiostat_EC_Tech Tech;
    Potentiostat_Serial_Com Communicator;
    Potentiostat_SW_PID SW_Regulator;

    MCP4921 DAC_SPI;  // HW SPI

};

#endif
