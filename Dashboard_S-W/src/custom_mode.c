#include <custom_mode.h>

void Custom_visualization()
{
  blank_rectangle(1,1,130,70,0); 
  write_custom_parameters();
  blink_variable_selected();
  send_Custom_Mode=0;
   if(input(Button_UP))
   {
      while(input(Button_UP));
      {
         variable_VDC_seleccionada--;
         if(variable_VDC_seleccionada==0)
         {
            variable_VDC_seleccionada=10;
         }
      }
   }
   if(input(Button_DOWN))
   {
      while(input(Button_DOWN));
      {
         variable_VDC_seleccionada++;
         if(variable_VDC_seleccionada==11)
         {
            variable_VDC_seleccionada=1;
         }
      }
   }
   if(input(Button_LEFT))
   {
      while(input(Button_LEFT));
      {
         if(variable_VDC_seleccionada<11&&variable_VDC_seleccionada>5)//para cambiar de columna
         {
            variable_VDC_seleccionada=variable_VDC_seleccionada-5;
         }
      }
   }
   if(input(Button_RIGHT))
   {
      while(input(Button_RIGHT));
      {
         if(variable_VDC_seleccionada>0&&variable_VDC_seleccionada<6)
         {
            variable_VDC_seleccionada=variable_VDC_seleccionada+5;
         }         
      }
   }
   
   if(input(Button_VDC)) //PARA SALIR DE ESTE MODO
   {
      while(input(Button_VDC)); 
      {
         Button_VDC_position=1;
      }
   }
   
   glcd_refresh();
}


void custom_modification()
{
   switch(variable_VDC_seleccionada) //9 i 10 s?n els par?metres exclusius del Custom, localitzats a dalt de tot, dar valor a las variables
   {
      case 1:
         x1=55;//posicion del numero
         x2=50;
         x3=45;
         y=1;
         SKF_cte=c*100+d*10+u;
      break;
      case 2:
         x1=55;
         x2=50;
         x3=45;
         y=13;
         SKF_initial=(c*100)+(d*10)+u;
      break;
      case 3:
         x1=55;
         x2=50;
         x3=45;
         y=27;
         APPS_Sat_Down=(c*100)+(d*10)+u;
      break;
      case 4:
         x1=55;
         x2=50;
         x3=45;
         y=41;
         Regenerative_Torque=(c*100)+(d*10)+u;
      break;
      case 5:
         x1=55;
         x2=50;
         x3=45;
         y=55;
         Power_Reduction=(c*100)+(d*10)+u;
      break;
      case 6:
         x1=120;
         x2=115;
         x3=110;
         y=1;
         CKF_cte=(c*100)+(d*10)+u;
      break;
      case 7:
         x1=120;
         x2=115;
         x3=110;
         y=13;
         CKF_initial=(c*100)+(d*10)+u;
      break;
      case 8:
         x1=120;
         x2=115;
         x3=110;
         y=27;
         APPS_Sat_UP=(c*100)+(d*10)+u;
      break;
      case 9:
         x1=120;
         x2=115;
         x3=110;
         y=41;
         Power_Limit=(c*100)+(d*10)+u;
      break;
      case 10:
         x1=120;
         x2=115;
         x3=110;
         y=55;
         Temperature_Reduction=(c*100)+(d*10)+u;
      break;
   }
   switch(cursorCustom)//para escribir el numero y que quede centrado
   {
      case 3:
            splitUP(c);
            writeParameter(1,0,0,0,x3,y);
      break;
      case 2:
            splitUP(c);
            writeParameter(1,0,0,0,x3,y);
            splitUP(d);
            writeParameter(1,0,0,0,x2,y);//se dibuja en write parameter a partir del splitup en el digitsnumber         
      break;
      case 1:
            splitUP(c);
            writeParameter(1,0,0,0,x3,y);
            splitUP(d);
            writeParameter(1,0,0,0,x2,y);         
            splitUP(u);
            writeParameter(1,0,0,0,x1,y);         
      break;
   }      
   if(input(Button_UP))
   {
      while(input(Button_UP));
      {
         switch(cursorCustom)//Restamos centenas
         {
             case 3:
             {
                 if(c>0)
                 {
                     c--;
                 }
                 else
                 {
                     c=9;
                 } 
             break;
             }
             case 2://Restamos decenas
             {
                 if(d>0)
                 {
                    d--;
                 }
                 else
                 {
                    d=9;
                 }
             break;
             }
             case 1://Restamos unidades
             {
                 if(u>0)
                 {
                    u--;
                 }
                 else
                 {
                    u=9;
                 }
             break;
             }
         }
      }
   }
   if(input(Button_DOWN))
  {
      while(input(Button_DOWN));
      {
          switch(cursorCustom)//Restamos centenas
               {
                  case 3:
                  {
                     if(c<10)
                     {
                        c++;
                     }
                     else
                     {
                        c=0;
                     }
                     break;
                  }
                  case 2://Restamos decenas
                  {
                     if(d<10)
                     {
                        d++;
                     }
                     else
                     {
                        d=0;
                     }
                     break;
                  }
                  case 1://Restamos unidades
                  {
                     if(u<10)
                     {
                        u++;
                     }
                     else
                     {
                        u=0;
                     }
                     break;
                  }
               }
      }
   }
   if(input(Button_SELECT))
   {
            while(input(Button_SELECT));
            {
               switch(cursorCustom)//al pulsar select pasamos a la siguiente unidad
               {
                  case 3://centenas
                  {
                     cursorCustom=2;
                     break;
                  }
                  case 2://decenas
                  {
                     cursorCustom=1;
                     break;
                  }
                  case 1://unidad
                  {
                     Button_VDC_position=0;//salimos del editor a la visualizacion de datos
                     cursorCustom=3;//reiniciamos el proceso
                     //reseteamos variables porque ya las hemos mandado
                     c=0;
                     d=0;
                     u=0;
                     send_Custom_Mode=1;
                     write_Custom_Parameters();//abrimos la pantalla de vizualizar parametros
                     break;
                  }
               }
            }
      }
      glcd_refresh();
}
