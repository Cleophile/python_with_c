cmake_minimum_required(VERSION 3.15)
SET(PROJ_NAME hello)
PROJECT(${PROJ_NAME})

ADD_DEFINITIONS(-std=c++17)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_BUILD_TYPE RELEASE)

LINK_DIRECTORIES(
	/usr/local/lib/
)

# From python3.9-config --includes --libs
INCLUDE_DIRECTORIES(
	/usr/local/include
    /usr/local/opt/python@3.9/Frameworks/Python.framework/Versions/3.9/include/python3.9
)

# Without this, any build libraries automatically have names "lib{x}.so"
set(CMAKE_SHARED_MODULE_PREFIX "")

FIND_PACKAGE(PythonLibs 3.9 REQUIRED)
MESSAGE("LOG: python_include_dirs " ${PYTHON_INCLUDE_DIRS})
MESSAGE("LOG: Python libraries " ${PYTHON_LIBRARIES})

FIND_PACKAGE(gflags REQUIRED)
FIND_PACKAGE(glog REQUIRED)
FIND_PACKAGE(Boost COMPONENTS python REQUIRED)
MESSAGE("LOG: Boost libraries" ${Boost_LIBRARIES})

ADD_LIBRARY(${PROJ_NAME} MODULE hello.cc)

# Set up the libraries and header search paths for this target
# TARGET_LINK_LIBRARIES(${PROJ_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
# TARGET_INCLUDE_DIRECTORIES(${PROJ_NAME} PRIVATE ${PYTHON_INCLUDE_DIRS})
