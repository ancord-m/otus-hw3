cmake_minimum_required(VERSION 3.5)

set(ENV{TRAVIS_BUILD_NUMBER} 1)

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
	#COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;"
	COMPILE_OPTIONS "-Wpedantic;-Wextra;-g;"
)

target_include_directories(allocator PRIVATE ${INCLUDE_DIR})

#[[
set_target_properties(bulk_tests PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(bulk_tests PRIVATE ${INCLUDE_DIR})

target_link_libraries(bulk_tests
	${Boost_LIBRARIES}
)

enable_testing()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT leon8005@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

add_test(BlockCreated_WhenCommandQuantityEquals_N 								bulk_tests)
add_test(N_commandsCaptured_N_plus_one_was_ignored 								bulk_tests)
add_test(BlockNotCreated_CommandQuantityLessThan_N 								bulk_tests)
add_test(CommandsInsideCurlyBraces_N_limitIgnored 								bulk_tests)
add_test(CommandsSurroundedBySeveralPairsOfCurlyBraces_OnlyFirstAndLastMatters 	bulk_tests)
add_test(CommandsFinishedBeforeLastClosingCurlyBrace_BulkIsEmpty 				bulk_tests)
add_test(CommandsFinishedBeforeClosingCurlyBrace_BulkIsEmpty 					bulk_tests)
add_test(PreviousBulkWasFinishedForcibly_AtFirstOpeningCurlyBrace 			   	bulk_tests)
]]
