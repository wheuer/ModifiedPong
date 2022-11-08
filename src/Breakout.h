#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Shapes.h"

#ifndef Breakout
#define Breakout

class Breakout_Game {
  private:
    int score;
    int lives;
    bool gameover;
    bool victory;
    bool tiles[120];
    Rectangle player = Rectangle(127/2 - 7, 59, 14, 2);
    Ball game_ball = Ball(62, 50, 1, 0, 0);
    Adafruit_SSD1306* display;
  public:
    Breakout_Game(Adafruit_SSD1306* display);
    void start();
    bool check_gameover();
    bool check_victory();
    void tick();
    void move_player(int direction);
    int get_score();
    void display_tiles();
};

#endif
