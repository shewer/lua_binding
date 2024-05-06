#include "library/lua_templates.h"
#include "library/optional.h"
#include "library/lua_export_type.h"
#include <iostream>
#include "library/common.h"


using namespace std;
class Cobj {
  public:
    Cobj(int x=0 , int y=0) : x_(x), y_(y) {}
    int get_x() { return x_ ;}
    int get_y() { return y_ ;}
    int area() { return x_ * y_;}
    void set_x(int x) { x_ = x;}
    void set_y(int y) { y_ = y;}
    an<Cobj> operator+(const Cobj& other) {
      return New<Cobj>(x_ + other.x_, y_ + other.y_);
    }
  protected:
    int x_;
    int y_;
};
class LuaTest {
  public:
    LuaTest(Lua *lua, const char *file1, const char* file2) : lua_(lua) {
      load_file(file1, f1_);
      load_file(file2, f2_);
    }
    LuaTest(Lua *lua, const string file1, const string file2) 
      : LuaTest(lua, file1.c_str(), file2.c_str() ) {}

    template <typename T>
    T execute(int s=1) { 
      an<LuaObj> f_ = (s == 1) ? f1_ : f2_ ;
      if (!f_)
        return 0;
      auto r = lua_->call<T, an<LuaObj>>(f_);
      if (!r.ok()) {
        auto e = r.get_err();
        std::cerr << "ERROR: "<< e.status << ": " << e.e << std::endl;
        return 0;
      }
      return r.get();
    };
  protected:
    Lua *lua_;
    an<LuaObj> f1_;
    an<LuaObj> f2_;

    void load_file(const char* fn, an<LuaObj> &obj) {
      lua_->to_state( 
        [&](lua_State *L) {
          if (int res = luaL_loadfilex(L, fn, "tb") == LUA_OK) 
            obj  = LuaObj::todata(L,-1);
          else 
            std::cerr << "loadfile error: " << res << std::endl;
      });
    }

};

void lualib_init(lua_State *L);
void lua_init(lua_State *L);



int main(int argc, char** argv) {
    std::cout << "hello world!" << std::endl;
    Lua *lua = new Lua();
    lua->to_state(lua_init);


    LuaTest t(lua,"./test1.lua","./test2.lua");
    try{
      auto res1 = t.execute<string>(1);
      std::cout << "res1: " << res1 << std::endl;
    } catch (const std::exception& e ) {
        std::cerr << "Error of func1" <<  "--" << e.what() << std::endl;
    }
    try {
      auto res2 = t.execute<bool>(2);
      std::cout << "res: " << res2 << std::endl;
    } catch (const std::exception& e ) {
        std::cerr << "Error of func2" <<  "--" << e.what() << std::endl;
    }

    return 0;
}




void lua_init(lua_State *L) {

  lualib_init(L);
}

namespace CobjReg {
  using T = Cobj;
  an<T> make(int x, int y) {
    return New<T>(x,y);
  }

  an<T> add(T& t1, T &t2){
    return  t1 + t2;
  }

  static const luaL_Reg funcs[] = {
    { "Cobj1", WRAP(make) },
    { "Cobj2", WRAP(New<T>) },
    { NULL, NULL },
  };

  static const luaL_Reg methods[] = {
    { "area", WRAPMEM(T, area) },
    { NULL, NULL },
  };

  static const luaL_Reg vars_get[] = {
    { "x", WRAPMEM(T, get_x) },
    { "y", WRAPMEM(T, get_y) },
    { NULL, NULL },
  };

  static const luaL_Reg vars_set[] = {
    { "x", WRAPMEM(T, set_x) },
    { "y", WRAPMEM(T, set_y) },
    { NULL, NULL },
  };

  static const luaL_Reg mt[] = {
    { "__add", WRAPMEM(T::operator+) },
    { NULL, NULL },
  };

}
void lualib_init(lua_State *L) {
  EXPORT(CobjReg, L);
}
