# Double Pendulum Chaos Theory

Here you can find the code to simulate 200 double pendulum with very small different start configuration!

SFML library is necessary to execute the simulation.  
For linux system you can install necessary package with:

    sudo apt-get install libsfml-dev

Clone the repostery:

    git clone https://github.com/yursds/double_pendulum_chaos.git

Navigate into the folder and run the following command:

    make ./main
    ./main

You can use [header file](./include/double_pendulum.h) to change parameters of simulation.  

## Simulation
Command:
* Keyboard_Space to start simulation
* Keyboard_Right to increase first (absolute) angle of PI/36
* Keyboard_Left to decrease first (absolute) angle of PI/36
* Keyboard_Up to increase second (absolute) angle of PI/36
* Keyboard_Down to decrease second (absolute) angle of PI/36
* Keyboard_R to reset simulation
  



## Video demostration:

<img src="image/video_doublePendulum.gif" alt="IMAGE ALT TEXT HERE" width="350" height="350">
