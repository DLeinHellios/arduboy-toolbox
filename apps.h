#ifndef APPS.H
#define APPS.H


/*
------- APP STATES -------
    0 = Main Menu
    1 = Move Mouse - HID Mouse Jiggler
    2 = Autoclick - HID Automatic Mouse Clicker
    3 = Roll Dice - DnD-style RNG 
--------------------------
*/


// =========== Common Functions =========

// --- Timing ----
void resetCounts() {
    // Reset frame counting for timers
    countFrames = 0;
    countSeconds = 0;
}


void updateCounts() {
    // Keeps counts of frames for timing
    countFrames++;
    if(countFrames >= APP_FPS) {
        countFrames = 0;
        countSeconds++;
    }
}


void increaseSeconds() {
    // Increases delay betweeen timed actions
    if(targetSeconds < MAX_SECONDS) {
        if(targetSeconds >= 120) {
            targetSeconds += 30;
        } else if(targetSeconds >= 60) {
            targetSeconds += 10;
        } else if(targetSeconds >= 10) {
            targetSeconds += 5;
        } else {
            targetSeconds++;
        }
    }
    resetCounts();
}


void decreaseSeconds() {
    // Decreases delay between timed actions
    if(targetSeconds > 0) {
        if(targetSeconds > 120) {
            targetSeconds -= 30;
        } else if(targetSeconds > 60) {
            targetSeconds -= 10;
        } else if(targetSeconds > 10) {
            targetSeconds -= 5;
        } else {
            targetSeconds--;
        }
    }
    resetCounts();
}


// --- HID ---
void activeLED() {
    // Turns on LED if HID tool is active
    if (HIDActive && !lightOn) {
        arduboy.setRGBled(0,100,100);
        lightOn = true;
    } else if (!HIDActive and lightOn) {
        arduboy.setRGBled(0,0,0);
        lightOn = false;
    }
}


void shutoffScreen() {
    // Turns off the display after a time while HID is active
    if (HIDActive) {
        if (screenTimer > SCREEN_SHUTOFF_DELAY) {
            screenOff = true;
        } else {
            screenTimer++;
        }
    } else {
        screenTimer = 0;
    }
}


void wakeScreen() {
    // Wakes screen from sleep
    screenOff = false;
    screenTimer = 0;
}


void resetScreenTimer() {
    // Resets screen timer without waking screen
    screenTimer = 0;
}


// --- Input ---
bool pressAnyButton() {
    arduboy.pollButtons();
    bool pressed = false;

    if (arduboy.justPressed(A_BUTTON)) {
        pressed = true;
    }

    if (arduboy.justPressed(B_BUTTON)) {
        pressed = true;
    }

    if (arduboy.justPressed(UP_BUTTON)) {
        pressed = true;
    }

    if (arduboy.justPressed(DOWN_BUTTON)) {
        pressed = true;
    }

    if (arduboy.justPressed(LEFT_BUTTON)) {
        pressed = true;
    }

    if (arduboy.justPressed(RIGHT_BUTTON)) {
        pressed = true;
    }

    return pressed;
}


// --- Drawing ---
void drawHorizontalArrows(int x, int y) {
    // Horizontal arrow pair for menus
    arduboy.drawPixel(x,y+1);
    arduboy.drawLine(x+1,y,x+1,y+2);
    arduboy.drawPixel(x+4,y+1);
    arduboy.drawLine(x+3,y,x+3,y+2);
}


void drawVerticalArrows(int x, int y) {
    // Vertical arrow pair for menus
    arduboy.drawPixel(x+1,y);
    arduboy.drawLine(x,y+1,x+2,y+1);
    arduboy.drawPixel(x+1,y+4);
    arduboy.drawLine(x,y+3,x+2,y+3);
}

drawRightFacingArrow(int x, int y) {
    // Single right-facing arrow
    arduboy.drawPixel(x+2,y+2);
    arduboy.drawLine(x+1,y+1,x+1,y+3);
    arduboy.drawLine(x,y,x,y+4);
}


// ========== Move Mouse ==========
void moveSetup() {
    // Initializes the move mouse tool
    arduboy.initRandomSeed();
    resetCounts();
    targetSeconds = INIT_MOVE_FREQ;
    moveModeRandom = false;
    appState = 1;
}


