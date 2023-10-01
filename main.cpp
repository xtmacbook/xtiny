#include "draw.h"
#include "geometry.h"

extern const TGAColor white = TGAColor(255, 255, 255, 255);
extern const TGAColor red   = TGAColor(255, 0,   0,   255);
extern const TGAColor green   = TGAColor(0, 255,   0,   255);

int main(int argc, char** argv) {
    TGAImage image(600, 800, TGAImage::RGB);
    //line0(13, 20, 80, 40, image, white);

    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 
    triangle0(t0[0], t0[1], t0[2], image, red); 
    triangle0(t1[0], t1[1], t1[2], image, white); 
    triangle0(t2[0], t2[1], t2[2], image, green);


    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}