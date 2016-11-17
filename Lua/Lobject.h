/*
** Common type for all collectable objects
*/
typedef struct GCObject GCObject;

/*
** Common Header for all collectable objects (in macro form, to be
** included in other objects)
*/
#define CommonHeader    GCObject *next; lu_byte tt; lu_byte marked

/*
** Union of all Lua values
*/
typedef union Value {
    GCObject *gc;
    void *p;            /* light userdata */
    int b;              /* booleans */
    lua_CFunction f;    /* light C functions */
    lua_Integer i;      /* integer numbers */
    lua_Number n;       /* float numbers */
} Value;




