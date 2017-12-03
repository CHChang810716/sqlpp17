#pragma once

/*
Copyright (c) 2017, Roland Bock
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

#include <functional>
#include <memory>
#include <string_view>

#include <mysql/mysql.h>

namespace sqlpp ::mysql
{
  class char_result_t
  {
    std::function<void(std::string_view)> _debug;
    std::unique_ptr<MYSQL_RES, void (*)(MYSQL_RES*)> _handle;

  public:
    char_result_t() = default;
    char_result_t(std::unique_ptr<MYSQL_RES, void (*)(MYSQL_RES*)>&& handle,
                  std::function<void(std::string_view)> debug)
        : _handle(std::move(handle)), _debug(debug)
    {
    }
    char_result_t(const char_result_t&) = delete;
    char_result_t(char_result_t&& rhs) = default;
    char_result_t& operator=(const char_result_t&) = delete;
    char_result_t& operator=(char_result_t&&) = default;
    ~char_result_t() = default;
  };
}  // namespace sqlpp::mysql

