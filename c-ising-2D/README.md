
 
Ising model in 2 dimensions
---------------------------


Simulation of the Ising model in 2D and visualization in the browser.

![Ising model](ising2D.png)


Usage
=====

NOTE: This is for UNIX machines.

**TL;DR**: Just enter in a terminal `cc ising2D.c -lm -o ising2D; ./ising2D 20 20 100000 | server.py` and open the file `index.html` in a browser.

To see the simulation, first compile the c code:

        cc ising2D.c -lm -o ising2D
        
Then, simulate, and save the output with:

        ./ising1D 20 20 100000 > simulation.dat
        
The output must be served via web with:

        python3 ./server.py < simulation.dat
        
Finally, open the `index.html` file in a browser.
        
 
