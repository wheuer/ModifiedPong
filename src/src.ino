#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pong.h"
#include "Breakout.h"
#include "Shapes.h"
#include "Sprites.h"

#define OLED_ADDR 0x3C

#define UP_BUTTON_PIN 5
#define DOWN_BUTTON_PIN 6
#define LEFT_BUTTON_PIN 7
#define RIGHT_BUTTON_PIN 8

#define CHARACTER_WIDTH 6
#define CHARACTER_HEIGHT 7

void print_game_select();
/**
 * CANNOT USE PINS PB5(13), PB4(12), or PB3(11) as these will be used to program the uC
 */

/**
 * Adafruit_GFX character size = font_size * (5x7)
 * note that each character will have a once pixel space aswell
  */

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Pong_Game pong(&display);
Breakout_Game breakout(&display);

int game_state = 0;

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
  
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);

  delay(2000); // Wait for OLED to initilize

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Intro
  display.drawBitmap(1, 1, image_data_sloth, 60, 60, WHITE);
  display.display();
  delay(1000);
  display.setCursor(63+2, 5);
  display.print(F("A Creation"));
  display.display();
  delay(500);
  display.setCursor(63+23, 20);
  display.print(F("By,"));
  display.display();
  delay(500);
  display.setCursor(63+11, 35);
  display.print(F("William"));
  display.display();
  delay(500);
  display.setCursor(63+17, 50);
  display.print(F("Heuer"));
  display.display();
  delay(2000);
}

void loop(){
  if (game_state == 0){
    print_game_select();
    if(!digitalRead(UP_BUTTON_PIN)){
      game_state = 1;
      pong.start();
    }
    if(!digitalRead(DOWN_BUTTON_PIN)){
      game_state = 2;
      breakout.start();
    }
  } else {
    if (game_state == 1){
      // Pong
      if (pong.check_gameover()){
        display.clearDisplay();
        display.setCursor(36, 10);
        display.print(F("Game over"));
        display.setCursor(4, 25);
        display.print(F("You scored "));
        display.print(pong.get_score());
        display.print(F(" points"));
        display.setCursor(30, 40);
        display.print(F("Play Again?"));
        display.display();

        if(!digitalRead(UP_BUTTON_PIN) || !digitalRead(DOWN_BUTTON_PIN) || !digitalRead(LEFT_BUTTON_PIN) || !digitalRead(RIGHT_BUTTON_PIN)){
          game_state = 0;
          print_game_select();
          delay(500);
        }

      } else {
        pong.tick();
        
        if(!digitalRead(UP_BUTTON_PIN)){
          pong.move_player1(1);
        }
        if(!digitalRead(DOWN_BUTTON_PIN)){
          pong.move_player1(0);
        }
        if(!digitalRead(LEFT_BUTTON_PIN)){
          pong.move_player2(1);
        }
        if(!digitalRead(RIGHT_BUTTON_PIN)){
          pong.move_player2(0);
        }

        delay(15);
        
      }
    } else if (game_state == 2){
      if (breakout.check_gameover()){
        display.clearDisplay();
        if (breakout.check_victory()){
          display.setCursor(39, 16);
          display.print(F("You win!"));
          display.setCursor(30, 32);
          display.print(F("Play Again?"));
        } else {
          display.setCursor(36, 10);
          display.print(F("Game over"));
          display.setCursor(4, 25);
          display.print("You scored " + String(breakout.get_score()) + " points");
          display.setCursor(30, 40);
          display.print(F("Play Again?"));
        }
        display.display();

        if(!digitalRead(UP_BUTTON_PIN) || !digitalRead(DOWN_BUTTON_PIN) || !digitalRead(LEFT_BUTTON_PIN) || !digitalRead(RIGHT_BUTTON_PIN)){
          game_state = 0;
          print_game_select();
          delay(500);
        }
      } else {
        breakout.tick();
        
        if(!digitalRead(UP_BUTTON_PIN)){
          breakout.move_player(0);
        }
        if(!digitalRead(LEFT_BUTTON_PIN)){
          breakout.move_player(1);
        }

        delay(15);

      }
    }
  }
}

void print_game_select(){
  display.clearDisplay();
  display.setCursor(30, 5);
  display.print(F("Select Game"));
  display.setCursor(10, 25);
  display.print(F("UP : Modified Pong"));
  display.setCursor(19, 40);
  display.print(F("DOWN : Breakout"));
  display.display();  
}
