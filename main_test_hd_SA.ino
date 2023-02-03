#include <msp430.h>
#include <msp430g2553.h>
#include <intrinsics.h>

#include <stdio.h>
#include <Energia.h>

/********************************/
/*        Pin connection        */
/********************************/
/* Connection for MSP430G2452   */
/*    MSP430    |    Display  */
/*     P1.4     |      SSN      */
/*     P1.6     |      SDI       */
/*     P1.5     |      SCK      */
/*..............................*/
/* Connection for MSP430G2553   */
/*    MSP430    |    Display    */
/*     P1.4     |      SSN      */
/*     P1.7     |      SDI       */
/*     P1.5     |      SCK      */
/*..............................*/


/*...................................................................................*/
/* void Init_USI_SPI()                                                               */
/*...................................................................................*/
/* Description : Initialisation of the SPI bus                                       */
/* Inputs :                                                                          */
/*      - void                                                                       */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Init_USI_SPI(unsigned int bit);

/*...................................................................................*/
/* void Send_char_SPI(unsigned char carac)                                           */
/*...................................................................................*/
/* Description : Send a char via SPI                                                 */
/* Inputs :                                                                          */
/*      - unsigned char carac : the char to send                                     */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Send_char_SPI(unsigned char carac,  unsigned int bit);





/*...................................................................................*/
/* void Aff_4carac(unsigned char buffer[4])                                       */
/*...................................................................................*/
/* Description : Display four characters                                             */
/* Inputs :                                                                          */
/*      - unsigned char buffer[4] : characters to display                            */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Aff_4carac(unsigned char buffer[4],unsigned char bit);


/*...................................................................................*/
/* void Aff_Points(unsigned char code)                                           */
/*...................................................................................*/
/* Description : Swicth on points on the display                                     */
/* Inputs :                                                                          */
/*      - unsigned char code :  points to switch on                                  */
/* Output : void                                                                     */
/*...................................................................................*/
void Aff_Points(unsigned char code, unsigned int bit);




/*...................................................................................*/
/* void Aff_Efface()                                     */
/*...................................................................................*/
/* Description : Clear the display                                                   */
/* Inputs :                                                                          */
/*      - void                                                                       */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Aff_Efface(unsigned int bit);


/*...................................................................................*/
/* void Aff_Luminosite(unsigned char lum)                                     */
/*...................................................................................*/
/* Description : Change the luminosity of the display                                */
/* Inputs :                                                                          */
/*      - unsigned char lum : Value of the luminosity between 0 (min) and 255 (max)  */
/* Output : void                                                                     */
/*...................................................................................*/
void Aff_Luminosite(unsigned char lum, unsigned int bit);



/*...................................................................................*/
/* void Aff_Init()                                                               */
/*...................................................................................*/
/* Description :Initializing of the display                                       */
/* Inputs :                                                                          */
/*      - void                                                                       */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Aff_Init(unsigned int bit);



/*...................................................................................*/
/* void Aff_1carac( unsigned char num, unsigned char code)                        */
/*...................................................................................*/
/* Description : Display only one character                                          */
/* Inputs :                                                                          */
/*      - unsigned char num : number of the character (between 1 and 4 )             */
/*      - unsigned char code : segments to swicth on                                 */
/* Output : void                                                                     */
/*...................................................................................*/
void Aff_1carac(unsigned char num, unsigned char code,unsigned int bit);


/*...................................................................................*/
/* void convert_digit(int value)                                                      */
/*...................................................................................*/
/* Description : Use for an other fonction                                           */
/* Inputs :                                                                          */
/*      - int value: value of the digit you want to convert in ASCII                       */
/*                                                                                   */
/* Output : int  : value of the ASCII code of the digit                                                                    */
/*...................................................................................*/

int convert_digit(int value);                       // fonction de conversion en hexadecimal




void ADC_init(void);



void ADC_Demarrer_conversion(unsigned char voie);
 


int ADC_Lire_resultat ();

/* Capteur particules */

void send_string(unsigned char *ptr);

void send_char(char sendchar);

void to_hex(char *s, int l, char *d);

void from_hex(char *s, int l, char *d);

unsigned char to_dec(char x);

void Init_uart(void);



char read[7];
int j=0;
int i=0;
double cal_result;
int pm25;

unsigned char commande[1];
unsigned char commande1[1];
unsigned char commande2[1];

unsigned char size =0;
char *adresse;
// unsigned char a[];
unsigned int length = 0;

// dunsigned char message[];
unsigned int len = 24;


