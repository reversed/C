//=====================================================================
// 
// mini3d.c - Mini Software Render All-In-One
//
// build:
//   mingw: gcc -O3 mini3d.c -o mini3d.exe -lgdi32
//   msvc:  cl -O2 -nologo mini3d.c 
//
// history:
//   2007.7.01  skywind  create this file as a tutorial
//   2007.7.02  skywind  implementate texture and color render
//   2008.3.15  skywind  fixed a trapezoid issue
//   2015.8.09  skywind  rewrite with more comment
//   2015.8.12  skywind  adjust interfaces for clearity 
// 
//=====================================================================

// Good Discussion: https://www.zhihu.com/question/24786878

// Notes:
// Clip Coordinates
// The clip coordinate system is a homogeneous coordinate system in the graphics pipeline.
// In OpenGL, clip coordinates are positioned in the pipeline just after view coordinates and 
// just before normalized device coordinates.

// Objects are transformed via a projection transformation into clip coordinates, 
// at which point it may be efficiently determined on an object-by-object basis which portions of the objects 
// will be visible to the user. All coordinates may then be divided by the w component 
// (the fourth component in homogeneous coordinates) in what is called the perspective division. 
// This transformation puts the objects into normalized device coordinates (NDC).


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <windows.h>
#include <tchar.h>

typedef unsigned int IUINT32;

//=====================================================================
// Math Lib (Refer to D3D)
//=====================================================================
typedef struct { float m[4][4]; } matrix_t;
typedef struct { float x, y, z, w; } vector_t;
typedef vector_t point_t;

int CMID(int x, int min, int max) { return (x < min)? min : ((x > max)? max : x); }

// interpolation. t is [0,1]
float interp(float x1, float x2, float t) { return x1 + (x2 - x1) * t; }

// | v |
float vector_length(const vector_t *v) {
    float sq = v->x * v->x + v->y * v->y + v->z * v->z;
    return (float)sqrt(sq);
}

// z = x + y
void vector_add(vector_t *z, const vector_t *x, const vector_t *y) {
    z->x = x->x + y->x;
    z->y = x->y + y->y;
    z->z = x->z + y->z;
    z->w = 1.0;
}

// z = x - y
void vector_sub(vector_t *z, const vector_t *x, const vector_t *y) {
    z->x = x->x - y->x;
    z->y = x->y - y->y;
    z->z = x->z - y->z;
    z->w = 1.0;
}

// dot product
// https://en.wikipedia.org/wiki/Dot_product
float vector_dotproduct(const vector_t *x, const vector_t *y) {
    return x->x * y->x + x->y * y->y + x->z * y->z;
}

// cross product
// https://en.wikipedia.org/wiki/Cross_product
// Mnemonic: xyzzy
// Direction: right hand rule
void vector_crossproduct(vector_t *z, const vector_t *x, const vector_t *y) {
    float m1, m2, m3;
    m1 = x->y * y->z - x->z * y->y;
    m2 = x->z * y->x - x->x * y->z;
    m3 = x->x * y->y - x->y * y->x;
    z->x = m1;
    z->y = m2;
    z->z = m3;
    z->w = 1.0f;
}

// vector interpolation. t is [0,1]
void vector_interp(vector_t *z, const vector_t *x1, const vector_t *x2, float t) {
    z->x = interp(x1->x, x2->x, t);
    z->y = interp(x1->y, x2->y, t);
    z->z = interp(x1->z, x2->z, t);
    z->w = 1.0f;
}

// normalize
void vector_normalize(vector_t *v) {
    float length = vector_length(v);
    if (length != 0.0f) {
        float inv = 1.0f / length;
        v->x *= inv; 
        v->y *= inv;
        v->z *= inv;
    }
}

// c = a + b
void matrix_add(matrix_t *c, const matrix_t *a, const matrix_t *b) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
            c->m[i][j] = a->m[i][j] + b->m[i][j];
    }
}

// c = a - b
void matrix_sub(matrix_t *c, const matrix_t *a, const matrix_t *b) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
            c->m[i][j] = a->m[i][j] - b->m[i][j];
    }
}

// c = a * b
void matrix_mul(matrix_t *c, const matrix_t *a, const matrix_t *b) {
    matrix_t z;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            z.m[j][i] = (a->m[j][0] * b->m[0][i]) +
                        (a->m[j][1] * b->m[1][i]) +
                        (a->m[j][2] * b->m[2][i]) +
                        (a->m[j][3] * b->m[3][i]);
        }
    }
    c[0] = z; // directly struct copy. note: here is *not* a pointer to a local struct.
}

// c = a * f
void matrix_scale(matrix_t *c, const matrix_t *a, float f) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) 
            c->m[i][j] = a->m[i][j] * f;
    }
}

// y = x * m  --- vector * matrix
void matrix_apply(vector_t *y, const vector_t *x, const matrix_t *m) {
    float X = x->x, Y = x->y, Z = x->z, W = x->w;
    y->x = X * m->m[0][0] + Y * m->m[1][0] + Z * m->m[2][0] + W * m->m[3][0];
    y->y = X * m->m[0][1] + Y * m->m[1][1] + Z * m->m[2][1] + W * m->m[3][1];
    y->z = X * m->m[0][2] + Y * m->m[1][2] + Z * m->m[2][2] + W * m->m[3][2];
    y->w = X * m->m[0][3] + Y * m->m[1][3] + Z * m->m[2][3] + W * m->m[3][3];
}

void matrix_set_identity(matrix_t *m) {
    m->m[0][0] = m->m[1][1] = m->m[2][2] = m->m[3][3] = 1.0f; 
    m->m[0][1] = m->m[0][2] = m->m[0][3] = 0.0f;
    m->m[1][0] = m->m[1][2] = m->m[1][3] = 0.0f;
    m->m[2][0] = m->m[2][1] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;
}

