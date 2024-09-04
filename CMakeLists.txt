cmake_minimum_required(VERSION 3.28)
project(final_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(final_project main.cpp
        Controller.h
        Controller.cpp
        View.h
        View.cpp
        Model.h
        Model.cpp
        ImperialAgent.h
        ImperialAgent.cpp
        Midshipman.h
        Midshipman.cpp
        Commander.h
        Commander.cpp
        Admiral.h
        Admiral.cpp
        AgentFactory.h
        AgentFactory.cpp
        MidshipmanFactory.h
        MidshipmanFactory.cpp
        AdmiralFactory.h
        AdmiralFactory.cpp
        CommanderFactory.h
        CommanderFactory.cpp
        SpaceStation.h
        SpaceStation.cpp
        Station.h
        Station.cpp
        FortressStar.h
        FortressStar.cpp
        SpaceShip.h
        SpaceShip.cpp
        Shuttle.h
        TIEBomber.h
        StarDestroyer.h
        MillenniumFalcon.h
        StarDestroyer.cpp
        TIEBomber.cpp
        MillenniumFalcon.cpp
        Shuttle.cpp
        Exceptions.h
        Exceptions.cpp
        Missile.h
        Missile.cpp
)
