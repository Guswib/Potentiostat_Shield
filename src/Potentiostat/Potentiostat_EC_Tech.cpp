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




#include <Arduino.h>


#include "Potentiostat_EC_Tech.h"




Potentiostat_EC_Tech::Potentiostat_EC_Tech()
{};

void Potentiostat_EC_Tech::begin()
{LastTime=micros();}



void Potentiostat_EC_Tech::runECtech()
{
       
    
long NewTime=micros();
unsigned long dT=NewTime-LastTime;
LastTime=NewTime;

long  int2nano=1000000;
 //   Serial.print("Wait");
 //  Serial.println(EC_Tech);
 switch (EC_Tech){
  case 1:  //RAMP
        if(Ramp_ini)
        {
          lCtrlValue=int2nano*Ramp_Start; //lctrl value in 10nV
          if(millis()-lTech_sTime>2000)
              {
                Ramp_ini=0;
                lRamp_MAX=Ramp_MAX*int2nano;
                lRamp_MIN=Ramp_MIN*int2nano;
                lRamp_Start=Ramp_Start*int2nano;
                Tech_Index=0; 
                if(Ramp_Start>Ramp_MAX){lRamp_Start=lRamp_MAX;}
                if(Ramp_Start<Ramp_MIN){lRamp_Start=lRamp_MIN;}
                if(((Ramp_Start>Ramp_MAX)||(Ramp_Start<Ramp_MIN))){Ramp_Sweeps=Ramp_Sweeps-1;}  
                Serial.print(F("Start Ramp"));
                Serial.println("");
                Serial.println(F("Next Loop 0"));
                Serial.print(F("change to "));
               if(inc>0){
                  Serial.println(F("pos"));
                  }
                else
                {
                  Serial.println(F("neg"));
                  }
              }
        }
        else
        {
        long dE=(long)inc*dT*(long)Ramp_Rate ;    //dT is in us and Ramp_Rate is in mV/s = nV, so /10 to get 10nV ;
        long lnewValue= lCtrlValue+dE ;    //10nV
        long  newValue0 = (lCtrlValue+dE)/int2nano; //from 10nV to mV 
       // Serial.print(newValue0);
          if(lnewValue>lRamp_MAX && inc!=-1) {inc=-1; Tech_Index+=1; Serial.print(F("change to neg"));Serial.println(Tech_Index);}// change the analog out value:
          else{if(lnewValue<lRamp_MIN && inc!=1) {inc=1;Tech_Index+=1; Serial.print(F("change to pos"));Serial.println(Tech_Index);}}
          
        
          if(Ramp_Sweeps>0) //when more than one sweep.
            {
              bool Crossed_Start = (lCtrlValue>lRamp_Start)^ (lnewValue>lRamp_Start);
              if(Crossed_Start){
              Serial.println(F("Crossed Start"));
              }
              if ((Tech_Index>Ramp_Sweeps) || ((Tech_Index+1>Ramp_Sweeps)&& Crossed_Start && Tech_Index>1))
                {
                Serial.println(F("Done Ramp"));
                EC_Tech=0;
                dE=0;
                }
              else
                {
                if(Crossed_Start && (Tech_Index %2)==0 && Tech_Index>0)
                  { 
                  Serial.print(F("Next Loop "));
                  Serial.println(Tech_Index/2);
                  }
                }
            }
        if(Tech_Index>Ramp_Sweeps) //When Ramp_Sweeps are larger the Tech_Index.
                {
                Serial.println(F("Done Ramp"));
                EC_Tech=0;
                dE=0;
                }
            
        lCtrlValue= (lCtrlValue+dE);    
        }
       
      
       setValue=lCtrlValue/int2nano;    //from 10nV to setValue in mV
       break;
  
  ////////////////////////////////////////////////////////////////////////////////////////
    case 2:  //Steps
       if(Ramp_ini)
        {
          Tech_Index=0;
          Ramp_ini=0;
          Serial.println(F("Start Step"));
          
          Serial.print(F("Step: 1, SET= "));
          Serial.println(Steps_V[0]);
          setValue=Steps_V[0];        
        }

      if(millis()-lTech_sTime>lSteps_t[Tech_Index])
              {
                Tech_Index=Tech_Index+1;
              if(Tech_Index<Steps_nr)
                {
                  Serial.print(F("Step: "));
                  Serial.print(Tech_Index+1);
                  Serial.print(F(", SET= "));
                  Serial.println(Steps_V[Tech_Index]);
                  setValue=Steps_V[Tech_Index];
                }else{
                 Serial.println(F("Done Steps"));
                 EC_Tech=0;
                  }
              }
    
      break;
     default:
      {   ;}
  }  //Last of select 
             

}//END OF FUNCTION

///
