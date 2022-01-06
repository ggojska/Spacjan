//Graphics
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//Standard libs
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <conio.h>
#include <typeinfo>
#include <cstdio>
#include <sstream>

//Screen
#define ScreenW 800
#define ScreenH 600

//Scenes
#define GAME_ERROR -2
#define EXIT_GAME -1
#define MAIN_SCENE 0
#define ADVENTURE_SCENE 1
#define STATS_SCENE 2
#define INVENTORY_SCENE 3
#define MERCHANT_SCENE 4
#define BLACKSMITH_SCENE 5

//eq constants
#define BACKPACK_SIZE 10
#define EQUIPMENT_SIZE 6
#define WEAPON 0
#define SHIELD 1
#define ARMOR 2
#define HELMET 3
#define BOOTS 4
#define AMULET 5
