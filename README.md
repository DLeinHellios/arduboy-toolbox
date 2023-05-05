# Toolbox - Useful Tools for the Arduboy
![Title](images/readme_title.png)

## Description
Turn the Arduboy into a useful pocket device! Part productivity, part annoy-o-tron, this is a collection of tools packaged in a single Arduboy sketch. The Arduboy, in all its portable glory, seemed a perfect match for automating very simple keyboard & mouse tasks, and making use of its tiny screen to display helpful information. The goal of this project is to produce several small tools, expanding the utility of the Arduboy as a productive pocket gadget. Toolbox requires the [Arduboy2](https://github.com/MLXXXp/Arduboy2) and [TinyFont](https://github.com/MLXXXp/Arduboy2) libraries.

## Tools
**Mouse Move** - Automatically jiggles your mouse via USB HID*
	- Supports two modes; fixed and random
	- Fixed mode makes fine movements back-and-forth
	- Random mode moves the mouse erratically
	- Supports variable time intervals


**Autoclick** - Automatically clicks your mouse via USB HID*
	- Random or precise left mouse clicks
	- Supports variable time intervals


**Roll Dice** - Roll a set of DnD-styled dice
	- Supports D2, D4, D6, D8, D10, D12, D20, and D100
	- Store up to 5 concurrent rolls


*HID tools will blank the screen after a duration while active without user input. Obviously only work on original hardware!

*More tools to be added*

## Note on Timing
The sketch runs at 30 FPS by default and relies on the timing of the [Arduboy2 library](https://github.com/MLXXXp/Arduboy2), which conducts 62.5 frames per second at a designated 60 FPS. Nothing has been done to correct the timing disparity, so tools run slightly faster than the displayed frequency values (in seconds). A frequency of zero will run each of the 30 frames per second.

## Credits
Code by [DLeinHellios](https://github.com/dleinhellios) </br>
Title font by ZN </br>
Thanks to the [Arduboy2](https://github.com/MLXXXp/Arduboy2) and [TinyFont](https://github.com/yinkou/Arduboy-TinyFont) projects
