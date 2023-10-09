
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("osaclient")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.

#[[
set(HOME "${CMAKE_SOURCE_DIR}/../../../../../..")
set(OTU_DIR "${HOME}/Projects/OTU")

#list(APPEND CMAKE_FIND_ROOT_PATH /home/cyangreen/.local)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)

foreach(_target
        keyex_module keyex_grpc_proto)
    add_library(${_target}
            SHARED
            IMPORTED)

    set_target_properties(${_target}
            PROPERTIES IMPORTED_LOCATION
            ${OTU_DIR}/cmake/build/lib${_target}.so)
endforeach()
]]

set(WOLFSSL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/wolfssl")
add_library(WOLFSSL
        SHARED
        IMPORTED)
set_target_properties(WOLFSSL
        PROPERTIES IMPORTED_LOCATION
        "${WOLFSSL_PATH}/lib/libwolfssl.so.35")

if(NOT EXISTS "${WOLFSSL_PATH}/lib/libwolfssl.so.35")
    #build should fail
    message(FATAL_ERROR "failed to find wolfssl during build phase")
endif()

#FILE(GLOB LOCAL_LIBS
#        ${OTU_DIR}/examples/lib/*.a)



add_library(osa-lib SHARED
    # List C/C++ source files with relative paths to this CMakeLists.txt.
    osaclient.cpp
        )

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.

target_link_libraries(osa-lib
    # List libraries link to the target library
        android
        log
        #keyex_module
        #keyex_grpc_proto
        ${WOLFSSL}
        #${LOCAL_LIBS}
        )
target_include_directories(osa-lib PRIVATE
        #${OTU_DIR}/examples/include
        #${OTU_DIR}/src
        ${WOLFSSL_PATH}/include
        )
target_link_directories(osa-lib PRIVATE
        ${WOLFSSL_PATH}/lib
        )

