#include <7segments.h>

void segments_init()
{
   output_high(PIN_D2);//Apagamos los leds
   output_high(PIN_C5);
   output_high(PIN_C4);
   output_high(PIN_D3);
   output_high(PIN_C2);
   output_high(PIN_D1);
   output_high(PIN_D0);
   output_high(PIN_C3);
}

void visualitzar7seg(unsigned int8 valorSOC)
{
   for (cnt=0;cnt<2;cnt++)
   {
      if (valorSOC > 9)
         if (cnt==0)
         {
            decadaSOC=valorSOC/10;
            SEG_A=PIN_C2;
            SEG_B=PIN_D1;
            SEG_C=PIN_D0;
            SEG_D=PIN_C3;
         }
         else
         {
            decadaSOC=valorSOC%10;
            SEG_A=PIN_D2;
            SEG_B=PIN_C5;
            SEG_C=PIN_C4;
            SEG_D=PIN_D3;
         }
      switch(decadaSOC)
      
      {
         case 0: output_low(SEG_A); //num. 0
                 output_low(SEG_B);
                 output_low(SEG_C);
                 output_low(SEG_D);
                 break;
         case 1: output_high(SEG_A); //num. 1
                 output_low(SEG_B);
                 output_low(SEG_C);
                 output_low(SEG_D);
                 break;
         case 2: output_low(SEG_A); //num. 2
                 output_high(SEG_B);
                 output_low(SEG_C);
                 output_low(SEG_D);
                 break;
         case 3: output_high(SEG_A); //num. 3
                 output_high(SEG_B);
                 output_low(SEG_C);
                 output_low(SEG_D);
                 break;
         case 4: output_low(SEG_A); //num. 4
                 output_low(SEG_B);
                 output_high(SEG_C);
                 output_low(SEG_D);
                 break;
         case 5: output_high(SEG_A); //num. 5
                 output_low(SEG_B);
                 output_high(SEG_C);
                 output_low(SEG_D);
                 break;
         case 6: output_low(SEG_A); //num. 6
                 output_high(SEG_B);
                 output_high(SEG_C);
                 output_low(SEG_D);
                 break;
         case 7: output_high(SEG_A); //num. 7
                 output_high(SEG_B);
                 output_high(SEG_C);
                 output_low(SEG_D);
                 break;
         case 8: output_low(SEG_A); //num. 8
                 output_low(SEG_B);
                 output_low(SEG_C);
                 output_high(SEG_D);
                 break;
         case 9: output_high(SEG_A); //num. 9
                 output_low(SEG_B);
                 output_low(SEG_C);
                 output_high(SEG_D);
                 break;
         }
   }
      if (valorSOC<10)
      {
         decadaSOC=valorSOC%10;
         SEG_A=PIN_D2;
         SEG_B=PIN_C5;
         SEG_C=PIN_C4;
         SEG_D=PIN_D3;
         cnt=1;
      }
}
