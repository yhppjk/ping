#include <msp430.h>
#include <msp430g2553.h>
#include <intrinsics.h>

#include <stdio.h>
#include <math.h>

// Prototypes


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

void send_char(unsigned char sendchar);

void to_hex(char *s, int l, char *d);

void from_hex(char *s, int l, char *d);

unsigned char to_dec(char x);

void Init_uart(void);





/*...................................................................................*/
/* void convert_ASCII(int c, buffer)                                                         */
/*...................................................................................*/
/* Description : Convert the value of an int in ASCII                                          */
/* Inputs :                                                                          */
/*      - int c: value of the number you want to convert  (unsigned)                           */
/*      - buffer : adress of the ASCII buffer to put the results                                                                             */
/* Output : void                              */
/*...................................................................................*/

void convert_ASCII(int c, unsigned char hexa[4]);



/*...................................................................................*/
/* void convert_Hex_Dec(int valeur_hex)                                            */
/*...................................................................................*/
/* Description : Convert an hexadecimal to decimal                                   */
/* Inputs :                                                                          */
/*      - char toExtract[]: value of the number in hexadecimal you want to convert   */
/*                                                                                   */
/* Output : char                                                                     */
/*...................................................................................*/
int convert_Hex_Dec(int valeur_hex);



/*...................................................................................*/
/* void affiche_valeur(int c)                                                       */
/*...................................................................................*/
/* Description : Display a value without ASCII conversion                            */
/* Inputs :                                                                          */
/*      - int c: value of the number you want to display                            */
/*                                                                                   */
/* Output : void                                                                     */
/*...................................................................................*/
void Aff_valeur(int c,unsigned int bit);


/* ADC ESIG' */


/* ADC Haoping */
unsigned int ADC_Get(void);



void ADC_I(void);


/* ADC ESIG' */
void ADC_Demarrer_conversion(unsigned char voie);

void ADC_init(void);


/* Variables globales */

char read[16];
char value[8];
int j=0;
int i=0;

int pm25;

unsigned char commande[];
unsigned char commande1[];
unsigned char commande2[];
unsigned char sensor[8];
unsigned char button_ev;


unsigned int count=0;
unsigned char size =0;
unsigned int flag=1;

unsigned int origin_temperature;
unsigned int temperature;
unsigned int opacite;
unsigned int flag_opacite = 0;
unsigned char boucle_opacite=0;
unsigned int diff_temperature;

float temperature_num;
float opacite_num;

unsigned int seuil_temperature;
unsigned int seuil_opacite;
unsigned int seuil_particule;


unsigned char flag_ev=0;
unsigned char count_ev =0;
unsigned char state=0;

char *adresse;
// unsigned char a[];

// dunsigned char message[];

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;


    /*Init Uart Particule*/
    commande[0]=0x81;
    commande1[0]=0x11;
    commande2[0]=0x6e;
    Init_uart();
//    unsigned int exemple1=1998;
//    unsigned int exemple2=1996;
//    unsigned int exemple3=2005;


    /* Test température + SPI + 4 lEDS Vertes + 2 entrées SW */

