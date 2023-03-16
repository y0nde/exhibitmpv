cmake_minimum_required(VERSION 3.0)

project(mpvapp)

# You can comment/Uncomment this line if you wish to have slacking display
add_definitions(-DSLACKING_VERBOSE_OUTPUT=1)

# option(SLACKING_VERBOSE_OUTPUT "If you wish to have slacking display"  OFF)
option(CURL_STATIC_LINKING "Set to ON to build libcurl with static linking."  OFF)
  
if(CURL_STATIC_LINKING)
    message("-DCURL_STATICLIB [added]")
    add_definitions(-DCURL_STATICLIB)
endif()

add_definitions(-DJSON_USE_IMPLICIT_CONVERSIONS=0)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})
message("Using compiler ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

if ("${CMAKE_MAJOR_VERSION}${CMAKE_MINOR_VERSION}" LESS 31)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_executable(mpvapp
    main.cpp
    command.cpp
    commandsender.cpp
    scheduler.cpp
    schedulereader.cpp
    slack.cpp
    timer.cpp
    )
set_property(TARGET mpvapp PROPERTY CXX_STANDARD 11)
set_property(TARGET mpvapp PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(mpvapp ${CURL_LIBRARIES})
    
