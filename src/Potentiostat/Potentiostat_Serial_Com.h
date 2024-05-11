/**************************************************************************/
/*!
    @file     Potentiostat_Sherial_Com.h
    @author   Gustav Wiberg
    @license  BSD (see license.txt)

    This is a library to control the serial communication of the Potentiostat Shield.

    ----> http://www.nordicec.com/Product/Potentiostat_Shield

    created 2021
  by Gustav Wiberg

    @section  HISTORY

    v1.0  - First release

*/
/**************************************************************************/





#ifndef _Potentiostat_Serial_COM_H_
#define _Potentiostat_Serial_COM_H_

#define Potentiostat_Serial_COM_LIB_VERSION       (F("1.0.0"))


#include "Potentiostat_State.h"
#include "Potentiostat_EC_Tech.h"


#define ARRAYSIZE 20


enum PotCom: uint8_t{ 
  allComs, CELL, CMODE, IE, SET, ABORT , HALT, DEBUG, RAMP, VGND, STEP};

class Potentiostat_Serial_Com
{
    public:
    Potentiostat_Serial_Com();
    void begin();
     void GetCOM( Potentiostat_State &Pot, Potentiostat_EC_Tech &Tech);
     void Potentiostat_Serial_Com::PlotData(Potentiostat_State& Pot);


   // Potentiostat_Shield  Pot;
   // Potentiostat_EC_Tech  Tech;

    int intSerAvailable=0;
    int Debug=0;
    const String PotCOM[ARRAYSIZE] = { "/?", "CELL", "CMODE", "IE", "SET", "ABORT","HALT","DEBUG","RAMP", "VGND","STEP"};
    unsigned long LastSerialPlot=0;
    long update_dT=100000;
};


#endif // _Potentiostat_Shield_H_