void changeMoveMode() {
    // Changes between random and fixed methods of mouse movement
    if(moveModeRandom) {
        moveModeRandom = false;
    } else {
        moveModeRandom = true;
    }
}


void moveInput() {
    // Handles input on move mouse tool
    if (screenOff) {
        // Wake screen, disregard other input on this frame
        if (pressAnyButton()) {
            wakeScreen();
        }

    } else {
        arduboy.pollButtons();

        if(arduboy.justPressed(B_BUTTON)) {
            appState = 0; // Exit to Menu
            HIDActive = false;

        } else if(arduboy.justPressed(UP_BUTTON)) {
            increaseSeconds();
            resetScreenTimer();

        } else if(arduboy.justPressed(DOWN_BUTTON)) {
            decreaseSeconds();
            resetScreenTimer();

        } else if(arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)) {
            changeMoveMode();
            resetScreenTimer();

        } else if(arduboy.justPressed(A_BUTTON)) {
            // Start/Stop Tool
            if(HIDActive) {
                HIDActive = false;
            } else {
                HIDActive = true;
                resetCounts();
            }
        }
    }
}


void moveFixed() {
    // Executes a single mouse movement back-and-forth
    if(countSeconds >= targetSeconds) {
        if(moveLeft) {
            Mouse.move(0-moveDistance,0);
            moveLeft = false;
        } else {
            Mouse.move(moveDistance,0);
            moveLeft = true;
        }
        resetCounts();
    } else {
        updateCounts();
    }
}


void moveRandom() {
    // Executes a single mouse movement to a random distance and direction
    if(countSeconds >= targetSeconds) {
        int x = random(0,101);
        int y = 100 - x;

        if(random(2)) {
            x = 0-x;
        } else if(random(2)) {
            y = 0-y;
        }

        Mouse.move(x,y);
        resetCounts();
    } else {
        updateCounts();
    }
}


void moveUpdate() {
    // Conducts mouse movement
    if(HIDActive) {
        if(moveModeRandom) {
            moveRandom();
        } else {
            moveFixed();
        }
    }
}


void drawMove() {
    // Draws the move mouse tool menu
    if (!screenOff) {
        byte xOffset = 28;
        byte yOffset = 12;

        sprites.drawOverwrite(12 + xOffset,yOffset,titles,0);
        arduboy.drawLine(0 + xOffset,9 + yOffset,73 + xOffset,9 + yOffset);

        drawHorizontalArrows(1 + xOffset,13 + yOffset);
        tinyfont.setCursor(9 + xOffset,12 + yOffset);
        if(moveModeRandom) {
            tinyfont.print("MODE-RANDOM");
        } else {
            tinyfont.print("MODE-FIXED");
        }

        drawVerticalArrows(2 + xOffset,19 + yOffset);
        tinyfont.setCursor(9 + xOffset,20 + yOffset);
        tinyfont.print("FREQUENCY-");
        tinyfont.print(targetSeconds);

        arduboy.drawLine(0 + xOffset,27 + yOffset,73 + xOffset,27 + yOffset);
        tinyfont.setCursor(5 + xOffset,31 + yOffset);
        tinyfont.print("A-");
        if(HIDActive) {
            tinyfont.print("OFF");
        } else {
            tinyfont.print("ON ");
        }
        tinyfont.print("  B-EXIT");
    }
}


// ========== Autoclick ==========
void clickSetup(){
    // Initializes autoclick tool
    arduboy.initRandomSeed();
    resetCounts();
    targetSeconds = INIT_CLICK_FREQ;
    clickDoubleTime = -1;
    clickModeSingle = true;
    appState = 2;
}


void changeClickMode() {
    // Changes between single and double-click modes
    if(clickModeSingle) {
        clickModeSingle = false;
    } else {
        clickModeSingle = true;
    }
}


void clickInput() {
    // Handles input for autoclick tool
    arduboy.pollButtons();
    if(arduboy.justPressed(B_BUTTON)) {
        appState = 0; // Exit to Menu
        HIDActive = false;

    } else if(arduboy.justPressed(UP_BUTTON)) {
        increaseSeconds();
        resetScreenTimer();

    } else if(arduboy.justPressed(DOWN_BUTTON)) {
        decreaseSeconds();
        resetScreenTimer();

    } else if(arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)) {
        changeClickMode();
        resetScreenTimer();

    } else if(arduboy.justPressed(A_BUTTON)) {
        // Start/Stop Tool
        if(HIDActive) {
            HIDActive = false;
        } else {
            HIDActive = true;
            resetCounts();
            clickDoubleTime = -1;
        }
    }
}