void matrix_set_zero(matrix_t *m) {
    m->m[0][0] = m->m[0][1] = m->m[0][2] = m->m[0][3] = 0.0f;
    m->m[1][0] = m->m[1][1] = m->m[1][2] = m->m[1][3] = 0.0f;
    m->m[2][0] = m->m[2][1] = m->m[2][2] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = m->m[3][3] = 0.0f;
}

// translate matrix
void matrix_set_translate(matrix_t *m, float x, float y, float z) {
    matrix_set_identity(m);
    m->m[3][0] = x;
    m->m[3][1] = y;
    m->m[3][2] = z;
}

// scaling matrix
// https://en.wikipedia.org/wiki/Scaling_(geometry)
void matrix_set_scale(matrix_t *m, float x, float y, float z) {
    matrix_set_identity(m);
    m->m[0][0] = x;
    m->m[1][1] = y;
    m->m[2][2] = z;
}

// rotation matrix
// Refer to: 3D Math Primer for Graphics and Game Development 2nd Ed. Chapter 8 Rotation in Three Dimensions.
// @param[in]: Axis-Angle representation (x,y,z) and theta. (an axis of rotation and a rotation angle)
void matrix_set_rotate(matrix_t *m, float x, float y, float z, float theta) {
    // Transform Axis-Angle (theta, N) to Quaternions [w (x y z)]
    // [w (x y z)] = [cos(theta/2)  ( sin(theta/2)*Nx  sin(theta/2)*Ny  sin(theta/2)*Nz )]
    // Note: N is a unit vector
    float qsin = (float)sin(theta * 0.5f);
    float qcos = (float)cos(theta * 0.5f);
    vector_t vec = { x, y, z, 1.0f };
    float w = qcos;
    vector_normalize(&vec); // Make N as a unit vector
    x = vec.x * qsin;
    y = vec.y * qsin;
    z = vec.z * qsin;

    // Converting a Quaternion to a Matrix
    // See Section 8.7.3 in 3D Math Primer
    m->m[0][0] = 1 - 2 * y * y - 2 * z * z;
    m->m[1][0] = 2 * x * y - 2 * w * z;
    m->m[2][0] = 2 * x * z + 2 * w * y;
    m->m[0][1] = 2 * x * y + 2 * w * z;
    m->m[1][1] = 1 - 2 * x * x - 2 * z * z;
    m->m[2][1] = 2 * y * z - 2 * w * x;
    m->m[0][2] = 2 * x * z - 2 * w * y;
    m->m[1][2] = 2 * y * z + 2 * w * x;
    m->m[2][2] = 1 - 2 * x * x - 2 * y * y;
    m->m[0][3] = m->m[1][3] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;
    m->m[3][3] = 1.0f;
}

// Set camera
// gluLookAt(eyex, eyey, eyez, lookatx, lookaty, lookatz, upx, upy, upz)
// Detail introduction on camera transformation (world space -> camera space)
// https://blog.csdn.net/popy007/article/details/5120158
// Camera transformation can also be called view transformation (view space).
void matrix_set_lookat(matrix_t *m, const vector_t *eye, const vector_t *at, const vector_t *up) {
    // UVN Camera System
    vector_t xaxis, yaxis, zaxis;

    // eye: camera position (world space)
    // lookat: target position (world space)
    // N = lookat - eye
    // U = UP x N (UP is known)
    // V = N x U (crossproduct)
    vector_sub(&zaxis, at, eye);
    vector_normalize(&zaxis);
    vector_crossproduct(&xaxis, up, &zaxis);
    vector_normalize(&xaxis);
    vector_crossproduct(&yaxis, &zaxis, &xaxis);

    // Camera Transformation Matrix
    // Ux         Uy         Uz         -U*T
    // Vx         Vy         Vz         -V*T
    // Nx         Ny         Nz         -N*T
    // 0          0          0            1
    // T: Camera Translation
    m->m[0][0] = xaxis.x;
    m->m[1][0] = xaxis.y;
    m->m[2][0] = xaxis.z;
    m->m[3][0] = -vector_dotproduct(&xaxis, eye);

    m->m[0][1] = yaxis.x;
    m->m[1][1] = yaxis.y;
    m->m[2][1] = yaxis.z;
    m->m[3][1] = -vector_dotproduct(&yaxis, eye);

    m->m[0][2] = zaxis.x;
    m->m[1][2] = zaxis.y;
    m->m[2][2] = zaxis.z;
    m->m[3][2] = -vector_dotproduct(&zaxis, eye);

    m->m[0][3] = m->m[1][3] = m->m[2][3] = 0.0f;
    m->m[3][3] = 1.0f;
}


// D3DXMatrixPerspectiveFovLH
// Builds a perspective projection matrix based on a field of view.
// The projection matrix calculated will transform the objects into CVV space
// Detail introduction on projection transformation
// https://blog.csdn.net/popy007/article/details/1797121
void matrix_set_perspective(matrix_t *m, float fovy, float aspect, float zn, float zf) {
    // fovy (field of view on y-axis, in radians): PI * 0.5 (90 degree)
    // aspect: width / height
    // zn (near view-plane, z-axis): 1.0
    // zf (far view-plane, z-axis): 500.0

    // https://docs.microsoft.com/zh-cn/windows/desktop/direct3d9/d3dxmatrixperspectivefovlh
    // This function computes the returned matrix as shown:
    // xScale     0          0               0
    // 0        yScale       0               0
    // 0          0       zf/(zf-zn)         1
    // 0          0       -zn*zf/(zf-zn)     0
    // where:
    // yScale = cot(fovY/2)
    // xScale = yScale / aspect ratio

    // Other Reference: http://www.cnblogs.com/graphics/archive/2012/07/25/2582119.html
    // View Space (Camera) ---> Homogeneous Clipping Space
    // After apply this matrix, objects are in the clipping space. (w contains the "z" info in the view space)
    // We can clip the vertex not in:
    // -w <= x <= w
    // -w <= y <= w
    //  0 <= z <= w
    // refer to transform_check_cvv()
    
    float fax = 1.0f / (float)tan(fovy * 0.5f);
    matrix_set_zero(m);
    m->m[0][0] = (float)(fax / aspect);
    m->m[1][1] = (float)(fax);
    m->m[2][2] = zf / (zf - zn);
    m->m[3][2] = - zn * zf / (zf - zn);
    m->m[2][3] = 1;
}

