cmake_minimum_required(VERSION 3.20.0)

project(Desert LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 指定 Windows SDK 版本
set(CMAKE_SYSTEM_VERSION 10.0.22621.0)

# # 优化设置
# if (CMAKE_BUILD_TYPE MATCHES Release)
#     set(CMAKE_CXX_FLAGS "-O3")
# elseif (CMAKE_BUILD_TYPE MATCHES Debug)
#     set(CMAKE_CXX_FLAGS "-g")
# elseif (CMAKE_BUILD_TYPE MATCHES Dist)
#     set(CMAKE_CXX_FLAGS "-O3")
# endif ()

# 设置构建类型
# set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist")

add_subdirectory(Desert)
add_subdirectory(Sandbox)