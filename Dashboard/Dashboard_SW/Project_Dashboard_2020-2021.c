//EL ORDEN DE LOS INCLUDES ES IMPORTANTE, SE ORDENAN EN FUNCION DE QUE FUNCIONES SE USAN DENTRO
#include <configuration_PIC.h>   //CONFIGURACION DEL PIC
#include <font_tahoma.h>         //TIPO DE LETRA
#include <st7565-config.h>       //
#include <st7565.c>              //
#include <my_graphics.c>         //
#include <variables.h>           //DEFINIDAS TODAS LAS VARIABLES
#include <7segments.c>
#include <bargraph.c>
#include <conversions.c>         //
#include <modification_CAN.h> //No se debe modificar una libreria directamente por eso creo esto para poner las modificaciones
#include <Errors.c>              //LECTURA DE ERRORES QUE MANDA LA ETAS
#include <CAN.c>                 //COMUNICACION CON CAN
#include <templates.c>           //DIBUJOS DE LA PANTALLA
#include <driving_menu.c>        //PARA SABER SI ESTAMOS EN LA IZQUIERDA O EN LA DERECHA DEL MENU
#include <Buttons_function.c>    //FUNCION DE LOS BOTONES
#include <initialization.c>      //INICIALIZACION DE VARIABLES
#include <PrechargeScreen.c>     //FUNCIONES RELACIONADAS CON PRECHARGE
#include <draw_animation_blink.c>//PARPADEO PARA SABER DONDE ESTAMOS EN EL MENU
#include <Timers.c>              //DIFERENTES CONTADORES
#include <racescreen.c>
#include <Logo.c>
//���REVISAR EL TAMA�O DE TODAS LAS VARIABLES!!!
//EL WARNING 216 SALE POR CULPA DE LOS OUTPUT_LOW DEL IF DE NORMATIVEENABLE 
main()
{
   Dashboard_initialization(); //Iniciamos todas las variables y la pantalla
   Logo_ETR();
   delay_ms(3000);
   glcd_blank();
   while (true)
   {
      if ((CarState==0) || (CarState==21)) //Si estamos en el estado 0 o 21 del coche (el estado lo decide la ETAS)
      {
         resetvariables(); //Reseteamos todas las variables
         popUpWindow(); //Ventana donde aparece el error, si hay
      }
      
      if (Pantalla_actual==0 && (CarState==3||CarState==6||CarState==9)) //el codigo de abajo, durante su ejecucion pasamos por los 3 carstate por eso se ponen en or
      {
         LockOn= 0; // Le decimos a ETAS que no mande torque a los motores
         precharge_message(); //Dibujamos en la pantalla informacion para el precharge
         SteeringButtons();
         
         if (input(Button_Select)||(bothSteeringButtons==1))
         {
            while (input(Button_Select)||(bothSteeringButtons==1))
            {
            variable_startPrecharge=1;//Variable para controlar el estado del precharge
            PrechargeOrder=1;// Digo a ETAS que empiece el precharge
            }
         }
         if (variable_startPrecharge==0)
         {
            Pantalla_carga_precharge();//pantalla de carga del precharge
         }
         else
         {
            Precharge_information();
         }
         if(variable_startPrecharge==1)
            {
               PrechargeOrder=0; // Ya ha acabado el precharge, dejo de hablar con ETAS  de precharge
            }
         if(CarState==12)//cuando ha acabado todo el precharge del coche, etas manda el 12 y pasamos de pantalla
         {
            Pantalla_actual++; // Pasamos de precharge a active por tanto cambiamos a la siguiente pantalla
         }
      }
      
      if(Pantalla_actual==1 && CarState==12) //Pasamos de precharge a active por tanto cambiamos pantalla a seleccion mode y driver
      {
         ScrollDrivingModes();
         blink_draws();

         if(CarState==15) // RTD, para pasar al siguiente if
            {
               EnableDrive=0; //Le digo a ETAS que deje de escuchar
               Pantalla_actual=3; // Pantalla de race screen
            } 
      }
      
      if(Pantalla_actual==3 && CarState==15)
      {
         LockOn= 0;
         if (flag==0)
         {
            output_high(BUZZER);
            normativeCounter++;
            if(normativeCounter==250)
            {
               normativeCounter=0;
               normativeCounter2++;
               if (normativeCounter2==5)
               {
                  normativeCounter2=0;
                  output_low(BUZZER); //Parem el buzzer
                  flag=1;
               }
            }
         }
         else if (flag==1)
         {
            visualitzar7seg(LVbatterySOC);
            selectNumberLEDs (percentatgeBrakeSensor);
            bargraphFunctionality();
            write_raceScreen(); // Muestra la velocidad
            write_VDCparameters(); // Muestra 2 parametros del VDC
         }
      }
   }
return 0;
}
