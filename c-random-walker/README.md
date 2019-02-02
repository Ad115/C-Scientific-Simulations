Random Walker
-------------

A simulation of random walker particles in C that displays in the browser.

# Usage

NOTE: This is for UNIX machines.

**TL;DR**: Just type `make randomwalker; ./randomwalker 100 10000 | ./server.py` and open the file `index.html` in a browser.

To see the simulation, first compile with make:

        make randomwalker
        
Then, simulate, and save the output with:

        ./randomwalker N_PARTICLES N_STEPS > simulation.dat
        
The output must be served via web with:

        python3 ./server.py < simulation.dat
        
Finally, open the `index.html` file in a browser.

# Output

![output](randomwalker.jpeg)
        
