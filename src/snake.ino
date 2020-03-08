#ifndef SNAKE_GAME
#define SNAKE_GAME  

#include "Adafruit_SSD1306/Adafruit_SSD1306.h"

// SDA = MOSI
#define OLED_DC A1 // SA0 = MISO
#define OLED_CS A2
#define OLED_RESET A0
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

void Menu_and_Preset();
void newGame();
void endGame();
void highScore();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();

struct snake 
{
    int x;
    int y;
};
struct snake snakeObj[100] = {0};
struct snake food; 

bool isSwitched = false;
bool isGameOver = false;
bool isHighScore = true;

int len = 4;
int personScore = 0;

const size_t size = 5; // max high scores displayed 
int scoreList[size] = {0}; 

int xButton = 1; // move right initially
int yButton = 0;



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
}

void loop()
{
    if (!isSwitched)
    {
        Menu_and_Preset();
        display.println("   New Game");

        if (digitalRead(D7) == HIGH)
        {
            display.clearDisplay();
            do
            {
                newGame();
                delay(150);
            } while (!isGameOver); // is not over
        }
    }

    if (digitalRead(D5) == HIGH || isSwitched) // if press down
    {
        isSwitched = 1;

        Menu_and_Preset();
        display.println("   High Score");
        
        if (digitalRead(D7) == HIGH)
        {
            do
            {
                highScore();
            } while (isHighScore);
        }

        if (digitalRead(D3) == HIGH)
        {   // if press Up
            isSwitched = !isSwitched;
        }
    }
    display.display();
    delay(200);
}

void Menu_and_Preset()
{
    snakeObj[100] = {0};
    snakeObj[0].x = (rand() % 32) + 1;
    snakeObj[0].y = (rand() % 16) + 1;
    food.x = rand() % 32; // width = 0 -> 31
    food.y = rand() % 16; // height = 0 -> 15

    // for next game
    len = 4;    
    personScore = 0;
    isGameOver = false; 
    isHighScore = true;

    // GUI
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Snake Game!");
    
    display.setCursor(0, 48); // near bottom screen
    display.println("Right to Select");
    display.println("Up/Down to Change");
    display.setCursor(0, 16);
}    

void newGame()
{
    display.fillRect(food.x * 4, food.y * 4, 4, 4, true); 

    for (int i = len; i > 0; --i)
    {   // 1 update per loop
        snakeObj[i].x = snakeObj[i - 1].x;
        snakeObj[i].y = snakeObj[i - 1].y;
        display.fillRect(snakeObj[i].x * 4, snakeObj[i].y * 4, 4, 4, true); 
    }

    snakeObj[0].x += xButton; // snake's head
    snakeObj[0].y += yButton;
    
    // check over-border length-wise
    if (snakeObj[0].x == -1)
        snakeObj[0].x = 31;
    else if (snakeObj[0].x == 32)
        snakeObj[0].x = 0;

    // check over-border height-wise
    if (snakeObj[0].y == -1)
        snakeObj[0].y = 15;
    else if (snakeObj[0].y == 16)
        snakeObj[0].y = 0;
    
    if ((snakeObj[0].x != food.x) || (snakeObj[0].y != food.y))
    {   // if not eating
        display.fillRect(snakeObj[len].x * 4, snakeObj[len].y * 4, 4, 4, false); // false = remove last obj/pxl
    }
    else // else ++len + new food
    {
        ++personScore;
        len += 1;
        food.x = rand() % 32;
        food.y = rand() % 16;
    }
    display.fillRect(snakeObj[0].x * 4, snakeObj[0].y * 4, 4, 4, true);
    display.display();

    // self-collision
    for (int idx = 4; idx <= len; ++idx) // minimum 3 steps to self-collide
    {
        if ((snakeObj[0].x == snakeObj[idx].x) && (snakeObj[0].y == snakeObj[idx].y))
        {
            isGameOver = true;
            endGame(personScore);
        }
    }    
}

void endGame(int scoreIn) {
    for (int i = size - 1; i >= 0; i--)
    {
        if (scoreIn > scoreList[i])
        {
            scoreList[i] = scoreIn;
            break;
        }
    }

    while (digitalRead(D7) != HIGH) {
        // GUI
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        
        display.setCursor(0, 0);
        display.print("Score: ");
        display.println(scoreIn, DEC); // same line
        
        display.setCursor(0, 56); // near bottom screen
        display.println("Right to Menu");
        display.display();
    }
}

void highScore() {
    if (digitalRead(D6) == HIGH) // if Left, return to menu
    {
        isHighScore = 0;
    }

    // GUI
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    for (int i = size - 1; i >= 0; i--) {
        display.println(scoreList[i], DEC);
    }
    
    display.setCursor(0, 56); // near bottom screen
    display.println("Left to Menu");
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
#endif // SNAKE_GAME