//=====================================================================
// Coordinate Transform
//=====================================================================
typedef struct { 
    matrix_t world;         // World Coord
    matrix_t view;          // Camera Coord
    matrix_t projection;    // Projection Coord
    matrix_t transform;     // transform = world * view * projection
    float w, h;             // Screen Width, Height
} transform_t;

// Calculate transform = world * view * projection
void transform_update(transform_t *ts) {
    matrix_t m;
    matrix_mul(&m, &ts->world, &ts->view);
    matrix_mul(&ts->transform, &m, &ts->projection);
}

void transform_init(transform_t *ts, int width, int height) {
    float aspect = (float)width / ((float)height);
    matrix_set_identity(&ts->world);
    matrix_set_identity(&ts->view); // view matrix will be reinit in camera_at_zero()
    matrix_set_perspective(&ts->projection, 3.1415926f * 0.5f, aspect, 1.0f, 500.0f);
    ts->w = (float)width;
    ts->h = (float)height;
    transform_update(ts);
}

// project on vertex "x"
void transform_apply(const transform_t *ts, vector_t *y, const vector_t *x) {
    matrix_apply(y, x, &ts->transform);
}

// Clip in CVV (homogeneous coordinates, refer to matrix_set_perspective())
// -w <= x <= w
// -w <= y <= w
//  0 <= z <= w
int transform_check_cvv(const vector_t *v) {
    float w = v->w;
    int check = 0;
    if (v->z < 0.0f) check |= 1;
    if (v->z >  w) check |= 2;
    if (v->x < -w) check |= 4;
    if (v->x >  w) check |= 8;
    if (v->y < -w) check |= 16;
    if (v->y >  w) check |= 32;
    return check;
}

// Normalization. Get Screen Coordinates.
// @param[in]  x: points in CVV space
// @param[out] y: points in Screen space
void transform_homogenize(const transform_t *ts, vector_t *y, const vector_t *x) {
    // -w <= x.x <= w
    // -w <= x.y <= w
    //  0 <= x.z <= w
    float rhw = 1.0f / x->w;
    y->x = (x->x * rhw + 1.0f) * ts->w/*Screen Width*/ * 0.5f;  // 0 <= y.x <= Screen Width  (Direction left -> right)
    y->y = (1.0f - x->y * rhw) * ts->h/*Screen Height*/ * 0.5f; // 0 <= y.y <= Screen Height (Direction top -> down)
    y->z = x->z * rhw;                                          // 0 <= y.z <= 1
    y->w = 1.0f;
}

//=====================================================================
// Geometry Calc: Vertex, Scanline, Edge, Rectangle, Steps
//=====================================================================
typedef struct { float r, g, b; } color_t;
typedef struct { float u, v; } texcoord_t;
typedef struct { point_t pos; texcoord_t tc; color_t color; float rhw; } vertex_t;

typedef struct { vertex_t v, v1, v2; } edge_t; // v is the interpolation point. v1/v2 is the two endpoint of the line.
typedef struct { float top, bottom; edge_t left, right; } trapezoid_t;
typedef struct { vertex_t v /*start point, no rounding*/, step; int x/*start x (rounding)*/, y/*start y*/, w/*width*/; } scanline_t;

// http://www.skywind.me/blog/archives/1828
// rhw = 1/w (w is z, need double confirm)
// The rhw applied here is to do the linear interpolation in Screen space,
// and get the correct same effect as do the linear interpolation in the view space.
void vertex_rhw_init(vertex_t *v) {
    float rhw = 1.0f / v->pos.w;
    v->rhw = rhw;
    
    // https://blog.csdn.net/popy007/article/details/5570803
    // u/z, v/z is linear with x', y' (x', y' is the point coordinates on the projection plane)
    // The same relation applies to the color and normal.
    v->tc.u *= rhw;
    v->tc.v *= rhw;
    v->color.r *= rhw;
    v->color.g *= rhw;
    v->color.b *= rhw;
}

void vertex_interp(vertex_t *y, const vertex_t *x1, const vertex_t *x2, float t) {
    vector_interp(&y->pos, &x1->pos, &x2->pos, t);
    y->tc.u = interp(x1->tc.u, x2->tc.u, t);
    y->tc.v = interp(x1->tc.v, x2->tc.v, t);
    y->color.r = interp(x1->color.r, x2->color.r, t);
    y->color.g = interp(x1->color.g, x2->color.g, t);
    y->color.b = interp(x1->color.b, x2->color.b, t);
    y->rhw = interp(x1->rhw, x2->rhw, t);
}

void vertex_division(vertex_t *y, const vertex_t *x1, const vertex_t *x2, float w) {
    float inv = 1.0f / w; // w is width
    y->pos.x = (x2->pos.x - x1->pos.x) * inv;
    y->pos.y = (x2->pos.y - x1->pos.y) * inv;
    y->pos.z = (x2->pos.z - x1->pos.z) * inv;
    y->pos.w = (x2->pos.w - x1->pos.w) * inv;
    y->tc.u = (x2->tc.u - x1->tc.u) * inv;
    y->tc.v = (x2->tc.v - x1->tc.v) * inv;
    y->color.r = (x2->color.r - x1->color.r) * inv;
    y->color.g = (x2->color.g - x1->color.g) * inv;
    y->color.b = (x2->color.b - x1->color.b) * inv;
    y->rhw = (x2->rhw - x1->rhw) * inv;
}

