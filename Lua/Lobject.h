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

#define TValuefields    Value value_; int tt_

// tvk can be used to get nk.value_
typedef union TKey {
    struct {
        TValuefield;
        int next;   /* for chaining (offset for next node) */
    } nk;
    TValue tvk;
} TKey;

#define setnodekey(L,key,obj) \
    { TKey *k_ = (key); const TValue *io_ = (obj); \
      k_->nk.value = io_->value; k_->nk.tt_ = io_->tt_; \
      (void)L; checkliveness(L,io_); }

typedef struct Node {
    TValue i_val;
    TKey i_key;
} Node;

typedef struct Table {
    CommonHeader;
    lu_byte flags;  /* 1<<p means tagmethod(p) is not present */
    lu_byte lsizenode;  /* log2 of size of 'node' array */
    unsigned int sizearray; /* size of 'array' array */
    TValue *array;  /* array part */
    Node *node;
    Node *lastfree  /* any free position is before this position */
    struct Table *metatable;
    GCObject *gclist;
} Table;

/*
** 'module' operation for hashing (size is always a power of 2)
*/
#define lmod(s, size) \
    (check_exp((size & (size-1)) == 0, (cast(int, s & ((size)-1)))))


#define twoto(x)    (1<<(x))
#define sizenode(t) (twoto((t)->lsizenode))



















