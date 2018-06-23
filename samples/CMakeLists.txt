# file CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

option(SAMPLE_BASIC_THREAD		"A simple exemple of a thread abtraction class" ON)
option(SAMPLE_BASIC_MUTEX		"A simple exemple of a thread controled by mutex" ON)
option(SAMPLE_TASK_CONSUMER		"A task consumer thread exemple" ON)
option(SAMPLE_EVENT_DRIVEN		"A event driven based thread sample" ON)

if(SAMPLE_BASIC_THREAD)
	add_subdirectory(basic_thread)
endif(SAMPLE_BASIC_THREAD)

if(SAMPLE_BASIC_MUTEX)
	add_subdirectory(basic_mutex)
endif(SAMPLE_BASIC_MUTEX)

if(SAMPLE_TASK_CONSUMER)
	add_subdirectory(task_thread)
endif(SAMPLE_TASK_CONSUMER)

if(SAMPLE_EVENT_DRIVEN)
	add_subdirectory(event_driven)
endif(SAMPLE_EVENT_DRIVEN)