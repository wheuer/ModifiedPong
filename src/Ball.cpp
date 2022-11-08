#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Shapes.h"

Ball::Ball(int x, int y, int radius, int vx, int vy){
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->vx = vx;
    this->vy = vy;
}

void Ball::draw(Adafruit_SSD1306* display){
    display->fillCircle(this->x, this->y, this->radius, WHITE);
}

void Ball::set_position(int x, int y){
    this->x = x;
    this->y = y;  
}

void Ball::set_velocity(int vx, int vy){
    this->vx = vx;
    this->vy = vy;
}

void Ball::speed_up(){
    if (this->vx > 0){
        this->vx++;  
    } else {
        this->vx--;  
    }

    if (this->vy > 0){
        this->vy++;  
    } else {
        this->vy--;  
    }
}

void Ball::shift(int x, int y){
    if (((this->x + x + this->radius) >= SCREEN_WIDTH)){
        this->set_position(SCREEN_WIDTH - this->radius, this->y);
        this->set_velocity(this->vx*-1, this->vy);
    } else if ((this->x + x - this->radius) <= 0) {
        this->set_position(0 + this->radius, this->y);
        this->set_velocity(this->vx*-1, this->vy);
    } else {
        this->x += x;
    }
    
    if (((this->y + y + this->radius) >= SCREEN_HEIGHT)){
        this->set_position(this->x, SCREEN_HEIGHT - this->radius);
        this->set_velocity(this->vx, this->vy*-1);
    } else if ((this->y + y - this->radius) <= 0){
        this->set_position(this->x, 0 + this->radius);
        this->set_velocity(this->vx, this->vy*-1);
    } else {
        this->y += y;  
    }
}

void Ball::turn_around_x(){
  this->set_velocity(this->vx*-1, this->vy);
}

void Ball::turn_around_y(){
  this->set_velocity(this->vx, this->vy*-1);
}

void Ball::update_position(){
    this->shift(vx, vy);
}

bool Ball::check_collision_rectangle(int x, int y, int width, int height){
  int circle_to_square_x = this->x - this->radius;
  int circle_to_square_y = this->y - this->radius;

  if (circle_to_square_x < x + width &&
      circle_to_square_x + this->radius > x &&
      circle_to_square_y < y + height &&
      circle_to_square_y + this->radius > y) return true;

  return false;
}

bool Ball::check_collision_circle(int x, int y, int radius){
  float distance = sqrt(pow(this->x - x, 2) + pow(this->y - y, 2));
  if (distance <= this->radius + radius){
    return true;  
  }
  return false;  
}

int Ball::get_vx(){
  return this->vx;  
}

int Ball::get_vy(){
  return this->vy;  
}

int Ball::get_x(){
  return this->x;  
}

int Ball::get_y(){
  return this->y;  
}

int Ball::get_radius(){
  return this->radius;  
}
