cmake_minimum_required(VERSION 3.5)

project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(INCLUDE_DIR include)

set(SRC_DIR src)

set(SRC_LIST
		${SRC_DIR}/main.cpp
   )

add_executable(allocator ${SRC_LIST})

set_target_properties(allocator PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;"
)

target_include_directories(allocator PRIVATE ${INCLUDE_DIR})

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT leon8005@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)