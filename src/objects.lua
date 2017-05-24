objects = {
    obj1 = {
        displayName = "Lever",
        aliases = {"Lever"},
        properties = {
        	coolness = 1;
        	pulled = 0;
    	},
    	verbs = {
    		pull = function ()
    			print("lever was pulled")
    		end
    	}
    },
    obj2 = {
        displayName = "Button",
        aliases = {"Button"},
        properties = {
        	coolness = 2;
        	pushed = 0;
    	},
    	verbs = {}
    },
}