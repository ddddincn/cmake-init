cmake_minimum_required(VERSION 3.20)
project(cmake-init)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/src PROJECT_SOURCES)

# if you need
# find_package()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# if you need
# target_link_libraries(${PROJECT_NAME} ...)