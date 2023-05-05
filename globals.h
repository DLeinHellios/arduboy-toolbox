#ifndef GLOBALS_H
#define GLOBALS_H


Arduboy2 arduboy;
Sprites sprites;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

#define APP_FPS 30 // Application frames per second, used in timing events
#define SPLASH_DELAY 30 // Length of time to display splash screen, in frames
#define DEFAULT_MENU_ITEM 2 // Menu item selected on boot
#define MAX_MENU_ITEMS 2 // Max value of appState
#define MAX_SECONDS 300 // Maximum frequency value for HID timings
#define INIT_MOVE_FREQ 2 // Initial timing for move mouse app
#define INIT_CLICK_FREQ 5 // Initial timing for click mouse app
#define DOUBLE_CLICK_SPEED 4 // Frames between double clicks
#define SCREEN_SHUTOFF_DELAY 300 // Frames before screen shuts off while HID active

byte appState = 0;
byte menuState = 0;
int menuItem = DEFAULT_MENU_ITEM;

int splashWait = 0; // Count frames for boot animation
int screenTimer = 0; // Count frames to toggle screen on/off
bool screenOff = false; // Is screen currently off?
bool lightOn = false; // Is LED currently on?


// Timing
bool HIDActive = false; // Is an HID tool currently active
byte countFrames = 0; // Counts frames while HID is active
int countSeconds = 0; // Counts seconds while HID is active
int targetSeconds = 0; // User-set time in seconds

// Move Mouse
bool moveModeRandom = false; // For selecting between random and controlled mode
bool moveLeft = true; // Used in alternating mouse move direction
int moveDistance = 5; // Distance to move mouse horizontally, in pixels

// Autoclick
bool clickModeSingle = true; // Mode select for autoclick - single/double
int clickDoubleTime = 0; // Count frames between double-clicks

// Roll Dice
const int nDice = 8; // Number of dice supported
int diceSupported[nDice] = {2,4,6,8,10,12,20,100}; // Array of supported dice max values
int diceSelected = 0; // Currently selected dice
int diceRolled = -1; // Dice currently rolled with results
int diceResult[5] = {0}; // Array of dice results history
int currentRoll = 0; // Tracks position in diceResult
int rollStats[4] = {0}; // Stats for current diceResults [min,max,sum,avg]
float rollAvg = 0.0; // Float for better avg

#endif
