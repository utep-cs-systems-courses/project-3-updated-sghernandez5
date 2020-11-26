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

  clearScreen(COLOR_BLUE);

  drawString8x12(15,15, "hello", COLOR_GREEN, COLOR_RED);

  // fillRectangle(50,50, 80, 80, COLOR_ORANGE);
  drawString11x16(30,30, "yes", COLOR_GREEN, COLOR_RED);
}
