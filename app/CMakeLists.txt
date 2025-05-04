cmake_minimum_required(VERSION 3.6.0)

project(native_render)

add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
        ${ANDROID_NDK}/sources/android/native_app_glue)

set(CMAKE_CXX_STANDARD 23)

# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(algebra
        src/main/cpp/algebra/concepts.h
        src/main/cpp/algebra/common.h
        src/main/cpp/algebra/matrix.h
        src/main/cpp/algebra/matrix2.h
        src/main/cpp/algebra/matrix3.h
        src/main/cpp/algebra/matrix4.h
        src/main/cpp/algebra/vector.h
        src/main/cpp/algebra/vector2.h
        src/main/cpp/algebra/vector3.h
        src/main/cpp/algebra/vector4.h
        src/main/cpp/algebra/quaternion.h
)
set_target_properties(algebra PROPERTIES LINKER_LANGUAGE CXX)

# "tlog" module name to avoid interference with android native "log" module
add_library(tlog
        src/main/cpp/log/log.h
        src/main/cpp/log/log.cpp
)
target_link_libraries(tlog log)

add_library(render
        src/main/cpp/render/render.cpp
        src/main/cpp/render/render.h
        src/main/cpp/render/vk/vulkan/vk_enum_string_helper.h
        src/main/cpp/render/vk/rendervk.cpp
        src/main/cpp/render/vk/rendervk.h
        src/main/cpp/render/vk/main_loop.cpp
        src/main/cpp/render/vk/context.cpp
        src/main/cpp/render/vk/instance.cpp
        src/main/cpp/render/vk/context.h
        src/main/cpp/render/vk/device.cpp
        src/main/cpp/render/vk/swapchain.cpp
        src/main/cpp/render/vk/commands/scene_render_command.cpp
        src/main/cpp/render/vk/commands/scene_render_command.cpp
        src/main/cpp/render/vk/pipelines/pipeline.cpp
        src/main/cpp/render/vk/pipelines/pipeline_matrix_ready.cpp
        src/main/cpp/render/vk/pipelines/pipeline.h
        src/main/cpp/render/vk/pipelines/program.cpp
        src/main/cpp/render/vk/pipelines/program.h
        src/main/cpp/render/vk/pipelines/shader_source.h
)
target_link_libraries(render android native_app_glue tlog)

add_library(${CMAKE_PROJECT_NAME}
        SHARED
        src/main/cpp/glue.cpp
        src/main/cpp/glue.h
)
target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        native_app_glue
        vulkan
        render
        tlog
)