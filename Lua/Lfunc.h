/*
** Upvalues for Lua closures
*/
struct UpVal {
    TValue *v;  /* points to stack or to its own value */
    lu_mem refcount;  /* reference counter */
    union {
        struct { /* when open */
            Upval *next;  /* linked list */
            int touched;  /* mark to avoid cycles with dead threads */
        } open;
        TValue value;  /* the value (when closed) */
    } u;
};

#define upisopen(up)    ((up)->v != &(up)->u.value)

