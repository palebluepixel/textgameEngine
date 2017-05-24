#include <sol.hpp>
#include <iostream>
#include "ObjectList.hxx"
#include "Object.hxx"
#include "Room.hxx"
#include "Exit.hxx"

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

//inline Room* luaCastRoom(gameObject *obj) {return dynamic_cast<Room*>(obj);}
//inline Room* luaCastExit(gameObject *obj) {return dynamic_cast<Exit*>(obj);}

state luastate;


int main (int argc, char* argv[]) {
	
	/* Initalization */
	lua_atpanic(luastate, sol::c_call<decltype(&my_panic), &my_panic>);
    luastate.open_libraries( sol::lib::base );

    /* TODO: make class registration functions in the classes and call them in
    an organized way, rather than having it live in main */

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

    /* Register room class */
    luastate.new_usertype<Room>( "Room",
    	constructors<Room(), Room(sol::table, string)>(),
    	"addObject", &Room::addObject,
    	"removeObject", &Room::removeObject,
    	"containsObject", &Room::containsObject,
    	"addExit", &Room::addExit,
    	"removeExit", &Room::removeExit,
    	"containsExit", &Room::containsExit,
    	"executeOnLeave", &Room::executeOnLeave,
    	"executeOnEnter", &Room::executeOnEnter,
    	sol::base_classes, sol::bases<gameObject>()
    );

    /* Register exit class */
    luastate.new_usertype<Exit> ( "Exit",
    	constructors<Exit(), Exit(sol::table, string)>(),
    	"getRoomFrom", &Exit::getRoomFrom,
    	"getRoomTo", &Exit::getRoomTo,
    	"getCond", &Exit::getCond,
    	"getOnPass", &Exit::getOnPass,
    	"executeOnPass", &Exit::executeOnPass,
    	sol::base_classes, sol::bases<gameObject>()
    );

    /* Register object list class */
    luastate.new_usertype<ObjectList>("ObjectList",
    	constructors<ObjectList(), ObjectList(sol::table)>(),
    	"getObject", &ObjectList::getObject
    );
    luastate.new_usertype<RoomList>("RoomList",
    	constructors<RoomList(), RoomList(sol::table)>(),
    	"getObject", &RoomList::getObject
    );
    luastate.new_usertype<ExitList>("ExitList",
    	constructors<ExitList(), ExitList(sol::table)>(),
    	"getObject", &ExitList::getObject
    );

    printf("classes registered\n");

    /* Create test objects by loading lua script*/
    luastate.script_file("../src/objects.lua");
    luastate.script_file("../src/rooms.lua");
    //printf("Object script read\n");
    sol::table objectTable = luastate.get<table>("objectEntries");
    sol::table roomTable = luastate.get<table>("roomEntries");
    sol::table exitTable = luastate.get<table>("exitEntries");
    ObjectList *objects = new ObjectList(objectTable);
    RoomList *rooms = new RoomList(roomTable);
    ExitList *exits = new ExitList(exitTable);

    printf("gameObjects Created\n");

    //luastate.set("testGameObject1", objects->getObject("obj1"));
    //luastate.set("testGameObject2", objects->getObject("obj2"));
    luastate.set("objects", objects);
    luastate.set("rooms", rooms);
    luastate.set("exits", exits);

    //luastate.set_function("luaCastRoom", &luaCastRoom);
    //luastate.set_function("luaCastExit", &luaCastExit);

    printf("gameObjects added\n");

    luastate.script_file("../src/scriptObjTest.lua");

    printf("Done\n");
}
