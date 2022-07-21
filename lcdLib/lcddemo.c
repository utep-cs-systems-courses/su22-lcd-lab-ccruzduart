/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);

  //drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_BLACK);

  //fillRectangle(30,30, 60, 60, COLOR_WHITE);

  /* int col = 20, row = 50;
  int step = 1;
  for(int i = 0; i < 25; i++){
    drawPixel(col,row, COLOR_WHITE);
    col += 2;
    row += step;
    if (row >= height) {
      row -= step;
      step = -step;
    }
    step += 1;
  }*/

  int col = 20, row = 80, step = 1;
  
  for(int i = 0; i <= 25; i++) {
    drawPixel(col+i, row+i, COLOR_WHITE);
    drawPixel(col+i, row-i, COLOR_WHITE);
    drawPixel(70-i, row+i, COLOR_WHITE);
    drawPixel(70-i, row-i, COLOR_WHITE);
  }
}
