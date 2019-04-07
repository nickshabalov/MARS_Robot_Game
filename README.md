# MARS_Robot_Game
Rover control system. The robot is on the field, divided by square cells. The size of the field is unknown. Initially, at system startup control, the robot does not store any information about its surrounding space. The task of the robot is to explore the map and collect the maximum amount of resources. Robot can scan sensors surrounding 4 cells and get data that located in these cells:

1) Empty is an empty cage, the robot can pass through it.
2) Rock - a cage with a stone. The robot can not be in it. If he will try
move into this cage, it will remain in one place.
3) Bomb - Cage with a bomb. If a robot calls in this cage, it is destroyed.
4) Apple - a cell with a resource that must be collected.

There is one collector robot on the field. The robot is controlled in several modes:
1) Manual. The robot is controlled by operator commands entered from the console.
Commands:
MOVE U / R / D / L - the step of the robot up / down / right / left
GRAB - take the apple from the cage on which the robot stands
SCAN - examine the cells around. After this command, the robot remembers
2) Automatic study of the map. The robot moves on the unknown
terrain His goal - to make the most detailed map.
3) Automatic collection of resources. Having a map drawn up in modes 1 and 2,
the robot moves across the field and collects resources, avoiding bombs.
Switching between modes is done by the command
SET_MODE manual - manual
 scan N - Automatic map scan, where N is the number of steps,
