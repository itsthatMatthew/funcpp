#pragma once
#include <utility> // std::forward

// The helper struct for implementing the Y combinator (fixed-point combinator)
// for lambdas, where the fixed point is achieved by passing the struct itself
// back to the lambda before any arguments are applied.
template<class R, class F>
struct LAMBDA_FIX {
  F f;
  template<class... Args>
  constexpr R operator()(Args&&... args) const {
    return f(*this)(std::forward<Args>(args)...);
  }
};

// Y is a global helper function to create a fixed-point combinator for lambdas
template<class R, class F>
constexpr auto Y(F&& f) {
  return LAMBDA_FIX<R, F>{std::forward<F>(f)};
}
