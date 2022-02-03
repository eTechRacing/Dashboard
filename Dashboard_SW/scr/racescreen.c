#include <racescreen.h>

void write_VDCparameters(void)
{
       splitUP(SKF_actual);
       writeParameter(3,0,49,54,59,1);
       splitUP(CKF_actual);
       writeParameter(3,0,115,120,125,1);
       draw_text("SKF_actual", 1, 1, Tahoma7, 1);
       draw_text("CKF_actual", 64, 1, Tahoma7, 1);
       glcd_refresh();
}

void write_raceScreen (void)
{
   //blank_rectangle(1,1, 129, 129, 0); //Borrem tota la pantalla 
   drawXparameter(Speed, 100);
   writeXparameterValue(Speed);
   //draw_text("SPEED", 5, 1, Tahoma7, 1);
   draw_text("km/h", 80, 17, Tahoma7, 1);
   glcd_refresh();
}

void drawXparameter (unsigned int16 parameters_1, unsigned int16 maxValue)
{
   blank_rectangle(6, 61, 14, 64, 0); //Aquesta comanda,juntament amb les 9 seg?ents, borren cadascuna de les barres del par?metre
   blank_rectangle(18, 59, 26, 64, 0);
   blank_rectangle(30, 57, 38, 64, 0);
   blank_rectangle(42, 55, 50, 64, 0);
   blank_rectangle(54, 52, 62, 64, 0);
   blank_rectangle(66, 49, 74, 64, 0);
   blank_rectangle(78, 46, 86, 64, 0);
   blank_rectangle(90, 42, 98, 64, 0);
   blank_rectangle(102, 38, 110, 64, 0);
   blank_rectangle(114, 32, 122, 64, 0);
   barNumber=(((parameters_1*100)/maxValue)/10)+1; //Dividim entre 10 perqu? volem en tant per 10 i sumem 1 perq? sempre com a m?nim sigui 1 i el m?xim sigui a partir del 90%
   drawBars(barNumber);
   glcd_refresh();   
}

void drawBars (unsigned int8 numero)
{
   if (numero>=1)
   {
      blank_rectangle(6, 61, 14, 64, 1); 
   }
   if (numero>=2)
   {
      blank_rectangle(18, 59, 26, 64, 1); 
   }
   if (numero>=3)
   {
      blank_rectangle(30, 57, 38, 64, 1);
   }
   if (numero>=4)
   {
      blank_rectangle(42, 55, 50, 64, 1); 
   }
   if (numero>=5)
   {
      blank_rectangle(54, 52, 62, 64, 1);
   }
   if (numero>=6)
   {
      blank_rectangle(66, 49, 74, 64, 1);
   }
   if (numero>=7)
   {
      blank_rectangle(78, 46, 86, 64, 1);
   }
   if (numero>=8)
   {
      blank_rectangle(90, 42, 98, 64, 1); 
   }
   if (numero>=9)
   {
      blank_rectangle(102, 38, 110, 64, 1);
   }
   if (numero>=10)
   {
      blank_rectangle(114, 32, 122, 64, 1);
   }
}

void writeXparameterValue (unsigned int16 parameters)
{
   blank_rectangle(2, 13, 74, 47, 0); //Borrem els n?meros de unitats, desenes i centenes
   centenesXparameter=parameters/100; //Calculem els valors de unitats, desenes i centenes
   residuXparameter=parameters%100;
   desenesXparameter=residuXparameter/10;
   unitatsXparameter=residuXparameter%10;
   writeCentenes(centenesXparameter); //Escribim els n?meros de unitats, desenes i centenes  
   writeDesenes(desenesXparameter);
   writeUnitats(unitatsXparameter);
   glcd_refresh();
}

