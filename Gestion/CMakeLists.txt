cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
if (NOT EXISTS "${d}")
    message(FATAL_ERROR "Error: environment variable IMAGINEPP_ROOT=" "${d}")
endif ()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
find_package(Imagine)

project(Carte)
add_executable(Carte main.cpp carte.h carte.cpp priorite.h priorite.cpp unite.h unite.cpp joueurs.h joueurs.cpp
                outils.cpp outils.h boutons.cpp boutons.h ../Combat/objet.cpp ../Combat/objet.h)
ImagineUseModules(Carte Graphics)
