cmake_minimum_required(VERSION 3.16)
project(ScoreBoard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)   # gère moc automatiquement
set(CMAKE_AUTOUIC OFF)  # les fichiers ui_*.h sont générés directement dans ui/
set(CMAKE_AUTORCC ON)   # au cas où tu ajoutes des ressources plus tard

# Indique où trouver Qt (adapte le chemin à ta version)
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.2/mingw_64")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(UI_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ui")

add_custom_command(
    OUTPUT "${UI_DIRECTORY}/ui_ScoreBoardParty.h"
    COMMAND "$<TARGET_FILE:Qt6::uic>"
            "${UI_DIRECTORY}/ScoreBoardParty.ui"
            -o "${UI_DIRECTORY}/ui_ScoreBoardParty.h"
    DEPENDS "${UI_DIRECTORY}/ScoreBoardParty.ui"
)

add_custom_command(
    OUTPUT "${UI_DIRECTORY}/ui_NewParty.h"
    COMMAND "$<TARGET_FILE:Qt6::uic>"
            "${UI_DIRECTORY}/NewParty.ui"
            -o "${UI_DIRECTORY}/ui_NewParty.h"
    DEPENDS "${UI_DIRECTORY}/NewParty.ui"
)

add_custom_command(
    OUTPUT "${UI_DIRECTORY}/ui_NewPlayer.h"
    COMMAND "$<TARGET_FILE:Qt6::uic>"
            "${UI_DIRECTORY}/NewPlayer.ui"
            -o "${UI_DIRECTORY}/ui_NewPlayer.h"
    DEPENDS "${UI_DIRECTORY}/NewPlayer.ui"
)

add_executable(ScoreBoard
    ui/ScoreBoardParty.ui
    ui/NewParty.ui
    ui/NewPlayer.ui
    resources.qrc
    "${UI_DIRECTORY}/ui_ScoreBoardParty.h"
    "${UI_DIRECTORY}/ui_NewParty.h"
    "${UI_DIRECTORY}/ui_NewPlayer.h"
    main.cpp
    include/scoreboardparty.h
    include/newplayer.h
    include/newparty.h
    include/elo_utils.h

    source/scoreboardparty.cpp
    source/newparty.cpp
    source/newplayer.cpp
)

target_link_libraries(ScoreBoard PRIVATE Qt6::Widgets)
target_include_directories(ScoreBoard PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)

if(WIN32)
    target_link_options(ScoreBoard PRIVATE "-mwindows")
    target_sources(ScoreBoard PRIVATE app.rc)

    find_program(WINDEPLOYQT_EXECUTABLE
        NAMES windeployqt.exe windeployqt
        HINTS "${CMAKE_PREFIX_PATH}/bin"
    )

    if(NOT WINDEPLOYQT_EXECUTABLE)
        message(FATAL_ERROR "windeployqt.exe est introuvable dans ${CMAKE_PREFIX_PATH}/bin")
    endif()

    add_custom_command(TARGET ScoreBoard POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                --no-translations
                --compiler-runtime
                "$<TARGET_FILE:ScoreBoard>"
        COMMENT "Copie des DLL Qt et des plugins a cote de ScoreBoard.exe"
    )
endif()