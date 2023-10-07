#include "draw.h"
#include "util.h"

extern const TGAColor white ;
extern const TGAColor red ;
extern const TGAColor green ;

void line0(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for (float t=0.; t<1.; t+=.1) {
        int x = x0*(1.-t) + x1*t;
        int y = y0*(1.-t) + y1*t;
        image.set(x, y, color);
    }
}

void line1(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) 
{
   bool steep = false;
   if(std::abs(x0 - x1) < std::abs(y0 - y1)){
    std::swap(x0,y0);
    std::swap(x1,y1);
    steep = true;
   }

    if(x0 > x1){
        std::swap(x0,x1);
        std::swap(y0,y1);
    }

    for(int x = x0; x<=x1;x++)
    {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1. - t) + y1 * t;
        if(steep)
            image.set(y,x,color);
        else
            image.set(x,y,color);
    }
}

void line(int x0,int y0,int x1,int y1,TGAImage&image,TGAColor color)
{
    bool steep = false;
    if(std::abs(x0 -x1) < std::abs(y0 -y1)){
        std::swap(x0 ,y0);
        std::swap(x1,y1);
        steep = true;
    }

    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
}

void triangleline0(Vec2i t0,Vec2i t1,Vec2i t2,TGAImage&image,TGAColor color)
{
    line(t0.x,t0.y ,t1.x,t1.y, image, color); 
    line(t1.x,t1.y, t2.x,t2.y, image, color); 
    line(t2.x,t2.y, t0.x,t0.y, image, color); 
}

void triangleline1(Vec2i t0,Vec2i t1,Vec2i t2,TGAImage&image,TGAColor color)
{
    if(t0.y > t1.y) {
        Vec2i tmp = t0;
        t0 = t1;
        t1 = tmp;
    }
    if(t0.y > t2.y)  {
        Vec2i tmp = t0;
        t0 = t2;
        t2 = tmp;
    }
    if(t1.y > t2.y)  {
        Vec2i tmp = t1;
        t1 = t2;
        t2 = tmp;
    }

    line(t0.x,t0.y, t1.x,t1.y, image, green); 
    line(t1.x,t1.y, t2.x,t2.y, image, green); 
    line(t2.x,t2.y, t0.x,t0.y, image, white); 
}

void triangle0(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) { 
    // sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!) 
    if (t0.y==t1.y && t0.y==t2.y) return; // I dont care about degenerate triangles 
    // sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!) 
    if (t0.y>t1.y) std::swap(t0, t1); 
    if (t0.y>t2.y) std::swap(t0, t2); 
    if (t1.y>t2.y) std::swap(t1, t2); 
    int total_height = t2.y-t0.y; 
    for (int i=0; i<total_height; i++) { 
        bool second_half = i>t1.y-t0.y || t1.y==t0.y; 
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y; 
        float alpha = (float)i/total_height; 
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here 
        Vec2i A =               t0 + (t2-t0)*alpha; 
        Vec2i
        B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta; 
        if (A.x>B.x) std::swap(A, B); 
        for (int j=A.x; j<=B.x; j++) { 
            image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y 
        } 
    } 
}

void triangleWithBarycentric(Vec2i *pts, TGAImage &image, TGAColor color) { 
    Vec2i bboxmin(image.width()-1,  image.height()-1); 
    Vec2i bboxmax(0, 0); 
    Vec2i clamp(image.width()-1, image.height()-1); 
    for (int i=0; i<3; i++) { 
        bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
	bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));

	bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
	bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
    } 
    Vec2i P; 
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) { 
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) { 
            vec3 bc_screen  = barycentric(pts, P); 
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue; 
            image.set(P.x, P.y, color); 
        } 
    } 
} 