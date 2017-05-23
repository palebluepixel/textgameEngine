// main.cpp
#include <lua.hpp>
#include <LuaBridge.h>
#include <iostream>
#include <unordered_map>
 
using namespace luabridge;
using namespace std;

unordered_map<string, luabridge::LuaRef> getKeyValueMap(const luabridge::LuaRef& table)
{
    using namespace luabridge;
    unordered_map<string, LuaRef> result;
    if (table.isNil()) { return result; }
 
    auto L = table.state();
    push(L, table); // push table
 
    lua_pushnil(L);  // push nil, so lua_next removes it from stack and puts (k, v) on stack
    while (lua_next(L, -2) != 0) { // -2, because we have table at -1
        if (lua_isstring(L, -2)) { // only store stuff with string keys
            result.emplace(lua_tostring(L, -2), LuaRef::fromStack(L, -1));
        }
        lua_pop(L, 1); // remove value, keep key for lua_next
    }
 
    lua_pop(L, 1); // pop table
    return result;
}

void printMap(unordered_map<string, luabridge::LuaRef> map)
{
    for (auto it : map){
        auto& key = it.first;
        auto& value = it.second;
        printf("%d\n", lua_type(value,0));
        if (value.isNumber())
        {
            printf("%s : %d\n", key.c_str(), it.second.cast<int>());
        }
    }
}

int main(int argc, char*argv[]) 
{
    string filename = "../src/script.lua";

    lua_State* L = luaL_newstate();
    if (luaL_loadfile(L, filename.c_str()) ||
    lua_pcall(L, 0, 0, 0)) {
        printf("Script not loaded.\n");
    }
    luaL_openlibs(L);
    
    /*LuaRef s = getGlobal(L, "teststring");
    if (s.isNil()) {
        cout << "Variable not found!" << endl;
    }
    string luaString = s.cast<string>();

    LuaRef t = getGlobal(L, "window");
    LuaRef title = t["title"];
    string titleString = title.cast<string>();
    int width = t["width"].cast<int>();
    LuaRef inner = t["inner"];
    int height = inner["height"].cast<int>();

    LuaRef n = getGlobal(L, "number");
    int answer = n.cast<int>();


    cout << luaString << endl;
    cout << titleString << endl;
    cout << "width = " << width << endl;
    cout << "height = " << height << endl;
    cout << "And here's our number:" << answer << endl;*/

    /* Build unordered map */
    LuaRef mapRef = getGlobal(L, "window");
    if (mapRef.isNil()) {
        cout << "Variable not found!" << endl;
    }

    unordered_map<string, luabridge::LuaRef> map = getKeyValueMap(mapRef);
    printMap(map);
}