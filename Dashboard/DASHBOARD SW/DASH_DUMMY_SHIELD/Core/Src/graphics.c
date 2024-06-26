/*
 * graphics.c
 *
 *  Created on: Apr 13, 2024
 *      Author: usuari
 */

#include <glcd_etr.h>
#include "graphics.h"
#include <stdint.h>
#include <stdlib.h>
#include "main.h"


uint16_t barNumber;
uint16_t centenesXparameter;
uint16_t residuXparameter;
uint16_t desenesXparameter;
uint16_t unitatsXparameter;




bounding_box_t draw_text(char *string, unsigned char x, unsigned char y, unsigned char *font, unsigned char spacing) {
   bounding_box_t ret;
   bounding_box_t tmp;

   ret.x1 = x;
   ret.y1 = y;

   spacing += 1;

   // BUG: As we move right between chars we don't actually wipe the space
   while (*string != 0) {
      tmp = draw_char(*string++, x, y, font);

      // Leave a single space between characters
      x = tmp.x2 + spacing;
   }

   ret.x2 = tmp.x2;
   ret.y2 = tmp.y2;

   return ret;
}

bounding_box_t draw_char(unsigned char c, unsigned char x, unsigned char y, unsigned char *font) {
   uint16_t pos;
   unsigned char width;
   bounding_box_t ret;

   ret.x1 = x;
   ret.y1 = y;
   ret.x2 = x;
   ret.y2 = y;

   // Read first byte, should be 0x01 for proportional
   if (font[FONT_HEADER_TYPE] != FONT_TYPE_PROPORTIONAL) return ret;

   // Check second byte, should be 0x02 for "vertical ceiling"
   if (font[FONT_HEADER_ORIENTATION] != FONT_ORIENTATION_VERTICAL_CEILING) return ret;

   // Check that font start + number of bitmaps contains c
   if (!(c >= font[FONT_HEADER_START] && c <= font[FONT_HEADER_START] + font[FONT_HEADER_LETTERS])) return ret;

   // Adjust for start position of font vs. the char passed
   c -= font[FONT_HEADER_START];

   // Work out where in the array the character is
   pos = font[c * FONT_HEADER_START + 5];
   pos <<= 8;
   pos |= font[c * FONT_HEADER_START + 6];

   // Read first byte from this position, this gives letter width
   width = font[pos];

   // Draw left to right
   unsigned char i;
   for (i = 0; i < width; i++) {
      unsigned char j;
      // Draw top to bottom
      for (j = 0; j < font[FONT_HEADER_HEIGHT]; j++) {
         // Increment one data byte every 8 bits, or
         // at the start of a new column  HiTech optimizes
         // the modulo, so no need to try and avoid it.
         if (j % 8 == 0) pos++;

         if (font[pos] & 1 << (j % 8)) {
            glcd_pixel(x + i, y + j, 1);
         } else {
            glcd_pixel(x + i, y + j, 0);
         }
      }
   }

   ret.x2 = ret.x1 + width - 1;
   // TODO: Return the actual height drawn, rather than the height of the
   //       font.
   //ret.y2 = ret.y1 + height;
   ret.y2 = ret.y1 + font[FONT_HEADER_HEIGHT];

   return ret;
}

unsigned char text_height(unsigned char *string, unsigned char *font) {
   // TODO: Possibly work out the actual pixel height.  Letters with
   //       descenders (like 'g') are taller than letters without (like 'k')

   // Height is stored in the header
   return font[FONT_HEADER_HEIGHT];
}

unsigned char text_width(unsigned char *string, unsigned char *font, unsigned char spacing) {
   unsigned char width = 0;
   uint16_t pos;
   unsigned char c;

   // TODO: Implement for fixed width fonts

   // Check font type, should be 0x01 for proportional
   if (font[FONT_HEADER_TYPE] != FONT_TYPE_PROPORTIONAL) return 0;

   while (*string != 0) {
      c = *string++;

      // Check that font start + number of bitmaps contains c
      // TODO: Should we continue here but add 0 to width?
      if (!(c >= font[FONT_HEADER_START] && c <= font[FONT_HEADER_START] + font[FONT_HEADER_LETTERS])) return 0;

      // Adjust for start position of font vs. the char passed
      c -= font[FONT_HEADER_START];

      // Work out where in the array the character is
      pos = font[c * FONT_HEADER_START + 5];
      pos <<= 8;
      pos |= font[c * FONT_HEADER_START + 6];

      // Read first byte from this position, this gives letter width
      width += font[pos];

      // Allow for space between letters
      width += spacing;
   }

   // The last letter wont have a space after it
   return width - spacing;
}