void clickSingle() {
    // Executes a single click
    if(countSeconds >= targetSeconds) {
        Mouse.click();
        resetCounts();
    } else {
        updateCounts();
    }
}


void clickDouble() {
    // Executes a double-click
    if(countSeconds >= targetSeconds) {
        Mouse.click();
        clickDoubleTime = DOUBLE_CLICK_SPEED;
        resetCounts();

    } else if(clickDoubleTime > 0) {
        clickDoubleTime--;

    } else if(clickDoubleTime == 0) {
        Mouse.click();
        clickDoubleTime--;

    } else {
        updateCounts();
    }
}


void clickUpdate() {
    // Conducts click actions
    if(HIDActive) {
        if(clickModeSingle) {
            clickSingle();
        } else {
            clickDouble();
        }
    }
}


void drawClick() {
    // Draws autoclick tool menu
    byte xOffset = 28;
    byte yOffset = 12;

    sprites.drawOverwrite(13 + xOffset,yOffset,titles,1);
    arduboy.drawLine(0 + xOffset,9 + yOffset,73 + xOffset,9 + yOffset);

    drawHorizontalArrows(1 + xOffset,13 + yOffset);
    tinyfont.setCursor(9 + xOffset,12 + yOffset);
    if(clickModeSingle) {
        tinyfont.print("MODE-SINGLE");
    } else {
        tinyfont.print("MODE-DOUBLE");
    }

    drawVerticalArrows(2 + xOffset,19 + yOffset);
    tinyfont.setCursor(9 + xOffset,20 + yOffset);
    tinyfont.print("FREQUENCY-");
    tinyfont.print(targetSeconds);

    arduboy.drawLine(0 + xOffset,27 + yOffset,73 + xOffset,27 + yOffset);
    tinyfont.setCursor(5 + xOffset,31 + yOffset);
    tinyfont.print("A-");
    if(HIDActive) {
        tinyfont.print("OFF");
    } else {
        tinyfont.print("ON ");
    }
    tinyfont.print("  B-EXIT");
}


// ========== Roll Dice ==========
void resetResults() {
    for (int i = 0; i < 5; i++) {
        diceResult[i] = 0;
    }
}

void rollSetup() {
    arduboy.initRandomSeed();
    appState = 3;
    diceSelected = 0;
    diceRolled = -1;
    currentRoll = 0;
    resetResults();
}

int maxRoll() {
    int roll = 0;
    for (int r = 0; r < 5; r++) {
        if (diceResult[r] > roll) {
            roll = diceResult[r];
        }
    }

    return roll;
}

int minRoll() {
    int roll = 999;
    for (int r = 0; r < 5; r++) {
        if (diceResult[r] < roll && diceResult[r] > 0) {
            roll = diceResult[r];
        }
    }

    return roll;
}

int sumRolls() {
    int roll = 0;
    for (int r = 0; r < 5; r++) {
        roll += diceResult[r];
    }

    return roll;
}

int avgRolls() {
    int count = 0;
    for (int r = 0; r < 5; r++) {
        if (diceResult[r] > 0) {
            count++;
        }
    }

    return sumRolls() / count;
}

void rollInput() {
    arduboy.pollButtons();
    if (arduboy.justPressed(B_BUTTON)) {
        if (diceRolled > 0) {
            diceRolled = -1;
        } else {
            appState = 0; // Exit to Menu
        }
    }
    if (arduboy.justPressed(DOWN_BUTTON) || arduboy.justPressed(RIGHT_BUTTON)) {
        if (diceSelected < nDice - 1) {
            diceSelected++;
        } else {
            diceSelected = 0;
        }
    }
    if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(LEFT_BUTTON)) {
        if (diceSelected > 0) {
            diceSelected--;
        } else {
            diceSelected = nDice - 1;
        }
    }
    if (arduboy.justPressed(A_BUTTON)) {
        if (!(diceSupported[diceSelected] == diceRolled)) {
            currentRoll = 0;
            resetResults();
        } else if (currentRoll > 4) {
            currentRoll = 0;
        }
        diceRolled = diceSupported[diceSelected];
        diceResult[currentRoll] = random(1,diceRolled+1);
        currentRoll++;
    }
}


