#include <bargraph.h>


void bargraph_init(void) //Resetea el bargraph
{
   output_low(PIN_E1); 
   output_low(PIN_A4);
   output_low(PIN_A5);
   for (contBargraph=0; contBargraph<1; contBargraph++) 
   {
      flancoCLK();
   }
}

void flancoCLK (void)// Genera un CLK
{  
      output_low(PIN_E0);
      delay_ms(5);
      output_high(PIN_E0);
      delay_ms(5);
}

void selectNumberLEDs (unsigned int8 parameter)//trsnsforma el valor que le llega a valor decimal para saber que numero de leds encender
{
   
   if (parameter>96)// esta en hexadecimal
   {
      numBargraphLEDsActual=12;
   }
   else if (parameter>88) 
   {
      numBargraphLEDsActual=11;
   }
   else if (parameter>80)
   {
      numBargraphLEDsActual=10;
   }
   else if (parameter>72)
   {
      numBargraphLEDsActual=9;
   }
   else if (parameter>64)
   {
      numBargraphLEDsActual=8;
   }
   else if (parameter>56)
   {
      numBargraphLEDsActual=7;
   }
   else if (parameter>48)
   {
      numBargraphLEDsActual=6;
   }
   else if (parameter>40)
   {
      numBargraphLEDsActual=5;
   }
   else if (parameter>32)
   {
      numBargraphLEDsActual=4;
   }
   else if (parameter>24)
   {
      numBargraphLEDsActual=3;
   }
   else if (parameter>16)
   {
      numBargraphLEDsActual=2;
   }
   else if (parameter>8)
   {
      numBargraphLEDsActual=1;
   }
   else
   {
      numBargraphLEDsActual=0;
   }
}

void bargraphFunctionality(void)
{  
   if(numBargraphLEDsActual!=numBargraphLEDsAnterior)
   {
      bargraph_init();//Reseteamos el bargraph
      output_high(PIN_A5);//RST OFF
      output_high(pin_E1);//Activamos el controlador
      for (contBargraph=0; contBargraph<numBargraphLEDsActual; contBargraph++) 
      {
         if (contBargraph>7)
         {
            output_high(PIN_A4);
            flancoCLK();
         }
         else
         {
            flancoCLK();
         }

      }
      numBargraphLEDsAnterior=numBargraphLEDsActual;
   }
}


