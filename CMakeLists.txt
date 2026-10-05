# Tau-Argus core: data model, Argus/JJ file I/O, and SDC engine entry points.
# Solver-independent. Ported from the NetBeans/MinGW Makefile.
#
# The COM/Visual-Basic-6 sources (GhmiterANCO, TauArgCtrl, StdAfx, NewTauArgus)
# and the SWIG JNI wrapper (TauArgusJava_wrap) are intentionally excluded;
# bindings to the new stack are generated with pybind11 instead of SWIG.

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
    set_source_files_properties(src/Versioninfo.rc PROPERTIES LANGUAGE C)
endif()

add_library(tauargus_core STATIC ${CORE_SRC})
add_library(tauargus::core ALIAS tauargus_core)

target_include_directories(tauargus_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(tauargus_core PUBLIC cxx_std_11)

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
