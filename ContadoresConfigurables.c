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
int contador,ContadorX=0,ContadorY=0,InicioIzquierda=0,InicioDerecha=0;
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
      if(caracter=='X'||caracter=='x')
      {
         ContadorX++;
      } 
      else if(caracter=='y'||caracter=='Y')
      {
         ContadorY++;
      }
      else if(caracter=='d'||caracter=='D')
      {
         InicioDerecha=1;
      }
      else if(caracter=='i'||caracter=='I')
      {
         InicioIzquierda=1;
      }
      if(FlagSerial==1)
      {
         if((caracter=='x'||caracter=='X')&&(InicioDerecha==1))
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
         else if((caracter=='y'||caracter=='Y')&&(InicioDerecha==1))
         {
            if(ContadorY==1||ContadorY==3)
            {
               for(int ValorContador=1;ValorContador<=128;ValorContador*=2)
               {
                  output_d(ValorContador);
               }
            }
            else if(ContadorY==2||ContadorY==1)
            {
               for(int ValorContador=1;ValorContador<=128;ValorContador*=2)
               {
                  output_b(ValorContador);
               }
            }
            else if(ContadorY==3)
            {
               for(int ValorContador=1;ValorContador<=128;ValorContador*=2)
               {
                  output_a(ValorContador);
               }
            }
            else if(ContadorY==4)
            {  
               ContadorY=1;
            }
         }
         //Derecha
         if((caracter=='x'||caracter=='X')&&(InicioIzquierda==1))
         {
            if(Contadorx==1)
            {
               for(int ValorContador=128;ValorContador>=1;ValorContador/=2)
               {
                  output_a(ValorContador);
               }
            }
            else if(ContadorX==2)
            {
               for(int ValorContador=128;ValorContador>=1;ValorContador/=2)
               {
                  output_b(ValorContador);
               }
            }
            else if(ContadorX==3)
            {
               for(int ValorContador=128;ValorContador>=1;ValorContador/=2)
               {
                  output_d(ValorContador);
               }
            }
            else if(ContadorX==4)
            {  
               ContadorX=1;
            }
         }
         else if((caracter=='y'||caracter=='Y')&&(InicioIzquierda==1))
         {
            if(ContadorY==1||ContadorY==3)
            {
               for(int ValorContador=128;ValorContador>=1;ValorContador/=2)
               {
                  output_d(ValorContador);
               }
            }
            else if(ContadorY==2||ContadorY==1)
            {
               for(int ValorContador=128;ValorContador>=1;ValorContador/=2)
               {
                  output_b(ValorContador);
               }
            }
            else if(ContadorY==3)
            {
               for(int ValorContador=128;ValorContador>=1;ValorContador/=2)
               {
                  output_a(ValorContador);
               }
            }
            else if(ContadorY==4)
            {  
               ContadorY=1;
            }
         }
      }
   }

}
