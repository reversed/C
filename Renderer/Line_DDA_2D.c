typedef struct { float x, y; } vector_t;
typedef vector_t point_t;
typedef struct { float r, g, b, a; } color_t;

void DrawLineDDA2d(point_t v1, point_t v2, color_t c)
{
    glColor4d(c.r, c.g, c.b, c.a);
    float x1 = v1.x;
    float y1 = v1.y;
    float x2 = v2.x;
    float y2 = v2.y;
    float length = __max(abs(x1 - x2), abs(y1 - y2));
    float dx = (x2 - x1) / length;
    float dy = (y2 - y1) / length;
    float x = x1;
    float y = y1;

    int i = 0;
    while (i <= length)
    {
        glVertex2i((int)x, (int)y);
        x += dx;
        y += dy;
        i++;
    }
}