void vertex_add(vertex_t *y, const vertex_t *x) {
    y->pos.x += x->pos.x;
    y->pos.y += x->pos.y;
    y->pos.z += x->pos.z;
    y->pos.w += x->pos.w;
    y->rhw += x->rhw;
    y->tc.u += x->tc.u;
    y->tc.v += x->tc.v;
    y->color.r += x->color.r;
    y->color.g += x->color.g;
    y->color.b += x->color.b;
}

// Divide one triangle into 0-2 trapezoid(up/down triangles described in trapezoid term)
// @return: number of valid trapezoid
int trapezoid_init_triangle(trapezoid_t *trap, const vertex_t *p1, const vertex_t *p2, const vertex_t *p3) {
    const vertex_t *p;
    float k, x;

    // Note: Here p1/p2/p3 are in Screen space. 
    // 0 <= p.x <= Screen Width  (Direction left -> right)
    // 0 <= p.y <= Screen Height (Direction top -> down)
    // 0 <= p.z <= 1

    // p1 is the top vertex
    if (p1->pos.y > p2->pos.y) p = p1, p1 = p2, p2 = p;
    if (p1->pos.y > p3->pos.y) p = p1, p1 = p3, p3 = p;

    // p3 is the bottom vertex
    if (p2->pos.y > p3->pos.y) p = p2, p2 = p3, p3 = p;
    
    // p1,p2,p3 forms a line, return 0
    if (p1->pos.y == p2->pos.y && p1->pos.y == p3->pos.y) return 0;
    if (p1->pos.x == p2->pos.x && p1->pos.x == p3->pos.x) return 0;

    // triangle down case (flat triangle)
    if (p1->pos.y == p2->pos.y) {
        // p1 is on the left, p2 is on the right
        if (p1->pos.x > p2->pos.x) p = p1, p1 = p2, p2 = p;

        trap[0].top = p1->pos.y;
        trap[0].bottom = p3->pos.y;
        trap[0].left.v1 = *p1;
        trap[0].left.v2 = *p3;
        trap[0].right.v1 = *p2;
        trap[0].right.v2 = *p3;
        return (trap[0].top < trap[0].bottom)? 1 : 0; // Actually, the compare is not needed here.
    }

    // triangle up case (flat triangle)
    if (p2->pos.y == p3->pos.y) {
        // p2 is on the left, p3 is on the right
        if (p2->pos.x > p3->pos.x) p = p2, p2 = p3, p3 = p;
        
        trap[0].top = p1->pos.y;
        trap[0].bottom = p3->pos.y;
        trap[0].left.v1 = *p1;
        trap[0].left.v2 = *p2;
        trap[0].right.v1 = *p1;
        trap[0].right.v2 = *p3;
        return (trap[0].top < trap[0].bottom)? 1 : 0; // Actually, the compare is not needed here.
    }

    // arbitrary triangle (can be divided into two up/down flat triangles)
    trap[0].top = p1->pos.y; // up triangle
    trap[0].bottom = p2->pos.y; // up triangle
    trap[1].top = p2->pos.y; // down triangle
    trap[1].bottom = p3->pos.y; // down triangle

    // determine p2 is on the left or right of the triangle
    k = (p3->pos.y - p1->pos.y) / (p2->pos.y - p1->pos.y);
    x = p1->pos.x + (p2->pos.x - p1->pos.x) * k;

    // If we know two points on a line (x1, y1), (x2, y2), we have line formula,
    // (y-y1) / (y2-y1) = (x-x1) / (x2-x1)
    // x = x1 + (y-y1) * (x2-x1) / (y2-y1)
    
    // line formula for line(p1-p2)
    // x = p1->pos.x + (y - p1->pos.y) * (p2->pos.x - p1->pos.x) / (p2->pos.y - p1->pos.y)
    // make y = p3->pos.y
    // x = p1->pos.x + (p3->pos.y - p1->pos.y) * (p2->pos.x - p1->pos.x) / (p2->pos.y - p1->pos.y)
    
    // On the line(p1-p2) with (x, p3->pos.y). If x <= p3->pos.x, then the triangle is towards left.
    // Otherwise if x > p3->pos.x, then the triangle is towards right.
    if (x <= p3->pos.x) {
        // triangle left
        trap[0].left.v1 = *p1;
        trap[0].left.v2 = *p2;
        trap[0].right.v1 = *p1;
        trap[0].right.v2 = *p3;
        trap[1].left.v1 = *p2;
        trap[1].left.v2 = *p3;
        trap[1].right.v1 = *p1;
        trap[1].right.v2 = *p3;
    } else {
        // triangle right
        trap[0].left.v1 = *p1;
        trap[0].left.v2 = *p3;
        trap[0].right.v1 = *p1;
        trap[0].right.v2 = *p2;
        trap[1].left.v1 = *p1;
        trap[1].left.v2 = *p3;
        trap[1].right.v1 = *p2;
        trap[1].right.v2 = *p3;
    }

    return 2;
}

// Get edge vertex with the y-coord specified
void trapezoid_edge_interp(trapezoid_t *trap, float y) {
    float s1 = trap->left.v2.pos.y - trap->left.v1.pos.y;
    float s2 = trap->right.v2.pos.y - trap->right.v1.pos.y;
    float t1 = (y - trap->left.v1.pos.y) / s1; // interp percentage
    float t2 = (y - trap->right.v1.pos.y) / s2; // interp percentage
    vertex_interp(&trap->left.v /* OUT */, &trap->left.v1, &trap->left.v2, t1);
    vertex_interp(&trap->right.v /* OUT */, &trap->right.v1, &trap->right.v2, t2);
}

