#pragma once

/*
Copyright (c) 2016 - 2019, Roland Bock
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

#include <sqlpp17/to_sql_name.h>
#include <sqlpp17/utils.h>

namespace sqlpp
{
  namespace type_vector_to_sql_name_detail {
    template<class Context, class ColumnSpec>
    struct TypeVectorToSQLNameHelper {
      TypeVectorToSQLNameHelper(Context& context)
      : context_(context)
      {}
      auto operator()() const {
        return ", " + to_sql_name(context_, ColumnSpec{});
      }
      Context& context_;
    };
  }
  template <typename Context, typename FirstColumnSpec, typename... ColumnSpecs>
  [[nodiscard]] constexpr auto type_vector_to_sql_name(Context& context,
                                                  sqlpp::type_vector<FirstColumnSpec, ColumnSpecs...>)
  {
    return vapply(
      std::plus<void>{},
      [&]() { return to_sql_name(context, FirstColumnSpec{}); },
      type_vector_to_sql_name_detail::TypeVectorToSQLNameHelper<Context, ColumnSpecs>{context}...
    );
  }
}  // namespace sqlpp
