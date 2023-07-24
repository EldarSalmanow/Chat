cmake_minimum_required(VERSION 3.23)
project(Chat)

set(CMAKE_CXX_STANDARD 20)

if (${MSVC})
    add_compile_options(/utf-8)
endif()

set(EXTERNAL_INCLUDE_DIRS )
set(EXTERNAL_LIBS         )

# Boost

find_package(Boost REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set(EXTERNAL_LIBS         ${EXTERNAL_LIBS}         ${Boost_LIBRARIES})

# GSCrossPlatform

find_package(GSCrossPlatform 1.0 REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${GSCrossPlatform_INCLUDE_DIRS})
set(EXTERNAL_LIBS         ${EXTERNAL_LIBS}         ${GSCrossPlatform_LIBRARIES})

# Server

add_executable(Server Server.cpp)

target_include_directories(Server PRIVATE ${EXTERNAL_INCLUDE_DIRS})

target_link_libraries(Server PRIVATE ${EXTERNAL_LIBS})

# Client

add_executable(Client Client.cpp)

target_include_directories(Client PRIVATE ${EXTERNAL_INCLUDE_DIRS})

target_link_libraries(Client PRIVATE ${EXTERNAL_LIBS})
