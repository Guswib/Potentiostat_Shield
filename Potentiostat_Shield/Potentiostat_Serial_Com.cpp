

#include "Potentiostat_Shield.h"
#include "Potentiostat_EC_Tech.h"
#include "Potentiostat_Serial_Com.h"


Potentiostat_Serial_Com::Potentiostat_Serial_Com(Potentiostat_Shield& Pot_in,  Potentiostat_EC_Tech &EC_Tech_in)
{
  //  Pot= Pot_in;
  //  Tech =EC_Tech_in;

}

void Potentiostat_Serial_Com::begin()
{
    Serial.begin(1000000);
    delay(2000);
    int testa=0;
    if(Serial.read()=='f'){ testa+=1;}
    if(Serial.read()=='a'){ testa+=1;}
    if(Serial.read()=='s'){ testa+=1;}
    if(Serial.read()=='t'){ testa+=1;}
    Serial.print("Fast Configuration: ");
    Serial.println(testa);
  
    if(testa==0){
        Serial.begin(115200);
    }
}


void Potentiostat_Serial_Com::GetCOM(Potentiostat_Shield& Pot,  Potentiostat_EC_Tech &Tech){

    int i=0;
    int  NEWintSerAvailable=Serial.available();
  
    if (NEWintSerAvailable == 0 || NEWintSerAvailable != intSerAvailable ) {
        intSerAvailable = NEWintSerAvailable;
    } else{
        int ReadWrite = 0;
        // if (inByte !='\n'){ReadWrite = 1;}
        String COM = "5";

        int comSelect=-1;
        
        COM= Serial.readStringUntil('\n');
        COM.trim();
        COM.toUpperCase();
        Serial.println("");
        Serial.print(F("DATA READ: "));
        Serial.println(COM);
        
        String COMMAND= COM;
        int index = COM.indexOf(" ");
        Serial.print("Index:");
        Serial.print(index);
        if(index>0){
            ReadWrite=1 ;
        COMMAND= COM.substring(0,index);
        COM= COM.substring(index+1);
        }
        for (i = 0; i< ARRAYSIZE; i++)  //Find commands
        {
            if( COMMAND==PotCOM[i]){comSelect=i; break;}
            }
            ////////////
    //Find arguments as int.
        int Com_Arg[6]={0,0,0,0,0,0};  
        if(ReadWrite>0)  
        {
        for (i = 0; i< 10; i++) 
           {
                  Com_Arg[i]=COM.toInt(); 
                  Serial.print(Com_Arg[i]);
                  Serial.print(" ");
                  COM.trim();
                  index=COM.indexOf(" ");
                  if(index>0){
                      COM= COM.substring(index+1);
                  }else{
                    break;
                  }
          }
                                    
        }


//Serial.print(" aaaaa - ");
Serial.print(" Arguments: ");
Serial.print(i);
//Serial.print("RW: ");
//Serial.println(ReadWrite);
//Serial.println(inByte); 
//Serial.println(inByte2);
Serial.print(COMMAND);Serial.print(" - extra:");Serial.print(COM);Serial.print(" - Case Number: ");
Serial.println(comSelect);
    switch (comSelect) {
      case 0: // "/? 
        Serial.println(F("Here follows all Commands"));
         for (int i =0; i< ARRAYSIZE; i++) { Serial.println(PotCOM[i]);}
          break;
          ////////////////////////////////////////////////////////////////////
      case 1:    // "CW" - Cell Switch
         if(ReadWrite>0) {
          Pot.CellSW=(bool)Com_Arg[0];} 
          Pot.FX_CellSW();
          break;
        //////////////////////////////////////////////////////////////
        case 2:    // "Mode" - Control Mode
         if(ReadWrite>0) 
          {
           Pot.FX_cMode(Com_Arg[0]);
          } 
          Pot.FX_cMode();
           break;
           //////////////////////////////////////////////////////////////
        case 3:    // "IRange" - Current Range
         if(ReadWrite>0) 
          {
           Pot.FX_IRange(Com_Arg[0]);
          }
          Pot.FX_IRange(); 
           break;
      /////////////////////////////////////////////////////////////////////////
      case 4: // SET Control Value 
        
        if(ReadWrite>0 && Tech.EC_Tech==0) { 
          Tech.setValue=Com_Arg[0]; //mV        
          Serial.print("E set ");
          Serial.println(Tech.setValue);
          } 
             
        break;
        //////////////////////////////////////////////////////////////////////////////
       case 5: // Abort
        
        Tech.EC_Tech=0;
        
                Serial.println("Aborted");
             
        break;
        //////////////////////////////////////////////////////////////////////////////
               case 6: // Halt
        
        Tech.runHALT= !Tech.runHALT;
        if(Tech.runHALT)
                Serial.println(F("Halted"));
        else
              Serial.println(F("restarted"));
        break;
        //////////////////////////////////////////////////////////////////////////////
                     case 7: // DEBUG
         if(ReadWrite>0) {
          Debug=Com_Arg[0];} 
        
              Serial.print(F("DEBUG"));
               Serial.println(Debug);
        break;
        //////////////////////////////////////////////////////////////////////////////
      case 'd':
        digitalWrite(5, HIGH);
        break;
        ////////////////////////////////////////////////////////////////////////
      case 8:   // Ramp
        Tech.EC_Tech=1;
        Tech.Ramp_Rate=10;
         if(ReadWrite>0) 
            {
            
            Tech.Ramp_Start= Com_Arg[0];
            int V1= Com_Arg[1];
            int V2= Com_Arg[2];
            Tech.Ramp_Rate=Com_Arg[3];
            Tech.Ramp_Sweeps= Com_Arg[4];


            if(Tech.Ramp_Start>V1){Tech.inc=-1;}else{Tech.inc=1;}
            if(Tech.Ramp_Sweeps==1) {Tech.Ramp_MAX=V1;Tech.Ramp_MIN=V1;}  //Special case when we have a LSV.
            else //All other cases
              {
              if(V2>V1){Tech.Ramp_MAX=V2;Tech.Ramp_MIN=V1;}else{Tech.Ramp_MAX=V1;Tech.Ramp_MIN=V2;}
              }
            Serial.print(F("Rate:\t"));
            Serial.print(Tech.Ramp_Rate);
            Serial.print(F(" , Start:\t"));
            Serial.print(Tech.Ramp_Start);        
            Serial.print(F(", Max:\t"));
            Serial.print(Tech.Ramp_MAX);
            Serial.print(F(", MIN:\t"));
            Serial.print(Tech.Ramp_MIN);
            Serial.print(F(", INC:\t"));
            Serial.print(Tech.inc);
         
            
            Serial.print(F(" Sweeps:\t"));
            Serial.println(Tech.Ramp_Sweeps);
            
            
            //
            Tech.Ramp_ini=1; //Start initian sequence. 
            
            } 
         Serial.print(F("INI Ramp - "));
         Serial.println(Tech.EC_Tech);
        Tech.lTech_sTime=millis();
        break;
        
        ////////////////////////////////////////////////////////////////////////////////////
      case 9:
        Pot.FX_Vgnd();
        break;
        ////////////////////////////////////////////////////////////////////////
       case 10:
        Tech.EC_Tech=2;
        if(ReadWrite>0) 
            {
            Tech.Steps_V[0]= Com_Arg[0];
            Tech.lSteps_t[0]= Com_Arg[1];
            Tech.Steps_V[1]= Com_Arg[2];
            Tech.lSteps_t[1]=Com_Arg[3]+Tech.lSteps_t[0];
            Tech.Steps_V[2]= Com_Arg[4];
            Tech.lSteps_t[2]=Com_Arg[5]+Tech.lSteps_t[1];
            Tech.Steps_nr=(i+1)/2;
            
        
            for (i = 0; i< Tech.Steps_nr; i++) 
              {
                Serial.print(F("@Step"));
                Serial.print(i);
                Serial.print(F("\tS: "));
                Serial.print(Tech.Steps_V[i]);
                Serial.print(F("\tt: "));
                Serial.println(Tech.lSteps_t[i]);
                
              }
              Tech.Ramp_ini=1; //Start initian sequence.
            }
        //Serial.println(EC_Tech);
        Tech.lTech_sTime=millis();
        break;
        ////////////////////////////////////////////////////////////////////////
     
      default:
        Serial.println(F("Command NOT Regocnized")); 
        
     
               
        } // End of Switch

        
   if (Serial.available() > 0) {
            Serial.println(F("Clean")); 
              Serial.println(  Serial.readStringUntil('/n'));
   }
 } // End of if clause
}  // End of function


void Potentiostat_Serial_Com::PlotData(Potentiostat_Shield& Pot)
{
  unsigned long NewTime=millis();
  if(NewTime-LastSerialPlot>100) //100ms per data point
        {
        float AVGvalueRE2 = (float)Pot.AVGvalueRE /Pot.AVG_index;
        float AVGvalueI2  =  (float)Pot.AVGvalueI/Pot.AVG_index ;
        
        
        Serial.print("\t"); Serial.print(NewTime);
        Serial.print("\t"); Serial.print(AVGvalueRE2);
        Serial.print("\t"); Serial.print(AVGvalueI2); Serial.print("E");  Serial.print(-8+Pot.IRange); // I2 is in mV, so 3 must be subtracted to the scale. 
       
        Serial.println("");   
     
        LastSerialPlot=NewTime;
            
            
        Pot.AVG_index=0;
        Pot.AVGvalueRE=0;
        Pot.AVGvalueI=0;
        Pot.AVGvalueCE=0;
    }
}
    
