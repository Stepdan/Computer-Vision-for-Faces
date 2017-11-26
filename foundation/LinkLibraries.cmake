# Функция линковки внешних библиотек к executable цели.

function(LinkLibraries EXECUTABLE_NAME INCLUDE_PATH LIB_PATH LIB_LIST)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(suffix "d.lib")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(suffix ".lib")
endif()

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${${INCLUDE_PATH}})
message("Add additional includes for ${EXECUTABLE_NAME}: ${${INCLUDE_PATH}}")

foreach(lib ${${LIB_LIST}})
	set(libname "${${LIB_PATH}}/${lib}${suffix}")
	target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${libname})
	message("Linking external library for ${EXECUTABLE_NAME}: ${libname}")
endforeach()

message("")

endfunction()
