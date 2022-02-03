#int_ext //Interrupcion del puerto RB0
int_rb0()
{
   if ((CarState!=0) && (CarState!=21) && (idPantalla!=3)) //Estados donde no se puede abrir la pantalla de diagnosticos
   {
      if (variable_button_Diagnostics == 1) //Si se ha apretado el boton de diagnosticos
         {
            diagnosticsScreen();
         }
   }
}

