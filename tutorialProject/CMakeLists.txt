cmake_minimum_required(VERSION 3.1.0)
project(tutorialProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(tutorial tutorial.cpp)

add_subdirectory(mathFunctions)

target_link_libraries(tutorial PUBLIC mathFunctions)

install(TARGETS tutorial
	RUNTIME DESTINATION bin)

install(EXPORT mathFunctionsTargets
	FILE mathFunctionsTargets.cmake
	NAMESPACE mathFunctions::
	DESTINATION lib/cmake/mathFunctions)
