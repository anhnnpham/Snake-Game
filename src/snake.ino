// #pragma ONCE
#ifndef SNAKE_GAME
#define SNAKE_GAME  

#include "Adafruit_SSD1306/Adafruit_SSD1306.h"

// SDA = MOSI
#define OLED_DC A1 // SA0 = MISO
#define OLED_CS A2
#define OLED_RESET A0
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

struct snake 
{
    int x;
    int y;
};
struct snake snakeObj[50]; // 30 objs
struct snake food; 

bool stateSwitch = false;
bool isGameOver = false;

int len = 4;
int xButton = 1; // always move right
int yButton = 0;

const size_t lim = 5; // max high scores displayed
int scoreList[lim] = {0, 1, 2, 3, 4}; 


void defaultMenu();
void menu();
void newGame();
void endGame();
void highScore();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();

void setup()
{
    pinMode(D3, INPUT_PULLDOWN); // -> mode = RISING
    pinMode(D5, INPUT_PULLDOWN);
    pinMode(D6, INPUT_PULLDOWN);
    pinMode(D7, INPUT_PULLDOWN);

    attachInterrupt(D3, moveUp, RISING, 1); // highest priority
    attachInterrupt(D5, moveDown, RISING, 2);
    attachInterrupt(D6, moveLeft, RISING, 4);
    attachInterrupt(D7, moveRight, RISING, 3);

    display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
    
    snakeObj[0].x = 5;
    snakeObj[0].y = 5;
    
/*     snakeObj[1].x = 6;
    snakeObj[1].y = 5;
    
    snakeObj[2].x = 7;
    snakeObj[2].y = 5;
    
    snakeObj[3].x = 8;
    snakeObj[3].y = 5;
    
    snakeObj[4].x = 9;
    snakeObj[4].y = 5;
 */
    food.x = rand() % 32; // width = 0 -> 31
    food.y = rand() % 16; // height = 0 -> 15
}

void loop()
{
                newGame();
                delay(300);

/*     if (stateSwitch == 0)
    {
        // stateSwitch = 0;
        
        defaultMenu();
        display.setCursor(0, 32);
        display.println("NEWGAMEWBELOW");
        display.display();
        
        if (digitalRead(D7) == HIGH)
        {
            display.clearDisplay();
            do
            {
                newGame();
                delay(500);
            } while (!isGameOver); // is not over
        }
    }

    if (digitalRead(D5) == HIGH || stateSwitch == 1) // if press down
    {
        stateSwitch = 1;
        
        defaultMenu();
        display.setCursor(0, 32);
        display.println("HIGHSCORESBELOW");
        display.display();
        
        if (digitalRead(D7) == HIGH)
        { 
            do
            {
                highScore();
            } while (digitalRead(D6) != HIGH);
        }

        if (digitalRead(D3) == HIGH)
        { // if press up again
            stateSwitch = 0;
        }
    }

    // display.display();
    delay(500);
    // if(state == 1 && select == 1 )

    //     if(state == 1)
    //     menu();
    // else if(state == 2)
    //     game();
 */}

// TODO: 3 states (menu, game, high score);
void defaultMenu()
{    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Snake Game!");

    display.println("          New");
    display.println("          High");

    // display.setCursor(0, 32);
    // display.println("NEWBELOW");
    // display.display();
    
}    

void menu()
{   
}

int totScore = 0;
void newGame()
{
    display.fillRect(food.x * 4, food.y * 4, 4, 4, true); 

    for (int i = len; i > 0; --i)
    {
        // 1 update per loop
        snakeObj[i].x = snakeObj[i - 1].x; // [2] = [1] -> [1] = [0]
        snakeObj[i].y = snakeObj[i - 1].y;
        // drawRect(x, y, width, height, color); x y indicate the rec's top left corner
        // * 4 = full screen
        display.fillRect(snakeObj[i].x * 4, snakeObj[i].y * 4, 4, 4, true); 
    }

    snakeObj[0].x += xButton; // head
    snakeObj[0].y += yButton;
    
    // check over-border length
    if (snakeObj[0].x == -1)
        snakeObj[0].x = 31;
    else if (snakeObj[0].x == 32)
        snakeObj[0].x = 0;

    // check over-border height
    if (snakeObj[0].y == -1)
        snakeObj[0].y = 15;
    else if (snakeObj[0].y == 16)
        snakeObj[0].y = 0;
    
    // TODO: logic???
    if ((snakeObj[0].x != food.x) || (snakeObj[0].y != food.y))
    {   // if not eating
        display.fillRect(snakeObj[len].x * 4, snakeObj[len].y * 4, 4, 4, false); // false = remove last obj
    }
    else // else increase len + new food
    {
        ++totScore;
        len += 10; // TODO:
        food.x = rand() % 32;
        food.y = rand() % 16;
    }

    // self-collision
    for (int idx = 4; idx <= len; ++idx)
    {
        if ((snakeObj[0].x == snakeObj[idx].x) && (snakeObj[0].y == snakeObj[idx].y))
        {
            endGame(totScore);
            isGameOver = true;
        }
    }    

    display.fillRect(snakeObj[0].x * 4, snakeObj[0].y * 4, 4, 4, true);
    display.display();
}

void endGame(int totScoreIn) {
    for (int i = lim - 1; i >= 0; i--)
    {
        if (totScoreIn > scoreList[i])
        {
            scoreList[i] = totScoreIn;
            break;
        }   
    }

    while (1)
    {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Score: ");
    display.println(totScoreIn, DEC); // same line
    // display.println(totScoreIn);
    display.display();
    delay(5000); // before return to menu

    }
    
}

void highScore() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    for (int i = lim - 1; i >= 0; i--) {
        display.println(scoreList[i], DEC);
    }
    display.display();
}

void moveUp()
{
    if (yButton == 0) // can't down if not right/left yet
        yButton = -1;
    xButton = 0;
}

void moveDown()
{
    if (yButton == 0)
        yButton = 1;
    xButton = 0;
}

void moveRight()
{
    if (xButton == 0)
        xButton = 1;
    yButton = 0;
}

void moveLeft()
{
    if (xButton == 0)
        xButton = -1;
    yButton = 0;
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
} */

/* void testscrolltext(void)
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


/*     display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.println("Hello, world!");
    
    // for Selection
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.println(3.141592);
    
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("0x");
    display.println(0xDEADBEEF, HEX);
    display.display();
    delay(2000);
    display.clearDisplay();

    draw the first ~12 characters in the font
    testdrawchar();
    display.display();
    delay(2000);
    display.clearDisplay();

    draw scrolling text
    testscrolltext();
    delay(2000);
    display.clearDisplay();
 */

#endif // SNAKE_GAME