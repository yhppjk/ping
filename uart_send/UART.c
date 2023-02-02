#include <msp430.h>
#include "UART.h"
#include <stdio.h>
const char hex_table[] = {
'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

void send_char(char sendchar){

    while (!(IFG2&UCA0TXIFG));              //等待发送寄存器为空
    UCA0TXBUF = sendchar;
}


void send_string(unsigned char *ptr){
    _disable_interrupts();
    while(*ptr != '\0'){
        send_char(*ptr++);                  // 发送数据
    }
    _enable_interrupts();
}

void to_hex(char *s, int l, char *d)
{
    while(l--)
    {
        *(d+2*l+1) = hex_table[(*(s+l))&0x0f];
        *(d+2*l) = hex_table[(*(s+l))>>4];
    }
}
unsigned char to_dec(char x){
    unsigned int y=0;
    unsigned int product = 1;
    unsigned int p = 16;
    while(x!=0){
            y=y+(x%10)*product;
            x=x/10;
            product=product*p;
        }
    return y;
}

