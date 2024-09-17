# CMakeList.txt : CMake project for INF1015_TD_A24, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (TD2_A24 "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TD2_A24 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
