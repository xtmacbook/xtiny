#include "tgaimage.h"
#include "geometry.h"

void line0(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void line1(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void line(int x0,int y0,int x1,int y1,TGAImage&image,TGAColor color);

void triangleline0(Vec2i t0,Vec2i t1,Vec2i t2,TGAImage&image,TGAColor color);
void triangleline1(Vec2i t0,Vec2i t1,Vec2i t2,TGAImage&image,TGAColor color);

void triangle0(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color);