// Get scanline start/step based on the edge vertex in trap
void trapezoid_init_scan_line(const trapezoid_t *trap, scanline_t *scanline, int y) {
    float width = trap->right.v.pos.x - trap->left.v.pos.x;
    scanline->x = (int)(trap->left.v.pos.x + 0.5f); // rounding
    scanline->w = (int)(trap->right.v.pos.x + 0.5f) - scanline->x;
    scanline->y = y;
    scanline->v = trap->left.v;
    if (trap->left.v.pos.x >= trap->right.v.pos.x) scanline->w = 0;

    // Get step (all divided by width to get percentage). Note: step is a vertex_t struct
    vertex_division(&scanline->step, &trap->left.v, &trap->right.v, width);
}


//=====================================================================
// Render Device
//=====================================================================
typedef struct {
    transform_t transform;      // Used for coordinator transform
    int width;                  // Screen width (800)
    int height;                 // Screen height (600)
    IUINT32 **framebuffer;      // framebuffer[y] (y line)
    float **zbuffer;            // zbuffer[y] (y line)
    IUINT32 **texture;          // texture: line index same as framebuffer/zbuffer
    int tex_width;              // texture width
    int tex_height;             // texture height
    float max_u;                // max u: tex_width - 1
    float max_v;                // max v: tex_height - 1
    int render_state;           // render state
    IUINT32 background;         // background color
    IUINT32 foreground;         // wireframe color
} device_t;

#define RENDER_STATE_WIREFRAME      1   // render wireframe
#define RENDER_STATE_TEXTURE        2   // render texture
#define RENDER_STATE_COLOR          4   // render color

// width 800, height 600
void device_init(device_t *device, int width, int height, void *fb) {
    int need = sizeof(void*) * (height * 2 + 1024) + width * height * 8;

    // 64 is for init texture pointers. Currently only init 2 pointers.
    // texture pointers will recalculated in init_texture(). So here is just an unimportant minimum init.
    char *ptr = (char*)malloc(need + 64);
    char *framebuf, *zbuf;
    int j;
    assert(ptr);

    // device->framebuffer ----->     | sizeof(void*) * height | array of pointers (height)
    //                                |                        |
    //                                |------------------------|
    // device->zbuffer     ----->     | sizeof(void*) * height | array of pointers
    //                                |                        |
    //                                |------------------------|
    // device->texture     ----->     | sizeof(void*) * 1024   | array of pointers
    //                                |                        |
    //                                |------------------------|
    // device->framebuffer[0..height] | width * height * 4     | 4 bytes one pixel
    //                                |                        |
    //                                |------------------------|  
    // device->zbuffer[0..height]     | width * height * 4     | 4 bytes one pixel
    //                                |                        |
    //                                |------------------------|
    // device->texture[0]             | 16 bytes               |
    //                                |                        |
    //                                |------------------------|
    // device->texture[1]             | 16 bytes               |
    //                                |                        |
    //                                |------------------------|
    //                                | 64 - 16 * 2            |
    //                                |                        |
    //                                |------------------------|
    device->framebuffer = (IUINT32**)ptr;
    device->zbuffer = (float**)(ptr + sizeof(void*) * height);
    ptr += sizeof(void*) * height * 2;
    device->texture = (IUINT32**)ptr;
    ptr += sizeof(void*) * 1024;
    framebuf = (char*)ptr;
    zbuf = (char*)ptr + width * height * 4;
    ptr += width * height * 8;
    if (fb != NULL) framebuf = (char*)fb; // if fb is not NULL, use fb location specified by the parameter.
    for (j = 0; j < height; j++) {
        device->framebuffer[j] = (IUINT32*)(framebuf + width * 4 * j);
        device->zbuffer[j] = (float*)(zbuf + width * 4 * j);
    }
    device->texture[0] = (IUINT32*)ptr; // init texture pointer 0
    device->texture[1] = (IUINT32*)(ptr + 16); // init texture pointer 1
    memset(device->texture[0], 0, 64);
    device->tex_width = 2; // 2*2 texture, will be init again later
    device->tex_height = 2; // 2*2 texture, will be init again later
    device->max_u = 1.0f; // tex_width - 1
    device->max_v = 1.0f; // tex_height - 1
    device->width = width;
    device->height = height;
    device->background = 0xc0c0c0;
    device->foreground = 0; // black
    transform_init(&device->transform, width, height);
    device->render_state = RENDER_STATE_WIREFRAME;
}

// destory device
void device_destroy(device_t *device) {
    if (device->framebuffer) 
        free(device->framebuffer);
    device->framebuffer = NULL;
    device->zbuffer = NULL;
    device->texture = NULL;
}

// pitch: 256*4 w: 256 h: 256
void device_set_texture(device_t *device, void *bits, long pitch, int w, int h) {
    char *ptr = (char*)bits;
    int j;
    assert(w <= 1024 && h <= 1024);

    // 256 lines of texture
    for (j = 0; j < h; ptr += pitch, j++) // recalc every texture pointer (1024 bytes one line)
        device->texture[j] = (IUINT32*)ptr;
    device->tex_width = w;
    device->tex_height = h;
    device->max_u = (float)(w - 1);
    device->max_v = (float)(h - 1);
}

// clear framebuffer and zbuffer
void device_clear(device_t *device, int mode) {
    int y, x, height = device->height;
    for (y = 0; y < device->height; y++) {
        IUINT32 *dst = device->framebuffer[y]; // y line
        IUINT32 cc = (height - 1 - y) * 230 / (height - 1);
        cc = (cc << 16) | (cc << 8) | cc; // It's a color from almost white to black (top to bottom)
        if (mode == 0) cc = device->background;
        for (x = device->width; x > 0; dst++, x--) dst[0] = cc; // fill y line
    }
    for (y = 0; y < device->height; y++) {
        float *dst = device->zbuffer[y]; // y line
        for (x = device->width; x > 0; dst++, x--) dst[0] = 0.0f; // fill y line
    }
}

