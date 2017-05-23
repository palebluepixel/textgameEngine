#include "Object.hxx"

gameObject::gameObject()
{

}

int gameObject::goesByAlias(string s) 
{ 
	for(string it : this->aliases ){
		if (it == s) return 1;
	} 
	return 0;
}

/* This will add a new property with the given value if the
given property does not already exist in this object. */
void gameObject::setProperty(string prop, sol::object value)
{
	this->properties[prop] = value;
}

/* Returns the value of the given property. Returns nil if
the object doesn't have an entry for this property. */
sol::object gameObject::getProperty(string prop)
{
	auto result = this->properties.find(prop);
	if(result == this->properties.end()){
		return sol::object(sol::nil);
	}
	return result->second;
}

/* Returns the type of the value stored for the given property,
or nil if the object does not have the property. */
sol::type gameObject::getPropertyType(string prop)
{
	sol::object obj = this->getProperty(prop);
	return obj.get_type();
}

/* Checks if the return value for the given property matches the
expected type, and returns nil if it does not. */
sol::object gameObject::getPropertyExpectType(string prop, sol::type t)
{
	sol::object obj = this->getProperty(prop);
	return obj.get_type() == t ? obj : sol::nil;
}


/* Adds a new verb entry, or overwrites the existing entry if
one exists. */
void gameObject::setVerb(string v, sol::function f)
{
	this->verbs[v] = f;
}

/* Returns the function associated with the verb v, or nil if none
exists. */
sol::function gameObject::getVerbFunction(string v)
{
	return this->verbs[v];
}

/* Executes the verb function and returns 1 if it an entry exists
for this verb, otherwise returns 0. */
int gameObject::executeVerbFunction(string v)
{
	return 0;
}