void draw_rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, char colour)
{
   // Top
   draw_line(x1, y1, x2, y1, colour);
   // Left
   draw_line(x1, y1, x1, y2, colour);
   // Bottom
   draw_line(x1, y2, x2, y2, colour);
   // Right
   draw_line(x2, y1, x2, y2, colour);
}

void blank_rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, char colour)
{
   while ((x2-x1)!=0)
   {
      draw_line(x1, y1, x1, y2, colour);
      x1+=1;
   }

}

// A rounded box
void draw_box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, char colour)
{
   // Top
   draw_line(x1 + 1, y1, x2 - 1, y1, colour);
   // Left
   draw_line(x1, y1 + 1, x1, y2 - 1, colour);
   // Bottom
   draw_line(x1 + 1, y2, x2 - 1, y2, colour);
   // Right
   draw_line(x2, y1 + 1, x2, y2 - 1, colour);
}

// Implementation of Bresenham's line algorithm
//
// This code credit Tom Ootjers, originally obtained from:
// http://tinyurl.com/czok7vx

void draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, char colour)
{
   int16_t xinc1, yinc1, den, num, numadd, numpixels, curpixel, xinc2, yinc2;

   int16_t deltax = abs(x2 - x1);       // The difference between the x's
   int16_t deltay = abs(y2 - y1);       // The difference between the y's
   int16_t x = x1;                      // Start x off at the first pixel
   int16_t y = y1;                      // Start y off at the first pixel

   if (x2 >= x1) {                // The x-values are increasing
     xinc1 = 1;
     xinc2 = 1;

    } else {                         // The x-values are decreasing
     xinc1 = -1;
     xinc2 = -1;
   }

   if (y2 >= y1)                   // The y-values are increasing
   {
     yinc1 = 1;
     yinc2 = 1;
   }
   else                            // The y-values are decreasing
   {
     yinc1 = -1;
     yinc2 = -1;
   }

   if (deltax >= deltay)           // There is at least one x-value for every y-value
   {
     xinc1 = 0;                    // Don't change the x when numerator >= denominator
     yinc2 = 0;                    // Don't change the y for every iteration
     den = deltax;
     num = deltax / 2;
     numadd = deltay;
     numpixels = deltax;           // There are more x-values than y-values
   }
   else                            // There is at least one y-value for every x-value
   {
     xinc2 = 0;                    // Don't change the x for every iteration
     yinc1 = 0;                    // Don't change the y when numerator >= denominator
     den = deltay;
     num = deltay / 2;
     numadd = deltax;
     numpixels = deltay;           // There are more y-values than x-values
   }

   for (curpixel = 0; curpixel <= numpixels; curpixel++)
   {
     glcd_pixel(x, y, colour);     // Draw the current pixel
     num += numadd;                // Increase the numerator by the top of the fraction
     if (num >= den)               // Check if numerator >= denominator
     {
      num -= den;                 // Calculate the new numerator value
      x += xinc1;                 // Change the x as appropriate
      y += yinc1;                 // Change the y as appropriate
     }
     x += xinc2;                   // Change the x as appropriate
     y += yinc2;                   // Change the y as appropriate
   }
}


// Implementation of Bresenham's circle algorithm
void draw_circle(unsigned char centre_x, unsigned char centre_y, unsigned char radius, unsigned char colour)
{
   signed char x = 0;
   signed char y = radius;
   signed char p = 1 - radius;

   if (!radius) return;

   for (x = 0; x < y; x++) {
      if (p < 0) {
         p += x * 2 + 3;
      } else {
         p += x * 2 - y * 2 + 5;
         y--;
      }

//      glcd_pixel(centre_x - x, centre_y - y, colour);
//      glcd_pixel(centre_x - y, centre_y - x, colour);
//      glcd_pixel(centre_x + y, centre_y - x, colour);
//      glcd_pixel(centre_x + x, centre_y - y, colour);
//      glcd_pixel(centre_x - x, centre_y + y, colour);
//      glcd_pixel(centre_x - y, centre_y + x, colour);
//      glcd_pixel(centre_x + y, centre_y + x, colour);
//      glcd_pixel(centre_x + x, centre_y + y, colour);
   }
}

