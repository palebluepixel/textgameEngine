#include <sol.hpp>
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
    luastate.new_usertype<Object>( "Object",
        constructors<Object(sol::table)>(),
        "addAlias", Object::addAlias,
        "goesByAlias", Object::goesByAlias,
        "setProperty", &Object::setProperty,
        "getProperty", &Object::getProperty,
        "getPropertyType", &Object::getPropertyType,
        "getPropertyExpectType", &Object::getPropertyExpectType,
        "setVerb", &Object::setVerb,
        "getVerbFunction", &Object::getVerbFunction,
        "executeVerbFunction", &Object::executeVerbFunction,
        "displayName", property(&Object::getDisplayName, &Object::setDisplayName)
    );

    
}
