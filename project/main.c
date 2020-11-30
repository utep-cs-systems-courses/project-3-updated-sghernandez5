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

static char buttonPressed =0; 
short redrawScreen = 1;
u_int bgColor = COLOR_AQUAMARINE;

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


void wdt_c_handler()
{
     u_int count = 0; 
     u_int check = p2sw_read();
     if(check & 256){
        led_advance(); 
        buttonPressed = 1; 
      }
     else if(check & 512){
       //song
       bgColor = COLOR_PINK;
       buttonPressed = 2;
     }
     else if(check & 1024){
       bgColor = COLOR_BLACK; 
       layerDraw(&layer1);
       drawArrow(COLOR_WHITE);
       buttonPressed = 3;
       drawString8x12(5,10,"Avatar State",COLOR_WHITE, COLOR_BLACK);
       
     }
     else if(check & 2048){
        buttonPressed = 4; 
     }
    
     static int secCount = 0;
     
     // check what button is pressed every 1/250 
     if(++secCount!= 250){
      
       switch(buttonPressed){
       case(1):
	 
	 redrawScreen = 1;
	 break;
       case(2):
	 redrawScreen = 1; 
	 buzz_advance(); 
	 break;
       case(3):
	 redrawScreen = 1;
	 break;
       case(4):
	 // buzzer is off and the red led is off
	 red_on =0;
	 led_update(); 
	 buzzer_set_period(0);
	 break;
       }
     }
     else{
       secCount = 0;
       redrawScreen =1;
     }

}


void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  led_init(); 
  lcd_init();
  buzzer_init(); 
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  //default background image aangs face 
  layerDraw(&layer1);
  drawArrow(COLOR_LIGHT_BLUE); 
  while (1) {			/* forever */
    if (redrawScreen) {      
      redrawScreen =0;
    }
  }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
}
