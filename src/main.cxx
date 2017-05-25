#include <sol.hpp>
#include <iostream>
#include "ObjectList.hxx"
#include "Object.hxx"
#include "Room.hxx"
#include "Exit.hxx"
#include "Player.hxx"
#include "Parser.hxx"

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

/* Globals */
state luastate;
ObjectList *objectsLIST;
RoomList *roomsLIST;
ExitList *exitsLIST;
Player *player;

int shouldClose = 0;
void closeGame() {shouldClose = 1;}

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
        "getStringFromFunc", &gameObject::getStringFromFunc,
        "printDescription", &gameObject::printDescription,
        "displayName", property(&gameObject::getDisplayName, &gameObject::setDisplayName)
    );

    /* Register room class */
    luastate.new_usertype<Room>( "Room",
    	constructors<Room(), Room(sol::table, string)>(),
    	"addObject", &Room::addObject,
    	"removeObject", &Room::removeObject,
    	"hasObject", &Room::containsObject,
    	"addExit", &Room::addExit,
    	"removeExit", &Room::removeExit,
    	"containsExit", &Room::containsExit,
    	"executeOnLeave", &Room::executeOnLeave,
    	"executeOnEnter", &Room::executeOnEnter,
    	"describeRoomContents", &Room::describeRoomContents,
    	"describeObjects", &Room::describeObjects,
    	"describeExits", &Room::describeExits,
    	sol::base_classes, sol::bases<gameObject>()
    );

    /* Register exit class */
    luastate.new_usertype<Exit> ( "Exit",
    	constructors<Exit(), Exit(sol::table, string)>(),
    	"getRoomFrom", &Exit::getRoomFrom,
    	"getRoomTo", &Exit::getRoomTo,
    	"getCond", &Exit::getCond,
    	"executeCond", &Exit::executeCond,
    	"getOnPass", &Exit::getOnPass,
    	"executeOnPass", &Exit::executeOnPass,
    	"executeOnFail", &Exit::executeOnFail,
    	sol::base_classes, sol::bases<gameObject>()
    );

    /* Register object list class */
    luastate.new_usertype<ObjectList>("ObjectList",
    	constructors<ObjectList(), ObjectList(sol::table)>(),
    	"getObject", &ObjectList::getObject
    );
    luastate.new_usertype<RoomList>("RoomList",
    	constructors<RoomList(), RoomList(sol::table)>(),
    	"getRoom", &RoomList::getRoom
    );
    luastate.new_usertype<ExitList>("ExitList",
    	constructors<ExitList(), ExitList(sol::table)>(),
    	"getExit", &ExitList::getExit
    );

    /* Register class player */
    luastate.new_usertype<Player>("Player",
    	constructors<Player(), Player(sol::table)>(),
    	"getRoom", &Player::getRoom,
    	"addObject", &Player::addObject,
    	"removeObject", &Player::removeObject,
    	"hasObject", &Player::hasObject,
    	/* Remove these eventually */
    	"takeItem", &Player::takeItem,
    	"dropItem", &Player::dropItem,
    	"moveThrough", &Player::moveThrough
    );

    /* Register class parser */
    luastate.new_usertype<Parser>("Parser",
    	constructors<Parser(), Parser(sol::table)>(),
    	"handleInput", &Parser::handleInput
    );

    //printf("classes registered\n");

    /* Create test objects by loading lua script*/
    luastate.script_file("../src/objects.lua");
    luastate.script_file("../src/rooms.lua");
    luastate.script_file("../src/player.lua");
    luastate.script_file("../src/parserCommands.lua");
    //printf("Object script read\n");
    sol::table objectTable = luastate.get<table>("objectEntries");
    sol::table roomTable = luastate.get<table>("roomEntries");
    sol::table exitTable = luastate.get<table>("exitEntries");
    sol::table playerTable = luastate.get<table>("playerStart");
    sol::table parserTable = luastate.get<table>("parserCommands");
    objectsLIST = new ObjectList(objectTable);
    roomsLIST = new RoomList(roomTable);
    exitsLIST = new ExitList(exitTable);

    //printf("gameObjects Created\n");

    //luastate.set("testGameObject1", objects->getObject("obj1"));
    //luastate.set("testGameObject2", objects->getObject("obj2"));
    luastate.set("objects", objectsLIST);
    luastate.set("rooms", roomsLIST);
    luastate.set("exits", exitsLIST);

    /* Player */
    player = new Player(playerTable);
    luastate.set("player", player);

    /* Parser */
    Parser *parser = new Parser(parserTable);
    luastate.set("parser", parser);

    //luastate.set_function("luaCastRoom", &luaCastRoom);
    //luastate.set_function("luaCastExit", &luaCastExit);

    //printf("gameObjects added\n");

    luastate.script_file("../src/scriptObjTest.lua");

    /* Ability to quit the game */
    luastate.set_function("closeGame", &closeGame);

    /* Print starting description */
    luastate.script_file("../src/gamestart.lua");

    string inp;
    while(!shouldClose){
    	cout << "\n\n> ";
    	getline(cin, inp);
    	parser->handleInput(inp); 
    }

    printf("Done\n");
}
