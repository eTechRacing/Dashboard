#include <conversions.h>

void splitUP(unsigned int16 valor)
{
   milers=valor/1000;//"/" guardas el valor entero
   residu=valor%1000;// "%" guardas el residuo
   centenes=residu/100;
   residu=residu%100;
   desenes=residu/10;
   unitats=residu%10;
   //ejemplo->valor=4371
   /*NO LE VEO SENTIDO A ESTE ARRAY
   array[0]=milers;//4
   array[1]=centenes;//3
   array[2]=desenes;//7
   array[3]=unitats;//1
*/
}

void writeParameter (unsigned int32 digitsNumber,unsigned int32 xMilers,unsigned int32 xCentenes,unsigned int32 xDesenes,unsigned int32 xUnitats, y)
{   
   sprintf(unitatsInt, "%s", number[unitats]);
   sprintf(desenesInt, "%s", number[desenes]);
   sprintf(centenesInt, "%s", number[centenes]);
   sprintf(milersInt, "%s", number[milers]);
   if (digitsNumber >= 1)
   {
      draw_text(unitatsInt, xUnitats, y, Tahoma7, 1);
   }
   if (digitsNumber >= 2)
   {
      draw_text(desenesInt, xDesenes, y, Tahoma7, 1);
   }
   if (digitsNumber >= 3)
   {
      draw_text(centenesInt, xCentenes, y, Tahoma7, 1);
   }
   if (digitsNumber >= 4)
   {
      draw_text(milersInt, xMilers, y, Tahoma7, 1);
   }
}
