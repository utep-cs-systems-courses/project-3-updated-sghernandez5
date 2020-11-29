#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include <libTimer.h>

#include "lcdutils.h"
#include "lcddraw.h"

#include "p2switches.h"
#include "abCircle.h"
#include "shape.h"
#include "stateMachines.h"



#define LED_GREEN BIT6             // P1.6

u_int bgColor = COLOR_BLUE; 

short redrawScreen = 1;
u_int fontFgColor = COLOR_WHITE;

void wdt_c_handler()

{
  static int secCount = 0;
  secCount++;
   if (secCount == 250) {		/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
  
}
Layer layer1 = {
  (AbShape *)&circle50,
  {(screenWidth/2), (screenHeight/2)
  },
  {0,0}, {0,0},
  COLOR_ORANGE,
  0
};




void drawArrow(u_int color)
{  
  int center = 64;
  //rectangle
  fillRectangle(55,30,20,25,color);
  //upside down triangle
  for (u_char c = 0; c < 20; c++) {
    for (u_char r = 0; r <= 20-c; r++) {
      //right triangle
      drawPixel(center+c, r+50, color);
      //left triangle
      drawPixel(center-c, r+50, color); 
    }
  } 
}



void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init(); 
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_AQUAMARINE);
  //background image aangs face 
  layerDraw(&layer1);
  drawArrow(COLOR_LIGHT_BLUE); 
  while (1) {			/* forever */
    if (redrawScreen) {      
      redrawScreen =0;
      u_int switches = p2sw_read(); 
      /*
      switch(buttonPressed){
	case 1:
	  //turn on dim red
	  led_advance();
	  break;
	case 2:
	  //turn on music
	  buzz_advance();
	  break; 
	case 3:
	  //change LCD and add string 
	  transition_advance();
	  break;
	case 4:
	  //turn off both leds and buzzer
	  buzzer_set_period(0);
	  red_on = 0;
	  green_on = 0;
	  led_changed = 1;
	  led_update();
	  break; 
      }
      */
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
