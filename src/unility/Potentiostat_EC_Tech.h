/**************************************************************************/
/*!
    @file     Potentiostat_EC_Tech.h
    @author   Gustav Wiberg
    @license  BSD (see license.txt)

    This is a library to control the electrochemical techniques, such as ramping and steps.

    ----> http://www.nordicec.com/Product/Potentiostat_Shield

    created 2021
  by Gustav Wiberg

    @section  HISTORY

    v1.0  - First release

*/
/**************************************************************************/



#ifndef _Potentiostat_EC_Tech_H_
#define _Potentiostat_EC_Tech_H_

#define Potentiostat_EC_Tech_LIB_VERSION       (F("1.0.0"))



class Potentiostat_EC_Tech
{

    public:
    Potentiostat_EC_Tech();
void    begin();

void runECtech();


///////////////////////////EC technquies
unsigned long lTech_sTime=0;
long LastTime=0;
int EC_Tech=0;
unsigned int Tech_Index=0;
int Ramp_Rate=100; //mV/s
int Ramp_Start=0; //mV 
int Ramp_MAX=1000; //mV
int Ramp_MIN=-1000; //mV
bool Ramp_ini=0;
int Ramp_Sweeps=0; //Sweeps.

long lRamp_Start=0; //rampstart in nV for calc. 
long lRamp_MAX=0; //mV
long lRamp_MIN=0; //mV

int Steps_V[3]={0,0,0}; //mV
long lSteps_t[3]={0,0,0}; //ms
int Steps_nr=0;

int setValue = 60;
long lCtrlValue=0;  // Value in nV
float fCtrlValue=0;  // Value in mV

bool runHALT = 0; 
 int inc=0;

const String EC_Techs[3] = { "    ", "Ramp", "I   "};



};

#endif // _Potentiostat_Shield_H_
