cmake_minimum_required(VERSION 3.16)
project(ScoreBoard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)   # gère moc automatiquement
set(CMAKE_AUTOUIC ON)   # gère uic automatiquement (plus besoin de ton .bat !)
set(CMAKE_AUTORCC ON)   # au cas où tu ajoutes des ressources plus tard

# Indique où trouver Qt (adapte le chemin à ta version)
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.2/mingw_64")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(ScoreBoard
    main.cpp
    ui/ScoreBoardParty.ui
    ui/NewParty.ui
    ui/NewPlayer.ui
)

target_link_libraries(ScoreBoard PRIVATE Qt6::Widgets)