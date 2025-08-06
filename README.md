This game is a side project made by me just for fun and to learn programming and C++. 
You can use it for whatever you want.
If you want to use it and make it better, you can.
If you are better than me at programming you can change it and upgrade it.
Thank you for reading this.
Mouad. 

## **Summary**
1. Commands & controls.
2. Screenshots and gameplay explanations.
3. Project's structure.
4. Setup for the game.
5. History of the project.
6. Future ideas...

# **1. Commands & controls**

***

To move, you can use the arrow keys on your keyboard. 

You can move in any direction: Left, up, down, and right. On the menu, only the arrow are supported (to be updated).

To be able to play you just have to press SPACE in the title screen. You can pause the game at any moment by pressing the key ESCAPE. To quit pause mode, press again ESCAPE.

If you have a Game Over, press ENTER to quit the game.

***
# **2. Screenshots and gameplay**

## The Title screen.

<img width="629" height="470" alt="image" src="https://github.com/user-attachments/assets/378d1472-e6f0-4feb-a4c9-b2b3ea145afd" />

## The Game Board:

<img width="756" height="755" alt="image" src="https://github.com/user-attachments/assets/b50c2e13-c2e9-46b0-b79c-4d25c84716c7" />

* The **player** spawns at the center of the board.
* The **enemies** spawn randomly on the board with the **Sword** item.
* You can see here a **Heal potion**. This heal potion spawns **only** if the player have low Hp.
* At the top right of the screen, more information about the player and the board is displayed.
* You can see here only one enemy. If **all** the enemy are dead, **3** more enemies will **always** spawn randomly with stats based on the player's **level**.

***

## **3. Project's structure**

The main project's folder is like this:

<img width="281" height="509" alt="image" src="https://github.com/user-attachments/assets/c982a078-d45b-4578-be2a-2ba45771aeab" />

* **.vscode/** contains Visual studio code stuff.
* **assets/** contains **fonts/** and **images/**.
> **fonts/** contains all the fonts used for texts and **images/** all the textures of the player and other entities.
* The folder **headers/** contains all the headers files __(.h / .hpp)__ for the **src/** folder.
* **include/** is for all the headers file necessary for SDL2.
> same for **lib/**.
* **src/** contains the source code and mains files (.cpp) for the game.
> all others files are necessary for SDL2 or are complements for the game, like the Makefile.

***

# **4. Setup for the game**

***
## On Windows 10/11.
* Double click on the .exe file. It should launch the game. If it doesn't work, compile it by yourself using gcc and the .dll files of the library SDL2. Use MINGW64 and write **make**. Then write **./gameRpg_Win.exe** and launch the game.

## On Linux.

```
sudo apt install libsdl2-image-dev libsdl2-ttf-dev libsdl2-dev
mkdir build && cd build
cmake ..
make -j6
./GameRpg
```

***
# 5. History of the project
***
* At first, this project was just an idea to get better at coding by trying to code a procedural environnement gamd. It was really difficult so I went to just make a little terminal game beside school. The earliest prototype was just a board with a player moving on the terminal in a board drawed with texts. By the time and by the adding of SDL library, this little project changed direction and went to a "rpg" game. I really enjoyed coding every day to add some features to the game to be more alive. I always dreamed about making a game when I was little. This one is probably not the best but maybe one day I will do a real game who knows?

## The game in prototype on terminal in June 2025:

<img width="949" height="859" alt="image" src="https://github.com/user-attachments/assets/84f89b0d-8a0f-4a3c-b284-c1688cd07e4f" />on

## How the game looked with the inclusion of SDL2 in June 22th 2025: 

<img width="1236" height="861" alt="image" src="https://github.com/user-attachments/assets/25832dc5-5716-4116-b3fa-b3d5380b39e3" />

***
# 6. Future ideas...

* For the future, I will probably continue making little project like this on C++ or other languages. Maybe a real game like a 2d platformer or 3D. Only the future knows.

Thank you for reading that. 
Mouad.
