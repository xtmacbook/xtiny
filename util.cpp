#include "util.h"

vec3 barycentric(Vec2i *pts, Vec2i P)
{
    vec3 u = vec3(pts[2][0] - pts[0][0],
                  pts[1][0] - pts[0][0],
                  pts[0][0] - P[0]) ^
             vec3(pts[2][1] - pts[0][1], pts[1][1] - pts[0][1], pts[0][1] - P[1]);

    if (std::abs(u.z) < 1)
        return vec3(-1., 1., 1.);
    return vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

vec3 barycentric(vec3 *pts, vec3 P)
{
    vec3&A = pts[0];
    vec3&B = pts[1];
    vec3&C = pts[2];

    vec3 s[2];
    for (int i = 2; i--;)
    {
        s[i][0] = C[i] - A[i];
        s[i][1] = B[i] - A[i];
        s[i][2] = A[i] - P[i];
    }
    vec3 u = cross(s[0], s[1]);
    if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
    return vec3(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}
