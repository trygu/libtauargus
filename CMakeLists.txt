# Tau-Argus core: data model, Argus/JJ file I/O, and SDC engine entry points.
# Solver-independent. Ported from the legacy NetBeans/MinGW build.
#
# The legacy Windows COM server, VB6, and SWIG/JNI wrapper sources were
# removed from this repo; bindings to the new stack are generated with
# pybind11 (see python/cpp/bind_core.cpp in the top-level repo).

cmake_minimum_required(VERSION 3.16)

project(tauargus_core CXX)

set(CORE_SRC
    src/AMPL.cpp
    src/Code.cpp
    src/DataCell.cpp
    src/General.cpp
    src/Ghmiter.cpp
    src/Hitas.cpp
    src/JJFormat.cpp
    src/PTable.cpp
    src/PTableCont.cpp
    src/Properties.cpp
    src/SubCodeList.cpp
    src/Table.cpp
    src/TauArgus.cpp
    src/Variable.cpp
)

if(WIN32)
    # Compile the Windows version resource (harmless no-op elsewhere).
    list(APPEND CORE_SRC src/Versioninfo.rc)
endif()

add_library(tauargus_core STATIC ${CORE_SRC})
add_library(tauargus::core ALIAS tauargus_core)

# The train version. The superbuild injects it from engine/ENGINE-VERSION;
# a standalone module build reads the same file from the engine root, and
# only a detached core (no engine root) falls back to VERSIONNUMBER in
# defines.h.
if(NOT DEFINED TAUARGUS_ENGINE_VERSION)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../ENGINE-VERSION")
        file(READ "${CMAKE_CURRENT_SOURCE_DIR}/../../ENGINE-VERSION" _TA_EVER)
        string(STRIP "${_TA_EVER}" _TA_EVER)
        set(TAUARGUS_ENGINE_VERSION "${_TA_EVER}")
    else()
        set(TAUARGUS_ENGINE_VERSION "1.1.4.11")
    endif()
endif()
target_compile_definitions(tauargus_core PRIVATE
    TAUARGUS_ENGINE_VERSION="${TAUARGUS_ENGINE_VERSION}")

target_include_directories(tauargus_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(tauargus_core PUBLIC cxx_std_11)

option(TAUARGUS_CORE_BUILD_TESTS "Build native core regression tests" OFF)
if(TAUARGUS_CORE_BUILD_TESTS)
    enable_testing()
    add_executable(test_error_message_buffer tests/test_error_message_buffer.cpp)
    target_link_libraries(test_error_message_buffer PRIVATE tauargus_core)
    add_test(NAME error_message_buffer COMMAND test_error_message_buffer)
    add_executable(test_ptable_columns tests/test_ptable_columns.cpp)
    target_link_libraries(test_ptable_columns PRIVATE tauargus_core)
    add_test(NAME ptable_columns COMMAND test_ptable_columns)
    add_executable(test_cell_copy tests/test_cell_copy.cpp)
    target_link_libraries(test_cell_copy PRIVATE tauargus_core)
    add_test(NAME cell_copy COMMAND test_cell_copy)
    add_executable(test_cell_buffer_sizes tests/test_cell_buffer_sizes.cpp)
    target_link_libraries(test_cell_buffer_sizes PRIVATE tauargus_core)
    add_test(NAME cell_buffer_sizes COMMAND test_cell_buffer_sizes
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/capacity.asc")
    add_executable(test_table_index_guards tests/test_table_index_guards.cpp)
    target_link_libraries(test_table_index_guards PRIVATE tauargus_core)
    add_test(NAME table_index_guards COMMAND test_table_index_guards)
endif()

target_compile_options(tauargus_core PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -fno-strict-aliasing>
)

# MinGW used the Microsoft C runtime on Windows; keep that behaviour there so
# the preprocessor guards that depend on _WIN32 keep working.
if(WIN32)
    target_compile_definitions(tauargus_core PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

install(TARGETS tauargus_core
    ARCHIVE DESTINATION lib
)
install(DIRECTORY src/
    DESTINATION include/tauargus_core
    FILES_MATCHING PATTERN "*.h"
)
