#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ising1D.h"
#include "random.h"


int random_spin() {/**
    Select randomly +1 or -1
    */
    double selector = random_uniform();
    return (selector > 0.5) ? +1:-1;
}

double coupling = -1;
double temperature = 2;

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        printf("Usage: %s N_PARTICLES N_STEPS\n", argv[0]);
        return 0;
    }
    int n = atoi(argv[1]);
    int frames = atoi(argv[2]);
    
    seed_random();
    
    Ising *ising = create_Ising(n, coupling, &random_spin);
    print_state_Ising(ising, n);
    
    for (int i=0; i<frames; i++) {
        montecarlo_sample_Ising(ising, temperature);
        print_state_Ising(ising, n);
    }
}