void writeCentenes (unsigned int8 numero)
{
   switch (numero)
   {
      case 0: blank_rectangle(2, 13, 24, 19, 1); //Segment a centenes
              blank_rectangle(17, 13, 24, 33, 1); //Segment b centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              blank_rectangle(2, 41, 24, 47, 1); //Segment d centenes
              blank_rectangle(2, 27, 9, 47, 1); //Segment e centenes
              blank_rectangle(2, 13, 9, 33, 1); //Segment f centenes
              break;      
      case 1: blank_rectangle(17, 13, 24, 33, 1); //Segment b centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              break;
      case 2: blank_rectangle(2, 13, 24, 19, 1); //Segment a centenes
              blank_rectangle(17, 13, 24, 33, 1); //Segment b centenes
              blank_rectangle(2, 41, 24, 47, 1); //Segment d centenes
              blank_rectangle(2, 27, 9, 47, 1); //Segment e centenes
              blank_rectangle(2, 27, 24, 33, 1); //Segment g centenes 
              break;
      case 3: blank_rectangle(2, 13, 24, 19, 1); //Segment a centenes
              blank_rectangle(17, 13, 24, 33, 1); //Segment b centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              blank_rectangle(2, 41, 24, 47, 1); //Segment d centenes
              blank_rectangle(2, 27, 24, 33, 1); //Segment g centenes 
              break;
      case 4: blank_rectangle(17, 13, 24, 33, 1); //Segment b centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              blank_rectangle(2, 13, 9, 33, 1); //Segment f centenes
              blank_rectangle(2, 27, 24, 33, 1); //Segment g centenes 
              break;
      case 5: blank_rectangle(2, 13, 24, 19, 1); //Segment a centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              blank_rectangle(2, 41, 24, 47, 1); //Segment d centenes
              blank_rectangle(2, 13, 9, 33, 1); //Segment f centenes
              blank_rectangle(2, 27, 24, 33, 1); //Segment g centenes 
              break;
      case 6: blank_rectangle(2, 13, 24, 19, 1); //Segment a centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              blank_rectangle(2, 41, 24, 47, 1); //Segment d centenes
              blank_rectangle(2, 27, 9, 47, 1); //Segment e centenes
              blank_rectangle(2, 13, 9, 33, 1); //Segment f centenes
              blank_rectangle(2, 27, 24, 33, 1); //Segment g centenes 
              break;     
      case 7: blank_rectangle(2, 13, 24, 19, 1); //Segment a centenes
              blank_rectangle(17, 13, 24, 33, 1); //Segment b centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              break;    
      case 8: blank_rectangle(2, 13, 24, 19, 1); //Segment a centenes
              blank_rectangle(17, 13, 24, 33, 1); //Segment b centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              blank_rectangle(2, 41, 24, 47, 1); //Segment d centenes
              blank_rectangle(2, 27, 9, 47, 1); //Segment e centenes
              blank_rectangle(2, 13, 9, 33, 1); //Segment f centenes
              blank_rectangle(2, 27, 24, 33, 1); //Segment g centenes 
              break;    
      case 9: blank_rectangle(2, 13, 24, 19, 1); //Segment a centenes
              blank_rectangle(17, 13, 24, 33, 1); //Segment b centenes
              blank_rectangle(17, 27, 24, 47, 1); //Segment c centenes
              blank_rectangle(2, 41, 24, 47, 1); //Segment d centenes
              blank_rectangle(2, 13, 9, 33, 1); //Segment f centenes
              blank_rectangle(2, 27, 24, 33, 1); //Segment g centenes 
              break;
   }
}

void writeDesenes (unsigned int8 numero)
{
   switch (numero)
   {
      case 0: blank_rectangle(27, 13, 49, 19, 1); //Segment a desenes
              blank_rectangle(42, 13, 49, 33, 1); //Segment b desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              blank_rectangle(27, 41, 49, 47, 1); //Segment d desenes
              blank_rectangle(27, 27, 34, 47, 1); //Segment e desenes
              blank_rectangle(27, 13, 34, 33, 1); //Segment f desenes
              break;      
      case 1: blank_rectangle(42, 13, 49, 33, 1); //Segment b desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              break;
      case 2: blank_rectangle(27, 13, 49, 19, 1); //Segment a desenes
              blank_rectangle(42, 13, 49, 33, 1); //Segment b desenes
              blank_rectangle(27, 41, 49, 47, 1); //Segment d desenes
              blank_rectangle(27, 27, 34, 47, 1); //Segment e desenes
              blank_rectangle(27, 27, 49, 33, 1); //Segment g desenes
              break;
      case 3: blank_rectangle(27, 13, 49, 19, 1); //Segment a desenes
              blank_rectangle(42, 13, 49, 33, 1); //Segment b desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              blank_rectangle(27, 41, 49, 47, 1); //Segment d desenes
              blank_rectangle(27, 27, 49, 33, 1); //Segment g desenes
              break;
      case 4: blank_rectangle(42, 13, 49, 33, 1); //Segment b desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              blank_rectangle(27, 13, 34, 33, 1); //Segment f desenes
              blank_rectangle(27, 27, 49, 33, 1); //Segment g desenes
              break;
      case 5: blank_rectangle(27, 13, 49, 19, 1); //Segment a desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              blank_rectangle(27, 41, 49, 47, 1); //Segment d desenes
              blank_rectangle(27, 13, 34, 33, 1); //Segment f desenes
              blank_rectangle(27, 27, 49, 33, 1); //Segment g desenes
              break;
      case 6: blank_rectangle(27, 13, 49, 19, 1); //Segment a desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              blank_rectangle(27, 41, 49, 47, 1); //Segment d desenes
              blank_rectangle(27, 27, 34, 47, 1); //Segment e desenes
              blank_rectangle(27, 13, 34, 33, 1); //Segment f desenes
              blank_rectangle(27, 27, 49, 33, 1); //Segment g desenes
              break;     
      case 7: blank_rectangle(27, 13, 49, 19, 1); //Segment a desenes
              blank_rectangle(42, 13, 49, 33, 1); //Segment b desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              break;    
      case 8: blank_rectangle(27, 13, 49, 19, 1); //Segment a desenes
              blank_rectangle(42, 13, 49, 33, 1); //Segment b desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              blank_rectangle(27, 41, 49, 47, 1); //Segment d desenes
              blank_rectangle(27, 27, 34, 47, 1); //Segment e desenes
              blank_rectangle(27, 13, 34, 33, 1); //Segment f desenes
              blank_rectangle(27, 27, 49, 33, 1); //Segment g desenes
              break;    
      case 9: blank_rectangle(27, 13, 49, 19, 1); //Segment a desenes
              blank_rectangle(42, 13, 49, 33, 1); //Segment b desenes
              blank_rectangle(42, 27, 49, 47, 1); //Segment c desenes
              blank_rectangle(27, 41, 49, 47, 1); //Segment d desenes
              blank_rectangle(27, 13, 34, 33, 1); //Segment f desenes
              blank_rectangle(27, 27, 49, 33, 1); //Segment g desenes
              break;
   }
}

