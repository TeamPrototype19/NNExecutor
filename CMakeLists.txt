project(nne)
cmake_minimum_required(VERSION 3.0)
include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/inc"
	"${CMAKE_CURRENT_SOURCE_DIR}/inc/builtin-kernels"
	"${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/flatbuffers/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/libs"
)
file(GLOB SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/builtin-kernels/*.cc"
)
#set(CMAKE_CXX_FLAGS "--std=c++11 -fsigned-char -Wall -Wno-comment -g")
set(CMAKE_CXX_FLAGS "--std=c++11 -fsigned-char -Wall -Wno-comment -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_definitions( -DCL_TARGET_OPENCL_VERSION=200)
add_definitions( -DLOG_LEVEL=0 )
add_definitions( -DDUMP_LEVEL=0 )

add_custom_command (
	OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/inc/instPacket_generated.h"
	COMMENT "Compiling flatbuffer fbs file."
	DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/fbs/instPacket.fbs"
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/fbs"
	COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/flatbuffers/build/flatc" --cpp instPacket.fbs
	COMMAND mv instPacket_generated.h  "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

add_executable(nne
	"${SRCS}"
	"${CMAKE_CURRENT_SOURCE_DIR}/inc/instPacket_generated.h"
)
target_link_libraries(nne "-lpthread -lMali")