// draw a point
void device_pixel(device_t *device, int x, int y, IUINT32 color) {
    if (((IUINT32)x) < (IUINT32)device->width && ((IUINT32)y) < (IUINT32)device->height) {
        device->framebuffer[y][x] = color;
    }
}

void device_draw_line(device_t *device, int x1, int y1, int x2, int y2, IUINT32 c) {
    int x, y, rem = 0;
    if (x1 == x2 && y1 == y2) {
        device_pixel(device, x1, y1, c);
    } else if (x1 == x2) {
        int inc = (y1 <= y2)? 1 : -1;
        for (y = y1; y != y2; y += inc) device_pixel(device, x1, y, c);
        device_pixel(device, x2, y2, c);
    } else if (y1 == y2) {
        int inc = (x1 <= x2)? 1 : -1;
        for (x = x1; x != x2; x += inc) device_pixel(device, x, y1, c);
        device_pixel(device, x2, y2, c);
    } else {
        // Basic Bresenham algorithm, no optimization.
        // Bresenham should only includes ops like add/sub, so it's fast.
        int dx = (x1 < x2)? x2 - x1 : x1 - x2;
        int dy = (y1 < y2)? y2 - y1 : y1 - y2;
        if (dx >= dy) {
            // Slope is closer to x-axis, so use dx as increasement. Otherwise, line continuous will be broken.
            if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y; // Swap x1/y1 and x2/y2
            for (x = x1, y = y1; x <= x2; x++) {
                device_pixel(device, x, y, c);
                rem += dy; // rem is the accumulated error
                if (rem >= dx) {
                    // when accumulated error >= dx
                    rem -= dx;
                    y += (y2 >= y1)? 1 : -1; // add 1 increasement to y
                    device_pixel(device, x, y, c); // draw extra one pixel when y changed.
                }
            }
            device_pixel(device, x2, y2, c);
        } else {
            // y major branch
            if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
            for (x = x1, y = y1; y <= y2; y++) {
                device_pixel(device, x, y, c);
                rem += dx;
                if (rem >= dy) {
                    rem -= dy;
                    x += (x2 >= x1)? 1 : -1;
                    device_pixel(device, x, y, c);
                }
            }
            device_pixel(device, x2, y2, c);
        }
    }
}

// read texture on coord (u,v)
// @param[in] u: range [0,1]
// @param[in] v: range [0,1]
IUINT32 device_texture_read(const device_t *device, float u, float v) {
    int x, y;
    u = u * device->max_u; // max_u == tex_width - 1
    v = v * device->max_v; // max_v == tex_height - 1
    x = (int)(u + 0.5f); // rounding
    y = (int)(v + 0.5f); // rounding
    x = CMID(x, 0, device->tex_width - 1);
    y = CMID(y, 0, device->tex_height - 1);
    return device->texture[y][x];
    }


//=====================================================================
// Render Implementation
//=====================================================================
void device_draw_scanline(device_t *device, scanline_t *scanline) {
    IUINT32 *framebuffer = device->framebuffer[scanline->y];
    float *zbuffer = device->zbuffer[scanline->y];
    int x = scanline->x;
    int w = scanline->w;
    int width = device->width;
    int render_state = device->render_state;
    for (; w > 0; x++, w--) {
        if (x >= 0 && x < width) {
            float rhw = scanline->v.rhw; // rhw = 1/w (w is z)
            if (rhw >= zbuffer[x]) { // Passed z test. zbuffer saves 1/w (1/z)
                float w = 1.0f / rhw;
                zbuffer[x] = rhw; // save new z
                if (render_state & RENDER_STATE_COLOR) {
                    // Interpolation was done in Screen space in trapezoid_edge_interp()
                    // see comments in vertex_rhw_init() and 
                    // https://blog.csdn.net/popy007/article/details/5570803
                    // Here we get View space r/g/b by applying w
                    float r = scanline->v.color.r * w;
                    float g = scanline->v.color.g * w;
                    float b = scanline->v.color.b * w;
                    int R = (int)(r * 255.0f);
                    int G = (int)(g * 255.0f);
                    int B = (int)(b * 255.0f);
                    R = CMID(R, 0, 255);
                    G = CMID(G, 0, 255);
                    B = CMID(B, 0, 255);
                    framebuffer[x] = (R << 16) | (G << 8) | (B);
                }
                if (render_state & RENDER_STATE_TEXTURE) {
                    // Same operation as Color. See comments above.
                    float u = scanline->v.tc.u * w;
                    float v = scanline->v.tc.v * w;
                    IUINT32 cc = device_texture_read(device, u, v);
                    framebuffer[x] = cc;
                }
            }
        }
        vertex_add(&scanline->v, &scanline->step);
        if (x >= width) break;
    }
}

// main render function
void device_render_trap(device_t *device, trapezoid_t *trap) {
    scanline_t scanline;
    int j, top, bottom;
    top = (int)(trap->top + 0.5f); // round off to the nearest integer
    bottom = (int)(trap->bottom + 0.5f); // round off to the nearest integer
    for (j = top; j < bottom; j++) {
        if (j >= 0 && j < device->height) {
            trapezoid_edge_interp(trap, (float)j + 0.5f); // 0.5f means interp at the mid of two pixels
            trapezoid_init_scan_line(trap, &scanline, j);
            device_draw_scanline(device, &scanline);
        }
        if (j >= device->height) break;
    }
}

