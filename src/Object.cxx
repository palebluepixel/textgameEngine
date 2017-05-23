#include "Object.hxx"

Object::Object(sol::table t)
{

}

Object::~Object() {}

/* This will add a new property with the given value if the
given property does not already exist in this object. */
void Object::setProperty(string prop, sol::object value)
{
	this->properties[prop] = value;
}

/* Returns the value of the given property. Returns nil if
the object doesn't have an entry for this property. */
sol::object Object::getProperty(string prop)
{
	auto search = this->properties.find(prop);
	return search == properties.end() ? 
	sol::make_object(luastate, sol::nil) | 
	search;
}

/* Returns the type of the value stored for the given property,
or nil if the object does not have the property. */
sol::type Object::getPropertyType(string prop)
{
	sol::object obj = this->getProperty(prop);
	return obj.get_type();
}

/* Checks if the return value for the given property matches the
expected type, and returns nil if it does not. */
sol::object Object::getPropertyExpectType(string prop, sol::type t)
{
	sol::object obj = this->getProperty(prop);
	return obj.get_type == t ? obj | sol::make_object(luastate, sol::nil);
}


/* Adds a new verb entry, or overwrites the existing entry if
one exists. */
void Object::setVerb(string v, sol::function f)
{
	this->verbs[v] = f;
}

/* Returns the function associated with the verb v, or nil if none
exists. */
sol::function Object::getVerbFunction(string v)
{
	return this->verbs[v];
}

/* Executes the verb function and returns 1 if it an entry exists
for this verb, otherwise returns 0. */
int Object::executeVerbFunction(string v)
{
	return 0;
}