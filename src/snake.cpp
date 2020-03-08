/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/anhnnpham/aproject/snake/src/snake.ino"
#include "Adafruit_SSD1306/Adafruit_SSD1306.h"

// SDA = MOSI
void setup();
void loop();
void moveRight();
void moveLeft();
void moveUp();
void moveDown();
#line 4 "/home/anhnnpham/aproject/snake/src/snake.ino"
#define OLED_DC A1 // SA0 = MISO
#define OLED_CS A2
#define OLED_RESET A0
struct snake
{
    int x;
    int y;
};

struct snake snake_obj[30];
struct snake food;

int length = 2;
int dx = 1;
int dy = 0;

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

void game();
void menu();
void endgame();
void highscore();

void setup()
{
    pinMode(D3, INPUT_PULLDOWN);
    pinMode(D5, INPUT_PULLDOWN);
    pinMode(D6, INPUT_PULLDOWN);
    pinMode(D7, INPUT_PULLDOWN);

    attachInterrupt(D3, moveUp, RISING, 1);
    attachInterrupt(D5, moveDown, RISING, 2);
    attachInterrupt(D6, moveLeft, RISING, 4);
    attachInterrupt(D7, moveRight, RISING, 3);

    display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
    
    display.setTextSize(1);
    display.setTextColor(WHITE);

    // display.setCursor(0, 0);
    // display.println("Hello, world!");
    // display.setTextColor(BLACK, WHITE); // 'inverted' text
    // display.println(3.141592);
    // display.setTextSize(2);
    // display.setTextColor(WHITE);
    // display.print("0x");
    // display.println(0xDEADBEEF, HEX);
    // display.display();
    // delay(2000);
    // display.clearDisplay();

    // // draw the first ~12 characters in the font
    // testdrawchar();
    // display.display();
    // delay(2000);
    // display.clearDisplay();

    // // draw scrolling text
    // testscrolltext();
    // delay(2000);
    // display.clearDisplay();

    snake_obj[0].x = 5;
    snake_obj[0].y = 5;
    snake_obj[1].x = 6;
    snake_obj[1].y = 5;
    snake_obj[2].x = 7;
    snake_obj[2].y = 5;

    // srand(time(0));
    food.x = rand() % 32; // width
    food.y = rand() % 16; // height
}

void loop()
{
    //     if(state == 1)
    //     menu();
    // else if(state == 2)
    //     game();

    display.fillRect(food.x * 4, food.y * 4, 4, 4, true);
    for (int i = length; i > 0; i--)
    {
        snake_obj[i].x = snake_obj[i - 1].x;
        snake_obj[i].y = snake_obj[i - 1].y;
        display.fillRect(snake_obj[i].x * 4, snake_obj[i].y * 4, 4, 4, true);
    }
    snake_obj[0].x += dx;
    snake_obj[0].y += dy;

    if (snake_obj[0].x == -1)
        snake_obj[0].x = 31;
    else if (snake_obj[0].x == 32)
        snake_obj[0].x = 0;

    if (snake_obj[0].y == -1)
        snake_obj[0].y = 15;
    else if (snake_obj[0].y == 16)
        snake_obj[0].y = 0;
    if ((snake_obj[0].x != food.x) || (snake_obj[0].y != food.y))
    {
        display.fillRect(snake_obj[length].x * 4, snake_obj[length].y * 4, 4, 4, false);
    }
    else
    {
        length++;
        food.x = rand() % 32;
        food.y = rand() % 16;
    }

    display.fillRect(snake_obj[0].x * 4, snake_obj[0].y * 4, 4, 4, true);
    display.display();

    delay(100);

}

// TODO: new game & high score; 3 states (menu, game, high score); check button press w if()
void menu()
{/* 
    display.setCursor(0, 0);
    display.println("Hello, world!");
    // if( && select == 1 )
 */}

/* void game()
{
    display.fillRect(food.x * 4, food.y * 4, 4, 4, true);
    for (int i = length; i > 0; i--)
    {
        snake_obj[i].x = snake_obj[i - 1].x;
        snake_obj[i].y = snake_obj[i - 1].y;
        display.fillRect(snake_obj[i].x * 4, snake_obj[i].y * 4, 4, 4, true);
    }
    snake_obj[0].x += dx;
    snake_obj[0].y += dy;

    if (snake_obj[0].x == -1)
        snake_obj[0].x = 31;
    else if (snake_obj[0].x == 32)
        snake_obj[0].x = 0;

    if (snake_obj[0].y == -1)
        snake_obj[0].y = 15;
    else if (snake_obj[0].y == 16)
        snake_obj[0].y = 0;
    if ((snake_obj[0].x != food.x) || (snake_obj[0].y != food.y))
    {
        display.fillRect(snake_obj[length].x * 4, snake_obj[length].y * 4, 4, 4, false);
    }
    else
    {
        length++;
        food.x = rand() % 32;
        food.y = rand() % 16;
    }

    display.fillRect(snake_obj[0].x * 4, snake_obj[0].y * 4, 4, 4, true);
    display.display();
} */

void moveRight()
{
    if (dx == 0)
        dx = 1;
    dy = 0;
}

void moveLeft()
{
    if (dx == 0)
        dx = -1;
    dy = 0;
}

void moveUp()
{
    if (dy == 0)
        dy = -1;
    dx = 0;
}

void moveDown()
{
    if (dy == 0)
        dy = 1;
    dx = 0;
}

/* void testdrawchar(void)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  for (uint8_t i = 0; i < 168; i++)
  {
    if (i == '\n')
      continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
}

void testscrolltext(void)
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.clearDisplay();
  display.println("scroll");
  display.display();

  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
} */