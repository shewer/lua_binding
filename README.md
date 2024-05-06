# lua_binding

```
[         92]  .
├── [         14]  README.md
├── [         86]  src
│   ├── [        356]  library
│   │   ├── [       1251]  common.h            * alias name
│   │   ├── [      18028]  *lua_templates.h    * light userdata 相互轉換 ，主要引用headfile
│   │   ├── [       1189]  *lua.h      * class Lua
│   │   ├── [       7928]  *lua.cc     * class Lua 產生 lua_State
│   │   ├── [       2513]  *lua_export_type.h  * 註冊 c_api 巨集
│   │   ├── [        694]  lua-compat.h  
│   │   ├── [       1964]  lauxlib-compat.c
│   │   ├── [       9209]  lutf8lib-compat.c
│   │   ├── [        179]  optional.h         
│   │   ├── [        605]  luatype_boost_optional.h
│   │   ├── [        579]  luatype_std_optional.h
│   │   └── [       2254]  *result.h LuaResult for lua->call(functional) , lua->void_call(functional) 
│   ├── [       2803]  main.cc  測試 
│   ├── [         70]  test1.lua
│   └── [        191]  test2.lua
└── [       2081]  xmake.lua
```

LuaObj   void LuaObj::pushdata(L, shared_ptr<LuaObj>),  shared_ptr<LuaObj>  LuaObj::todata(L, index)
LuaType  void LuaType<T>::pushdata(L, T obj),              T LuaType<T>::todata(L, index)
Lua      Lua state :    
       LuaResult lua->call<ret, args...>(functional) --   LuaResult (lua_CFUNCTION)(lua_State*, ...)
       void      lua->void_call<args...>(functional) void (lua_CFUNCTION)(Lua_State*) 
       void    , lua->to_state(functional)  void (Lua_CFUNCTION)(lua_State*)
LuaResult   lua->call() 


