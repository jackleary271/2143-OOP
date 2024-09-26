# *****************************************************************************
#
#  Author:           Jack Leary
#  Personal Email:   jackleary645@gmail.com
#  School Email:     jeleary0604@my.msutexas.edu
#  Label:            PO1
#  Title:            Fraction Class
#  Course:           2143 OOP
#  Semester:         Fall 2024
#
#****************************************************************************/

﻿# CMakeList.txt : CMake project for Project1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Project1 "fraction.cpp" "Fraction.h" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Project1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
