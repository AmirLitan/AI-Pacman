
## AI Pac-Man Game Project

This project is an demo that shows how AI algorithms can build and run a random Pac-Man game without any human interaction.
The AI uses A* and Unifromcust algorithms to find and choose the right path for every senior.
Seniors are chosen by an FSM algorithm, for example Pac-Man (the Player) is searching for tokens(senior one) until an enemy is closer.
When the enemy is closer pacman moves to search a switch point (senior two).

The project is Written in C++ and runs OpenGL library for the view
and utilizes OOP and design patterns principles.

The project uses an VDC (view, data, controller) design pattern:
```
1. Controller – handles all AI/FSM algorithms and contact between the view and the data. 
2. View – handles view logic.
3. Data – containing all data (entities, cells, game data).
4. State – handles the different states.
```
### Class Discerption

Main – Create a GameController class and runs idle and display.

GameController – Control the game, creating the map and running AI algorithms as well as controlling the view output.

Entity – Represent Pac-Man(player) or enemy(ghost).

CompareAStar – Return true if the F in cell1 is bigger than cell2 ( F = distance(H) + path(G) ).

CompareUnifromCost – Return true if the G in cell1 is bigger than cell2 ( path(G) ).

Data – Containing  all constant data of the game.

View – Handles all view outputs.

State – Abstract class for different kinds of states or behavior of Entities.


### Class degerm

![AIPacman](https://user-images.githubusercontent.com/76840396/208319598-501fe8ab-6744-4e8e-aac6-9703c8d2593f.jpg)

### FSM explanation

The FSM handles the behavior of the entities.
Every behavior is represented by a class that is a child of an abstract state class.
The states move in a cyclic method.

(example: 1 -> 2, 2 -> 3, 3 -> 4, 4 -> 1)

#### There are four state:

#### State 1 - GoToNearestTokenState:
```
Player behavior:
  By using Unifromcust algorithm finds the nearest token and
   move to the token direction by using A* path finder algorithm
Enemy behavior:
  Move to next state
```
#### State 2 - GoToNearestTokenState:
```
Player behavior
  By using Unifromcust algorithm finds the nearest Switch and
   move to the token direction by using A* path finder algorithm
Enemy behavior
  Move to next state
```
#### State 3 - GoToNearestTokenState:
```
Player behavior
  Move to next state
Enemy behavior
  Using A* to find the direction of the player and moves to the opposite direction
```
#### State 4 - GoToNearestTokenState:
```
Player behavior
  Using A* to find the direction of the player and moves to that direction
Enemy behavior
  Using A* to find the direction of the player and moves to that direction
```
### General description of the algorithm

1.	Randomly built rooms according to a range of parameters.
2.	Connecting the rooms by using A* algorithm.
3.	Dividing the different entities into rooms and distributing tokens and switch points.
4.	Game start:
	- Iterate through all entities.
    - If it's player, it searches for a token by searching UnifromCost and sets it as a target in addition pacman also searches for an enemy and records the distance to it (G).
    - Player advances to target by using A* also searches for an enemy by searching UnifromCost  and records the distance to him (G).
    - If the enemy is closer than the target: the player will switch state and search (in the same way) for a switch coin.
    - Once the player lands on a switch coin: the player will change state into chase state and enemy will go into escape state for some number of iterations.
    - If in this state player gets on top of an enemy, he will be deleted from the game.
    - In any other situation when an enemy gets to the player the game is over.
    - If the player collects all the tokens the game is over.
    - The enemies throughout the game move to the player by using A*.

### Technology

C/C++ , OpenGL
