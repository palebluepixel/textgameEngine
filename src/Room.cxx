#include "Room.hxx"
#include "ObjectList.hxx"

Room::Room()
{

}


/* A room must have the following fields, in addition to the normal
object fields:
	* objects : (sol::table) an array of strings of the names of
	objects which spawn starting in this room
	* exits : (sol::table) an array of strings of the names of 
	exits which leave this room. 
	* onEnter : (sol::function) a function that will trigger whenever
	the player enters the room. 
	* onLeave : (sol::function) a function that will trigger whenever
	the player leaves the room. */ 
Room::Room(sol::table t, string name)
{
	/* Set fields for object parent class */
	this->setObjectDataFromTable(t, name);

	/* Set room-specific information */
	sol::table objects = t.get<sol::table>("objects");
	sol::table exits = t.get<sol::table>("exits");
	sol::function onLeave = t.get<sol::function>("onLeave");
	sol::function onEnter = t.get<sol::function>("onEnter");

	this->setOnLeave(onLeave);
	this->setOnEnter(onEnter);
	this->addObjectsFromArray(objects);
	this->addExitsFromArray(exits);

}

/* Construct room contents from table */
void Room::addObjectsFromArray(sol::table t)
{
	t.for_each([&](const sol::object& /*key*/, const sol::object& value) 
		{this->addObject(value.as<string>());});
}

void Room::addExitsFromArray(sol::table t)
{
	t.for_each([&](const sol::object& /*key*/, const sol::object& value) 
		{this->addExit(value.as<string>());});
}


int Room::containsObjectByAlias(string alias)
{
	gameObject *obj = objectsLIST->getObjectByAlias(alias);
	return (obj && this->containsObject(obj->getChristianName()));
}

int Room::containsExitByAlias(string alias)
{
	Exit *exit = exitsLIST->getExitByAlias(alias);
	return (exit && this->containsExit(exit->getChristianName()));
}



/* Print out a description of all objects and exits in the room. */
void Room::describeRoomContents()
{
	this->describeObjects();
	this->describeExits();
}

void Room::describeObjects()
{

}

void Room::describeExits()
{

}