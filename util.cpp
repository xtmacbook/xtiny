#include "util.h"


vec3 barycentric(Vec2i*pts,Vec2i P)
{
    vec3 u = vec3(pts[2][0]-pts[0][0], 
                pts[1][0]-pts[0][0], 
                pts[0][0]-P[0])
                ^vec3(pts[2][1]-pts[0][1], pts[1][1]-pts[0][1], pts[0][1]-P[1]);

    if (std::abs(u.z)<1) return vec3(-1.,1.,1.);
    return vec3(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z); 
}