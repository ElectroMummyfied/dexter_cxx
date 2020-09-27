cmake_minimum_required(VERSION 3.6.0 FATAL_ERROR)

project(dexter VERSION 0.0.1 LANGUAGES C CXX)

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/template
	${PROJECT_SOURCE_DIR}/src
)

file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/template/*"
	"${PROJECT_SOURCE_DIR}/src/*"
)

add_executable(test ${SRCS})

list(APPEND flags "-fpermissive")

target_compile_options(test
	PRIVATE
		${flags}
)

set_target_properties(test
	PROPERTIES
		C_STANDARD 11
		CXX_STANDARD 17
		CXX_EXTENSIONS OFF
		CXX_STANDARD_REQUIRED ON
		POSITION_INDEPENDENT_CODE 0
)