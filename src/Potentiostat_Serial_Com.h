/**************************************************************************/
/*!
    @file     Potentiostat_Sherial_Com.h
    @author   Gustav Wiberg
    @license  BSD (see license.txt)

    This is a library to control the serial communication of the Potentiostat Shield.

    ----> http://www.nordicec.com/Product/Potentiostat_Shield

    created 2021
  by Gustav Wiberg
*/
/**************************************************************************/





#ifndef _Potentiostat_Serial_COM_H_
#define _Potentiostat_Serial_COM_H_

#define Potentiostat_Serial_COM_LIB_VERSION       (F("0.1.1"))


#include "Potentiostat_Shield.h"
#include "Potentiostat_EC_Tech.h"


#define ARRAYSIZE 20


class Potentiostat_Serial_Com
{
    public:
    Potentiostat_Serial_Com( Potentiostat_Shield &Pot_in, Potentiostat_EC_Tech &EC_Tech_in);
    void begin();
     void GetCOM( Potentiostat_Shield &Pot, Potentiostat_EC_Tech &Tech);
     void Potentiostat_Serial_Com::PlotData(Potentiostat_Shield& Pot);


   // Potentiostat_Shield  Pot;
   // Potentiostat_EC_Tech  Tech;

    int intSerAvailable=0;
    int Debug=0;
    const String PotCOM[ARRAYSIZE] = { "/?", "CELL", "CMODE", "IE", "SET", "ABORT","HALT","DEBUG","RAMP", "VGND","STEP"};
    unsigned long LastSerialPlot=0;
    long update_dT=100000;
};


#endif // _Potentiostat_Shield_H_