int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  Init_uart();
  P1DIR |= BIT0; // mode sortie
  Aff_Init(BIT0);
  Aff_Luminosite(200, BIT0);
  Aff_Init(BIT1);
  Aff_Luminosite(200, BIT1);
  Aff_Init(BIT2);
  Aff_Luminosite(200, BIT2);
  Aff_valeur(convert_Hex_Dec(1998),BIT0);
  Aff_valeur(convert_Hex_Dec(1999),BIT1);
  Aff_valeur(convert_Hex_Dec(2000),BIT2);  
  P1OUT |= BIT0;
  __delay_cycles(2000000); // Attente 1 seconde
  P1OUT &= ~BIT0;
  
  
  while(1)
  {
    P1OUT |= BIT0;
    __delay_cycles(50000); // Attente 1 seconde
    __enable_interrupt();
    Aff_valeur(convert_Hex_Dec(read[1]),BIT0);
    Aff_valeur(convert_Hex_Dec(read[2]),BIT1);
    Aff_valeur(convert_Hex_Dec(read[3]),BIT2);

//    Aff_valeur(read[1],BIT0);
//    Aff_valeur(read[2],BIT1);
//    Aff_valeur(read[3],BIT2);
    
    P1OUT &= ~BIT0;
    __delay_cycles(50000); // Attente 1 seconde
  }
  
}




// Fonctions

/********************************/
/*        Pin connection        */
/********************************/
/* Connection for MSP430G2452   */
/*    MSP430    |    Display  */
/*     P1.4     |      SSN      */
/*     P1.6     |      SDI       */
/*     P1.5     |      SCK      */
/*..............................*/
/* Connection for MSP430G2553   */
/*    MSP430    |    Display    */
/*     P1.4     |      SSN      */
/*     P1.7     |      SDI       */
/*     P1.5     |      SCK      */
/*..............................*/


/*...................................................................................*/
/* void Init_USI_SPI()                                                               */
/*...................................................................................*/
/* Description : Initialisation of the SPI bus                                       */
/* Inputs :                                                                          */
/*      - unsigned int bit : the PIN to use                                                                       */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Init_USI_SPI(unsigned int bit)
{
    UCB0CTL1 = UCSWRST;

    P2DIR |= bit; // pin bit CS output
    P2OUT |= bit; // pin bit CS high
    P1SEL |= BIT7 | BIT5;  // Enable SIMO + SCLK
    P1SEL2 |= BIT7 | BIT5; // Enable SIMO + SCLK
    UCB0CTL0 |= UCCKPH | UCMSB | UCMST | UCSYNC; // 3-pin, 8-bit SPI master
    UCB0CTL1 |= UCSSEL_2; // SMCLK
    UCB0CTL1 &= ~UCSWRST;
}

/*...................................................................................*/
/* void Send_char_SPI(unsigned char carac)                                           */
/*...................................................................................*/
/* Description : Send a char via SPI                                                 */
/* Inputs :                                                                          */
/*      - unsigned char carac : the char to send
 *      - unsigned int bit : the PIN to send                                         */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Send_char_SPI(unsigned char carac,  unsigned int bit)
{
    P2OUT &= ~bit;  // CS low
    UCB0TXBUF = carac; // Put caracter in transmit buffer
    while (!(IFG2 & UCB0TXIFG)); // USCI_A0 TX buffer ready?
    P2OUT |= bit; // CS high
}




/*...................................................................................*/
/* void Aff_4carac(unsigned char buffer[4])                                       */
/*...................................................................................*/
/* Description : Display four characters                                             */
/* Inputs :                                                                          */
/*      - unsigned char buffer[4] : characters to display
 *      - unsigned int bit : the PIN to send                       */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Aff_4carac(unsigned char buffer[4],unsigned char bit)
{
  Send_char_SPI(buffer[0],bit);
  Send_char_SPI(buffer[1],bit);
  Send_char_SPI(buffer[2],bit);
  Send_char_SPI(buffer[3],bit);
}


/*...................................................................................*/
/* void Aff_Points(unsigned char code)                                           */
/*...................................................................................*/
/* Description : Swicth on points on the display                                     */
/* Inputs :                                                                          */
/*      - unsigned char code :  points to switch on
 *      - unsigned int bit : the PIN to send                                  */
/* Output : void                                                                     */
/*...................................................................................*/
void Aff_Points(unsigned char code, unsigned int bit)
{
  Send_char_SPI(0x77,bit);
  Send_char_SPI(code,bit);
}



/*...................................................................................*/
/* void Aff_Efface()                                     */
/*...................................................................................*/
/* Description : Clear the display                                                   */
/* Inputs :                                                                          */
/*      - unsigned int bit : the PIN to send                                                                       */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Aff_Efface(unsigned int bit)
{
  Send_char_SPI(0x76, bit);
  Aff_Points(0x00, bit);
}

