#include <VDC_parameters.h>


void show_competition_parameters()
{
   write_VDC_Parameters();
   
   if(input(Button_VDC))//SI PULSAMOS EL BOTON VDC SALIMOS DEL CUSTOM MENU
   {
      while(input(Button_VDC));
      {
         cursor=1;
         refresh_display=1;
         Pantalla_actual--;
      }
   } 
   glcd_refresh();
}
