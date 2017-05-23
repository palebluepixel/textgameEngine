#include <sol.hpp> // or #include "sol.hpp", whichever suits your needs
#include <iostream>
#include <unordered_map>

using namespace sol;
using namespace std;

int add(int a, int b) { return a+b; }

inline void my_panic(sol::optional<std::string> maybe_msg) {
        std::cerr << "Lua is in a panic state and will now abort() the application" << std::endl;
        if (maybe_msg) {
                const std::string& msg = maybe_msg.value();
                std::cerr << "\terror message: " << msg << std::endl;
        }
        // When this function exits, Lua will exhibit default behavior and abort()
}

class my_class {
public:
        int a = 0;
        inline int geta() { return this->a; }
        inline void seta(int a) { this->a = a; }

        inline my_class(int x) : a(x) {

        }

        inline int func() {
                ++a; // increment a by 1
                return a;
        }
};

class my_class_list {
public:
    inline my_class_list() {};

    inline my_class* getInstance(string s) {
        my_class* result = this->instances[s];
        printf("In getInstance %s, getting %p\n", s.c_str(), result);
        return result;
    }

    inline void addInstance(string s, my_class* m) {
        this->instances[s] = m;
    }

private:
    unordered_map<string, my_class*> instances;
};

int main (int argc, char* argv[]) {

        state lua(sol::c_call<decltype(&my_panic), &my_panic>);
        lua.open_libraries( sol::lib::base );

        /* Two ways, in one we bind to an instance now, in the second
        we bind to the instance later */
        my_class inst = my_class(0);
        inst.func();
        inst.func();
        lua.set_function("my_class_func", &my_class::func, &inst);
        lua.set_function("my_class_func_2", &my_class::func);

        lua.script(R"(
                first_value = my_class_func()
                second_value = my_class_func()
        )");

        // With no bound instance:
        my_class inst2 = my_class(24);
        lua.set("obj", &inst2); //just "inst2" passes a copy
        // Calls "func" on the class instance
        // referenced by "obj" in Lua
        lua.script(R"(
                third_value = my_class_func_2(obj)
                fourth_value = my_class_func_2(obj)
        )");

        // Have to mantually go back and get data from lua if we didn't
        // pass it as a reference
        //inst2.a = lua.get<my_class>("obj").a;

        my_class inst3 = my_class(69);

        lua.new_usertype<my_class>( "my_class",
            constructors<my_class(int)>(),
            "func", &my_class::func,
            "a", property(&my_class::geta, &my_class::seta) //would add getter and setter here if private
        );
        lua.set("real", &inst3);
        lua.script(R"(
            fifth_value = real:func()
            sixth_value = real:func()
            final_value = real.a
        )");

        printf("Instance 1: %d\nInstance2: %d\nInstance3: %d\n", inst.a, inst2.a, inst3.a);
        printf("Lua sees %d %d %d %d %d %d and %d\n", 
            lua.get<int>("first_value"),
            lua.get<int>("second_value"),
            lua.get<int>("third_value"),
            lua.get<int>("fourth_value"),
            lua.get<int>("fifth_value"),
            lua.get<int>("sixth_value"),
            lua.get<int>("final_value"));


        lua["add_func"] = add;

        lua.script_file( "../src/script.lua" );

        lua.script_file("../src/script2.lua");

        int width = lua["window"]["width"];
        std::string name = lua["window"]["title"];
        printf("%s width: %d number : %d\n", name.c_str(), width, lua.get<int>("number"));

        lua["newtable"] = lua.create_table_with(
            "key0", 24,
            "key1", 25
        );

        int key0 = lua["newtable"]["key0"];
        printf("key0: %d\n", key0);


        // Functions
        sol::function inc = lua.get<sol::function>("inc");
        int x = 0;
        int xinc = inc(x);
        printf("Increment test %d %d\n", x, xinc);



        //Creating an object from a lua script, then modifying
        //that data in a second script
        my_class fromLua = my_class(lua.get<table>("myclass1").get<int>("a"));
        lua.set("myclass1", &fromLua); //replace existing table entry
        printf("My class before third script: %d %d\n", fromLua.geta(), lua.get<my_class>("myclass1").geta());
        lua.script_file("../src/script3.lua");
        printf("My class after third script: %d %d\n", fromLua.geta(), lua.get<my_class>("myclass1").geta());


        my_class_list instList;
        instList.addInstance("instance1", &inst);
        instList.addInstance("instance2", &inst2);
        instList.addInstance("instance3", &inst3);
        instList.addInstance("instanceFromLua", &fromLua);

        printf("Checking instances added: %d %d %d %d\n", 
            instList.getInstance("instance1")->geta(),
            instList.getInstance("instance2")->geta(),
            instList.getInstance("instance3")->geta(),
            instList.getInstance("instanceFromLua")->geta());

        lua.new_usertype<my_class_list>( "my_class_list",
            constructors<my_class_list()>(),
            "getInstance", &my_class_list::getInstance,
            "addInstance", &my_class_list::addInstance
        );

        lua.set("instList", &instList);

        lua.script_file("../src/script4.lua");
        table verbs = lua.get<table>("verbs");
        sol::function zeroa = verbs.get<sol::function>("zeroa");
        zeroa();

        printf("Zero out 'a' for the last instance: %d \n", fromLua.geta());

        printf("Done.\n");

        return 0;
}