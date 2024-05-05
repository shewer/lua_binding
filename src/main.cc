#include "library/lua_templates.h"
#include "library/optional.h"
#include <iostream>
#include "library/common.h"


using namespace std;

class LuaTest {
  public:
    LuaTest(Lua *lua, const char *file) : lua_(lua) {
      lua_->to_state( [&](lua_State *L) {
            if (luaL_loadfilex(L, file, "tb") == LUA_OK) 
              f_ = LuaObj::todata(L,-1);
          });
    }
    LuaTest(Lua *lua, const string file) : LuaTest(lua, file.c_str()) {}
    void execute() { 
      if (!f_)
        return;
      auto r = lua_->void_call<an<LuaObj>>(f_);
      if (!r.ok()) {
        auto e = r.get_err();
        std::cerr << "ERROR: "<< e.status << ": " << e.e << std::endl;
      }
    }
  protected:
    Lua *lua_;
    an<LuaObj> f_;
};

void lualib_init(lua_State *L);
void lua_init(lua_State *L);



int main(int argc, char** argv) {
    std::cout << "hello world!" << std::endl;
    Lua *lua = new Lua();
    lua->to_state(lua_init);
    LuaTest t(lua,string("./test.lua"));
    t.execute();

    return 0;
}




void lua_init(lua_State *L) {
  lualib_init(L);
}

/*
namespace ArrayReg {
  using T = std::vector<string>;
  an<T> make() {
    return make_shared<T>();
  }
  const string& get_at(T &t, int index){
    index = index <0 ? t.size()+index : index;
    return t[index];
  }
  void set_at(T &t, int index, const string &s) {
    index = index <0 ? t.size()+index : index;
    t[index] = s;
  }

  static const luaL_Reg funcs[] = {
    { "Array", WRAP(make) },
    { NULL, NULL },
  };

  static const luaL_Reg methods[] = {
    //{ "append", WRAPMEM(T::push_back) },
    { "gat_at", WRAP(get_at) },
    { "set_at", WRAP(set_at) },
    { NULL, NULL },
  };

  static const luaL_Reg vars_get[] = {
    { "size", WRAPMEM(T::size) },
    { NULL, NULL },
  };

  static const luaL_Reg vars_set[] = {
    { NULL, NULL },
  };
  static const luaL_Reg mt[] = {
    { NULL, NULL },
  };

}
*/
void lualib_init(lua_State *L) {
  //EXPORT(ArrayReg, L);
}
