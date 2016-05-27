cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
if (NOT EXISTS "${d}")
    message(FATAL_ERROR "Error: environment variable IMAGINEPP_ROOT=" "${d}")
endif ()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
find_package(Imagine)

project(Jeu)
add_executable(Jeu main.cpp carte.h carte.cpp priorite.h priorite.cpp unite.h unite.cpp joueurs.h joueurs.cpp
                outils.cpp outils.h boutons.cpp boutons.h objet.cpp objet.h testgraph.cpp outilsaff.h outilsaff.cpp
        outilscontr.h outilscontr.cpp constante.h constante.cpp case_graph.h case_graph.cpp map_graph.h map_graph.cpp
        include_graph.h ecran.h ecran.cpp bouton_graph.h bouton_graph.cpp icone_graph.h icone_graph.cpp)
ImagineUseModules(Jeu Graphics)
