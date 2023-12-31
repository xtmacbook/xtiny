#include "draw.h"
#include "geometry.h"
#include "model.h"

extern const TGAColor white = TGAColor(255, 255, 255, 255);
extern const TGAColor red = TGAColor(255, 0, 0, 255);
extern const TGAColor green = TGAColor(0, 255, 0, 255);

vec3 light_dir(0,0,-1); // define light_dir

const int width = 800;
const int height = 800;

vec3 world2screen(vec3 v) {
    return vec3(int((v.x+1.)*width/2.+.5), int((v.y+1.)*height/2.+.5), v.z);
}

int main(int argc, char **argv)
{
    TGAImage image(width, height, TGAImage::RGB);
    // line0(13, 20, 80, 40, image, white);

    // Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
    // Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
    // Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
    // triangle0(t0[0], t0[1], t0[2], image, red);
    // triangle0(t1[0], t1[1], t1[2], image, white);
    // triangle0(t2[0], t2[1], t2[2], image, green);

    Model *pModel = new Model("../tiny/tinyrenderer/obj/african_head/african_head.obj");

    // with line
    if (0)
    {
        for (int i = 0; i < pModel->nfaces(); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                vec3 v0 = pModel->vert(i, j);
                vec3 v1 = pModel->vert(i, (j + 1) % 3);
                int x0 = (v0.x + 1.) * width / 2.;
                int y0 = (v0.y + 1.) * height / 2.;
                int x1 = (v1.x + 1.) * width / 2.;
                int y1 = (v1.y + 1.) * height / 2.;
                line(x0, y0, x1, y1, image, white);
            }
        }
    }

    float *zbuffer = new float[width*height];
    for (int i=width*height; i--; zbuffer[i] = -std::numeric_limits<float>::max());

    for (int i = 0; i < pModel->nfaces(); i++)
    {
        vec3 screen_coords[3];
        vec3 world_coords[3]; 
        for (int j = 0; j < 3; j++)
        {
            vec3 v0 = pModel->vert(i, j);
            screen_coords[j] = world2screen(v0);
            world_coords[j] = v0;
        }

        vec3 n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]); 
        n.normalize(); 
        float intensity = n*light_dir; 
        if (intensity>0) 
           // triangleWithBarycentric(screen_coords, image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
            triangleWithBaryCentricAndZBuffer (screen_coords,zbuffer, image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
    }

    //image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}