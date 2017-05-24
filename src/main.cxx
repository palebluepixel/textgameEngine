#include <sol.hpp>
#include <iostream>
#include "ObjectList.hxx"

using namespace sol;
using namespace std;

inline void my_panic(sol::optional<std::string> maybe_msg) {
        std::cerr << "Lua is in a panic state and will now abort() the application" << std::endl;
        if (maybe_msg) {
                const std::string& msg = maybe_msg.value();
                std::cerr << "\terror message: " << msg << std::endl;
        }
        // When this function exits, Lua will exhibit default behavior and abort()
}

state luastate;


int main (int argc, char* argv[]) {
	
	/* Initalization */
	lua_atpanic(luastate, sol::c_call<decltype(&my_panic), &my_panic>);
    luastate.open_libraries( sol::lib::base );

    /* Register object class */
    luastate.new_usertype<gameObject>( "gameObject",
        constructors<gameObject(), gameObject(sol::table, string)>(),
        "addAlias", gameObject::addAlias,
        "goesByAlias", gameObject::goesByAlias,
        "setProperty", &gameObject::setProperty,
        "getProperty", &gameObject::getProperty,
        "getPropertyType", &gameObject::getPropertyType,
        "getPropertyExpectType", &gameObject::getPropertyExpectType,
        "setVerb", &gameObject::setVerb,
        "getVerb", &gameObject::getVerb,
        "executeVerbFunction", &gameObject::executeVerbFunction,
        "getChristianName", &gameObject::getChristianName,
        "displayName", property(&gameObject::getDisplayName, &gameObject::setDisplayName)
    );

    /* Register object list class */
    luastate.new_usertype<ObjectList>("ObjectList",
    	constructors<ObjectList(), ObjectList(sol::table)>(),
    	"getObject", &ObjectList::getObject
    );

    printf("classes registered\n");

    /* Create test objects by loading lua script*/
    luastate.script_file("../src/objects.lua");
    //printf("Object script read\n");
    sol::table objectTable = luastate.get<table>("objectEntries");
    ObjectList *objects = new ObjectList(objectTable);

    printf("gameObjects Created\n");

    //luastate.set("testGameObject1", objects->getObject("obj1"));
    //luastate.set("testGameObject2", objects->getObject("obj2"));
    luastate.set("objects", objects);

    printf("gameObjects added\n");

    luastate.script_file("../src/scriptObjTest.lua");

    printf("Done\n");
}
