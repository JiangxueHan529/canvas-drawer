#ifndef canvas_H_
#define canvas_H_

#include <string>
#include <vector>
#include "ppm_image.h"
using namespace std;
namespace agl
{

   enum PrimitiveType {UNDEFINED, LINES, TRIANGLES,CIRCLES, POINTS};
   
   class canvas
   {
   private:
       PrimitiveType curShape;
       unsigned char* curColor;
       int width;
       int height;
       vector<vector<int>> vertices;
       int numVec;
       int numColor;
       int* tracker;
       int* color_tracker;
       vector<int> radius;
       vector<int> line_width;
       ppm_image _canvas;


   public:
      canvas(int w, int h);
      virtual ~canvas();

      // Save to file
      void save(const std::string& filename);
      void barycentric_fill(vector<int> a, vector<int> b, vector<int> c, int color_index, int color_track);
      int helper(vector<int> a, vector<int> b, vector<int> c);
      void draw_circle(int x, int y, int radius, int color_index);
      void drawC(int x, int y, int x1, int y1, ppm_pixel* our_color);
      void input_radius(int r);
      void input_line_width(int lw);
      void draw_rectangle(int cx, int xy, int w, int h);
      void fill_rectangle(int cx, int xy, int w, int h);

      // Draw primitives with a given type (either LINES or TRIANGLES)
      // For example, the following draws a red line followed by a green line
      // begin(LINES);
      //    color(255,0,0);
      //    vertex(0,0);
      //    vertex(100,0);
      //    color(0,255,0);
      //    vertex(0, 0);
      //    vertex(0,100);
      // end();

      void begin(PrimitiveType type);
      void end();

      // Specifiy a vertex at raster position (x,y)
      // x corresponds to the column; y to the row
      void vertex(int x, int y);

      // Specify a color. Color components are in range [0,255]
      void color(unsigned char r, unsigned char g, unsigned char b);

      // Fill the canvas with the given background color
      void background(unsigned char r, unsigned char g, unsigned char b);
    
   };
}
#endif


