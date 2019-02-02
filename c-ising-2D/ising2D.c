#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ising2D.h"
#include "random.h"


int random_spin() {/**
    Select randomly +1 or -1
    */
    double selector = random_uniform();
    return (selector > 0.5) ? +1:-1;
}

double coupling = -1;
double temperature = 10;

int main(int argc, char *argv[]) {
    
    if (argc != 4) {
        printf("Usage: %s ROWS COLS N_STEPS\n", argv[0]);
        return 0;
    }
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int frames = atoi(argv[3]);
    
    seed_random();
    
    Ising *ising = create_Ising(rows, cols, coupling, &random_spin);
    print_state_Ising(ising);
    
    for (int i=0; i<frames; i++) {
        montecarlo_sample_Ising(ising, temperature);
        print_state_Ising(ising);
    }
}
