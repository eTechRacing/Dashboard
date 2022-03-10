#include "PrechargeScreen.h"

void precharge_message (void)
//////////////////////////////////////
// ESCRIBE:                         //
//    PRE-CHARGE SEQUENCE           //
//    sequence inicialization . . . //
//    Waiting for precharge         //
//////////////////////////////////////
{
   blank_rectangle(1,1,130,64,0);
   draw_text("PRE-CHARGE SEQUENCE", 10, 3, Tahoma7, 1);// carstate==9
   draw_line(1, 14, 128, 14, 1);
   draw_text("sequence inicialization", 14, 30, Tahoma7, 1);// carstate==6
   draw_text("Waiting for precharge", 20, 20, Tahoma7, 1);  // carstate==3
   draw_box (14, 48, 114, 63, 1); //Recuadre que indicar? el percentatge de precharge
   glcd_refresh();
}

void Pantalla_carga_precharge()
{
   if (prescalerTimer==0)//simular la secuencia de movimientos de los puntos
   {               
      blank_rectangle(102, 30, 128, 42, 0); //Si no hem començat el precharge i el comptador del prescaler es 0 (s'ha reiniciat), borrem els punts
   }   
   else 
   {
      switch(prescalerTimer)
      {
         case 1: draw_text("sequence inicialization .", 14, 30, Tahoma7, 1);
                 break;
         case 2: draw_text("sequence inicialization . .", 14, 30, Tahoma7, 1);
                 break;
         case 3: draw_text("sequence inicialization . . .", 14, 30, Tahoma7, 1);
                 break;
      }
      draw_text("Waiting for precharge", 20, 20, Tahoma7, 1);  
   }  
   glcd_refresh();//siempre hay que refrescar para que se actualice el aspecto de la pantalla
}

void Precharge_information()
{
   blank_rectangle(14, 48, 114, 63, 0); //Borrem el percentatge que porta
   draw_box (14, 48, 114, 63, 1); //Dibuixem el recuadre del percentatge
   splitUp(PrechargePercentage);
   blank_rectangle(14, 49, (PrechargePercentage+14), 62, 1); //Pintem la part de la barra indicadora del proces que toqui en funcio del percentatge 
   glcd_refresh();
}

