#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"

int main(void) {
    char buff[256];
    int error;
    lua_State *L = luaL_newstate();         // opens lua
    luaL_openlibs(L);                       // opens the standard libraries
    
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        error = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }
    
    lua_close(L);
    return 0;
}

static void stackDump (lua_State *L) {
    int i;
    int top = lua_gettop(L);                // depth of the stack
    for (i = 1; i <= top; ++i) {
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING: {
                printf("'%s'", lua_tostring(L, i));
                break;
            }
            case LUA_TBOOLEAN: {
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;
            }
            case LUA_TNUMBER: {
                printf("%g", lua_tonumber(L, i));
                break;
            }
            default: {
                printf("%s", lua_typename(L, t));
                break;
            }
        }
        printf("    ");
    }
    printf("\n");
}
