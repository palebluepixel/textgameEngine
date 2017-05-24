#ifndef _OBJECT_LIST_
#define _OBJECT_LIST_

#include <unordered_map>
#include "Object.hxx"
#include "Room.hxx"
#include "Exit.hxx"

using namespace std;
using namespace sol;

/* Map of christian names (unique identifiers) to objects. */

/* This is obviously inelegant, ObjectList should be a template 
that takes a subclass of gameObject, but I'm not sure how to do it the
elegant way and this project is due soon. 

If I could do it again from scratch, I would have gameObject be
the only class, and rooms and exits would simply have additional
property fields relating to their use as exits. 

Since I didn't do that, please forgive me for the copy/pasted 
code. */

class ObjectList {
public:
	ObjectList();
	ObjectList(sol::table t);

	/* Create an object for each entry in t. The entries must be tables
	with the four required components of objects: 
		* a display name (string),
		* a list of aliases (table where the aliases are values (array string)),
		* a table of properties (table string -> sol::object),
		* a table of verbs (table string -> sol::function)
	The christian name for the object will be the name of the entry in the
	table. All entries must have unique names. This is not currently checked
	by the constructor. */
	void addTableToList(sol::table t);

	/* Get an object by its christian name (unique identifier),
	or NULL if none exists. */
	gameObject *getObject(string name);

private:
	void addObject(string name, gameObject *obj);

	unordered_map<string, gameObject*> objects;
};


class RoomList {
public:
	RoomList();
	RoomList(sol::table t);

	void addTableToList(sol::table t);

	/* Get an object by its christian name (unique identifier),
	or NULL if none exists. */
	Room *getObject(string name);

private:
	void addObject(string name, Room *obj);

	unordered_map<string, Room*> objects;
};


class ExitList {
public:
	ExitList();
	ExitList(sol::table t);

	void addTableToList(sol::table t);

	/* Get an object by its christian name (unique identifier),
	or NULL if none exists. */
	Exit *getObject(string name);

private:
	void addObject(string name, Exit *obj);

	unordered_map<string, Exit*> objects;
};

#endif