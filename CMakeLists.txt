project(nne)
cmake_minimum_required(VERSION 3.0)
include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/inc"
	"${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/flatbuffers/include"
)
file(GLOB SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
)
set(CMAKE_CXX_FLAGS "--std=c++11 -fsigned-char -Wall -Wno-comment -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_custom_command (
	OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/inc/instPacket_generated.h"
	COMMENT "Compiling flatbuffer idl file."
	DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/idl/instPacket.fbs"
	WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/idl"
	COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/flatbuffers/build/flatc" --cpp instPacket.fbs
	COMMAND mv instPacket_generated.h  "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

add_executable(nne
	"${SRCS}"
	"${CMAKE_CURRENT_SOURCE_DIR}/inc/instPacket_generated.h"
)
#target_link_libraries(nnc ${PROTOBUF_LIBRARIES})