// Implementation of Bresenham's circle algorithm, filled.
void draw_filled_circle(unsigned char centre_x, unsigned char centre_y, unsigned char radius, unsigned char colour)
{
   signed char x = 0;
   signed char y = radius;
   signed char p = 1 - radius;

   if (!radius) return;

   for (x = 0; x < y; x++) {
      if (p < 0) {
         p += x * 2 + 3;
      } else {
         p += x * 2 - y * 2 + 5;
         y--;
      }

      draw_line(centre_x - x, centre_y - y, centre_x + x, centre_y - y, colour);
      draw_line(centre_x - y, centre_y - x, centre_x + y, centre_y - x, colour);
      draw_line(centre_x + x, centre_y + y, centre_x - x, centre_y + y, colour);
      draw_line(centre_x + y, centre_y + x, centre_x - y, centre_y + x, colour);
   }
}

	// Draws the logo "ETR"
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

}
void drawXparameter (uint16_t parameters_1, uint16_t maxValue)
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

}

void drawBars (uint8_t numero)
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

void writeXparameterValue (uint16_t parameters)
{
   blank_rectangle(2, 13, 74, 47, 0); //Borrem els n?meros de unitats, desenes i centenes
   centenesXparameter=parameters/100; //Calculem els valors de unitats, desenes i centenes
   residuXparameter=parameters%100;
   desenesXparameter=residuXparameter/10;
   unitatsXparameter=residuXparameter%10;
   writeCentenes(centenesXparameter); //Escribim els n?meros de unitats, desenes i centenes
   writeDesenes(desenesXparameter);
   writeUnitats(unitatsXparameter);
}

void writeCentenes (uint8_t numero)
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

void writeDesenes (uint8_t numero)
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

void writeUnitats (uint8_t numero)
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
void scrollDrawing(uint8_t competicion_seleccionada,uint8_t *font)
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
      	   case(0):
		   blank_rectangle(1,1,130,64,0);
      	   break;
      	   case 1:
			 //blank_rectangle(26, 22, 103, 42, 0);
			 //blank_rectangle(26, 54, 103, 74, 0);
			 //blank_rectangle(26, 1, 103, 11, 0);
			 //blank_rectangle(1, 27, 22, 37, 0);
			 //blank_rectangle(108, 27, 130, 37, 0);
			 ////////////////////////////////////////
			 draw_text("rtd", 114, 27, font, 1);//DERECHA DEL MODO QUE ESTAMOS SELECCIONANDO
			 draw_text("rtd", 3, 27, font, 1);//IZQUIERDA DEL MODO QUE ESTAMOS SELECCIONANDO
			 draw_text("ENDURANCE",36,1,font,1);
			 draw_text("WORKSHOP",38,27,font,1);//ESTE ES EL MODO QUE ESTAMOS SELECCIONANDO
             draw_text("SKIDPAD",43,54,font,1);
			 break;
            case 2:
               blank_rectangle(26, 22, 103, 42, 0);
               blank_rectangle(26, 54, 103, 74, 0);
               blank_rectangle(26, 1, 103, 11, 0);
               ////////////////////////////////////////
               draw_text("rtd", 114, 27, font, 1);//DERECHA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("rtd", 3, 27, font, 1);//IZQUIERDA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("WORKSHOP",38,1,font,1);
               draw_text("SKIDPAD",43,27,font,1);
               draw_text("ACCELERATION",27,54,font,1);
               break;
            case 3:
               blank_rectangle(26, 22, 103, 42, 0);
               blank_rectangle(26, 54, 103, 74, 0);
               blank_rectangle(26, 1, 103, 11, 0);
               ///////////////////////////////////////
               draw_text("rtd", 114, 27, font, 1);//DERECHA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("rtd", 3, 27, font, 1);//IZQUIERDA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("SKIDPAD",43,1,font,1);
               draw_text("ACCELERATION",27,27,font,1);
               draw_text("AUTOCROSS",35,54,font,1);
               break;
            case 4:
               blank_rectangle(26, 22, 103, 42, 0);
               blank_rectangle(26, 54, 103, 74, 0);
               blank_rectangle(26, 1, 103, 11, 0);
               ///////////////////////////////////////
               draw_text("rtd", 114, 27, font, 1);//DERECHA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("rtd", 3, 27, font, 1);//IZQUIERDA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("ACCELERATION",27,1,font,1);
               draw_text("AUTOCROSS",35,27,font,1);
               draw_text("ENDURANCE",36,54,font,1);
            break;
            case 5:
               blank_rectangle(26, 22, 103, 42, 0);
               blank_rectangle(26, 54, 103, 74, 0);
               blank_rectangle(26, 1, 103, 11, 0);
               ////////////////////////////////////////
               draw_text("rtd", 114, 27, font, 1);//DERECHA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("rtd", 3, 27, font, 1);//IZQUIERDA DEL MODO QUE ESTAMOS SELECCIONANDO
               draw_text("AUTOCROSS",35,1,font,1);
               draw_text("ENDURANCE",36,27,font,1);
               draw_text("WORKSHOP",38,54,font,1);
            break;

         }
   }
