*This project has been created as part of the 42 curriculum by tle-rhun and lozhao.*

# cub3D - My first RayCaster with miniLibX

## Description
[cite_start]**cub3D** is a 3D graphical simulation project inspired by the world-famous 1992 game *Wolfenstein 3D*, which is widely considered the first First-Person Shooter (FPS) ever created[cite: 3, 10]. 

[cite_start]The goal of this project is to explore the principles of **Raycasting** in C to render a dynamic, real-time 3D perspective from inside a maze using a grid-based map configuration file[cite: 4, 22, 123]. [cite_start]The program parses a scene description file (`*.cub`), validates the environment constraints, and handles window management, smooth player movement, and camera rotations using the **miniLibX** graphics library[cite: 23, 107, 109, 123].

---

## Features
### Mandatory Part
* [cite_start]**Real-time 3D Raycasting:** Smooth rendering of a maze using Raycasting principles[cite: 4, 107].
* [cite_start]**Texture Mapping:** Wall textures vary dynamically depending on which cardinal direction the wall is facing (North, South, East, West)[cite: 112].
* [cite_start]**Configurable Environment:** Custom floor and ceiling colors parsed directly from the configuration file[cite: 116].
* [cite_start]**Controls:** * `W`, `A`, `S`, `D` keys to move the player's point of view through the maze[cite: 119].
  * [cite_start]Left and Right arrow keys to look around[cite: 118].
  * [cite_start]`ESC` or clicking the window's red cross frame closes the window and terminates the program cleanly[cite: 120, 121].

### Bonus Part
* **Wall Collisions:** Prevents the player from walking through walls (handled by `lozhao`).
* [cite_start]**Mouse Rotation:** Rotate the point of view dynamically using the mouse cursor (handled by `lozhao`)[cite: 215].
* [cite_start]**Centred Minimap:** A 2D minimap displayed in real-time on top of the window (handled by `tle-rhun`)[cite: 212].
  * Size is dynamically constrained to 1/5th of the smallest window dimension (width or height).
  * The player is represented as a red square fixed right in the center of the minimap.
  * *Color indicators:* Black represents empty space, Brown represents doors, and transparent spaces define map boundaries.
* [cite_start]**Interactive Doors:** Functional doors that can be opened or closed (handled by `tle-rhun`)[cite: 213].
  * Configured with `2` in the `.cub` map layout when closed.
  * To interact, look directly at the door and press the `F` key. Once opened, its internal state updates to `3`, allowing the player to pass through seamlessly.

---

## Instructions

### Prerequisites
[cite_start]To compile and run this project, you need the standard C development tools along with the **X11** and **miniLibX** graphical dependency headers installed on your system[cite: 35, 107, 109].

### Compilation
[cite_start]The project includes a robust `Makefile` configured with `-Wall -Wextra -Werror` flags[cite: 35]. [cite_start]It contains the following targets[cite: 37, 38]:

* [cite_start]`make` or `make all`: Compiles the mandatory version of the program[cite: 37].
* [cite_start]`make bonus`: Compiles the extended version including collisions, minimap, doors, and mouse rotations[cite: 38, 211, 212, 213, 215].
* [cite_start]`make clean`: Removes binary object files (`.o`)[cite: 37].
* [cite_start]`make fclean`: Removes object files as well as the compiled executable[cite: 37].
* [cite_start]`make re`: Recompiles the whole project from scratch[cite: 37].

### Execution
[cite_start]Run the executable by passing a valid configuration file with a `.cub` extension as the first argument[cite: 123]:

```bash
# For the mandatory part
./cub3D maps/mandatory_map.cub

# For the bonus part
./cub3D maps/basic_door.cub