void drawRoll() {
    sprites.drawOverwrite(40, 0, titles, 2);
    arduboy.drawLine(0, 9, 128, 9);

    // Select left
    byte textLine = 12;
    for (byte i = 0; i < nDice; i++) {
        tinyfont.setCursor(6, textLine);
        tinyfont.print("D");
        tinyfont.print(diceSupported[i]);
        if (diceSelected == i) {
            drawRightFacingArrow(0, textLine);
        }
        textLine += 6;
    }

    // Results center
    if (diceRolled > 0) {
        tinyfont.setCursor(40,12);
        tinyfont.print("ROLL D");
        tinyfont.print(diceRolled);
        drawRightFacingArrow(45,52);

        for (int r = 0; r < 5; r++) {
            int result;
            if (currentRoll + r >= 5) {
                result = diceResult[currentRoll + r - 5];
            } else {
                result = diceResult[currentRoll + r];
            }

            if (result > 0) {
                arduboy.setCursor(52, 18+(8*r));
                arduboy.print(result);
                if (diceRolled == 2 && result == 1) {
                    arduboy.print("(H)");
                } else if (diceRolled == 2 && result == 2) {
                    arduboy.print("(T)");
                }
            }
        }
    }

    // Stats Right
    if (diceRolled > 0) {
        tinyfont.setCursor(88,22);
        tinyfont.print("MIN:");
        tinyfont.print(minRoll());
        tinyfont.setCursor(88,30);
        tinyfont.print("MAX:");
        tinyfont.print(maxRoll());
        tinyfont.setCursor(88,38);
        tinyfont.print("SUM:");
        tinyfont.print(sumRolls());
        tinyfont.setCursor(88,46);
        tinyfont.print("AVG:");
        tinyfont.print(avgRolls());
    }
}


// ========== Main Menu ==========
void menuInput() {
    // Main menu button input
    if(menuState) {
        arduboy.pollButtons();

        if(arduboy.justPressed(RIGHT_BUTTON)) {
            menuItem++;
            if(menuItem > MAX_MENU_ITEMS) {
                menuItem = 0;
            }

        } else if(arduboy.justPressed(LEFT_BUTTON)) {
            menuItem--;
            if(menuItem < 0) {
                menuItem = MAX_MENU_ITEMS;
            }

        } else if(arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
            switch(menuItem) {
                case 0:
                    moveSetup();
                    break;

                case 1:
                    clickSetup();
                    break;

                case 2:
                    rollSetup();
                    break;
            }
        }
    }
}


void menuUpdate() {
    // Updates menu
    if(!menuState) {
        if(splashWait >= SPLASH_DELAY) {
            menuState = 1;
            splashWait = -1;
        } else if (splashWait >= 0) {
            splashWait++;
        }
    }
}


void drawMenuSelection(int item) {
    // Draws selected app text
    switch(item) {
        case 0:
            tinyfont.setCursor(40,42);
            tinyfont.print("MOVE MOUSE");
            break;

        case 1:
            tinyfont.setCursor(42,42);
            tinyfont.print("AUTOCLICK");
            break;

        case 2:
            tinyfont.setCursor(42,42);
            tinyfont.print("ROLL DICE");
            break;
    }
}


void menuDraw() {
    // Draws menu screens
    switch(menuState) {
        case 0:
            sprites.drawOverwrite(47,10,logo,0);
            if(splashWait < 24) {
                arduboy.fillRect(47,10+splashWait,81,39,BLACK);
            }

            if(splashWait < 31) {
                arduboy.drawLine(64-splashWait,37,64+splashWait,37);
            }

            break;

        case 1:
            // Draw app selection menu
            sprites.drawOverwrite(47,10,logo,0);
            arduboy.drawPixel(35,44);
            arduboy.drawLine(36,45,36,43);
            arduboy.drawPixel(93,44);
            arduboy.drawLine(92,45,92,43);
            arduboy.drawLine(33,37,95,37);
            drawMenuSelection(menuItem);
            break;
    }
}


#endif
