--TODO: move generics to new file
function genericEnter (roomsList, roomName)
	r = roomsList:getRoom(roomName)
	r:printDescription("descLong")
	r:describeRoomContents()
end

roomEntries = {
	room1 = {
		displayName = "field of grass",
		aliases = {},
		properties = {
			descLong = function () return "You are standing in a field of grass. " end
		},
		verbs = {},
		objects = {},
		exits = {"exit_room1_room2"},
		onEnter = function () genericEnter(rooms,"room1") end,
		onLeave = function () end
	},

	room2 = {
		displayName = "house wall",
		aliases = {},
		properties = {
			descLong = function () return "You are standing next to the wall of a house. " end
		},
		verbs = {},
		objects = {"obj1"},
		exits = {"exit_room2_room1"},
		onEnter = function() genericEnter(rooms, "room2") end,
		onLeave = function () end
	}
}




exitEntries = {
	exit_room1_room2 = {
		displayName = "east",
		aliases = {},
		properties = {
			descInRoom = function () return "You see the wall of a house to the east. " end
		},
		verbs = {
			go = function() player:moveThrough("exit_room1_room2") end
		},
		roomFrom = "room1",
		roomTo = "room2",
		cond = function () 
			return 1 
		end,
		onPass = function () end,
		onFail = function () print("You can't go that way rn. ") end
	},

	exit_room2_room1 = {
		displayName = "west",
		aliases = {},
		properties = {
			descInRoom = function () return "There is an open field of grass to the west. " end
		},
		verbs = {
			go = function() player:moveThrough("exit_room2_room1") end
		},
		roomFrom = "room2",
		roomTo = "room1",
		cond = function () 
			return 1
		end,
		onPass = function () end,
		onFail = function () print("You can't go that way rn. ") end
	}
}