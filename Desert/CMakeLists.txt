cmake_minimum_required(VERSION 3.20.0)

project(Desert LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 指定 Windows SDK 版本
set(CMAKE_SYSTEM_VERSION 10.0.22621.0)

if (WIN32)
    # 生成动态库时，Windows 平台加上这段代码才会输出 lib
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif(UNIX)
    # TODO
endif()

# 递归查找 src 目录下所有 .cpp 和 .h
file(GLOB_RECURSE DesertSources src/*.cpp src/*.h)

# 生成动态库
add_library(${PROJECT_NAME} SHARED ${DesertSources})

# 编译设置
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/MD>
        $<$<CONFIG:Debug>:/MDd>
    )
endif()

# 添加预定义
add_compile_definitions(DESERT_PLATFORM_WINDOWS
DESERT_BUILD_DLL)

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
${CMAKE_CURRENT_LIST_DIR}/vendor/glad/include)

# glfw
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glfw)

# glad
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glad)

# 链接库目录
# target_link_directories(${PROJECT_NAME}
# PRIVATE
# ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/vendor/glfw/src
# ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/vendor/glad/src)

# 如果是项目会优先引用项目，如果不是则链接库
target_link_libraries(${PROJECT_NAME} glfw glad opengl32)

# ---------------------------------------------------------------------------------------------------------------
# 拷贝 DLL 操作
# ---------------------------------------------------------------------------------------------------------------
# 创建文件夹（如果不存在下面复制命令会有报错，例如：Debug 模式下不会生成 Release 目录，复制 Release 目录中的文件时会报错）
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/Debug)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/Release)

# 原文件路径
set(ORIGFILE_DEBUG ${PROJECT_BINARY_DIR}/Debug/${PROJECT_NAME}.dll)
set(ORIGFILE_RELEASE ${PROJECT_BINARY_DIR}/Release/${PROJECT_NAME}.dll)
# 目标文件路径
set(TARGET_FOLDER_NAME "Sandbox")
set(TARGETFILE_DEBUG ${CMAKE_SOURCE_DIR}/${TARGET_FOLDER_NAME}/Debug/${PROJECT_NAME}.dll)
set(TARGETFILE_RELEASE ${CMAKE_SOURCE_DIR}/${TARGET_FOLDER_NAME}/Release/${PROJECT_NAME}.dll)

# 添加生成前创建两个 dll 文件（如果不存在，下面复制命令会有报错）
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E touch "${ORIGFILE_DEBUG}"
)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E touch "${ORIGFILE_RELEASE}"
)

# 添加生成后事件复制 DLL 到主程序下
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy ${ORIGFILE_DEBUG} ${TARGETFILE_DEBUG}
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E 
    copy ${ORIGFILE_RELEASE} ${TARGETFILE_RELEASE}
)
# ---------------------------------------------------------------------------------------------------------------