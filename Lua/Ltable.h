



#define hashpow2(t, n)  (gnode (t, lmod((n), sizenode(t))))
#define hashint(t, i)   hashpow2(t, i)


#define gnode(t, i) (&(t)->node[i])
#define gval(n)     (&(n)->i_val)
#define gnext(n)    ((n)->i_key.nk.next)

/* 'const' to avoid wrong writings that can mess up field 'next' */
#define gkey(n)     cast(const TValue*, (&(n)->i_key.tvk))







