#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef Pong
#define Pong

#include "Shapes.h"

class Pong_Game {
    private:
      int score;
      bool gameover;
      Rectangle player1 = Rectangle(2, 32-14, 2, 14);
      Rectangle player2 = Rectangle(SCREEN_WIDTH-4, 32-14, 2, 14);
      Ball game_ball = Ball(62, random(0,30), 2, 0, 0);
      Adafruit_SSD1306* display;
    public:
      Pong_Game(Adafruit_SSD1306* display);
      bool check_gameover();
      void tick();
      void start();
      void move_player1(int direction);
      void move_player2(int direction);
      int get_score();
};


#endif
