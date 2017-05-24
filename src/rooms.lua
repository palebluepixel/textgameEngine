roomEntries = {
	room1 = {
		displayName = "Field of Grass",
		aliases = {"Field of Grass"},
		properties = {},
		verbs = {},
		objects = {},
		exits = {"exit_room1_room2"},
		onEnter = function () end,
		onLeave = function () end
	},
	room2 = {
		displayName = "House wall",
		aliases = {"House wall"},
		properties = {},
		verbs = {},
		objects = {"obj1"},
		exits = {},
		onEnter = function () end,
		onLeave = function () end
	}
}




exitEntries = {
	exit_room1_room2 = {
		displayName = "East",
		aliases = {"East"},
		properties = {},
		verbs = {},
		roomFrom = "room1",
		roomTo = "room2",
		cond = function () return 1 end,
		onPass = function () end
	}
}