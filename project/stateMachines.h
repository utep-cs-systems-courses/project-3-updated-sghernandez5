#ifndef stateMachine_included
#define stateMachine_included 

u_int color;
u_int background;
u_int arrow; 


void buzz_advance();

void led_advance();

void dim25();
void dim50();
void dim75();

void transition_advance(); 

 
void drawArrow( u_int color);

void drawAang( u_int background, u_int arrow);

void drawFlower( u_int color, int center);

#endif // included
