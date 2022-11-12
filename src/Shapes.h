#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#ifndef Shapes
#define Shapes

// Adafruit uses zero indexing so need to -1
#define SCREEN_WIDTH 128-1
#define SCREEN_HEIGHT 64-1

class Rectangle {
  private:
    int x,y,width,height;
  public:
    Rectangle(int x, int y, int width, int height);

    void draw(Adafruit_SSD1306* display);
    void shift(int x, int y);
    bool check_collision_rectangle(int x, int y, int width, int height);
    bool check_collision_circle(int x, int y, int radius);
    void set_position(int x, int y);
    int get_x();
    int get_y();
    int get_height();
    int get_width();
};

class Ball {
    private:
        int x,y,radius,vx,vy;
    public:
        Ball(int x, int y, int radius, int vx, int vy);
        void draw(Adafruit_SSD1306* display);
        void set_position(int x, int y);
        void set_velocity(int vx, int vy);
        void speed_up();
        void shift(int x, int y);   
        void update_position();
        bool check_collision_rectangle(int x, int y, int width, int height);
        bool check_collision_circle(int x, int y, int radius);
        int get_vx();
        int get_vy();
        int get_x();
        int get_y();
        int get_radius();
        void turn_around_x();
        void turn_around_y();
};

#endif
