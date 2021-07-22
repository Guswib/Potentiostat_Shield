


#include <Arduino.h>
#include "Potentiostat_Shield.h"


////////////////////////////////////////////////////////////////////////

Potentiostat_Shield::Potentiostat_Shield()
{};


  //Configure all digital pins
 void  Potentiostat_Shield::begin()
 {pinMode(PIN_CEllSW, OUTPUT);
    pinMode(PIN_IR0, OUTPUT);
    pinMode(PIN_IR1, OUTPUT);
    pinMode(PIN_IR1, OUTPUT);

    FX_Vgnd();

  CellSW=0;
  FX_CellSW();
  FX_IRange();
  FX_cMode();
  
}
    


int Potentiostat_Shield::FX_cMode(int Value)
{
if(Value>-1 && Value<3)
  {
    CtrlMode=Value;
    //FX_cMode();
  }
  else
  {
    Serial.print(F("Value not supported"));  
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Set the contriol Mode
int Potentiostat_Shield::Get_Ctrl_Value()
{
 if(CtrlMode==1){ return valueRE;}
 else if(CtrlMode==2){ return valueI;}
 else {return valueCE;}

  }

 int Potentiostat_Shield::FX_cMode()
{    
     Serial.print(F("CMODE "));
     Serial.print(CtrlMode); 
     Serial.print(F(" - ")); 
     Serial.println(PotCMODES[CtrlMode]); 
}



////////////////////////////////////////////////////////////////////////

int Potentiostat_Shield::FX_CellSW()
{
    digitalWrite(PIN_CEllSW, 0==CellSW);
    Serial.print("CELL ");
    Serial.println(CellSW);
  }



int Potentiostat_Shield::FX_IRange(int Value)
{
    if((Value>-7) && (Value<-2) )
              {
                IRange = 6+Value;  // Value is the exponent of the current range(-3 to -6), and IRange is the 
                Serial.print(F("RANGE"));
                Serial.println(IRange);
              }
             else
              {
                Serial.println(F("Error - Wrong Current Range selected"));
              }
  
}

////////////////////////////////////////////////////////////////////////
int Potentiostat_Shield::FX_IRange()
{
   int Rgn=IRange;
    bool IR0= Rgn & 2; //(IRange==1) ||(IRange==3);
    bool IR1 =Rgn & 1; // (IRange==2) ||(IRange==3);

    //IR0=!IR0;
    //IR1=!IR1;
    digitalWrite(PIN_IR0, IR0);
    digitalWrite(PIN_IR1, IR1);
    delay(10);
    Serial.print(F("IE "));
    Serial.print(IRange);
    Serial.print(F(" - "));
    Serial.print(F("IRange: "));
    Serial.print(PotIRanges[IRange]);
    Serial.println("");
  }
////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////
float Potentiostat_Shield::FX_ReadADC(int PIN)
{
    return (float)analogRead(PIN)* ADC_value_2_V;      
}

///////////////////////////
float Potentiostat_Shield::FX_Vgnd()
{
  CellSW=0;
  FX_CellSW();
  float data=0;
  int i=0;
  for(i=0;i<10;i++){
  delay(3);
  data+=FX_ReadADC(PIN_GND);
  
  }
  
  vGND=data/10;
    
  Serial.print(F("vGND = "));
  Serial.print(vGND);
  Serial.println(F("mV vs GND"));
  }

float Potentiostat_Shield::Read_valueRE()
{
  valueRE = FX_ReadADC(PIN_RE)-vGND; //Reads Potential
  AVGvalueRE += valueRE;
  return valueRE;
}

float Potentiostat_Shield::Read_valueI()
{
  valueI = -(FX_ReadADC(PIN_I)-vGND);//Reads Current
  AVGvalueI += valueI;
  AVG_index +=1;
  return valueI;
}