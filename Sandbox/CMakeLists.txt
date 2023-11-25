cmake_minimum_required(VERSION 3.20.0)

project(Sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 指定 Windows SDK 版本
set(CMAKE_SYSTEM_VERSION 10.0.22621.0)

# 设置 VS 启动项目
if (MSVC)
    set_property (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

# 递归查找 src 目录下所有 .cpp 和 .h
file(GLOB_RECURSE CMakeTESTSources src/*.cpp src/*.h)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${CMakeTESTSources})

# 编译设置
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/MD>
        $<$<CONFIG:Debug>:/MDd>
    )
endif()

# 添加预定义
add_compile_definitions(DESERT_PLATFORM_WINDOWS)

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

# include 目录
target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_LIST_DIR}/src)

# 如果是项目会优先引用项目，如果不是则链接库
target_link_libraries(${PROJECT_NAME} Desert)