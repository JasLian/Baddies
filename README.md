## Escaping Baddies Game

This project is a text based dungeon escape game, where the user tries the reach the exit of a dungeon while avoiding obstacles and monsters.

Project originally based and original files from UIC Programming Practicum course.

## How it works

First, the user selects the settings for the game such as dungeon size and number of monsters.

Once set up, the user is presented with the game board. Now they can take control of the Hero using the directional inputs

Q | W | E     NW |   N   | NE 
A | S | D      W |  Stay | E
Z | X | C     SW |   S   | SE

and try to reach the exit.


## Files

* main.cpp - The main file of the project. Contains the main functionality of the project.
* grid.h - Contains the Grid class representing the underlying grid system of the game
* boardcell.h - Contains the BoardCell class and its derived classes. Each class represents on cell/element on the game board
* gameboard.h - Contains the Gameboard class, utlizes the Grid and BoardCell class to help create the actual game board the user interacts with
* game.exe - A compiled executeable of the project
