 
Ising model in 1 dimension
--------------------------

Simulation of the Ising model and visualization in the browser.

![Ising model](ising1D.png)


Usage
=====

NOTE: This is for UNIX machines.

**TL;DR**: Just enter in a terminal `cc ising1D.c -lm -o ising1D; ./ising1D 30 100000 | ./server.py` and open the file `index.html` in a browser.

To see the simulation, first compile the c code:

        cc ising1D.c -lm -o ising1D
        
Then, simulate, and save the output with:

        ./ising1D 30 100000 > simulation.dat
        
The output must be served via web with:

        python3 ./server.py < simulation.dat
        
Finally, open the `index.html` file in a browser.
        
 
