## Escaping Baddies Game

This project is a text based dungeon escape game, where the user tries the reach the exit of a dungeon while avoiding obstacles and monsters.

Project originally based and original files from UIC Programming Practicum course.

## How it works

First, the user selects the settings for the game such as dungeon size and number of monsters.

Once set up, the user is presented with the game board. Now they can take control of the Hero using the directional inputs

<table>
  <caption>Inputs</caption>
  <tr>
    <td>Q</td>
    <td>W</td>
    <td>E</td>
  </tr>
  <tr>
    <td>A</td>
    <td>S</td>
    <td>D</td>
  </tr>
  <tr>
    <td>Z</td>
    <td>X</td>
    <td>C</td>
  </tr>
</table>

<table>
  <caption>Move</caption>
  <tr>
    <td>NW</td>
    <td>North</td>
    <td>NE</td>
  </tr>
  <tr>
    <td>West</td>
    <td>Stay</td>
    <td>East</td>
  </tr>
  <tr>
    <td>SW</td>
    <td>South</td>
    <td>SE</td>
  </tr>
</table>

and try to reach the exit.


## Files

* main.cpp - The main file of the project. Contains the main functionality of the project.
* grid.h - Contains the Grid class representing the underlying grid system of the game
* boardcell.h - Contains the BoardCell class and its derived classes. Each class represents on cell/element on the game board
* gameboard.h - Contains the Gameboard class, utlizes the Grid and BoardCell class to help create the actual game board the user interacts with
* game.exe - A compiled executeable of the project
