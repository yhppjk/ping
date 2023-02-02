#include <msp430.h>
#include <NextPM.h>
#include <stdio.h>
#include "string.h"

extern char sensorResponse[];
extern unsigned int responseLength;
void readResponse(void){
    responseLength =0;

    while(1){
        sensorResponse[responseLength] = getchar();
        responseLength++;
        if(responseLength >16){
            break;
        }
    }
}


