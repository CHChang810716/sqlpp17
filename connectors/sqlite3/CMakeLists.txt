# Copyright (c) 2017 - 2018, Roland Bock
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
#   Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
#   Redistributions in binary form must reproduce the above copyright notice, this
#   list of conditions and the following disclaimer in the documentation and/or
#   other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

find_package(Threads REQUIRED)

# option(SQLCIPHER "Build with SQLCipher" Off)
# 
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# if(SQLCIPHER)
#   find_package(SQLCipher)
#   set_package_properties(SQLCipher PROPERTIES URL "https://www.zetetic.net/sqlcipher/" DESCRIPTION "Full Database Encryption for SQLite" TYPE OPTIONAL)
#   set (SQLITE3_LIBRARIES "${SQLCIPHER_LIBRARIES}" )
#   set (SQLITE3_INCLUDE_DIRS "${SQLCIPHER_INCLUDE_DIRS}" )
#   set (SQLITE3_LIBRARY "${SQLCIPHER_LIBRARY}")
#   set (SQLITE3_FOUND ${SQLCipher_FOUND})
# else()
#   find_package(Sqlite3)
#   set_package_properties(Sqlite3 PROPERTIES URL "https://www.postgresql.org/" DESCRIPTION "Sqlite3 support" TYPE OPTIONAL)
# endif()

if (USE_SQLITE)
    hunter_add_package(sqlite3)
    find_package(sqlite3 CONFIG REQUIRED)
    set_package_properties(Sqlite3 PROPERTIES URL "https://www.sqlite.org/index.html" DESCRIPTION "Sqlite3 support" TYPE OPTIONAL)
    add_library(sqlpp17-connector-sqlite3 INTERFACE)

    target_include_directories(sqlpp17-connector-sqlite3 INTERFACE
        ${SQLITE3_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )

    target_link_libraries(sqlpp17-connector-sqlite3 INTERFACE sqlpp17)
    target_link_libraries(sqlpp17-connector-sqlite3 INTERFACE sqlite3::sqlite3)

    list(APPEND inst_targets sqlpp17-connector-sqlite3)
    set(inst_targets ${inst_targets} PARENT_SCOPE)

    add_subdirectory(tests)

    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/sqlpp17"
            DESTINATION include
            FILES_MATCHING PATTERN "*.h")
endif()
