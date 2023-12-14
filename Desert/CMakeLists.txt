cmake_minimum_required(VERSION 3.20.0)

project(Desert LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 指定 Windows SDK 版本
set(CMAKE_SYSTEM_VERSION 10.0.22621.0)

# 递归查找 src 目录下所有 .cpp 和 .h 以及其他
file(GLOB_RECURSE DesertSources
src/*.cpp
src/*.h
vendor/glm/*.hpp
vendor/glm/*.inl)

# 生成动态库
add_library(${PROJECT_NAME} STATIC ${DesertSources})

# 编译设置
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/MD>
        $<$<CONFIG:Debug>:/MDd>
    )
endif()

# 添加预定义
add_compile_definitions(DESERT_PLATFORM_WINDOWS
DESERT_BUILD_DLL
# 抑制警告
_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)

# 根据构建配置添加预定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
# 生成器扩展
$<$<CONFIG:Debug>:DESERT_DEBUG>
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
$<$<CONFIG:Release>:DESERT_RELEASE>
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
$<$<CONFIG:Dist>:DESERT_DIST>
)

# 设置预编译头
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/DesertPCH.h)

# include 目录
target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_LIST_DIR}/src
${CMAKE_CURRENT_LIST_DIR}/vendor/spdlog/include
${CMAKE_CURRENT_LIST_DIR}/vendor/glfw/include
${CMAKE_CURRENT_LIST_DIR}/vendor/glad/include
${CMAKE_CURRENT_LIST_DIR}/vendor/imgui
${CMAKE_CURRENT_LIST_DIR}/vendor/glm)

# glfw
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glfw)

# glad
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glad)

# imgui
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/imgui)

# 链接库目录
# target_link_directories(${PROJECT_NAME}
# PRIVATE
# ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/vendor/glfw/src
# ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/vendor/glad/src)

# 如果是项目会优先引用项目，如果不是则链接库
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad opengl32 imgui)