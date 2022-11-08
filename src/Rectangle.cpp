#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Shapes.h"

Rectangle::Rectangle(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;  
}
    
void Rectangle::draw(Adafruit_SSD1306* display){
    display->fillRect(this->x, this->y, this->width, this->height, WHITE);
}

void Rectangle::set_position(int x, int y){
  this->x = x;
  this->y = y;
}

void Rectangle::shift(int x, int y){
    if (this->x + x + this->width >= SCREEN_WIDTH){
      this->x = SCREEN_WIDTH - this->width;  
    } else if (this->x + x <= 0){
      this->x = 0;  
    } else {
      this->x += x;  
    }

    if (this->y + y + this->height >= SCREEN_HEIGHT){
      this->y = SCREEN_HEIGHT - this->height;
    } else if (this->y + y <= 0){
      this->y = 0;
    } else {
      this->y += y;  
    }
}

bool Rectangle::check_collision_rectangle(int x, int y, int width, int height){
  if (this->x < x + width &&
      this->x + this->width > x &&
      this->y < y + height &&
      this->y + this->height > y) return true;
  return false;  
}

bool Rectangle::check_collision_circle(int x, int y, int radius){
  int circle_to_square_x = x - radius;
  int circle_to_square_y = y - radius;
  return this->check_collision_rectangle(circle_to_square_x, circle_to_square_y, 2*radius, 2*radius);
}

int Rectangle::get_x(){
  return this->x;  
}

int Rectangle::get_y(){
  return this->y;  
}

int Rectangle::get_height(){
  return this->height;  
}

int Rectangle::get_width(){
  return this->width;  
}
