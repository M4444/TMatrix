# Version 3.8 is the first version that supports CXX_STANDARD 17.
cmake_minimum_required(VERSION 3.8)
project(TMatrix CXX)

# Use the C++17 standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup different build types. Release is the default.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Add linking with pthread.
set(CMAKE_EXE_LINKER_FLAGS "-pthread")

# Add the required ncurses library.
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
link_libraries(${CURSES_LIBRARIES})

# Link libatomic because some OSes require explicitly linking it.
find_library(ATOMIC_LIB atomic)
# Check if libatomic is present (it may not be, for example on macOS)
if(NOT ATOMIC_LIB)
	link_libraries(${ATOMIC_LIB})
endif()

# Add all the .cpp files.
file(GLOB tmatrix_SRC "src/*.cpp")
add_executable(tmatrix ${tmatrix_SRC})

# Specify the include directory.
include_directories(include)

install(TARGETS tmatrix DESTINATION bin)
