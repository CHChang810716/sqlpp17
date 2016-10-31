#pragma once

/*
Copyright (c) 2016, Roland Bock
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

#include <sqlpp17/pre_join.h>
#include <sqlpp17/on.h>

namespace sqlpp
{
  template <typename PreJoin, typename On>
  class join_t : public join_functions<join_t<PreJoin, On>>
  {
    using _traits = make_traits<no_value_t, tag::is_table, tag::is_join>;
    using _nodes = detail::type_vector<PreJoin, On>;
    using _can_be_null = std::false_type;
    using _provided_tables = provided_tables_of<PreJoin>;
    using _required_tables = detail::make_difference_set_t<required_tables_of<On>, _provided_tables>;

    PreJoin _pre_join;
    On _on;
  };

  template <typename Context, typename PreJoin, typename On>
  struct interpreter_t<Context, join_t<PreJoin, On>>
  {
    using T = join_t<PreJoin, On>;

    static Context& _(const T& t, Context& context)
    {
      interpret(t._pre_join, context);
      interpret(t._on, context);
      return context;
    }
  };
}

