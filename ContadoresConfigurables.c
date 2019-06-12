#include <18f4620.h>
#include <stdlib.h>
#fuses HS,NOWDT,NOPROTECT,PUT,BROWNOUT,NOLVP,NOMCLR
#use delay(clock=40000000)

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif
int FlagSerial=0;
char caracter;
int contador;
#INT_RDA
void isr_rda(void)
{
   caracter= getc();
   FlagSerial=1;
}
#INT_Timer0
void timer0(void)
{
     contador++;
     set_timer0(15536);
}
void main()
{
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RDA);
   set_tris_c(0x80);
   while(TRUE)
   {
      if(FlagSerial==1)
      {
      }
   }

}
