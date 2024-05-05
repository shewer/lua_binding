//
// Copyright RIME Developers
// Distributed under the BSD License
//
// 2011-03-14 GONG Chen <chen.sst@gmail.com>
//

#ifndef _COMMON_H_
#define _COMMON_H_

#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::function;
using std::list;
using std::make_pair;
using std::make_unique;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

template <class Key, class T>
using hash_map = std::unordered_map<Key, T>;
template <class T>
using hash_set = std::unordered_set<T>;

template <class T>
using the = std::unique_ptr<T>;
template <class T>
using an = std::shared_ptr<T>;
template <class T>
using of = an<T>;
template <class T>
using weak = std::weak_ptr<T>;

template <class X, class Y>
inline an<X> As(const an<Y>& ptr) {
  return std::dynamic_pointer_cast<X>(ptr);
}

template <class X, class Y>
inline bool Is(const an<Y>& ptr) {
  return bool(As<X, Y>(ptr));
}

template <class T, class... Args>
inline an<T> New(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}



#endif  // _COMMON_H_
