#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <abCircle.h>
#include "stateMachines.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_WHITE;

void wdt_c_handler()

{
  buzz_advance(); 
  static int secCount = 0;
  secCount ++;
  if (secCount == 250) {/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
}



void drawArrow()
{  
  int center = 64;
  //rectangle
  fillRectangle(55,30,20,25,COLOR_LIGHT_BLUE);
  //upside down triangle
  for (u_char c = 0; c < 20; c++) {
    for (u_char r = 0; r <= 20-c; r++) {
      //right triangle
      drawPixel(center+c, r+50, COLOR_LIGHT_BLUE);
      //left triangle
      drawPixel(center-c, r+50, COLOR_LIGHT_BLUE); 
    }
  } 
}


/*
Layer layer0 = {	     
  (AbShape *)&circle50,
  {(screenWidth/2), (screenHeight/2)}, 
  {0,0}, {0,0},	 
  COLOR_ORANGE,
  0,
};
*/

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init(); 
  //p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_AQUAMARINE);
  // buzz_advance();    

  
  while (1) {			/* forever */
    if (redrawScreen) {      
      redrawScreen =0;
      drawArrow(); 
      //  layerDraw(&layer0); 
    }
    
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

