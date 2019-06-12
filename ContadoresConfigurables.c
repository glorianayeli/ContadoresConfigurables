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
int contador,ContadorX=1,ContadorY=1;
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
     set_timer0(6);
}
void main()
{
   enable_interrupts(INT_RDA);
   enable_interrupts(int_timer0);
   enable_interrupts(GLOBAL);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4|RTCC_8_BIT);
   set_timer0(6);
   set_tris_c(0x80);
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_d(0x00);
   while(TRUE)
   {
      if(FlagSerial==1)
      {
         if(caracter=='x'||caracter=='X')
         {
            if(Contadorx==1)
            {
               for(int ValorContador=1;ValorContador<=128;ValorContador*=2)
               {
                  output_a(ValorContador);
               }
            }
            else if(ContadorX==2)
            {
               for(int ValorContador=1;ValorContador<=128;ValorContador*=2)
               {
                  output_b(ValorContador);
               }
            }
            else if(ContadorX==3)
            {
               for(int ValorContador=1;ValorContador<=128;ValorContador*=2)
               {
                  output_d(ValorContador);
               }
            }
            else if(ContadorX==4)
            {  
               ContadorX=1;
            }
         }
         
      }
   }

}
