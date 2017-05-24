--testGameObject1.displayName = "friend"
print("\n",testGameObject1.displayName)
print(testGameObject1:getProperty("coolness"))

print("\n",testGameObject2.displayName)
print(testGameObject2:getProperty("coolness"))

print("\nLever pulling test")
print(testGameObject1:getProperty("pulled"))
print("pulling lever")
testGameObject1:executeVerbFunction("pull")
print(testGameObject1:getProperty("pulled"))