# SDL2_C++_Game_Project

A non-commercial game which made by SDL2 and C++

# Introduce

- This game is a simple endless-runner game,  written in C++ programming language with SDL graphic libraries (https://www.libsdl.org/)
- Name of the game: Cat's Adventure

# Description

In a beautiful day, you became a cat and got up in a totally strange area. After a moment for calming down, you decided to find ways to come home. Nevertheless, in the ways there are a lot of obstacles, and with your determination, you need to overcome it!

# Play Guides 

- Use SPACE button or UP ARROW button to jump above the obstacles in the ways
- Be careful, because the speed of these objects'speed will be increased after a certain period since the game started
- Your score will be increased overtime, unless your character collides with one of these objects. If this happens, you will lose.
- Your score and highscore is displayed in the above-right corner
- Have fun!

# Function

The game have the following features:
- Play: Start the game
- Pause: You can pause the game if you want to take a break
- Mute/Unmute: If you do not want to hear the sound, you can click the button and the sound will be paused/played
- About: Information and description about the game
- Highscore: The highest score reached
- Return: When you click the highscore button / about button, you can return to the main menu by pressing the return one
- Replay: If you lose, you can choose to replay without returning to menu
- Quit: End the game

# Installation

***Note***: This game is only tested in Windows environment and is compiled by Visual Studio Code

- Step 1: Download Visual Studio Code from Microsoft page
- Step 2: Install the MinGW compiler and then put the directory address in System Path
- Step 3: Download the source code from this repository
- Step 4: Install the SDL2 libraries (including SDL2, SDL2_image, SDL2_ttf, SDL2_mixer)
    - Copy all the headers of SDL2 (for example: SDL.h) into the sdl folder (which should be created in include folder)
    - Copy all the libraries of SDL2 (cmake, pkgconfig, libSDL2) into the lib folder (which should be created in main directory)
    - Copy all the SDL dll files into the main directory
- Step 5: Open the terminal, and enter this command (without space): mingw32-make -f MakeFile
- Step 6: After complied successfully, you will the an executable file named "main.exe" and you can open this file to play the game!

# Credits

- This project is made by Nguyen Chi Trung
- Game assets are available free use by various developers:
    - itch.io
 
# Licenses

- This is the free and non-commercial game project
- Pull requests are welcome.