/*...................................................................................*/
/* void Aff_Luminosite(unsigned char lum)                                     */
/*...................................................................................*/
/* Description : Change the luminosity of the display                                */
/* Inputs :                                                                          */
/*      - unsigned char lum : Value of the luminosity between 0 (min) and 255 (max)  */
/* Output : void                                                                     */
/*...................................................................................*/
void Aff_Luminosite(unsigned char lum, unsigned int bit)
{
  Send_char_SPI(0x7A, bit);
  Send_char_SPI(lum, bit);
}


/*...................................................................................*/
/* void Aff_Init()                                                               */
/*...................................................................................*/
/* Description :Initializing of the display                                       */
/* Inputs :                                                                          */
/*      - unsigned int bit : the PIN to send                                                                       */
/* Output :                                                                          */
/*      - void                                                                       */
/*...................................................................................*/
void Aff_Init(unsigned int bit)
{
  Init_USI_SPI(bit);
  Aff_Efface(bit);
  Aff_4carac((unsigned char *)"8888",bit);
  Aff_Points(0x3F,bit);
  Aff_Luminosite(255,bit);
  __delay_cycles(1000000);
  Aff_Efface(bit);
}


/*...................................................................................*/
/* void Aff_1carac( unsigned char num, unsigned char code)                        */
/*...................................................................................*/
/* Description : Display only one character                                          */
/* Inputs :                                                                          */
/*      - unsigned char num : number of the character (between 1 and 4 )             */
/*      - unsigned char code : segments to swicth on
 *      - unsigned int bit : the PIN to send                             */
/* Output : void                                                                     */
/*...................................................................................*/
void Aff_1carac(unsigned char num, unsigned char code,unsigned int bit)
{
  num %=5;
  num +=0x7A;
  Send_char_SPI(num,bit);
  Send_char_SPI(code,bit);
}

/*...................................................................................*/
/* void convert_digit(int value)                                                      */
/*...................................................................................*/
/* Description : Use for an other fonction                                           */
/* Inputs :                                                                          */
/*      - int value: value of the digit you want to convert in ASCII                       */
/*                                                                                   */
/* Output : int  : value of the ASCII code of the digit                                                                    */
/*...................................................................................*/

int convert_digit(int value)                       // fonction de conversion en hexadecimal
{
  int valTens=0;

  if(value<=9) valTens = value +0x30;          // pour les unités

    else valTens = value +0x37;                  // pour les nombres > 9

  return valTens;
}


/*...................................................................................*/
/* void convert_ASCII(int c, buffer)                                                         */
/*...................................................................................*/
/* Description : Convert the value of an int in ASCII                                          */
/* Inputs :                                                                          */
/*      - int c: value of the number you want to convert  (unsigned)                           */
/*      - buffer : adress of the ASCII buffer to put the results                                                                             */
/* Output : void                              */
/*...................................................................................*/

void convert_ASCII(int c, unsigned char hexa[4])
{

  int digit1,digit2,digit3,digit4;

  digit4= c & ( 0x000F);                     //  décalage de bit selon le digit
  digit3=(c & ( 0x00F0))>>0x04;
  digit2=(c & ( 0x0F00))>>0x08;
  digit1=(c & ( 0xF000))>>0x0C;
  hexa[3]=convert_digit(digit4);      // placement dans un tableau de 4 caractères + conversion
  hexa[2]=convert_digit(digit3);
  hexa[1]=convert_digit(digit2);
  hexa[0]=convert_digit(digit1);

}


/*...................................................................................*/
/* void convert_Hex_Dec(int valeur_hex)                                            */
/*...................................................................................*/
/* Description : Convert an hexadecimal to decimal                                   */
/* Inputs :                                                                          */
/*      - char toExtract[]: value of the number in hexadecimal you want to convert   */
/*                                                                                   */
/* Output : char                                                                     */
/*...................................................................................*/
int convert_Hex_Dec(int valeur_hex)
{
  unsigned char dec [4];
        int val_dec;
  dec[0]= valeur_hex / 0x03e8;
  dec[1]= (valeur_hex % 0x03e8) / 0x64;
  dec[2]= (valeur_hex % 0x64) / 0x0A;
  dec[3]= (valeur_hex % 0x0A);
  val_dec= (dec[0]<<12) + (dec[1]<<8)+ (dec[2]<<4) + dec[3];
  return val_dec;


}


/*...................................................................................*/
/* void affiche_valeur(int av)                                                       */
/*...................................................................................*/
/* Description : Display a value without ASCII conversion                            */
/* Inputs :                                                                          */
/*      - int av: value of the number you want to display
 *      - unsigned int bit : the PIN to send                            */
