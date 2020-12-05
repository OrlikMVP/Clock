#include <HCMAX7219.h>
#include "SPI.h"
#define LOAD 10
HCMAX7219 HCMAX7219(LOAD);
#include <Wire.h>  
#include <iarduino_RTC.h>                                  
const char* strM="JanFebMarAprMayJunJulAugSepOctNovDec";    
const char* sysT=__TIME__;                                 
const char* sysD=__DATE__;            
iarduino_RTC watch(RTC_DS1307);   
const int i[6] {(sysT[6]-48)*10+(sysT[7]-48), (sysT[3]-48)*10+(sysT[4]-48), (sysT[0]-48)*10+(sysT[1]-48), (sysD[4]-48)*10+(sysD[5]-48), ((int)memmem(strM,36,sysD,3)+3-(int)&strM[0])/3, (sysD[9]-48)*10+(sysD[10]-48)};
      
void setup() {
    delay(300);                                            
    Serial.begin(9600);                                    
    watch.begin();                                          
    watch.settime(i[0],i[1],i[2],i[3],i[4],i[5]); 
    pinMode(2, OUTPUT);
}

void loop() {
         digitalWrite(2, LOW);
 if(millis()%250==0){   
         digitalWrite(2, HIGH);
         HCMAX7219.Clear();
         HCMAX7219.print7Seg(watch.gettime("H-i-s"),8);
         HCMAX7219.Refresh();
          Serial.println(watch.gettime("d-m-Y, H:i:s, D"));     // Выводим время.
      delay(1);                                             // Приостанавливаем скетч на 1 мс, чтоб не выводить время несколько раз за 1мс.
    }                                                       //
}         
