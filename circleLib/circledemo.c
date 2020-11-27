#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "abCircle.h"

AbRect rect10 = {abRectGetBounds, abRectCheck, {10,10}};; /**< 10x10 rectangle */

u_int bgColor = COLOR_BLACK;

void drawArrow()
{
 

  
  int center = 64;
  //rectangle
  fillRectangle(55,30,20,25,COLOR_LIGHT_BLUE);


  //upside down triangle 
  for (u_char c = 0; c < 20; c++) {
    for (u_char r = 0; r <= 20-c; r++) {
      drawPixel(center+c, r+50, COLOR_LIGHT_BLUE);
      drawPixel(center-c, r+50, COLOR_LIGHT_BLUE); 
    }
  } 
}

Layer layer1 = {		/**< Layer with a red square */
  (AbShape *)&rect10,
  {screenWidth/2, screenHeight/2-45}, /**< center */
  {0,0}, {0,0},				    /* next & last pos */
  COLOR_BLUE,
  0
};

Layer layer0 = {		/**< Layer with an orange circle */
  (AbShape *)&circle50,
  {(screenWidth/2), (screenHeight/2)}, /**< bit below & right of center */
  {0,0}, {0,0},				    /* next & last pos */
  COLOR_ORANGE,
  0,
};



Layer layer2 = {		/**< Layer with a red square */
  (AbShape *)&rect10,
  {screenWidth/2, screenHeight/2-45}, /**< center */
  {0,0}, {0,0},				    /* next & last pos */
  COLOR_BLUE,
  &layer0
};



int
main()
{
  configureClocks();
  lcd_init();

  // clearScreen(COLOR_BLACK);
  // drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  layerDraw(&layer0);
  drawArrow(); 

}
