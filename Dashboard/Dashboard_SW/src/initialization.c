#include "initialization.h"

void Dashboard_initialization()
{
   output_low(BUZZER); //Apaguem buzzer (cal comprobar)(!!!!!!!!!!!!)
   canConfiguration();
   segments_init();
   bargraph_init();
   
   enable_interrupts(INT_TIMER2);   
   ext_int_edge(l_to_h); //Configurem el flanco de la interrupci? quan passi d'estat baix a estat alt
   enable_interrupts(GLOBAL);
   setup_timer_2(T2_DIV_BY_4, 250, 10); //Envia un flag cada 4ms --> (1/20?10^6)*4ciclosMaquina*4 - flag al arribar a 250 - 10 vegades*/
   ///////////////////////////////////
   //INICIALIZACI?N DE LA PANTALLA //
   /////////////////////////////////
   glcd_init();
   delay_ms(200);
   glcd_blank(); 
   delay_ms(200); 
   glcd_contrast(6, 25);
   //FIN DE LA INIZIALIZACI?N DE LA PANTALLA
   blank_rectangle(1, 1, 128, 64, 0);  //Netegem la pantalla abans d'escriure-hi
   output_high(LED_AMS); //Encenem indicador del BMS durant uns 2.5s (normatiu)
   output_high(LED_IMD); //Encenem indicador del IMD durant uns 2.5s (normatiu)
   normativeEnable=1;
}

void resetvariables()
{
   LockOn=0;
   Pantalla_actual=0;
   PrechargeOrder=0;
   variable_startPrecharge=0;
   EnableDrive=0;
   cursor=1;
   refresh_display=1;
   competicion_seleccionada=1;
   idCustom=0;
   piloto=0;
   PrechargeOrder=0;
   variable_startPrecharge=0;
   segments_init();
   bargraph_init();
}