/*                                                                                   */
/* Output : void                                                                     */
/*...................................................................................*/
void Aff_valeur(int c,unsigned int bit)
{

  int digit1,digit2,digit3,digit4;
  unsigned char v[4];


  digit4= c & ( 0x000F);                     //  décalage de bit selon le digit
  digit3=(c & ( 0x00F0))>>0x04;
  digit2=(c & ( 0x0F00))>>0x08;
  digit1=(c & ( 0xF000))>>0x0C;
  v[3]=(digit4);                 // placement dans un tableau de 4 caractères + conversion
  v[2]=(digit3);
  v[1]=(digit2);
  v[0]=(digit1);
  Aff_4carac(v, bit);                          // affichage du tableau

}




/* ADC ESIG */

void ADC_init(void)
{
    ADC10CTL0 = ADC10CTL1 = 0;

// Choix de la r閒閞ence de tension Vcc GND
// R閒閞ence interne active et g閚閞ateur � 2,5 Volts  ADC10 actif
// Les autres bits sont suppos閟 � 0

    ADC10CTL0 =  SREF_0 | ADC10SHT_0  | REF2_5V | REFON | ADC10ON;  ;

// Choix du diviseur par 1 pour l'horloge, d閙arrage conversion logiciel
// Horloge de conversion 1MHz, conversion monovoie-monocoup 

    ADC10CTL1 =  ADC10DIV_0 | ADC10SSEL_2 |  SHS_0 | CONSEQ_0 ;

}



void ADC_Demarrer_conversion(unsigned char voie)
{
     ADC10CTL1 = (voie * 0x1000)| ADC10DIV_0 | ADC10SSEL_2 |  SHS_0 | CONSEQ_0 ;
    ADC10CTL0 |= ENC | ADC10SC;     // Sampling and conversion start
 }  


int ADC_Lire_resultat ()
{
    while (ADC10CTL1 & ADC10BUSY);  // Tant que ADC occup� on attend
  ADC10CTL0 &= ~ENC;    // Conversion finie alors  ADC conversion

      return ADC10MEM;          // Return Conversion value
}


/* ADC Haoping */

void ADC_I(void){
    //SET UP MCLK
    ADC10CTL1 |= ADC10SSEL_2;
    //ADC
    ADC10CTL1 |= ADC10DIV_0;
    //ADC REFERENCE TENSION
    ADC10CTL0 |= SREF_1;
    //ADC SAMPLE HOLD ON 64CLK
    ADC10CTL0 |= ADC10SHT_3;
    //ADC SAMPLE FREQUENCE 200K
    ADC10CTL0 &= ~ADC10SR;
    //ADC REFERENCE 2.5V
    ADC10CTL0 |= REF2_5V;
    //ACTIVATE REFERENCE
    ADC10CTL0 |= REFON;
    //ADC CHANNEL A1
    ADC10CTL1 |= INCH_1;
    //ALLOW A1 ANALOG
    ADC10AE0 |= 0x0002;
    //ACTIVATE ADC
    ADC10CTL0 |= ADC10ON;

}

unsigned int ADC_Get(void){
    //convert start
    ADC10CTL0 |= ADC10SC|ENC;
    //wait for result
    while(ADC10CTL1&ADC10BUSY);
    //return result
    return ADC10MEM;
}


void Init_uart(void){

    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
      if (CALBC1_1MHZ==0xFF)                    // If calibration constant erased
      {
        while(1);                               // do not load, trap CPU!!
      }
      // P1DIR |= BIT0;
      // P1OUT = ~BIT0;
      DCOCTL = 0;                               // Select lowest DCOx and MODx settings
      BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
      DCOCTL = CALDCO_1MHZ;
      P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
      P1SEL2 = BIT1 + BIT2;
      UCA0CTL1 |= UCSSEL_2;                     // SMCLK
      UCA0BR0 = 8;                              // 1MHz 115200
      UCA0BR1 = 0;                              // 1MHz 115200
      UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5
      UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
                                                // stop 1
      UCA0CTL0 |= UCPEN + UCPAR;                // even
      IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    if (IFG2 & UCA0RXIFG){

       if(i<8){
            read[i]=UCA0RXBUF;
            i++;
            // if(read[0]!=0xFF || read[0]!=0x81)
               //  i=0;
            
        }
       else{
               IE2&=~UCA0RXIE;

//               int calculatedChecksum = 0;
//               for (j = 0; j < 16;j++) {
//                   calculatedChecksum += read[j];
//               }
//               if((calculatedChecksum % 0x100) != 0){
//                   // P1OUT &=~BIT0;
//               }
//               else
//                   // P1OUT |=BIT0;

               IE2|=UCA0RXIE;
               i=0;
       }
    }
}