// render triangle based on "render_state"
void device_draw_primitive(device_t *device, const vertex_t *v1, 
    const vertex_t *v2, const vertex_t *v3) {
    point_t p1, p2, p3; // points in Screen space
    point_t c1, c2, c3; // points in CVV space
    int render_state = device->render_state;

    // Transform
    transform_apply(&device->transform, &c1/*OUT*/, &v1->pos);
    transform_apply(&device->transform, &c2/*OUT*/, &v2->pos);
    transform_apply(&device->transform, &c3/*OUT*/, &v3->pos);

    // Notes:
    // After camera transform, objects will be in the camera space.
    // After perspective projection transform, object will be in the CVV space.
    // Objects can be clipped in the camera space, but it's difficult since the frustum is irregular.
    // Usually clipping happen in CVV (Canonical View Volume), CVV is cube with x, y, z in the range [-1,1]

    // Notes:
    // Use perspective transform matrix to turn objects into the CVV space (also called clipping space?).
    // After clipping in CVV, then apply perspective divide.
    
    // Notes:
    // Divided by the w component (the fourth component in homogeneous coordinates) in what is called the perspective division. 
    // This transformation puts the objects into normalized device coordinates (NDC).

    // Clipping. Here use the simplest approach. Clip if there're points outside of CVV.
    // To be improved below:
    // 1. Judge how many points are in CVV and the intersections with the CVV plane.
    // 2. Then, generate several new triangles completely in CVV based on the original one (intersect with CVV).
    if (transform_check_cvv(&c1) != 0) return;
    if (transform_check_cvv(&c2) != 0) return;
    if (transform_check_cvv(&c3) != 0) return;

    // Normalization. Get p1/p2/p3 in Screen space
    transform_homogenize(&device->transform, &p1, &c1);
    transform_homogenize(&device->transform, &p2, &c2);
    transform_homogenize(&device->transform, &p3, &c3);

    // Texture or Color render
    if (render_state & (RENDER_STATE_TEXTURE | RENDER_STATE_COLOR)) {
        vertex_t t1 = *v1, t2 = *v2, t3 = *v3;
        trapezoid_t traps[2];
        int n;

        // p1/p2/p3 Screen space points
        t1.pos = p1; 
        t2.pos = p2;
        t3.pos = p3;
        // c1/c2/c3 CVV space points, w contains the "z" info in the view space.
        // Note: w is not equal to z, but linear related? We can take w as another form of z? (TODO: Prove?)
        t1.pos.w = c1.w; 
        t2.pos.w = c2.w;
        t3.pos.w = c3.w;

        vertex_rhw_init(&t1); // Initialize rhw
        vertex_rhw_init(&t2); // Initialize rhw
        vertex_rhw_init(&t3); // Initialize rhw

        // Divide one triangle into 0-2 trapezoid(up/down triangles described in trapezoid term)
        // https://blog.csdn.net/cppyin/article/details/6232453
        n = trapezoid_init_triangle(traps, &t1, &t2, &t3);

        if (n >= 1) device_render_trap(device, &traps[0]);
        if (n >= 2) device_render_trap(device, &traps[1]);
    }

    if (render_state & RENDER_STATE_WIREFRAME) {
        device_draw_line(device, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, device->foreground); // foreground == 0 (Black)
        device_draw_line(device, (int)p1.x, (int)p1.y, (int)p3.x, (int)p3.y, device->foreground); // foreground == 0 (Black)
        device_draw_line(device, (int)p3.x, (int)p3.y, (int)p2.x, (int)p2.y, device->foreground); // foreground == 0 (Black)
    }
}

//=====================================================================
// Win32 window and render: Provide "device" a DibSection FB
//=====================================================================
int screen_w, screen_h, screen_exit = 0;
int screen_mx = 0, screen_my = 0, screen_mb = 0;
int screen_keys[512];              // current keyboard keydown status
static HWND screen_handle = NULL;  // Main window HWND
static HDC screen_dc = NULL;       // Corresponding HDC
static HBITMAP screen_hb = NULL;   // DIB
static HBITMAP screen_ob = NULL;   // Old BITMAP
unsigned char *screen_fb = NULL;   // frame buffer
long screen_pitch = 0;

int screen_init(int w, int h, const TCHAR *title);
int screen_close(void);
void screen_dispatch(void); // Handle Message
void screen_update(void); // Display FrameBuffer

// win32 event handler
static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);

#ifdef _MSC_VER
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#endif

