verbs = {
	zeroa = function() 
		print(instList)
		instFromLua = instList:getInstance("instanceFromLua");
		print(instFromLua.a)
		instFromLua.a = 0
		return nil
	end
}