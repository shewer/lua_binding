#ifndef LUATYPE_OPTIONAL_H
#define LUATYPE_OPTIONAL_H

#include "lua_templates.h"

#if __cplusplus >= 201703L || _MSVC_LANG >= 201703L
#include <optional>
using optional = std::optional;
#else
#include <boost/optional.hpp>
using optional = boost::optional;
#endif

template<typename T>
struct LuaType<optional<T>> {
  static void pushdata(lua_State *L, optional<T> o) {
    if (o)
      LuaType<T>::pushdata(L, *o);
    else
      lua_pushnil(L);
  }

  static optional<T> &todata(lua_State *L, int i, C_State *C) {
    if (lua_type(L, i) == LUA_TNIL)
      return C->alloc<boost::optional<T>>();
    else
      return C->alloc<optional<T>>(LuaType<T>::todata(L, i, C));
  }
};


#endif /* LUATYPE_OPTIONAL_H */
