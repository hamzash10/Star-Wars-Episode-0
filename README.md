# Star Wars Episode Zero

## Overview

This project is a **C++ simulation** designed to simulate the activities of the Galactic Empire, inspired by **Star Wars**. The simulation follows a **Model-View-Controller (MVC)** design pattern and demonstrates concepts like object-oriented programming, design patterns, and advanced simulation mechanics.

## Features

- **Object-oriented design**: Implements key principles of OOP using C++.
- **MVC architecture**: Separation of concerns between the Model, View, and Controller.
- **Space Simulation**: Includes different types of Imperial agents and spacecraft, such as:
    - **Shuttles** for crystal transportation.
    - **Bombers** for patrolling.
    - **Star Destroyers** with advanced weaponry.
    - **The Millennium Falcon** as a smuggling and attack ship.
- **Simulation world**: A 2D Euclidean space where various objects interact in real-time, based on user commands.

## Simulation Objects

- **Agents**: Imperial agents categorized as Midshipman, Commander, or Admiral. Each controls a specific ship type.
- **Ships**:
    - **Shuttle**: Transports crystals between space stations and fortresses.
    - **Bomber**: Patrols between stations.
    - **Star Destroyer**: Engages in combat with long-range attacks.
    - **Millennium Falcon**: Attacks Imperial shuttles to steal crystals.

## Technologies Used

- **C++**: The entire project is implemented in C++.
- **Design Patterns**: Utilizes patterns like Singleton and Abstract Factory.
- **Memory Management**: Includes the use of smart pointers for efficient resource management.


## Input Format Examples
The simulation takes user commands in the following format:

**Create Imperial agents**:

- create admiral <**name**>
- create commander <**name**> 
- create midshipman <**name**>


2. **Create spacecraft**:

- create destroyer <**name**> <**pilot_name**> (<x_coord>, <y_coord>)
- create bomber <**name**> <**pilot_name**> (<x_coord>, <y_coord>)
- create shuttle <**name**> <**pilot_name**> (<x_coord>, <y_coord>)
- create falcon <**name**> (<x_coord>, <y_coord>)


3. **Move spacecraft**:

- <**ship_name**> course <**angle**> <**speed**>
- <**ship_name**> destination <**dest_location**>
- <**ship_name**> start_supply <**src_location**> <**dest_location**>
- <**ship_name**> course <**angle**>
- <**falcon_name**> course <**angle**> <**speed**>

## Example Usage
- create admiral Tarkin
- create commander Ozzel
- create midshipman Peter
- create destroyer T0 Tarkin (24.00, 24.00)
- create bomber B2 Ozzel (40.00, 10.00)
- create shuttle GX Peter (0.00, 0.00)
- create falcon Millennium (42.00, 42.00)
- Time 0: Enter command : create admiral Tarkin
- Time 0: Enter command : create destroyer T0 Tarkin (24.00, 24.00)
- Time 1: Enter command : T0 course 180 20
- Time 2: Enter command : go
- Time 3: Enter command : status


## Code Structure
1. **Model**: Manages the simulation's state, including space stations, fortresses, ships, and agents.
2. **View**: ASCII-based map visualization.
3. **Controller**: Manages user input and translates commands into actions within the simulation.

## License
This project is for educational purposes.