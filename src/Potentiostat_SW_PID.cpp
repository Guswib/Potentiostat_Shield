/**************************************************************************/
/*!
    @file     Potentiostat_SW_PID.cpp
    @author   Gustav Wiberg
    @license  BSD (see license.txt)

    This is a simple software PID regulator.

    ----> http://www.nordicec.com/Product/Potentiostat_Shield

    created 2021
  by Gustav Wiberg
*/
/**************************************************************************/


#include "Potentiostat_SW_PID.h"

Potentiostat_SW_PID::Potentiostat_SW_PID(){};


void Potentiostat_SW_PID::begin()
{
  lLastTime_us=micros();

}



/////////////////////////////////////////////////////////////////////////////////////////////////
/// Basic software regulator to set the output voltage

int Potentiostat_SW_PID::PID(int setValue, int CurV)
{
  lNewTime_us=micros();
  long microdT=lNewTime_us-lLastTime_us;
  long Error=(CurV-setValue);  //CurV is in setValue is in mV, but in the long it is considered nV
  float dV=(Error*microdT)/50000;  //change 
  float ffREG=fREG-dV;
  if((ffREG>2600) ||(fREG>2600) )
  {
    fREG=2600;
    }
  else
    {if((ffREG<-2600) ||(fREG<-2600) )
      {
        fREG=-2600;
        }
      else
      {
        fREG =fREG-dV;
        }
    }
  lLastTime_us=lNewTime_us;
  return fREG;
}


/////////////////////////////////////////////////////

int Potentiostat_SW_PID::Output()
{
int newValue=((int) fREG + midValue);
if(newValue>maxValue)
 newValue=maxValue;
if(newValue<0)
 newValue=0;
 return newValue;
 }