parserCommands = {
	commands = {
		test = function () print("called test from custom commands") end,
		look = function () 
			r = rooms:getRoom(player:getRoom())
			r:printDescription("descLong")
			r:describeRoomContents()
		end,
		exit = function() closeGame() end
	}
}