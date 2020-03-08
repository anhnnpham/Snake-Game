
#include "Adafruit_SSD1306/Adafruit_SSD1306.h"

#define OLED_DC     A1
#define OLED_CS     A2
#define OLED_RESET  A0


struct snake
{
     int x;
     int y;
};

struct snake s[30];
struct snake food;

int length = 2;
int dx = 1;
int dy = 0;

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
void game();
void menu();
void endgame();
void highscore();

void setup()   {   
    
    pinMode(D5,  INPUT_PULLDOWN);
    pinMode(D6,  INPUT_PULLDOWN);
    pinMode(D7,  INPUT_PULLDOWN);
    pinMode(D3,  INPUT_PULLDOWN);
    
    attachInterrupt(D6,moveleft , RISING,4);
    attachInterrupt(D7,moveright, RISING,3);
    attachInterrupt(D3,moveup   , RISING,1);
    attachInterrupt(D5,movedown , RISING,2);

    
    display.setTextColor(WHITE);
    display.setTextSize(1);
    
    display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
  
    s[0].x = 5; s[0].y = 5;
    s[1].x = 6; s[1].y = 5;
    s[2].x = 7; s[2].y = 5;
    food.x = rand()%32;
    food.y = rand()%16;

}


void loop() {
    
    if(state == 1)
        menu();
    else if(state == 2)
        game();

  


    delay(500);

}

void menu(){

  display.setCursor(0,0);
  display.println("Hello, world!");
  if( && select == 1 )
    
}


void game(){
    display.fillRect(food.x*4,food.y*4,4,4,true);
    for(int i=length;i>0;i--){
        s[i].x = s[i-1].x;
        s[i].y = s[i-1].y;
        display.fillRect(s[i].x*4, s[i].y*4, 4, 4,true);
    }
    s[0].x += dx;
    s[0].y += dy;

    if(s[0].x == -1 ) 
        s[0].x = 31;
    else if(s[0].x == 32) 
        s[0].x = 0;
        
    if(s[0].y == -1) 
        s[0].y = 15;
    else if(s[0].y == 16) 
        s[0].y = 0;
    if( (s[0].x != food.x) || (s[0].y != food.y) ){
        display.fillRect(s[length].x*4, s[length].y*4, 4, 4,false);
    }
    else{
        length++;
        food.x = rand()%32;
        food.y = rand()%16;
    }
    
    display.fillRect(s[0].x*4, s[0].y*4, 4, 4,true);
    display.display();
}

void moveright()
{
  if(dx == 0) 
    dx = 1;
    dy = 0;
}

void moveleft()
{
  if(dx == 0) 
    dx = -1;
    dy = 0;
}

void moveup()
{
  if(dy == 0) 
    dy = -1;
    dx = 0;


}

void movedown()
{
  if(dy == 0) 
    dy = 1;
    dx = 0;
}













