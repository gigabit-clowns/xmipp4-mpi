cmake_minimum_required(VERSION 3.16)

# Define the project
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION PROJECT_VERSION)
string(STRIP "${PROJECT_VERSION}" PROJECT_VERSION)
project(
  xmipp4-mpi
	VERSION ${PROJECT_VERSION}
	LANGUAGES C CXX
)

# Include CMake packages
include(GNUInstallDirs)
include(CTest)

# Declare build options
option(XMIPP4_COMMUNICATION_MPI_LINT_CLANG_TIDY "Lint with clang-tidy" OFF)

# Find xmipp4-core
if(NOT TARGET xmipp4-core)
	find_package(xmipp4-core REQUIRED)
endif()

# Find dependencies
find_package(MPI 3 COMPONENTS CXX REQUIRED)

# Find all source and header files
file(
	GLOB_RECURSE 
	SOURCES 
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

# Create the shared library
add_library(${PROJECT_NAME} MODULE ${SOURCES})
set_target_properties(
	${PROJECT_NAME} 
	PROPERTIES 
		CXX_STANDARD 20
		DEFINE_SYMBOL "XMIPP4_COMMUNICATION_MPI_EXPORTING"
)
target_compile_definitions(
	${PROJECT_NAME} 
	PRIVATE
		VERSION_MAJOR=${CMAKE_PROJECT_VERSION_MAJOR}
		VERSION_MINOR=${CMAKE_PROJECT_VERSION_MINOR}
		VERSION_PATCH=${CMAKE_PROJECT_VERSION_PATCH}
		OMPI_SKIP_MPICXX # Skip C++ binding as it produces errors
)
target_link_libraries(
	${PROJECT_NAME} 
	PRIVATE
		xmipp4-core
		MPI::MPI_CXX
)

# Set up clang-tidy
if(XMIPP4_COMMUNICATION_MPI_LINT_CLANG_TIDY)
	find_program(CLANG_TIDY_EXE clang-tidy REQUIRED)
	set_target_properties(
		${PROJECT_NAME} 
		PROPERTIES 
			CXX_CLANG_TIDY ${CLANG_TIDY_EXE}
	)
endif()

# Enable all warnings during compilation
if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Disable min/max macros in windows
if(MSVC)
	target_compile_definitions(${PROJECT_NAME} PUBLIC -DNOMINMAX)
endif()

# Install library's binary files and headers
install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${XMIPP4_PLUGIN_INSTALL_DIR}
)

# Only build tests if it is the main project
if(BUILD_TESTING)
	add_subdirectory(tests)
endif()
