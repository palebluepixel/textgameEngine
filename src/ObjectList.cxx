#include "ObjectList.hxx"

ObjectList::ObjectList() {}

ObjectList::ObjectList(sol::table t)
{
	this->addTableToList(t);
}

/* Create an object for each entry in t. The entries must be tables
with the four required components of objects: 
	* a display name (string),
	* a list of aliases (table where the aliases are values (array string)),
	* a table of properties (table string -> sol::object),
	* a table of verbs (table string -> sol::function)
The christian name for the object will be the name of the entry in the
table. All entries must have unique names. This is not currently checked
by the constructor. If multiple entries have the same name, a 
nondeterministic one will overwrite all others. */
void ObjectList::addTableToList(sol::table t)
{
	t.for_each([&](const sol::object& key, const sol::object& value) 
		{
			/* Create new object using table entry, where the table
			key is the christian name */
			string cname = key.as<string>();
			gameObject *obj = new gameObject(value.as<table>(), cname);

			/* Add it to our list */
			this->addObject(cname, obj); 
		});
}

/* Get an object by its christian name (unique identifier),
or NULL if none exists. */
gameObject *ObjectList::getObject(string name)
{
	return this->objects[name];
}

void ObjectList::addObject(string name, gameObject *obj)
{
	this->objects[name] = obj;
}

/* Get an object by one of it's aliases. If multiple objects
go by the same alias, this can cause issues, so aliases should be
non-overlapping sets. */
gameObject *ObjectList::getObjectByAlias(string name)
{
	for (auto pair : this->objects){
		gameObject *obj = pair.second;
		if(obj->goesByAlias(name))
			return obj;
	}
	return NULL;
}







/************ ROOM LIST ***************/

RoomList::RoomList() {}

RoomList::RoomList(sol::table t)
{
	this->addTableToList(t);
}

void RoomList::addTableToList(sol::table t)
{
	t.for_each([&](const sol::object& key, const sol::object& value) 
		{
			/* Create new object using table entry, where the table
			key is the christian name */
			string cname = key.as<string>();
			Room *obj = new Room(value.as<table>(), cname);

			/* Add it to our list */
			this->addRoom(cname, obj); 
		});
}

/* Get an object by its christian name (unique identifier),
or NULL if none exists. */
Room *RoomList::getRoom(string name)
{
	return this->objects[name];
}

void RoomList::addRoom(string name, Room *obj)
{
	this->objects[name] = obj;
}

/* Get an object by one of it's aliases. If multiple objects
go by the same alias, this can cause issues, so aliases should be
non-overlapping sets. */
Room *RoomList::getRoomByAlias(string name)
{
	for (auto pair : this->objects){
		Room* obj = pair.second;
		if(obj->goesByAlias(name))
			return obj;
	}
	return NULL;
}



/************** EXIT LIST ***************/

ExitList::ExitList() {}

ExitList::ExitList(sol::table t)
{
	this->addTableToList(t);
}

/* Create an object for each entry in t. The entries must be tables
with the four required components of objects: 
	* a display name (string),
	* a list of aliases (table where the aliases are values (array string)),
	* a table of properties (table string -> sol::object),
	* a table of verbs (table string -> sol::function)
The christian name for the object will be the name of the entry in the
table. All entries must have unique names. This is not currently checked
by the constructor. If multiple entries have the same name, a 
nondeterministic one will overwrite all others. */
void ExitList::addTableToList(sol::table t)
{
	t.for_each([&](const sol::object& key, const sol::object& value) 
		{
			/* Create new object using table entry, where the table
			key is the christian name */
			string cname = key.as<string>();
			Exit *obj = new Exit(value.as<table>(), cname);

			/* Add it to our list */
			this->addExit(cname, obj); 
		});
}

/* Get an object by its christian name (unique identifier),
or NULL if none exists. */
Exit *ExitList::getExit(string name)
{
	return this->objects[name];
}

void ExitList::addExit(string name, Exit *obj)
{
	this->objects[name] = obj;
} 


/* Get an object by one of it's aliases. If multiple objects
go by the same alias, this can cause issues, so aliases should be
non-overlapping sets. */
Exit *ExitList::getExitByAlias(string name)
{
	for (auto pair : this->objects){
		Exit *obj = pair.second;
		if(obj->goesByAlias(name))
			return obj;
	}
	return NULL;
}