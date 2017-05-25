--testGameObject1.displayName = "friend"

testGameObject1 = objects:getObject("obj1")
testGameObject2 = objects:getObject("obj2")

print("\n",testGameObject1.displayName, testGameObject1:getChristianName())
print(testGameObject1:getProperty("coolness"))

print("\n",testGameObject2.displayName, testGameObject2:getChristianName())
print(testGameObject2:getProperty("coolness"))

print("\nLever pulling test")
print(testGameObject1:getProperty("pulled"))
print("pulling lever")
testGameObject1:executeVerbFunction("pull")
print(testGameObject1:getProperty("pulled"))
testGameObject1:executeVerbFunction("eat")

print("\n\n\n---Doing room tests---")
room1 = rooms:getRoom("room1")
room2 = rooms:getRoom("room2")
exit_room1_room2 = exits:getExit("exit_room1_room2")
print(exit_room1_room2:executeCond())
print(room1.displayName, " ", room1:containsObject("obj1"))
print(room2.displayName, " ", room2:containsObject("obj1"))
room2:removeObject("obj1")
print(room2.displayName, " ", room2:containsObject("obj1"))
room2:removeObject("obj1")
print(room2.displayName, " ", room2:containsObject("obj1"))
print(exit_room1_room2:executeCond())

print("\n walking between rooms")
room1:executeOnLeave()
exit_room1_room2:executeOnPass()
room2:executeOnEnter()

--I should make a function in room to call a "foreach"
--on every item in the room