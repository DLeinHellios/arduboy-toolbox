#ifndef GLOBALS_H
#define GLOBALS_H


Arduboy2 arduboy;
Sprites sprites;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

#define APP_FPS 30 // Application frames per second, used in timing events
#define SPLASH_DELAY 30 // Length of time to display splash screen, in frames
#define DEFAULT_MENU_ITEM 0 // Menu item selected on boot
#define MAX_MENU_ITEMS 1 // Max value of appState
#define MAX_SECONDS 300 // Maximum frequency value for HID timings
#define INIT_MOVE_FREQ 2 // Initial timing for move mouse app
#define INIT_CLICK_FREQ 5 // Initial timing for click mouse app
#define DOUBLE_CLICK_SPEED 4 // Frames between double clicks
#define SCREEN_SHUTOFF_DELAY 300 // Frames before screen shuts off while HID active

byte appState = 0;
byte menuState = 0;
int menuItem = DEFAULT_MENU_ITEM;

int splashWait = 0;
int screenTimer = 0;
bool screenOff = false;
bool lightOn = false;


// Timing
bool HIDActive = false;
byte countFrames = 0; // Counts frames while HID is active
int countSeconds = 0; // Counts seconds while HID is active
int targetSeconds = 0; // User-set time in seconds

// Move Mouse
bool moveModeRandom = false; // For selecting between random and controlled mode
bool moveLeft = true; // Used in alternating mouse move direction
int moveDistance = 5; // Distance to move mouse horizontally, in pixels

// Autoclick
bool clickModeSingle = true; // Mode select for autoclick - single/double
int clickDoubleTime;

#endif
