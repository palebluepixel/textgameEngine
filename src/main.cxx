#include <sol.hpp>
#include <iostream>
#include "object.hxx"

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
        constructors<gameObject()>(),
        "addAlias", gameObject::addAlias,
        "goesByAlias", gameObject::goesByAlias,
        "setProperty", &gameObject::setProperty,
        "getProperty", &gameObject::getProperty,
        "getPropertyType", &gameObject::getPropertyType,
        "getPropertyExpectType", &gameObject::getPropertyExpectType,
        "setVerb", &gameObject::setVerb,
        "getVerbFunction", &gameObject::getVerbFunction,
        "executeVerbFunction", &gameObject::executeVerbFunction,
        "displayName", property(&gameObject::getDisplayName, &gameObject::setDisplayName)
    );

    printf("gameObject class registered\n");

    /* Create test objects */
    gameObject *testGameObject1 = new gameObject();
    gameObject *testGameObject2 = new gameObject();

    printf("gameObjects Created\n");

    luastate.set("testGameObject1", testGameObject1);
    luastate.set("testGameObject2", testGameObject2);

    printf("gameObjects added\n");

    luastate.script_file("../src/scriptObjTest.lua");

    printf("%s\n", testGameObject1->getDisplayName().c_str());

    //printf("%d\n", testGameObject1->getProperty("coolness").get_type());

    printf("Luastate Property Coolness: %d %d\n", testGameObject1->getProperty("coolness").as<int>(),
    	testGameObject2->getProperty("coolness").as<int>());

    printf("Done\n");
}
