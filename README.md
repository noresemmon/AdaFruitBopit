# AdaFruitBopit

# Game Description
This game is similiar to the popular handheld game Bop it!, it is meant to be ran on the Circuit Playground Express (CPX). The game will start when both buttons are pressed, the goal is to complete the said action within the given time. The time given to complete the task goes down as you progress through the levels. There are seven levels with each one having more tasks then the last, with the last level being endless and the time goes down by one millisecond after every task. Each level is randomized. After every task completed in the time limit one point is given this will be outputed in the serial monitor once a game over happens. You can see the amount of time given by how fast the Neo Pixels LEDs light up. If you don't do the task within the time limit you will get a game over which will be shown in the serial monitor as well as being said through the speaker. If you want to reset the game press both buttons. 


### Game Inputs
When "press" is said press both buttons (D4 and D5).
When "switch" is said move the switch (D7) either to the right or left.
When "move" is said shake the CPX board it is using the accelormoter to calculate the total acceleration of the board.
When "say" is said make noise the CPX board is using the micropone to detect noise.
In order to reset/start the game you will need to press both buttons(D4 and D5). 


### Game Outputs
The game utilizes three outputs.
The Neo Pixel LEDs are used to show how much time is left to complete task. As well as a small animation is played while a game over has occured and when you first upload the CPX Bop It!. 
The speaker is used to tell the player which input to do using the speaker say function. 
The serial montor is used to display as another way to see what input to do. When gamer over happend the serial montior also outputs both points earned along with highscore since board was reset. 



