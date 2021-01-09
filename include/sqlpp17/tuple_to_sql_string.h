#pragma once

/*
Copyright (c) 2016 - 2017, Roland Bock
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

#include <string>
#include <tuple>

#include <sqlpp17/to_sql_string.h>

#include <sqlpp17/utils.h>

namespace sqlpp ::detail
{

namespace tuple_to_sql_string_detail {

  template <typename Context, typename T, std::size_t I>
  struct TupleToSQLStringImplHelper {
    TupleToSQLStringImplHelper(
      Context& context, 
      const std::string& separator, 
      const T& t
    )
    : context_(context)
    , separator_(separator)
    , t_(t)
    {}
    auto operator()() const {
      return ((I ? separator_ : "") + to_sql_string(context_, std::get<I>(t_)));
    }
  private:
    Context& context_;
    const std::string& separator_;
    const T& t_;
  };
} 
  template <typename Context, typename... Ts, std::size_t... Is>
  [[nodiscard]] auto tuple_to_sql_string_impl(Context& context,
                                              const std::string& separator,
                                              const std::tuple<Ts...>& t,
                                              std::integer_sequence<std::size_t, Is...>)
  {
    return vapply_allow_empty<std::string>(
      std::plus<void>{},
      tuple_to_sql_string_detail::TupleToSQLStringImplHelper<
        Context, std::tuple<Ts...>, Is
      >{context, separator, t}...
    );
  }
}  // namespace sqlpp::detail

namespace sqlpp
{
  template <typename Context, typename... Ts>
  [[nodiscard]] auto tuple_to_sql_string(Context& context, const std::string& separator, const std::tuple<Ts...>& t)
  {
    return detail::tuple_to_sql_string_impl(context, separator, t, std::make_index_sequence<sizeof...(Ts)>());
  }
}  // namespace sqlpp
