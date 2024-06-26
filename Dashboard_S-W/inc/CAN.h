#ifndef CAN_H
#define CAN_H

#define CAN_USE_EXTENDED_ID FALSE
#include <can-18xxx8.C> 

void canConfiguration (void);
void send_PrechargeOrder(void);
void send_Dash_LockOn (void);

#endif

