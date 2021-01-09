#pragma once

namespace sqlpp
{
  template<class Op, class ArgF0, class... ArgF>
  inline auto vapply(const Op& optr, ArgF0&& argf0, ArgF&&... argfs) {
    auto x0 = argf0();
    if constexpr(sizeof...(ArgF) == 0) {
      return x0;
    } else {
      return optr(x0, vapply(
        optr, std::forward<ArgF>(argfs)...
      ));
    }
  }
  template<class RT, class Op, class... ArgF>
  inline RT vapply_allow_empty(const Op& optr, ArgF&&... argfs) {
    if constexpr(sizeof...(ArgF) == 0) {
      return RT{};
    } else {
      return vapply(optr, std::forward<ArgF>(argfs)...);
    }
  }
} // namespace sqlpp
