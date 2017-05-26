-- Define useful feunctions used by other scripts. 

win = function ()
	print("[=============== You won the game! ===============]")
end


function genericEnter (roomsList, roomName)
	r = roomsList:getRoom(roomName)
	r:printDescription("descLong")
	r:describeRoomContents()
end

function genericMoveThrough(p, exit)
	p:moveThrough(exit)
end

function genericTake (p, item)
	p:takeItem(item)
	r = rooms:getRoom(p:getRoom())
	r:printDescription("descLong")
end

function genericDrop(p, item)
	p:dropItem(item)
	r = rooms:getRoom(p:getRoom())
	r:printDescription("descLong")
end