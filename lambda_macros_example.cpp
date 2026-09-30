#include "lambda_macros.hpp" // λxy.E -> λ(x, y, E)
#include "lambda_combinators.hpp" // Y fixed-point combinator implementation

auto main() -> int // Why not make everything a lambda, eh?
{
  // true ≡ λx.λy.x (≡ λxy.x)
  constexpr auto TRUE = λ(x, λ(y, x));
  // false ≡ λxy.y
  constexpr auto FALSE = λ(x, y, y);

  // Let's make - with just this power - some horrors beyond human comprehension!

  // Making pairs:
  // pair ≡ λxyz.zxy
  constexpr auto PAIR = λ(x, y, z, z(x)(y));
                         // ^~~ Precedence dictates the left-associativity
                         // required for applications, and this form looks
                         // visually more similar to λxyz.zxy as well
  constexpr auto FIRST = λ(x, x(TRUE));
  constexpr auto SECOND = λ(x, x(FALSE));

  constexpr auto p = PAIR(2)(3); // God, I wish for you hell existed,
  static_assert(FIRST(p) == 2);  //   but it does not,
  static_assert(SECOND(p) == 3); //     so there must be consequences.

  // Making linked lists:
  constexpr auto CONS = λ(x, y, PAIR(FALSE)(PAIR(x)(y)));
  constexpr auto NIL = PAIR(TRUE)(TRUE);
  constexpr auto HEAD = λ(x, FIRST(SECOND(x)));
  constexpr auto TAIL = λ(x, SECOND(SECOND(x)));

  constexpr int E1 = 1, E2 = 2, E3 = 3;

  constexpr auto Ep = CONS(E1)(NIL);
  constexpr auto Epp = CONS(E2)(Ep);
  constexpr auto Eppp = CONS(E3)(Epp);

  static_assert(HEAD(Eppp) == E3);
  static_assert(HEAD(TAIL(Eppp)) == E2);
  static_assert(HEAD(TAIL(TAIL(Eppp))) == E1);
  static_assert(HEAD(Ep) == E1);

  // Recursion needs a 'Y' fixed-point combinator, which needs lazy evaluation,
  // and cannot be expressed with the generic return type of decltype(auto) used
  // by the macro definition, hence the Y fixed-point combinator is a *tad* more
  // complex, but it does work.
  constexpr auto FACT = Y<int>(λ(f, λ(n, n == 0 ? 1 : n * f(n - 1))));

  static_assert(FACT(5) == 120);

  // Celsius and Fahrenheit - typed lambda calculus
  constexpr auto C = λ(x, x > 30);
  constexpr auto F = λ(x, x > 90);

  constexpr auto Celsius = λ(p, q, r, q(p));
  constexpr auto Fahrenheit = λ(p, q, r, r(p));

  constexpr auto w = λ(t, t(C)(F));

  static_assert(w(Celsius(20)) == false);
  static_assert(w(Celsius(40)) == true);
  static_assert(w(Fahrenheit(80)) == false);
  static_assert(w(Fahrenheit(100)) == true);
}
