// Toolbox.ino - A collection of useful tools for the Arduboy
// Code by DLeinHellios - Title font by ZN

#include <Arduboy2.h>
#include <Sprites.h>
#include <Mouse.h>
#include <Tinyfont.h>

#include "globals.h"
#include "bitmaps.h"
#include "apps.h"


void setup() { // Runs once at start
    arduboy.begin();
    Mouse.begin();
    arduboy.setFrameRate(APP_FPS);
}


void loop() { // Main Loop
    if(!arduboy.nextFrame()) {return;}
    arduboy.clear();

    switch(appState) {
        case 0: // Main Menu
            menuInput();
            menuUpdate();
            menuDraw();
            break;

        case 1: // Move Mouse
            drawMove();
            moveInput();
            moveUpdate();
            break;

        case 2: // Autoclick
            drawClick();
            clickInput();
            clickUpdate();
            break;

        case 3: // Roll Dice
            drawRoll();
            rollInput();
            rollUpdate();
            break;
    }

    activeLED();
    shutoffScreen();

    arduboy.display();
}
