/**************************************************************************/
/*!
    @file     Potentiostat_SW.PID.h
    @author   Gustav Wiberg
    @license  BSD (see license.txt)

    This is a  software to control a Potentiostat Shield.

    ----> http://www.nordicec.com/Product/Potentiostat_Shield

    created 2021
  by Gustav Wiberg
*/
/**************************************************************************/


#ifndef _Potentiostat_Shield_H_
#define _Potentiostat_Shield_H_



#define Potentiostat_Shield_LIB_VERSION       (F("0.1.1"))


#include <Arduino.h>



class Potentiostat_Shield
{
    public:
    Potentiostat_Shield();
    void  begin();
    // if only select is given ==> HW SPI

    float FX_ReadADC(int PIN);
    float Read_valueRE();
    float Read_valueI();

    int FX_CellSW();
    int FX_IRange(int Value);
    int FX_IRange();

    int FX_cMode(int Value);
    int FX_cMode();
    int Get_Ctrl_Value();

    float FX_Vgnd();

    int SPI_chipSelectPin = 10;

    int PIN_CEllSW = 5; // Cell switch 
    int PIN_IR0 = 6;   //Current range 
    int PIN_IR1 = 7;  // current range

    // Analog pins or the different signals
    int PIN_CE = A0;  // 
    int PIN_I = A2;  // Current signal
    int PIN_RE = A1;  // Voltage signal
    int PIN_GND = A0; // Reference voltage of the virtual ground.

    const String PotCMODES[3] = { "CEll", "E", "I"};
    const String PotIRanges[4] = { "1uA", "10uA", "100uA","1mA"};


    float ADC_value_2_V = 4.8875855;  // This value is the ration between the scale voltage 5000mV, and 1023, which corresponding to the max value.


    //Potentiostat Settings
    int CtrlMode = 1;  //control mode (P,G)
    bool CellSW = 0;  
    int IRange=0;
    bool runHALT = 0;  

    int vGND = 512;  

    int valueCE = 0;        // value read from the pot
    int valueRE = 0;        // value read from the pot
    int valueI = 0; 

    long AVGvalueCE = 0;
    long AVGvalueRE = 0;
    long AVGvalueI = 0;

    int AVG_index=0;

};
#endif // _Potentiostat_Shield_H_