void writeUnitats (unsigned int8 numero)
{
   switch (numero)
   {
      case 0: blank_rectangle(52, 13, 74, 19, 1); //Segment a unitats 
              blank_rectangle(67, 13, 74, 33, 1); //Segment b unitats
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              blank_rectangle(52, 41, 74, 47, 1); //Segment d unitats
              blank_rectangle(52, 27, 59, 47, 1); //Segment e unitats
              blank_rectangle(52, 13, 59, 33, 1); //Segment f unitats
              break;      
      case 1: blank_rectangle(67, 13, 74, 33, 1); //Segment b unitats
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              break;
      case 2: blank_rectangle(52, 13, 74, 19, 1); //Segment a unitats 
              blank_rectangle(67, 13, 74, 33, 1); //Segment b unitats
              blank_rectangle(52, 41, 74, 47, 1); //Segment d unitats
              blank_rectangle(52, 27, 59, 47, 1); //Segment e unitats
              blank_rectangle(52, 27, 74, 33, 1); //Segment g unitats
              break;
      case 3: blank_rectangle(52, 13, 74, 19, 1); //Segment a unitats 
              blank_rectangle(67, 13, 74, 33, 1); //Segment b unitats
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              blank_rectangle(52, 41, 74, 47, 1); //Segment d unitats
              blank_rectangle(52, 27, 74, 33, 1); //Segment g unitats
              break;
      case 4: blank_rectangle(67, 13, 74, 33, 1); //Segment b unitats
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              blank_rectangle(52, 13, 59, 33, 1); //Segment f unitats
              blank_rectangle(52, 27, 74, 33, 1); //Segment g unitats
              break;
      case 5: blank_rectangle(52, 13, 74, 19, 1); //Segment a unitats 
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              blank_rectangle(52, 41, 74, 47, 1); //Segment d unitats
              blank_rectangle(52, 13, 59, 33, 1); //Segment f unitats
              blank_rectangle(52, 27, 74, 33, 1); //Segment g unitats
              break;
      case 6: blank_rectangle(52, 13, 74, 19, 1); //Segment a unitats 
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              blank_rectangle(52, 41, 74, 47, 1); //Segment d unitats
              blank_rectangle(52, 27, 59, 47, 1); //Segment e unitats
              blank_rectangle(52, 13, 59, 33, 1); //Segment f unitats
              blank_rectangle(52, 27, 74, 33, 1); //Segment g unitats
              break;     
      case 7: blank_rectangle(52, 13, 74, 19, 1); //Segment a unitats 
              blank_rectangle(67, 13, 74, 33, 1); //Segment b unitats
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              break;    
      case 8: blank_rectangle(52, 13, 74, 19, 1); //Segment a unitats 
              blank_rectangle(67, 13, 74, 33, 1); //Segment b unitats
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              blank_rectangle(52, 41, 74, 47, 1); //Segment d unitats
              blank_rectangle(52, 27, 59, 47, 1); //Segment e unitats
              blank_rectangle(52, 13, 59, 33, 1); //Segment f unitats
              blank_rectangle(52, 27, 74, 33, 1); //Segment g unitats
              break;    
      case 9: blank_rectangle(52, 13, 74, 19, 1); //Segment a unitats 
              blank_rectangle(67, 13, 74, 33, 1); //Segment b unitats
              blank_rectangle(67, 27, 74, 47, 1); //Segment c unitats
              blank_rectangle(52, 41, 74, 47, 1); //Segment d unitats
              blank_rectangle(52, 13, 59, 33, 1); //Segment f unitats
              blank_rectangle(52, 27, 74, 33, 1); //Segment g unitats
              break;
   }
}
