#pragma once

using namespace std;

//stauts
const int BLANK = 0;
const int WALL = 1;
const int ROOM = 2;
const int CORRIDOR = 3;
const int CHECK = 4;
const int TARGET = 5;
const int SEARCH_WALL = 6;
const int SEARCH_TARGET = 7;
const int START = 8;
const int CHECK_TARGET = 9;
const int CHECK_WALL = 10;
const int SEARCH = 11;
const int SEARCH_CORRIDOR = 12;
const int CHECK_CORRIDOR = 13;
const int PACMAN = 14;
const int ENEMY = 15;
const int TOKEN = 16;
const int SWITCH_TOKEN = 17;
const int CHECK_ROOM = 18;
const int SEARCH_ROOM = 19;
const int CHECK_TOKEN = 20;
const int SEARCH_TOKEN = 21;
const int CHECK_SWITCH_TOKEN = 22;
const int SEARCH_SWITCH_TOKEN = 23;
const int CHECK_ENEMY = 24;
const int SEARCH_ENEMY = 25;


//Window loading data
const int WINDOW_SIZE_X = 600;
const int WINDOW_SIZE_Y = 600;
const int WINDOW_POSITION_X = 200;
const int WINDOW_POSITION_Y = 100;

const int NUM_OF_PIXEL = 40;

static  const char* WINDOW_NAME = "PACMAN";

//Room data
const int MAX_NUMBER_OF_ROOMS = 6;
const int MAX_NUM_OF_ATTEMPTS = 1000;
const int SIZE_OF_ROOM_MIN = 2;
const int SIZE_OF_ROOM_MAX = 4 + SIZE_OF_ROOM_MIN;
const int MIN_DISTANCE_FOR_ROOM = 3;
const int MIN_DISTANCE_FROM_EDGE = 2;
const int MAX_DISTANCE_FROM_TARGET = 60;

const int NUM_OF_TOKENS = 5;

//AStar data
const double ROUTE = 0.8;
const double WALL_ROUTE = -1;

//Direction
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NO_DIRECTION = -1;

//State type
const int GO_TO_TOKEN = 0;
const int GO_TO_SWITCH = 1;
const int RUN = 2;
const int CHASE = 3;

//Entity data
const int MIN_ENIMY_DISTANCE = 20;
const int MAX_TIMER = 25;
const double CHASE_ROUTE = 1;
const double PACMAN_ROUTE = 1;


