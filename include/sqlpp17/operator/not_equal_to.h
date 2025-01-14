#pragma once

/*
Copyright (c) 2017- 2018, Roland Bock
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

#include <sqlpp17/comparison.h>

namespace sqlpp
{
  struct not_equal_to_t
  {
    static constexpr auto symbol = " != ";
  };
  template<class A0, class A1> class column_t;

  template <class R, class... LArgs>
  constexpr auto operator!=(const column_t<LArgs...> l, R r)
  {
    using L = column_t<LArgs...>;
    if constexpr (constexpr auto _check = check_comparison_args<L, R>(); _check)
    {
      return comparison_t<L, not_equal_to_t, R>{l, r};
    }
    else
    {
      return bad_expression_t{_check};
    }
  }
  template <class L, class... RArgs>
  constexpr auto operator!=(L l, const column_t<RArgs...> r) {
    return r != l;
  }

}  // namespace sqlpp
