#include <Logo.h>

void logo_ETR(void)
{
   //E
   blank_rectangle(25, 8, 31, 57, 1);
   blank_rectangle(31, 8, 43, 17, 1);
   blank_rectangle(31, 29, 43, 35, 1);
   blank_rectangle(31, 48, 43, 57, 1);

   //T
   blank_rectangle(50, 8, 76, 17, 1);
   blank_rectangle(60, 18, 66, 57, 1);

   //R
   blank_rectangle(83, 8, 88, 57, 1);
   
   blank_rectangle(83, 8, 98, 17, 1);
   
   blank_rectangle(89, 29, 99, 37, 1);
   
   blank_rectangle(98, 12, 102, 35, 1);
   
   blank_rectangle(99, 9, 100, 11, 1);
   blank_rectangle(101, 10, 101, 11, 1);

   blank_rectangle(100, 36, 101, 36, 1);
   
   blank_rectangle(91, 38, 98, 39, 1);
   blank_rectangle(92, 40, 98, 42, 1);
   blank_rectangle(93, 42, 99, 45, 1);
   blank_rectangle(94, 46, 100, 49, 1);
   blank_rectangle(95, 50, 101, 52, 1);
   blank_rectangle(96, 52, 102, 57, 1);


   glcd_refresh();
}
