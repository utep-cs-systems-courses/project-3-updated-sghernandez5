#include "buzzer.h"
#include "stateMachines.h"
#include "led.h"





void dim25() {
  static char dimState = 0; 
  switch(dimState) {

  case 0: red_on = 1; dimState =1; break;

  case 1: red_on = 0; dimState =2; break;

  case 2: red_on = 0; dimState =3; break; 

  case 3: red_on = 0; dimState =0; break;

  }
  led_changed = 1; 
  led_update();
}



void dim50() {
  static char dimState =0; 
  switch(dimState) {

  case 0: red_on = 1; dimState =1; break; 

  case 1: red_on = 1; dimState =2; break;

  case 2: red_on = 0; dimState =3;break; 

  case 3: red_on = 0; dimState =0;  break;
  }
  led_changed = 1; 
  led_update();

}


/*
void dim75()
{
  static char dimState =0; 
  switch(dimState) {

  case 0: red_on = 0; dimState=1; break;

  case 1: red_on  =1; dimState=2; break; 

  case 2: red_on = 1; dimState=3; break; 

  case 3: red_on = 1; dimState=0; break;

  }
  led_changed = 1; 
  led_update();
}
*/


void led_advance()
{
  static char state  =0;
  static char count  = 0;
  if(++count  != 250){
  switch(state){
  case 0:
    // red_on = 1;
    // led_changed = 1;
    // led_update();
    break;
  case 1:
    // dim25();
    break;
  case 2:
    // red_on = 0;
    // led_changed = 1;
    // led_update(); 
    break; 
  case 3:
    // dim50(); 
    break;
  case 4:
    dim75();
    break; 
  }
  }
  else{
    if(state ==4){
      state =0;
      count = 0; 
    }
    else{
    state++; 
    }
  }
}

void buzz_advance()
{
  static char note = 0;
  static char blink_count = 0;
  static char rep = 0; 
  if(++blink_count ==250){
    switch(note){
    case 0:
      //D5
      buzzer_set_period(587);
      note++;
      break;
    case 1:
      //F#5
      buzzer_set_period(740);
      note++;
      break;
    case 2:
      //C#6
      buzzer_set_period(1109);
      note++;
      break;
    case 3:
      //Pause
      buzzer_set_period(0);
      note++;
      break;
    case 4:
      //E5
      buzzer_set_period(659);
      note++;
      break;
    case 5:
      //G5
      buzzer_set_period(784);
      note++;
      break;
    case 6:
      //D6
      buzzer_set_period(1175);
      note++;
      break;
    case 7:
      //pause
      buzzer_set_period(0);
      note++;
      break;
    case 8:
      //f#5
      buzzer_set_period(740);
      note++;
      break;
    case 9:
      // A5
      buzzer_set_period(880);
      note++;
      break;
    case 10:
      //E6
      buzzer_set_period(1319);
      note++;
      break;
    case 11:
      //pause
      buzzer_set_period(0);
      note++;
      break;
    case 12:
      //F#6
      buzzer_set_period(1480);
      note++;
      break;
    case 13:
      //pause
      buzzer_set_period(0);
      note++;
      break;
      //repeat 4 times
    case 14:
      //  D6
      buzzer_set_period(1175);
      rep++; 
      note++; 
      break;
    case 15:
      //c#6
      buzzer_set_period(1109);
      note++;
      break;
    case 16:
      //A5
      buzzer_set_period(880);
      note++;
      break;
    case 17:
      //F#5
      buzzer_set_period(740);
      if(rep ==3){
	note = 18; 
      }
      else{
	note = 14; 
      }
      break; 
    case 18:
      //G5
      buzzer_set_period(784);
      note++;
      break;
    case 19:
      //F#5
      buzzer_set_period(740);
      note++;
      break;
    case 20:
      //D5
      buzzer_set_period(587);
      note++;
      break;
    case 21:
      //B4
      buzzer_set_period(494);
      note++;
      break;
    case 22:
      //G5
      buzzer_set_period(784);
      note++;
      break;
    case 23:
      //F#5
      buzzer_set_period(740);
      note++;
      break;
    case 24:
      //D5 and F#5
      buzzer_set_period(587);
      buzzer_set_period(740);
      note++;
      break;
    case 25:
      // B4
      buzzer_set_period(494);
      note++;
      break;
    case 26:
      //G5
      buzzer_set_period(784);
      note++;
      break;
    case 27:
      //F#5
      buzzer_set_period(740);
      note++;
      break;
    case 28:
      //D5
      buzzer_set_period(587);
      note++;
      break;
    case 29:
      // B4
      buzzer_set_period(494);
      note++;
      break;
    case 30:
      //G5
      buzzer_set_period(784);
      note++;
      break;
    case 31:
      //F#5
      buzzer_set_period(740);
      note++;
      break;
    case 32:
      // D5 and F#5
      buzzer_set_period(587);
      buzzer_set_period(740); 
      note++;
      break;
    case 33:
      // D5
      buzzer_set_period(587);
      note++;
      break;
    case 34:
      //B4
      buzzer_set_period(494);
      note++;
      break;
    default:
      //set note to 0 and rep
      note = 0;
      rep = 0;
      break;
    }
    blink_count = 0; 
  }
}


