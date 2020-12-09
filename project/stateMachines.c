#include "buzzer.h"
#include "led.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "abCircle.h"
#include "shape.h"
#include "stateMachines.h"



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



void drawAang(u_int background, u_int arrow)
{
  //circle 
  Layer layer1 = {
    (AbShape *)&circle50,
    {(screenWidth/2), (screenHeight/2)
    },
    {0,0}, {0,0},
    COLOR_ORANGE,
    0
  };
  
  //change background and arrow color
  bgColor = background;
  layerDraw(&layer1); 
  drawArrow(arrow); 

}

void drawFlower(u_int color, int center, int y)
{
  //height of leaves 
  for(u_char r =0; r< 5; r++){
    //width of leaves
    for(u_char c = 0; c <4+ r; c++){
      drawPixel(center+c+5, r+40+y, COLOR_GREEN);
      drawPixel(center-c-5, r+40+y, COLOR_GREEN);
    }
  }

  //rose petals
   for(u_char r=0; r< 6; r++){
    //width of leaves
    for(u_char c = 0; c <=r; c++){    
      drawPixel(center+c-5, r+36+y,color);
      drawPixel(center-c+5, r+36+y,color); 
    }
  }
  //rose bud top 
  for (u_char r = 0; r < 6 ; r++) {
    for (u_char c = 0; c<=r; c++) {
      //right triangle
      drawPixel(center+c, r+35+y, color);
      //left triangle
      drawPixel(center-c, r+35+y, color);
    }
    }
}


void redbar(u_int color)
{
  int center = 50; 
  for(char c =0; c < 40; c++){
      drawPixel(center+c, 150, color);
      drawPixel(center+c, 151, color);
      drawPixel(center+c, 152, color);
      drawPixel(center+c, 153, color);
      drawPixel(center+c, 154, color); 

 }
}


void greenbar()
{
  static int load = 10;
  int center = 50; 
    for( char  c = 0; c < load  ;  c++){
      drawPixel(center+c, 150, COLOR_GREEN);
      drawPixel(center+c, 151, COLOR_GREEN);
      drawPixel(center+c, 152, COLOR_GREEN);
      drawPixel(center+c, 153, COLOR_GREEN);
      drawPixel(center+c, 154, COLOR_GREEN); 
   
  }
    if(load ==40){load =0; } 
    load+=10; 
}



void load()
{
  static int count = 0;
  static int state = 0; 
    count = 0;
    switch(state){
    case 0:
      redbar(COLOR_RED);
      state++;
      break;
    case 1:
      redbar(COLOR_RED);
      greenbar(); 
      state++; 
      break;
    case 2:
      redbar(COLOR_RED);
      greenbar();
      state++;
      break;
    case 3:
      redbar(COLOR_RED);
      greenbar();
      state++;
      break;
    case 4:
      // full green bar
      greenbar();
      state = 0; 
      break;
    }
}










void led_advance()
{
  static char state  =0;
  static char count  = 0;
  if(++count  != 250){
  switch(state){
  case 0:
    red_on = 1;
    led_changed = 1;
    led_update();
    break;
  case 1:
     dim25();
    break;
  case 2:
     red_on = 0;
     led_changed = 1;
     led_update(); 
    break; 
  case 3:
     dim50(); 
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


