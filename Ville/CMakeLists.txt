cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
if(NOT EXISTS "${d}")
    message(FATAL_ERROR "Error: environment variable IMAGINEPP_ROOT=" "${d}")
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
find_package(Imagine)

project(Ville)
add_executable(Ville main.cpp ville.h ville.cpp
        ../Gestion/carte.h ../Gestion/carte.cpp ../Gestion/unite.h ../Gestion/unite.cpp
        ../Gestion/priorite.h ../Gestion/priorite.cpp ../Gestion/outils.h ../Gestion/outils.cpp
        ../Gestion/boutons.cpp ../Gestion/boutons.h ../Combat/objet.cpp ../Combat/objet.h)
ImagineUseModules(Ville Graphics)
