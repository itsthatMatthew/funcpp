/// Man I really didn't want to write this one qwq

#pragma once
#include <utility> // std::forward

template<class R, class F>
struct LAMBDA_FIX {
  F f;
  template<class... Args>
  constexpr R operator()(Args&&... args) const {
    return f(*this)(std::forward<Args>(args)...);
  }
};

template<class R, class F>
constexpr auto Y(F&& f) {
  return LAMBDA_FIX<R, F>{std::forward<F>(f)};
}
