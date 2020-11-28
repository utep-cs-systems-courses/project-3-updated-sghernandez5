#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
//u_int fontFgColor = COLOR_GREEN;


/*
void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount == 250) {     
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
}
*/


void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_AQUAMARINE);
  //avatar aang orange circle and blue arrow 



  
  while (1) {			/* forever */
    if (redrawScreen) {
        // display circle and arrow
      switch(buttonPressed){
      case 1:
	// advance LEDS
	led_advance();
	break; 
      case 2:
	//music
	buzz_advance();
	break;
      case 3:
	// Turn arrow white
	// display strings
	

	break; 

      case 4:
	buzzer_set_period(0);
	red_on =0;
	led_changed = 1;
	led_update();
	break;

      }
      //reset to 0 
      redrawScreen =0; 
    }



    
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

