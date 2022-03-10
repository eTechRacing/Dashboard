#ifndef RACESCREEN_H
#define RACESCREEN_H

void write_VDCparameters(void);
void writeUnitats (unsigned int8 numero);
void writeDesenes (unsigned int8 numero);
void writeCentenes (unsigned int8 numero);
void writeXparameterValue (unsigned int16 parameter);
void drawBars (unsigned int8 numero);
void drawXparameter (unsigned int16 parameters, unsigned int16 maxValue);
void write_raceScreen (void);
#endif

