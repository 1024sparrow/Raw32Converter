cmake_minimum_required(VERSION 2.8)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)
#find_package(Qt5 REQUIRED COMPONENTS
#	Widgets
#)

add_executable(Raw32Converter
	main.c
	raw32converter.h
	raw32converter.c
)
target_link_libraries(Raw32Converter
	avcodec avformat avfilter avdevice swresample swscale avutil

#	#$<$<PLATFORM_ID:Linux>:pthread>
)

