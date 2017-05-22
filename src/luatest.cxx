// main.cpp
#include <lua.hpp>
#include <LuaBridge.h>
#include <iostream>
 
using namespace luabridge;
int main(int argc, char*argv[]) 
{
    std::string filename = "../src/script.lua";
    std::string varsname = "testString";

    lua_State* L = luaL_newstate();
    if (luaL_loadfile(L, filename.c_str()) ||
    lua_pcall(L, 0, 0, 0)) {
        printf("Script not loaded.\n");
    }
    luaL_openlibs(L);
    
    LuaRef s = getGlobal(L, varsname.c_str());
    if (s.isNil()) {
        std::cout << "Variable not found!" << std::endl;
    }

    LuaRef n = getGlobal(L, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;
}