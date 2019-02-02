#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "random.h"

int wrap_idx(int i, int n) { /**
    Simulates periodic boundary conditions.
    */
    
    return (i%n + n) % n;
}

double boltzmannf(double energy, double temperature) { /**
    Return the Boltzmann factor exp(-E).
    */
    return exp(-1/temperature * energy);
}

// ---

struct Particle_struct {
    int spin;
};

typedef struct Particle_struct Particle;


// ---


struct Ising_struct {
    Particle *particles;
    int n;
    double coupling;
};

typedef struct Ising_struct Ising;

typedef int(Spin_fn)();


Ising *create_Ising(int n, double coupling, Spin_fn *spinf) { /**
    Create a Ising 1D model object with custom spin selector.
    */
    
    Particle *particles = malloc(n * sizeof(*particles));
    
    for (int i=0; i<n; i++) {
        particles[i].spin = (*spinf)();
    }
    
    Ising *ising = malloc(sizeof(*ising));
    ising -> particles = particles;
    ising -> n = n;
    ising -> coupling = coupling;
    
    return ising;
}

int spin_at_Ising(Ising *ising, int i) { /**
    Return the value of the spin at the given position.
    */
    int n = ising -> n;
    Particle *particles = ising -> particles;
    
    // wrap_idx ensures the periodic boundary conditions are respected.
    return particles[wrap_idx(i, n)].spin;
}

double energy_at_Ising(Ising *ising, int i) { /**
    Return the interaction energy in the neighborhood of the position.
    */
    double coupling = ising -> coupling;
    
    
    return (
        coupling 
        * spin_at_Ising(ising, i) 
        * (spin_at_Ising(ising, i-1)
           + spin_at_Ising(ising, i+1)
        )
    );
}
    
double energy_Ising(Ising *ising) { /**
    Calculate the energy of the Ising system.
    */
    int n = ising -> n;
    
    double energy = 0;
    for (int i=0; i<n; i++) {
        energy += energy_at_Ising(ising, i);
    }
    
    // Compensate for double counting
    return energy/2;
}

double energy_delta_Ising(Ising *ising, int i) { /**
    Calculate the energy change resulting from a flip in the ith spin.
    */
    double previous_energy = energy_at_Ising(ising, i);
    double new_energy = -1 * previous_energy;
    return new_energy - previous_energy;
}

void swap_spin_Ising(Ising *ising, int i) { /**
    Swap the spin of the ith particle.
    */
    int n = ising -> n;
    Particle *particles = ising -> particles;
    
    particles[i].spin *= -1;
}

void montecarlo_sample_Ising(Ising *ising, double temperature) { /**
    Take the next sample using Monte Carlo.
    */
    
    int n = ising -> n;
    Particle *particles = ising -> particles;
    
    // 1 - Choose a random particle.
    int selected_idx = random_index(n);
    
    // 2 - Choose whether to accept or reject the change
    double dE = energy_delta_Ising(ising, selected_idx);
    
    int accepted = (
        (dE < 0) || random_test(boltzmannf(dE, temperature))
    );
    
    // 3 - Change accordingly
    
    if (accepted)
        swap_spin_Ising(ising, selected_idx);
}

void print_spins_Ising(Ising *ising, int n) {/**
    Print the spin state of the model.
    */
    Particle *particles = ising->particles;
    
    printf("[");
            
            int spin;
            for (int i=0; i<n-1; i++) {
                printf("%d,", particles[i].spin);
            }
            
            printf("%d", particles[n-1].spin);
            
    printf("]");
}

void print_state_Ising(Ising *ising, int n) { /**
    Print the state of the Ising model object in JSON.
    */
    
    Particle *particles = ising -> particles;
    
    printf("{");
    
        printf("\"spins\": ");
            print_spins_Ising(ising, n);
            
        printf(", ");
        
        printf("\"energy\": ");
            printf("%f", energy_Ising(ising));
            
    printf("}\n");
}
