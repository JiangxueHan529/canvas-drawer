#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   canvas drawer(640, 380);
   drawer.background(167, 242, 242);
   drawer.begin(LINES);
   drawer.draw_rectangle(280, 190, 180, 100);
   drawer.color(242, 168, 40);
   drawer.fill_rectangle(280, 190, 180, 100);
   drawer.end();
   drawer.begin(TRIANGLES);
   drawer.color(255, 0, 255);
   drawer.vertex(190, 190);
   drawer.color(0, 255, 255);
   drawer.vertex(110, 260);
   drawer.color(255, 255, 0);
   drawer.vertex(110, 120);
   drawer.end();
   drawer.begin(TRIANGLES);
   drawer.color(0, 255, 255);
   drawer.vertex(370, 240);
   drawer.color(255, 0, 255);
   drawer.vertex(370, 140);
   drawer.color(255, 255, 0);
   drawer.vertex(430, 190);
   drawer.end();
   drawer.begin(CIRCLES);
   drawer.color(0, 0, 0);
   drawer.input_radius(10);
   drawer.vertex(395, 190);
   drawer.end();
   drawer.begin(POINTS);
   drawer.color(0, 0, 0);
   drawer.vertex(395, 190);
   drawer.vertex(395, 191);
   drawer.vertex(395, 189);
   drawer.vertex(394, 190);
   drawer.vertex(396, 190);
   drawer.end();
   drawer.begin(LINES);
   drawer.color(0, 0, 0);
  
   drawer.vertex(210, 200);
   drawer.input_line_width(5);
   drawer.vertex(350, 200);
   drawer.vertex(210, 180);
   drawer.input_line_width(5);
   drawer.vertex(350, 180);
   drawer.end();
   drawer.begin(CIRCLES);
   drawer.color(150, 150, 255);
   drawer.input_radius(10);
   drawer.vertex(450, 185);
   drawer.input_radius(25);
   drawer.vertex(490, 140);
   drawer.input_radius(40);
   drawer.vertex(540, 80);
   drawer.end();

   drawer.save("my_art.png");

   canvas drawer2(600, 400);
   drawer2.background(0, 0, 0);
   drawer2.begin(POINTS);
   drawer2.color(214, 245, 48);
   drawer2.vertex(300, 200);
   drawer2.end();
   drawer2.begin(CIRCLES);
   drawer2.color(214, 245, 48);
   drawer2.input_radius(20);
   drawer2.vertex(300, 200);
   drawer2.input_radius(40);
   drawer2.vertex(300, 200);
   drawer2.input_radius(60);
   drawer2.vertex(300, 200);
   drawer2.input_radius(80);
   drawer2.vertex(300, 200);
   drawer2.input_radius(100);
   drawer2.vertex(300, 200);;
   drawer2.input_radius(120);
   drawer2.vertex(300, 200);
   drawer2.end();
   drawer2.begin(TRIANGLES);
   drawer2.color(235, 0, 200);
   drawer2.vertex(120, 320);
   drawer2.color(55, 205, 255);
   drawer2.vertex(45, 370);
   drawer2.color(100, 255, 170);
   drawer2.vertex(50, 270);

   drawer2.color(115, 197, 200);
   drawer2.vertex(520, 260);
   drawer2.color(197, 155, 25);
   drawer2.vertex(470, 370);
   drawer2.color(190, 176, 170);
   drawer2.vertex(440, 270);
   drawer2.end();

   drawer2.color(255, 138, 200);
   drawer2.vertex(520, 60);
   drawer2.color(87, 200, 175);
   drawer2.vertex(470, 130);
   drawer2.color(255, 200, 170);
   drawer2.vertex(440, 60);
   drawer2.end();

   drawer2.color(255, 200, 30);
   drawer2.vertex(90, 45);
   drawer2.color(0, 200, 175);
   drawer2.vertex(100, 130);
   drawer2.color(255, 20, 70);
   drawer2.vertex(30, 80);
   drawer2.end();
   drawer2.save("my_art2.png");



   return 0;
}