//    unsigned int i = 0;         // Initialize variables. This will keep count of how many cycles between LED toggles
//
//    float U = 0;
//    uint16_t val = 0;


    // Init ADC
    ADC_init();
    ADC_Demarrer_conversion(4);
    ADC_Lire_resultat();

    // Init afficheurs
    Aff_Init(BIT3);
    Aff_Luminosite(200, BIT3);

    // Init Port entrée SW
    P2DIR &= ~BIT0;
    P2DIR &= ~BIT1;
    P2REN |= BIT0;
    P2REN |= BIT1;
    P2OUT |= BIT0;
    P2OUT |= BIT1;
    //button
    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1OUT |= BIT3;

    // Init LED (1 port)
    P2DIR |= BIT2; // mode sortie
    P2OUT |= BIT2;

    // Init EV
    P2DIR |= BIT5; // mode sortie
    P2OUT &=~BIT5;


    /* Attend sensor particule */
       while(count<400){
        __delay_cycles(32500);
        count++;
    }
    count=0;

    /* Test Bouton switch + LED (lorsque les boutons switch sont activés (GND), les leds clignottent) */
    while(1)
    {



      // if((P2IN&BIT0 == 0) && (P2IN&BIT1 == 0)) && (P2IN&BIT1 == 0))
      if(!(P2IN&BIT0) && !(P2IN&BIT1) && !(P1IN&BIT3) && (state != 6) ) // Mode manuel et bouton enfonce
      {
          state = 1;

      }
        else{
            button_ev=0xff;
        }
//      if((P2IN&BIT0) && !(P2IN&BIT1) ){ // Seuil opacite > 300 diff_temperature > 2  particule > 2000
//
//        if((opacite>300) && (diff_temperature > 2) ){
//            state = 1;
//        }
//        else if ((opacite>300) && (pm25 > 2000) ){
//            state = 1;
//        }
//        else if ((pm25>2000) && (diff_temperature > 2) ){
//            state = 1;
//        }
//
//      }
//      if(!(P2IN&BIT0) && (P2IN&BIT1)){ //  Seuil opacite > 600   diff_temperature >  4  particule > 4000
//          if((opacite>600) && (diff_temperature > 4) ){
//              state = 1;
//          }
//          else if ((opacite>600) && (pm25 > 4000) ){
//              state = 1;
//          }
//          else if ((pm25>4000) && (diff_temperature > 4) ){
//              state = 1;
//          }
//      }
//      if((P2IN&BIT0) &&(P2IN&BIT1)){ //  Seuil opacite > 900    diff_temperature > 6  particule > 6000
//          if((opacite>900) && (diff_temperature > 6) ){
//              state = 1;
//          }
//          else if ((opacite>900) && (pm25 > 6000) ){
//              state = 1;
//          }
//          else if ((pm25>6000) && (diff_temperature >6) ){
//              state = 1;
//          }

//      }
      // Activation électrovanne

      switch(state)
      {
          case 1:
              if(P1IN&BIT3) // relachement bouton
              {
                  P2OUT |= BIT5; // Activation EV
                  state = 2;
                  button_ev = 0xfe;
              }
          break;

          case 2:
            if(count_ev < 50)
            {
                P2OUT &= ~BIT2; // ALlumage LED vertes
                state = 3;
                count_ev++;
            }

            else{
                state = 4;
            }
          break;

          case 3: // Extinction led verte
              P2OUT |= BIT2;
              state = 2;
          break;

          case 4:
              P2OUT &= ~BIT5; // desactivation EV

              state=6;
          break;

//          default:
      }


//      P2OUT &= ~BIT2; // Extinction LED vertes
//      P2OUT &= ~BIT5; // Désactivation EV





      ADC_init();
      ADC_Demarrer_conversion(4); // Température
      temperature_num = ADC_Lire_resultat();        //Get the value of ADC
      temperature = temperature_num * 2.5 /1023 *1000;       //Calculate with the 1024 steps of ADC10, the result is mV
      if(count==0){
          origin_temperature = temperature;
      }
      else{
          diff_temperature = abs(origin_temperature-temperature);
      }
      count++;
//      temperature = 1180-temperature;

//      temperature=(560-temperature)/10;

      ADC_init_opacite();
      ADC_Demarrer_conversion(6); // Opacité
      opacite_num = ADC_Lire_resultat();
      opacite = opacite_num * 1.5 /1023 *1000;

      /* boucle pour calculer opacite */
      if(boucle_opacite>10){
          flag_opacite=0;
          boucle_opacite=0;
      }
      else{
          boucle_opacite++;
      }
      if(opacite!=0)
          flag_opacite +=opacite;




//          if(count>2){
      /* Particles sensor */
      if(flag == 1){
          send_string(commande);
          send_string(commande1);
          send_string(commande2);
          pm25 = getpm25();
          flag = 2;
      }

      /* saisir particule */


      /*table sensor: 0      1 2 3 4 5 6   7 */
      /*             Start   T T C C P P  end  */
      else if(flag == 2){
//          sensor[0]=0xFF;
//          sensor[1]=i_tochar(exemple1,3);
//          sensor[2]=i_tochar(exemple1,4);
//          sensor[3]=i_tochar(exemple2,3);
//          sensor[4]=i_tochar(exemple2,4);
//          sensor[5]=i_tochar(exemple3,3);
//          sensor[6]=i_tochar(exemple3,4);
          sensor[0]=button_ev;
          sensor[1]=i_tochar(diff_temperature,3);
          sensor[2]=i_tochar(diff_temperature,4);
          sensor[3]=i_tochar(opacite,3);
          sensor[4]=i_tochar(opacite,4);
          sensor[5]=i_tochar(pm25,3);
          sensor[6]=i_tochar(pm25,4);
          sensor[7]=0x15;

          send_string_value(sensor);
          flag=1;
      }
//          for (j=0; j<5000; j++);
          __enable_interrupt();       // ´ò¿ªÈ«¾ÖÖÐ¶Ï

//          pm25 = getpm25();
//          Aff_valeur(convert_Hex_Dec(pm25),BIT3);
          __delay_cycles(100000);

    }
}


