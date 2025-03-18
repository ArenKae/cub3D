# cub3D

<p align="center">
  <img src="https://github.com/ArenKae/ArenKae/blob/main/42%20badges/cub3de.png" alt="cub3D 42 project badge"/>
</p>

## A small raycaster FPS game
Cub3D is a team project where we need to create a dynamic view inside a 3D maze. Using the [MiniLibX library](https://github.com/42Paris/minilibx-linux), we must implement raycasting in the style of the famous [Wolfenstein 3D](http://users.atw.hu/wolf3d/) game, the first true FPS in videogame history.
<br/><br/>
<p align="center">
  <img src="https://github.com/ArenKae/ArenKae/blob/main/screens/cub3d%20demo.gif" alt="cub3D demo gif" width="700" height="573">
</p>

### 💻 This project was developed on Ubuntu 24.04.2 LTS.

## Status
Finished 03/08/2024.

Grade: 105/100

## Usage

- First, install the following dependencies to allow the Minilibx to compile :
```
sudo apt install xauth xorg openbox libxext-dev libbsd-dev
```

- Clone the repository and use ```make``` or ```make bonus``` to compile with or without the bonus part.

- Launch the program using ```./cub3D map/your_map.cub``` or ```./cub3D_bonus map/bonus_map.cub```. You can use either WASD or ZQSD to move the player, and the left/right arrow keys to rotate the camera.
