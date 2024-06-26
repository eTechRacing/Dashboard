#include <driving_menu.h>

void left_or_right()
{
   if (cursor==0)//izquierda
   {
      if(competicion_seleccionada==2)
        {
            idCustom=1; //DASH
        }
     if(competicion_seleccionada>2)
        {
            piloto=1;
        }
   }
   
   else if (cursor==2)//derecha
   {
      if(competicion_seleccionada==2)
        {
            idCustom=2; //ETAS
        }
     if (competicion_seleccionada>2)
        {
            piloto=2;
        }
   }
}

