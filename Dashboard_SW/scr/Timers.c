#int_TIMER2
void TIMER_isr(void)
{
   if (counter<120)
   {
      counter++;
   }
   else
   {
      counter=0;
      toggle_envoltori=1;
   }
   
   if(enableSteeringCounter==1)
   {
      counterBothSteeringButtons++;
      if(counterBothSteeringButtons==255)
      {
         counterBothSteeringButtons=0;
         bothSteeringButtons=0;        
      }
   }
   contadorTimer++;
   if(contadorTimer==255) //Para que los puntos de la pantalla de precharge se muevan mas lentos
   {
      prescalerTimer++;
      if (prescalerTimer==4)
      {
         prescalerTimer=0;
      }
   }
   
   if (normativeEnable==1)
   {
      normativeCounter++;
      if(normativeCounter==250)
      {
         normativeCounter=0;
         normativeCounter2++;
         if (normativeCounter2==5)
         {
            normativeCounter2=0;
            output_low(BUZZER); //Parem el buzzer
            //PARAMOS LOS LEDS, ESTOS SE PONEN EN ALTO EN LA INICIALIZACION
            output_low(LED_AMS);
            output_low(LED_IMD);
            normativeEnable=0;
         }
      }
   }
}
