cmake_minimum_required(VERSION 3.5)

project(MyVector)

set(HEADERS
	myvector.h)

add_executable(myvector ${HEADERS})

set_target_properties(myvector PROPERTIES
	CXX_STANDART 11
	CXX_STANDART_REQUIRED ON
)