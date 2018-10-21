cmake_minimum_required(VERSION 3.7)

# Set the project name
project(DHT11)

set(CMAKE_CXX_STANDARD 14)

# Have CMake find our pthreads library within our toolchain (required for this library)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

#Find the wiringPi library
find_library(wiringPi_LIB wiringPi)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
        src/main.cpp
        src/dht.cpp)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})


target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${wiringPi_LIB} ${CMAKE_THREAD_LIBS_INIT} crypt m rt
        ${PROJECT_SOURCE_DIR}/include

        )
