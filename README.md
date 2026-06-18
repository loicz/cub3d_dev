*This project has been created as part of the 42 curriculum by tle-rhun and lozhao.*

# cub3D - My first RayCaster with miniLibX

## Description
**cub3D** is a 3D graphical simulation project inspired by the world-famous 1992 game *Wolfenstein 3D*, which is widely considered the first First-Person Shooter (FPS) ever created. 

The goal of this project is to explore the principles of **Raycasting** in C to render a dynamic, real-time 3D perspective from inside a maze using a grid-based map configuration file. The program parses a scene description file (`*.cub`), validates the environment constraints, and handles window management, smooth player movement, and camera rotations using the **miniLibX** graphics library.

---

## Features
### Mandatory Part
* **Real-time 3D Raycasting:** Smooth rendering of a maze using Raycasting principles.
* **Texture Mapping:** Wall textures vary dynamically depending on which cardinal direction the wall is facing (North, South, East, West).
* **Configurable Environment:** Custom floor and ceiling colors parsed directly from the configuration file.
* **Controls:** * `W`, `A`, `S`, `D` keys to move the player's point of view through the maze.
  * Left and Right arrow keys to look around.
  * `ESC` or clicking the window's red cross frame closes the window and terminates the program cleanly.

### Bonus Part
* **Wall Collisions:** Prevents the player from walking through walls (handled by `lozhao`).
* **Mouse Rotation:** Rotate the point of view dynamically using the mouse cursor (handled by `lozhao`).
* **Centred Minimap:** A 2D minimap displayed in real-time on top of the window (handled by `tle-rhun`).
  * Size is dynamically constrained to 1/5th of the smallest window dimension (width or height).
  * The player is represented as a red square fixed right in the center of the minimap.
  * *Color indicators:* Black represents empty space, Brown represents doors, and transparent spaces define map boundaries.
* **Interactive Doors:** Functional doors that can be opened or closed (handled by `tle-rhun`).
  * Configured with `2` in the `.cub` map layout when closed.
  * To interact, look directly at the door and press the `F` key. Once opened, its internal state updates to `3`, allowing the player to pass through seamlessly.

---

## Instructions

### Prerequisites
To compile and run this project, you need the standard C development tools along with the **X11** and **miniLibX** graphical dependency headers installed on your system.

### Compilation
The project includes a robust `Makefile` configured with `-Wall -Wextra -Werror` flags. It contains the following targets:

* `make` or `make all`: Compiles the mandatory version of the program.
* `make bonus`: Compiles the extended version including collisions, minimap, doors, and mouse rotations.
* `make clean`: Removes binary object files (`.o`).
* `make fclean`: Removes object files as well as the compiled executable.
* `make re`: Recompiles the whole project from scratch.

### Execution
Run the executable by passing a valid configuration file with a `.cub` extension as the first argument:

```bash
# For the mandatory part
./cub3D maps/mandatory_map.cub

# For the bonus part
./cub3D maps/basic_door.cub
```

## Resources
### Classic References

    Lode's Raycasting Tutorial - Main source for understanding the Digital Differential Analysis (DDA) algorithm and mathematical implementation of raycasting.

*    42 Docs - cub3D Graphic Library Guide - Documentation regarding textures and pixel rendering logic.
*    Fran-Byte cub3D Approach Guide - Structural guidelines for the project.
*    Nathan's cub3D Project Overview - Inspiration on engineering math workflows.
*    HackMD cub3D Reference - Notes on data structures and key bindings.
*    Cub3d-Linux GitHub Repository - Multi-platform reference setup for miniLibX under Linux.

### AI Usage Disclosure

In accordance with the 42 curriculum framework, Artificial Intelligence tools were utilized responsibly during the development phase:

    Tasks Assisted: AI helped break down the foundational mathematical concepts behind coordinate vectors and the DDA line-bounding mechanics.

    Validation Checkpoint: All structural logic and pseudocode suggestions provided by AI were systematically cross-referenced, adapted, and re-written by the team alongside the primary technical documentation on lodev.org to guarantee strict adherence to the project scope and codebase constraints.