cmake_minimum_required(VERSION 3.14)
project(NeverMind VERSION 0.0.1)
#set(CMAKE_CXX_STANDARD 11)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/icon.rc")

file(GLOB_RECURSE TARGET_SRC "./src/*.cpp" "./src/*.c")
file(GLOB_RECURSE TARGET_HDR "./src/*.hpp" "./src/*.h")

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_subdirectory(lib/tmxlite)

#FetchContent_Declare(tmxlite URL https://github.com/fallahn/tmxlite/archive/refs/tags/v1.3.1.tar.gz)
#FetchContent_Declare(tmxlite URL https://github.com/fallahn/tmxlite/archive/refs/tags/v1.3.1.tar.gz)
#FetchContent_MakeAvailable(tmxlite)

#FetchContent_GetProperties(tmxlite)
#if(NOT tmxlite_POPULATED)
#    message(WARNING ${tmxlite_SOURCE_DIR})
#    FetchContent_Populate(tmxlite)
#    add_subdirectory(${tmxlite_SOURCE_DIR} ${tmxlite_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()

#sfml
#set(SFML_STATIC_LIBRARIES FALSE)
#set(SFML_DIR "lib/SFML-2.5.1/cmake")
#set(SFML_DIR lib/SFML-2.5.1/cmake/SFML)#$
#set(SFML_DIR "{CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.5.1/lib/cmake/SFML")
#set(SFML_DIR "/lib/SFML-2.5.1/lib/cmake/SFML")
#set(SFML_DIR "lib/SFML-2.5.1/cmake/SFML")
#set(SFML_DIR "{CMAKE_CURRENT_LIST_DIR}/lib/SFML-2.5.1/lib/cmake/SFML")
#NO_DEFAULT_PATH

#find_package(SFML 2.5.1 NO_DEFAULT_PATH COMPONENTS graphics audio REQUIRED)
add_executable(${CMAKE_PROJECT_NAME} WIN32 ${TARGET_HDR} ${TARGET_SRC} ${APP_ICON_RESOURCE_WINDOWS})
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Werror)

#add_custom_target(copy_resources ALL
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ./resources
#        ${PROJECT_BINARY_DIR}/resources
#        COMMENT "Copying resources into binary directory")
add_custom_target(copy_resources
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
        COMMENT "Copying ${CMAKE_SOURCE_DIR}/resources to ${CMAKE_BINARY_DIR}/resources"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
add_dependencies(${CMAKE_PROJECT_NAME} copy_resources)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(main bingitup)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-graphics sfml-audio)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()
#target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio)

##doesn't work, last thing i did is dump the cmake into lib
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE tmxlite)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

