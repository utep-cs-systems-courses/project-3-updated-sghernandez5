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

//static char buttonPressed =0; 
short redrawScreen = 1;
static char buttonPressed =0;
static int yDeep =0;
static int yPurple =-30; 
static int yYellow =-35;
static int yRed = -60;
static int yOrangeRed = -55;
static int yGoldenRod = -65; 

u_int bgColor; 



void wdt_c_handler()
{
     u_int check = p2sw_read();
     static int secCount = 0;
     static int count = 0; 
     secCount++;
     count++; 
     //check what button is pressed every instance and have buttonPressed set 
     if((check & 1)==0){ 
        buttonPressed = 1;
      }
     if((check & 2)==0){
       buttonPressed = 2;
     }
    if((check & 4) == 0){
       buttonPressed = 3; 
     }
    if((check & 8) == 0){
        buttonPressed = 4;
     }
    //based on buttonPressed it will hold and follow within the main method 
     switch (buttonPressed){
     case 1:
       redrawScreen =1; 
       break;
     case 2:
       redrawScreen =1;
       break;
     case 3:
       if(count == 275){
	 redrawScreen =1;
       }
       break;
     case 4:
       if(secCount == 250){
       redrawScreen =1;
       }
       break; 
     }

     //reset secCount
      if(secCount == 250){
       secCount =0; 
     }
      if (count == 275){
	count = 0; 
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
  drawAang(COLOR_PINK,COLOR_LIGHT_BLUE); 
  bgColor = COLOR_PINK;
  while (1) {/* forever */ 
    if (redrawScreen) {      
      redrawScreen =0;
      switch(buttonPressed){
       case(1):
	 led_advance();
	 break;
	 
       case(2):
	 //start song 
	 buzz_advance(); 
	 break;
	 
       case(3):
	 //clearscreen w/in the method make sure the flowers dont copy and paste but imitate falling
	 drawAang(COLOR_PINK,COLOR_LIGHT_BLUE); 
	 drawString8x12(5,10,"Avatar Aang",COLOR_PURPLE, COLOR_PINK);

	 drawFlower(COLOR_DEEP, 15, yDeep);
	 drawFlower(COLOR_PURPLE,70, yPurple);
	 drawFlower(COLOR_YELLOW,110,yYellow);
	 drawFlower(COLOR_RED,35,yRed);
	 drawFlower(COLOR_ORANGE_RED,55, yOrangeRed);
	 drawFlower(COLOR_GOLDENROD,85,yGoldenRod); 

	 
	 //imitate falling flowers
	 yDeep+=10;
	 yPurple+=10;
	 yYellow+=10;
	 yRed+=10;
	 yOrangeRed+=10;
	 yGoldenRod+=10; 
	 // reset flower position to in screen to start at the top in order 
	 if(yDeep > 160){yDeep = 0;}
	 if(yPurple > 160){yPurple = -30;}
	 if(yYellow > 160){yYellow = -35; }
	 if(yRed >160){ yRed =-60; }
	 if(yOrangeRed >160){yOrangeRed = -55; }
	 if(yGoldenRod >160){yGoldenRod = -65; }
	 
	 break;
	 
       case(4):
	 // buzzer is off and the red led is off
 
	 buzzer_set_period(0);
	 drawString11x16(0,10,"RED LED OFF",COLOR_RED, COLOR_PINK);
	 drawString11x16(0,30,"BUZZER OFF",COLOR_RED, COLOR_PINK);

	 
	 






	 
	 red_on =0;
	 led_update();
	 break; 
      } 
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;         /* green on */
  }
}
