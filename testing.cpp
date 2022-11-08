#include <iostream>
#include <cmath>

bool check_collision_circle(int x1, int y1, int x2, int y2, int radius1, int radius2){
  float distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
  if (distance <= radius1 + radius2){
    return true;  
  }
  return false;  
}

bool check_collision_rectangle(int x1, int y1, int x2, int y2, int width1, int height1, int width2, int height2){
  if (x1 <= x2 + width2 && x2 <= x1 + width1){
    if (y1 <= y2 + height2 && y2 <= y1 + height1){
      return true;  
    }  
  }
  return false;  
}

int main(){
    // std::cout << std::boolalpha << check_collision_circle(2, 1, 2, 2, 2, 2) << std::endl;
    // std::cout << std::boolalpha << check_collision_circle(10, 5, 1, 1, 2, 2) << std::endl;
    // std::cout << std::boolalpha << check_collision_circle(2, 1, 1, 2, 1, 1) << std::endl;
    // std::cout << std::boolalpha << check_collision_rectangle(2, 1, 4, 1, 4, 2, 4, 2) << std::endl;

    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 15; j++){
            std::cout << i*j - 1 << " "; 
        }
        std::cout << std::endl;
    }
}