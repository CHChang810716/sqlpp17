# Copyright (c) 2016, Roland Bock
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this
#    list of conditions and the following disclaimer in the documentation and/or
#    other materials provided with the distribution.
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

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
include(cmake/HunterGate.cmake)
set(
    HUNTER_CACHE_SERVERS
    "https://github.com/CHChang810716/hunter-binary-cache"
    CACHE
    STRING
    "Hunter cache servers"
)
HunterGate(
    URL "https://github.com/CHChang810716/hunter.git"
    SHA1 62eee92093b4cd36e80ca033689d4abb7e2def32
)
project(sqlpp17 VERSION 0.1 LANGUAGES CXX)

include(FeatureSummary)

option(USE_MYSQL    "use mysql connector"       OFF)
option(USE_PGSQL    "use postgresql connector"  OFF)
option(USE_SQLITE   "use sqlite3 connector"     OFF)
option(ENABLE_TESTS "build test code"           OFF)
enable_testing()

add_library(sqlpp17 INTERFACE)
set(inst_targets sqlpp17)

target_include_directories(sqlpp17 INTERFACE
  $<BUILD_INTERFACE:${sqlpp17_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/sqlpp17"
        DESTINATION include
)
if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()
add_subdirectory(connectors)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(AKT_GEN_DIR             "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(AKT_CONFIG_INSTALL_DIR  "lib/cmake/${PROJECT_NAME}")
set(AKT_CONFIG_VERSION      "${AKT_GEN_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(AKT_PROJECT_CONFIG      "${AKT_GEN_DIR}/${PROJECT_NAME}Config.cmake")
set(AKT_TARGETS_EXPORT      "${PROJECT_NAME}Targets")
set(AKT_NAMESPACE           "${PROJECT_NAME}::")
configure_package_config_file(
    cmake/Config.cmake.in
    ${AKT_PROJECT_CONFIG}
    INSTALL_DESTINATION ${AKT_CONFIG_INSTALL_DIR}
)
write_basic_package_version_file(
    ${AKT_CONFIG_VERSION} COMPATIBILITY SameMajorVersion
)
install(
    FILES ${AKT_PROJECT_CONFIG}
    DESTINATION ${AKT_CONFIG_INSTALL_DIR}
)
install(
    TARGETS ${inst_targets}
    EXPORT ${AKT_TARGETS_EXPORT}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Develop
)
install(
    EXPORT ${AKT_TARGETS_EXPORT}
    NAMESPACE ${AKT_NAMESPACE}
    DESTINATION ${AKT_CONFIG_INSTALL_DIR}
)


feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
