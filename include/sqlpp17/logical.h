#pragma once

/*
Copyright (c) 2018, Roland Bock
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this
   list of conditions and the following disclaimer in the documentation and/or
   other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <sqlpp17/as_base.h>
#include <sqlpp17/bad_expression.h>
#include <sqlpp17/embrace.h>
#include <sqlpp17/to_sql_string.h>
#include <sqlpp17/type_traits.h>
#include <sqlpp17/wrapped_static_assert.h>

namespace sqlpp
{
  template <typename L, typename Operator, typename R>
  struct logical_t : public as_base<logical_t<L, Operator, R>>
  {
    logical_t() = delete;
    constexpr logical_t(L l, R r) : _l(l), _r(r)
    {
    }
    logical_t(const logical_t&) = default;
    logical_t(logical_t&&) = default;
    logical_t& operator=(const logical_t&) = default;
    logical_t& operator=(logical_t&&) = default;
    ~logical_t() = default;

    L _l;
    R _r;
  };

  template <typename L, typename Operator, typename R>
  struct nodes_of<logical_t<L, Operator, R>>
  {
    using type = type_vector<L, R>;
  };

  template <typename L, typename R>
  using check_logical_args = std::enable_if_t<has_boolean_value_v<L> and has_boolean_value_v<R>>;

  template <typename L, typename Operator, typename R>
  struct value_type_of<logical_t<L, Operator, R>>
  {
    using type = bool;
  };

  template <typename L, typename Operator, typename R>
  constexpr auto requires_braces_v<logical_t<L, Operator, R>> = true;

  template <typename Context, typename L, typename Operator, typename R>
  [[nodiscard]] auto to_sql_string(Context& context, const logical_t<L, Operator, R>& t)
  {
    auto l = to_sql_string(context, embrace(t._l));
    auto r = to_sql_string(context, embrace(t._r));
    return l + Operator::symbol + r;
  }

  template <typename Context, typename Operator, typename R>
  [[nodiscard]] auto to_sql_string(Context& context, const logical_t<none_t, Operator, R>& t)
  {
    return Operator::symbol + to_sql_string(context, embrace(t._r));
  }

  template <typename Context, typename L1, typename Operator, typename R1, typename R2>
  [[nodiscard]] auto to_sql_string(Context& context, const logical_t<logical_t<L1, Operator, R1>, Operator, R2>& t)
  {
    auto l = to_sql_string(context, embrace(t._l));
    auto r = to_sql_string(context, embrace(t._r));
    return l + Operator::symbol + r;
  }

}  // namespace sqlpp
