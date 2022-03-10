#include <templates.h>

void scrollDrawing()
   {
      draw_rectangle(25, 21, 104, 43, 1); //Quadrat central de 79x22 
      draw_rectangle(24, 20, 105, 44, 1);
      //////////////////////////////////////// fletxa superior
      draw_line(64, 12, 64, 12, 1);
      draw_line(63, 13, 65, 13, 1);
      draw_line(62, 14, 66, 14, 1);
      draw_line(61, 15, 67, 15, 1);
      draw_line(60, 16, 68, 16, 1);
      draw_line(59, 17, 69, 17, 1);
      //////////////////////////////////////// fletxa inferior
      draw_line(64, 52, 64, 52, 1);
      draw_line(63, 51, 65, 51, 1);
      draw_line(62, 50, 66, 50, 1);
      draw_line(61, 49, 67, 49, 1);
      draw_line(60, 48, 68, 48, 1);
      draw_line(59, 47, 69, 47, 1);
      //////////////////////////////////////// fletxa esquerra
      draw_line(21, 27, 21, 37, 1);
      draw_line(20, 28, 20, 36, 1);
      draw_line(19, 29, 19, 35, 1);
      draw_line(18, 30, 18, 34, 1);
      draw_line(17, 31, 17, 33, 1);
      draw_line(16, 32, 16, 32, 1);
      //////////////////////////////////////// fletxa dreta
      draw_line(108, 27, 108, 37, 1);
      draw_line(109, 28, 109, 36, 1);
      draw_line(110, 29, 110, 35, 1);
      draw_line(111, 30, 111, 34, 1);
      draw_line(112, 31, 112, 33, 1);
      draw_line(113, 32, 113, 32, 1);
      ////////////////////////////////////////
      switch(competicion_seleccionada)
         { 
            case 1:
               //blank_rectangle(26, 22, 103, 42, 0);
               //blank_rectangle(26, 54, 103, 74, 0);
               //blank_rectangle(26, 1, 103, 11, 0);
               //blank_rectangle(1, 27, 22, 37, 0);
               //blank_rectangle(108, 27, 130, 37, 0);
               ////////////////////////////////////////
               draw_text("rtd", 116, 27, Tahoma7, 1);//DERECHA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("rtd", 1, 27, Tahoma7, 1);//IZQUIERDA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("ENDURANCE",36,1,Tahoma7,1);
               draw_text("WORKSHOP",38,27,Tahoma7,1);//ESTE ES EL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("CUSTOM",43,54,Tahoma7,1);                  
               break;
            case 2:
               ////////////////////////////////////////
               draw_text("E", 116, 12, Tahoma7, 1);
               draw_text("T", 116, 22, Tahoma7, 1);
               draw_text("A", 116, 32, Tahoma7, 1);
               draw_text("S", 116, 42, Tahoma7, 1);
               draw_text("D", 7, 12, Tahoma7, 1);
               draw_text("A", 7, 22, Tahoma7, 1);
               draw_text("S", 7, 32, Tahoma7, 1);
               draw_text("H", 7, 42, Tahoma7, 1);
               draw_text("WORKSHOP",38,1,Tahoma7,1);
               draw_text("CUSTOM",45,27,Tahoma7,1);
               draw_text("ACCELERATION",27,54,Tahoma7,1);
               break;
            case 3:
               blank_rectangle(26, 22, 103, 42, 0);
               blank_rectangle(26, 54, 103, 74, 0);
               blank_rectangle(26, 1, 103, 11, 0);
               ////////////////////////////////////////
               draw_text("R1", 1, 27, Tahoma7, 1);
               draw_text("R2", 118, 27, Tahoma7, 1);
               draw_text("CUSTOM",43,1,Tahoma7,1);
               draw_text("ACCELERATION",27,27,Tahoma7,1);
               draw_text("SKIDPAD",43,54,Tahoma7,1);
               break;
            case 4: 
               blank_rectangle(26, 22, 103, 42, 0);
               blank_rectangle(26, 54, 103, 74, 0);
               blank_rectangle(26, 1, 103, 11, 0);
               ///////////////////////////////////////
               draw_text("R1", 1, 27, Tahoma7, 1);
               draw_text("R2", 118, 27, Tahoma7, 1);   
               draw_text("ACCELERATION",27,1,Tahoma7,1);
               draw_text("SKIDPAD",43,27,Tahoma7,1);
               draw_text("AUTOCROSS",35,54,Tahoma7,1);
               break;  
            case 5: 
               blank_rectangle(26, 22, 103, 42, 0);
               blank_rectangle(26, 54, 103, 74, 0);
               blank_rectangle(26, 1, 103, 11, 0);
               ///////////////////////////////////////
               draw_text("R1", 1, 27, Tahoma7, 1);
               draw_text("R2", 118, 27, Tahoma7, 1);   
               draw_text("SKIDPAD",43,1,Tahoma7,1);
               draw_text("AUTOCROSS",35,27,Tahoma7,1);
               draw_text("ENDURANCE",36,54,Tahoma7,1);
            break;
            case 6:
               blank_rectangle(26, 22, 103, 42, 0);
               blank_rectangle(26, 54, 103, 74, 0);
               blank_rectangle(26, 1, 103, 11, 0);
               ////////////////////////////////////////  
               draw_text("R1", 1, 27, Tahoma7, 1);
               draw_text("R2", 118, 27, Tahoma7, 1);   
               draw_text("AUTOCROSS",35,1,Tahoma7,1);
               draw_text("ENDURANCE",36,27,Tahoma7,1);
               draw_text("WORKSHOP",38,54,Tahoma7,1);
            break;   
         }
         glcd_refresh();
}
