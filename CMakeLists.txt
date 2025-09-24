cmake_minimum_required(VERSION 4.1.1)
project(zmake VERSION 1.0.2)
add_executable(zmake src/main.cc src/zmake.hh src/zmake.cc)

# Fetch CPR dependancy for ZMake::getLatestCmake
include(FetchContent)
FetchContent_Declare(
   cpr
   GIT_REPOSITORY https://github.com/libcpr/cpr.git
   GIT_TAG 1.10.5
)
FetchContent_MakeAvailable(cpr)
target_link_libraries(zmake PRIVATE cpr::cpr)
