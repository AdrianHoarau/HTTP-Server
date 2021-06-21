cmake_minimum_required(VERSION 3.12)
project(phpCgiModule)

set(SRCS_DIR ${PROJECT_SOURCE_DIR}/src)

set(INCLUDE_SERVER_DIR ${PROJECT_SOURCE_DIR}/../../include/Server)
set(SRCS_SERVER_DIR ${PROJECT_SOURCE_DIR}/../../src/Server)


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_SERVER_DIR})

# -------------------------------- SERVER SOURCES -------------------------------- #
set(SRCS_SERVER ${SRCS_SERVER_DIR}/Error.cpp
                ${SRCS_SERVER_DIR}/processingList.cpp
                ${SRCS_SERVER_DIR}/HTTPObject.cpp
)

# -------------------------------- PHPCGIMODULE SOURCES -------------------------------- #
set(SRCS ${SRCS_DIR}/phpCgiModule.cpp
         ${SRCS_DIR}/LinuxCmdExec.cpp
         ${SRCS_DIR}/WindowsCmdExec.cpp

)

# Create shared library
add_library(phpCgiModule SHARED ${SRCS} ${SRCS_SERVER})