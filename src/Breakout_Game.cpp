#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Breakout.h"
#include "Shapes.h"

Breakout_Game::Breakout_Game(Adafruit_SSD1306* display){
  this->display = display;
  this->gameover = false;
  this->victory = false;
  this->lives = 3;

  for (int i = 0; i < 120; i++){
    this->tiles[i] = true;
  }
}

void Breakout_Game::start(){
  this->gameover = false;
  this->victory = false;
  this->lives = 3;
  this->player.set_position(127/2 - 7, 59);
  this->game_ball.set_position(62, 50);

  for (int i = 0; i < 120; i++){
    this->tiles[i] = true;
  }
  
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

void Breakout_Game::tick(){
  this->display->clearDisplay();
  
  this->display->setCursor(3,2);
  this->display->print("Score:");
  this->display->print(this->score);
  this->display->setCursor(80, 2);
  this->display->print("Lives:");
  this->display->print(this->lives);
  
  this->player.draw(this->display);
  this->game_ball.draw(this->display);
  this->display_tiles();
  
  this->display->display();

  if (!this->gameover){
    this->game_ball.update_position();
    
    int current_x = 5;
    int current_y = 12;
    int current_arr_position = 0;
    for (int i = 0; i < 8; i++){
      for (int j = 0; j < 15; j++){
        if (tiles[current_arr_position]){
          if (this->game_ball.check_collision_rectangle(current_x, current_y, 6, 3)){
            this->score++; 
            if (this->score == 120){
              this->gameover = true;
              this->victory = true;
            }
            this->tiles[current_arr_position] = false;
            // Handle changing direction and reseting balls position relative to tile
            
            if (this->game_ball.get_y() % 2 == 0){
              // Hit horizontal
              if (this->game_ball.get_vx() < 0){
                this->game_ball.set_position(current_x + 6 + this->game_ball.get_radius(), this->game_ball.get_y());  
              } else {
                this->game_ball.set_position(current_x - this->game_ball.get_radius(), this->game_ball.get_y());    
              }  
              this->game_ball.turn_around_x();
            } else {
              if (this->game_ball.get_vy() < 0){
                this->game_ball.set_position(this->game_ball.get_x(), current_y + 3 + this->game_ball.get_radius());  
              } else {
                this->game_ball.set_position(this->game_ball.get_x(), current_y - this->game_ball.get_radius());  
              }
              this->game_ball.turn_around_y();
            }        

            goto exit_loop;
          }
        }
        current_arr_position++;
        current_x += 8;
      }
      current_x = 5;
      current_y += 4;
    }
    
    if (this->player.check_collision_circle(this->game_ball.get_x(), this->game_ball.get_y(), this->game_ball.get_radius())){
      this->game_ball.set_position(this->game_ball.get_x(), this->player.get_y() - this->game_ball.get_radius());
      this->game_ball.turn_around_y();
    } else if (this->game_ball.check_collision_rectangle(0, 60, SCREEN_WIDTH, 3)){
      this->lives--;
      if (this->lives == 0){
        this->gameover = true;
      }
      this->game_ball.turn_around_y();
    }
    exit_loop:;
  }
  
}

void Breakout_Game::display_tiles(){
  int current_x = 5;
  int current_y = 12;
  int current_arr_position = 0;
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 15; j++){
      if (this->tiles[current_arr_position]){
        this->display->fillRect(current_x, current_y, 6, 3, WHITE);
      }
      current_arr_position++;
      current_x += 8;
    }
    current_x = 5;
    current_y += 4;
  }
  
}


// Direction: 1 - Right
//            0 - Left
void Breakout_Game::move_player(int direction){
  if (direction){
    this->player.shift(2, 0);
  } else {
    this->player.shift(-2, 0);
  }
}

int Breakout_Game::get_score(){
  return this->score;
}

bool Breakout_Game::check_gameover(){
  return this->gameover;
}

bool Breakout_Game::check_victory(){
  return this->victory;
}
