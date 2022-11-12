#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pong.h"
#include "Shapes.h"

Pong_Game::Pong_Game(Adafruit_SSD1306* display){
  this->display = display;
  this->gameover = false;
}

void Pong_Game::start(){
  this->gameover = false;
  this->score = 0;
  this->player1.set_position(2, 32-14);
  this->player2.set_position(SCREEN_WIDTH-4, 32-14);
  this->game_ball.set_position(62, random(0,30));
  
  // Randomize the velocity for the game ball in the beginning
  if (random(0, 2)){
    if (random(0, 2)){
      this->game_ball.set_velocity(-1, 1);
    } else {
      this->game_ball.set_velocity(-1, -1); 
    }
  } else {
    if (random(0, 2)){
      this->game_ball.set_velocity(1, 1);
    } else {
      this->game_ball.set_velocity(1, -1);
    }
  }  
}

// Player can only move up and down
// Direction == 1 -> up
// Direction == 0 -> down
void Pong_Game::move_player1(int direction){
  if (direction){
    this->player1.shift(0, -2);
  } else {
    this->player1.shift(0, 2);
  }
}
void Pong_Game::move_player2(int direction){
  if (direction){
    this->player2.shift(0, -2);
  } else {
    this->player2.shift(0, 2);
  }
}

bool Pong_Game::check_gameover(){
  return this->gameover;  
}

void Pong_Game::tick(){
  this->display->clearDisplay();
  this->display->setCursor(59,0);
  this->display->print(score);
  this->player1.draw(this->display);
  this->player2.draw(this->display);
  this->game_ball.draw(this->display);
  this->display->display();
  
  int ball_radius = this->game_ball.get_radius();
  int ball_x = this->game_ball.get_x();
  int ball_y = this->game_ball.get_y();
  if (!this->gameover){
    this->game_ball.update_position();
    if (this->player1.check_collision_circle(ball_x, ball_y, ball_radius)){
      this->score++;
      if (score % 5 == 0){
        if (this->game_ball.get_vx() < 2){
          this->game_ball.speed_up();
        }
      }
      this->game_ball.set_position(this->player1.get_x() + this->player1.get_width() + ball_radius, ball_y);
      this->game_ball.turn_around_x();
    } else if (this->player2.check_collision_circle(ball_x, ball_y, ball_radius)){
      this->score++;
      if (score % 5 == 0){
        if (this->game_ball.get_vx() < 2){
          this->game_ball.speed_up();
        }
      }
      this->game_ball.set_position(this->player2.get_x() - ball_radius, ball_y);

      this->game_ball.turn_around_x();
    } else if (this->game_ball.check_collision_rectangle(SCREEN_WIDTH-4, 0, 4, 2*SCREEN_HEIGHT) || this->game_ball.check_collision_rectangle(0, 0, 3, 2*SCREEN_HEIGHT)){
      this->gameover = true;  
    }
  }
  
}

int Pong_Game::get_score(){
  return this->score;  
}
