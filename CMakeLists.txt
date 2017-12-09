cmake_minimum_required(VERSION 3.5)

project(Project)

find_package(Qt5Core)
find_package(Qt5Widgets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install/")
set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od")

########
# Пути #
########

set(REPO_ROOT       ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ROOT      ${REPO_ROOT}/cmake)
set(FOUNDATION_ROOT ${REPO_ROOT}/foundation)
set(SOURCE_ROOT     ${REPO_ROOT}/src)

set(VISION_APP_ROOT ${SOURCE_ROOT}/Application/VisionApp)
set(CORE_ROOT       ${SOURCE_ROOT}/Core)
set(CAPTURE_ROOT    ${SOURCE_ROOT}/Capture)
set(PROC_ROOT       ${SOURCE_ROOT}/Proc)
set(UTILS_ROOT      ${SOURCE_ROOT}/Utils)
set(TYPES_ROOT      ${SOURCE_ROOT}/Types)

set(THIRDPARTY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)

# Module path
set(CMAKE_MODULE_PATH
	${CMAKE_ROOT}
	${FOUNDATION_ROOT}
	${SOURCE_ROOT}
	${CORE_ROOT}
	${CAPTURE_ROOT}
	${PROC_ROOT}
	${TYPES_ROOT}
	${UTILS_ROOT}
	${VISION_APP_ROOT}
)

###############
# Configuring #
###############

include(${FOUNDATION_ROOT}/Target.cmake)

# cmake functions
include(${FOUNDATION_ROOT}/LinkLibraries.cmake)

include(${CMAKE_ROOT}/ProductConfig.cmake)

include(${TYPES_ROOT}/Types.cmake)
include(${CORE_ROOT}/Core.cmake)
include(${PROC_ROOT}/Proc.cmake)
include(${CAPTURE_ROOT}/Capture.cmake)
include(${UTILS_ROOT}/Utils.cmake)

set(EXECUTABLE_NAME "Core")
include(${CMAKE_ROOT}/LibrariesList.cmake)
LinkLibraries(${EXECUTABLE_NAME} "" COMMON_LIBS_PATH COMMON_LIBS)
LinkLibraries(${EXECUTABLE_NAME} OPENCV_INCLUDES_PATH OPENCV_LIBS_PATH OPENCV_LIBS)

set(EXECUTABLE_NAME "Proc")
include(${CMAKE_ROOT}/LibrariesList.cmake)
LinkLibraries(${EXECUTABLE_NAME} "" COMMON_LIBS_PATH COMMON_LIBS)
LinkLibraries(${EXECUTABLE_NAME} OPENCV_INCLUDES_PATH OPENCV_LIBS_PATH OPENCV_LIBS)
LinkLibraries(${EXECUTABLE_NAME} DLIB_INCLUDES_PATH DLIB_LIBS_PATH DLIB_LIBS)

set(EXECUTABLE_NAME "Capture")
target_link_libraries(${EXECUTABLE_NAME} PUBLIC "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/Vfw32.Lib")
include(${CMAKE_ROOT}/LibrariesList.cmake)
LinkLibraries(${EXECUTABLE_NAME} "" COMMON_LIBS_PATH COMMON_LIBS)
LinkLibraries(${EXECUTABLE_NAME} OPENCV_INCLUDES_PATH OPENCV_LIBS_PATH OPENCV_LIBS)

# Подключаем исполняемый проект
include(${VISION_APP_ROOT}/VisionApp.cmake)
set(EXECUTABLE_NAME "VisionApp")