char i_tochar(int input, int i){
    return (input >> 8*i) & 0xFF;
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

    P1DIR |= bit; // pin bit CS output
    P1OUT |= bit; // pin bit CS high
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
    P1OUT &= ~bit;  // CS low
    UCB0TXBUF = carac; // Put caracter in transmit buffer
    while (!(IFG2 & UCB0TXIFG)); // USCI_A0 TX buffer ready?
    P1OUT |= bit; // CS high
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
void ADC_init_opacite(void)
{
    ADC10CTL0 = ADC10CTL1 = 0;

// Choix de la r閒閞ence de tension Vcc GND
// R閒閞ence interne active et g閚閞ateur � 2,5 Volts  ADC10 actif
// Les autres bits sont suppos閟 � 0

    ADC10CTL0 =  SREF_0 | ADC10SHT_0  | REFON | ADC10ON;
    ADC10CTL0 &= ~REF2_5V;
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



/* Fonctions capteur particules */



const char hex_table[] = {
'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};

void send_char(unsigned char sendchar){

    while (!(IFG2&UCA0TXIFG));              //µÈ´ý·¢ËÍ¼Ä´æÆ÷Îª¿Õ
    UCA0TXBUF = sendchar;
}


void send_string(unsigned char *ptr){
    // _disable_interrupts();
    __disable_interrupt();
    while(*ptr != '\0'){
        send_char(*ptr++);                  // ·¢ËÍÊý¾Ý
    }
    __enable_interrupt();
}
void send_string_value(unsigned char *ptr){
    // _disable_interrupts();
    int temp = 0;
    __disable_interrupt();
    while(temp<8){
        send_char(*ptr++);                  // ·¢ËÍÊý¾Ý
        temp++;
    }
    __enable_interrupt();
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

void Init_uart(void){

    //WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
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


int getpm25(void){
    return (int)read[11]*16*16+(int) read[12];
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    if (IFG2 & UCA0RXIFG){

       if(i<16){
           read[i] = UCA0RXBUF;

            i++;
            if(read[0]!=0x81){
                i=0;
                if(read[1]!=0x11){
                    i=0;
                }
            }
//            else if(read[0]==0xFF){
//
//            }
        }
       else{
               IE2&=~UCA0RXIE;

               int calculatedChecksum = 0;
               for (j = 0; j < 16;j++) {
                   calculatedChecksum += read[j];
               }
               if((calculatedChecksum % 0x100) != 0){
                   // P1OUT &=~BIT0;
               }
               else
                   // P1OUT |=BIT0;

               IE2|=UCA0RXIE;
               i=0;
       }
    }
}
