cmake_minimum_required(VERSION 3.12)
project(zia)

set(INCLUDES_SERVER_DIR ${PROJECT_SOURCE_DIR}/include/Server)
set(SRCS_SERVER_DIR ${PROJECT_SOURCE_DIR}/src/Server)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Threads)
if (UNIX)
    link_libraries(stdc++fs)
endif()

# -------------------------------- SERVER SOURCES -------------------------------- #
set(SRCS_SERVER ${SRCS_SERVER_DIR}/main.cpp
                ${SRCS_SERVER_DIR}/jsonReader.cpp
                ${SRCS_SERVER_DIR}/Error.cpp
                ${SRCS_SERVER_DIR}/pathHandler.cpp
                ${SRCS_SERVER_DIR}/serverCore.cpp
                ${SRCS_SERVER_DIR}/tcpConnection.cpp
                ${SRCS_SERVER_DIR}/processingList.cpp
                ${SRCS_SERVER_DIR}/HTTPObject.cpp
                ${SRCS_SERVER_DIR}/requestManager.cpp
                ${SRCS_SERVER_DIR}/configHandler.cpp
                ${SRCS_SERVER_DIR}/SignalHandler.cpp
                ${SRCS_SERVER_DIR}/moduleManager.cpp
                ${SRCS_SERVER_DIR}/ASocketHandler.cpp
)

add_executable(zia ${SRCS_SERVER})
target_compile_features(zia PRIVATE cxx_std_17)
target_compile_options(zia
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /std:c++17 /TP>
                       $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3 -Wno-unused-local-typedefs>)
target_include_directories(zia PRIVATE SYSTEM ${INCLUDES_SERVER_DIR})
target_link_libraries(zia ${CONAN_LIBS})
target_link_libraries(zia ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(zia ${CMAKE_DL_LIBS})


add_subdirectory(modules)

if (UNIX)
    include(CTest)
    enable_testing(MAKE_DIRECTORY tests)#
    add_subdirectory(tests)
endif (UNIX)