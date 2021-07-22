/**************************************************************************/
/*!
    @file     Potentiostat_SW_PID.h
    @author   Gustav Wiberg
    @license  BSD (see license.txt)

    This is a simple software PID regulator.

    ----> http://www.nordicec.com/Product/Potentiostat_Shield

    created 2021
  by Gustav Wiberg

    @section  HISTORY

    v1.0  - First release

*/
/**************************************************************************/



#ifndef _Potentiostat_SW_PID_
#define _Potentiostat_SW_PID_

#define Potentiostat_SW_PID_LIB_VERSION       (F("1.0.0"))


#include <Arduino.h>

class Potentiostat_SW_PID
{
    public:
    Potentiostat_SW_PID();
    void  begin();
    
    
    int PID(int setValue, int CurV);
    int Output();

    long fREG=0;
    int maxValue=4095;
    int midValue=2048;
    long lNewTime_us=0;
    unsigned long lLastTime_us=0;
};

#endif // _Potentiostat_Shield_H_