// Init window and set title
int screen_init(int w, int h, const TCHAR *title) {
    WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)screen_events, 0, 0, 0, 
        NULL, NULL, NULL, NULL, _T("SCREEN3.1415926") };
    BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB, 
        w * h * 4, 0, 0, 0, 0 }  };
    RECT rect = { 0, 0, w, h };
    int wx, wy, sx, sy;
    LPVOID ptr;
    HDC hDC;

    screen_close();

    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    if (!RegisterClass(&wc)) return -1;

    screen_handle = CreateWindow(_T("SCREEN3.1415926"), title,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
    if (screen_handle == NULL) return -2;

    screen_exit = 0;
    hDC = GetDC(screen_handle);
    screen_dc = CreateCompatibleDC(hDC);
    ReleaseDC(screen_handle, hDC);

    screen_hb = CreateDIBSection(screen_dc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
    if (screen_hb == NULL) return -3;

    screen_ob = (HBITMAP)SelectObject(screen_dc, screen_hb);
    screen_fb = (unsigned char*)ptr;
    screen_w = w;
    screen_h = h;
    screen_pitch = w * 4;

    AdjustWindowRect(&rect, GetWindowLong(screen_handle, GWL_STYLE), 0);
    wx = rect.right - rect.left;
    wy = rect.bottom - rect.top;
    sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
    sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
    if (sy < 0) sy = 0;
    SetWindowPos(screen_handle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
    SetForegroundWindow(screen_handle);

    ShowWindow(screen_handle, SW_NORMAL);
    screen_dispatch();

    memset(screen_keys, 0, sizeof(int) * 512);
    memset(screen_fb, 0, w * h * 4);

    return 0;
}

int screen_close(void) {
    if (screen_dc) {
        if (screen_ob) { 
            SelectObject(screen_dc, screen_ob); 
            screen_ob = NULL; 
        }
        DeleteDC(screen_dc);
        screen_dc = NULL;
    }
    if (screen_hb) { 
        DeleteObject(screen_hb); 
        screen_hb = NULL; 
    }
    if (screen_handle) { 
        CloseWindow(screen_handle); 
        screen_handle = NULL; 
    }
    return 0;
}

static LRESULT screen_events(HWND hWnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CLOSE: screen_exit = 1; break;
    case WM_KEYDOWN: screen_keys[wParam & 511] = 1; break;
    case WM_KEYUP: screen_keys[wParam & 511] = 0; break;
    default: return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

void screen_dispatch(void) {
    MSG msg;
    while (1) {
        if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
        if (!GetMessage(&msg, NULL, 0, 0)) break;
        DispatchMessage(&msg);
    }
}

void screen_update(void) {
    HDC hDC = GetDC(screen_handle);
    BitBlt(hDC, 0, 0, screen_w, screen_h, screen_dc, 0, 0, SRCCOPY);
    ReleaseDC(screen_handle, hDC);
    screen_dispatch();
}


//=====================================================================
// main
//=====================================================================
vertex_t mesh[8] = {
    // {point_t (x,y,z,w)}, {texcoord_t (u,v)}, {color_t (r,g,b)},      {float rhw}
    {  {  1, -1,  1, 1 },   { 0, 0 },           { 1.0f, 0.2f, 0.2f },   1 },
    {  { -1, -1,  1, 1 },   { 0, 1 },           { 0.2f, 1.0f, 0.2f },   1 },
    {  { -1,  1,  1, 1 },   { 1, 1 },           { 0.2f, 0.2f, 1.0f },   1 },
    {  {  1,  1,  1, 1 },   { 1, 0 },           { 1.0f, 0.2f, 1.0f },   1 },
    {  {  1, -1, -1, 1 },   { 0, 0 },           { 1.0f, 1.0f, 0.2f },   1 },
    {  { -1, -1, -1, 1 },   { 0, 1 },           { 0.2f, 1.0f, 1.0f },   1 },
    {  { -1,  1, -1, 1 },   { 1, 1 },           { 1.0f, 0.3f, 0.3f },   1 },
    {  {  1,  1, -1, 1 },   { 1, 0 },           { 0.2f, 1.0f, 0.3f },   1 },
};


void draw_plane(device_t *device, int a, int b, int c, int d) {
    vertex_t p1 = mesh[a], p2 = mesh[b], p3 = mesh[c], p4 = mesh[d];
    p1.tc.u = 0, p1.tc.v = 0, p2.tc.u = 0, p2.tc.v = 1;
    p3.tc.u = 1, p3.tc.v = 1, p4.tc.u = 1, p4.tc.v = 0;
    device_draw_primitive(device, &p1, &p2, &p3);
    device_draw_primitive(device, &p3, &p4, &p1);
}

void draw_box(device_t *device, float theta) {
    matrix_t m;
    matrix_set_rotate(&m, -1, -0.5, 1, theta);
    device->transform.world = m;
    transform_update(&device->transform);
    draw_plane(device, 0, 1, 2, 3);
    draw_plane(device, 4, 5, 6, 7);
    draw_plane(device, 0, 4, 5, 1);
    draw_plane(device, 1, 5, 6, 2);
    draw_plane(device, 2, 6, 7, 3);
    draw_plane(device, 3, 7, 4, 0);
}

// camera look at zero positon
// x: 3 y: 0 z: 0
// camera at "eye" position (x,y,z,1)
// target at "at" postion (0,0,0,1)
void camera_at_zero(device_t *device, float x, float y, float z) {
    point_t eye = { x, y, z, 1 }, at = { 0, 0, 0, 1 }, up = { 0, 0, 1, 1 };
    matrix_set_lookat(&device->transform.view, &eye, &at, &up);
    transform_update(&device->transform);
}

void init_texture(device_t *device) {
    static IUINT32 texture[256][256];
    int i, j;
    for (j = 0; j < 256; j++) {
        for (i = 0; i < 256; i++) {
            int x = i / 32, y = j / 32;
            texture[j][i] = ((x + y) & 1)? 0xffffff : 0x3fbcef;
        }
    }
    device_set_texture(device, texture, 256 * 4, 256, 256); // init device->texture pointers to texture[256][256]
}

int main(void)
{
    device_t device;
    int states[] = { RENDER_STATE_TEXTURE, RENDER_STATE_COLOR, RENDER_STATE_WIREFRAME };
    int indicator = 0;
    int kbhit = 0;
    float alpha = 1;
    float pos = 3.5;

    TCHAR *title = _T("Mini3d (software render tutorial) - ")
        _T("Left/Right: rotation, Up/Down: forward/backward, Space: switch state");

    if (screen_init(800, 600, title)) 
        return -1;

    device_init(&device, 800, 600, screen_fb);
    camera_at_zero(&device, 3, 0, 0);

    init_texture(&device);
    device.render_state = RENDER_STATE_TEXTURE;

    while (screen_exit == 0 && screen_keys[VK_ESCAPE] == 0) {
        screen_dispatch();
        device_clear(&device, 1);
        camera_at_zero(&device, pos, 0, 0);
        
        if (screen_keys[VK_UP]) pos -= 0.01f;
        if (screen_keys[VK_DOWN]) pos += 0.01f;
        if (screen_keys[VK_LEFT]) alpha += 0.01f;
        if (screen_keys[VK_RIGHT]) alpha -= 0.01f;

        if (screen_keys[VK_SPACE]) {
            if (kbhit == 0) {
                kbhit = 1;
                if (++indicator >= 3) indicator = 0;
                device.render_state = states[indicator];
            }
        } else {
            kbhit = 0;
        }

        draw_box(&device, alpha);
        screen_update();
        Sleep(1);
    }
    return 0;
}
