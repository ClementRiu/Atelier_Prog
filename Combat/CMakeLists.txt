cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
if (NOT EXISTS "${d}")
    message(FATAL_ERROR "Error: environment variable IMAGINEPP_ROOT=" "${d}")
endif ()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
find_package(Imagine)

project(Combat)
add_executable(Combat main.cpp objet.cpp objet.h
            ../Gestion/carte.h ../Gestion/carte.cpp ../Gestion/unite.h ../Gestion/unite.cpp
            ../Gestion/priorite.h ../Gestion/priorite.cpp ../Gestion/outils.h ../Gestion/outils.cpp
            ../Gestion/boutons.cpp ../Gestion/boutons.h)
ImagineUseModules(Combat Graphics)
