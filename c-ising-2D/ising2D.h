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


struct Dimensions_struct {
    int rows;
    int cols;
};

typedef struct Dimensions_struct Dimensions;


// ---


struct Particle_struct {
    int spin;
};

typedef struct Particle_struct Particle;


// ---


struct Ising_struct {
    Particle *particles;
    Dimensions *dimensions;
    double coupling;
};

typedef struct Ising_struct Ising;

typedef int(Spin_fn)();


int idx2D(int i, int j, Dimensions *dimensions) { /**
    Linearize the 2D coordinates for a 2D grid.
    */
    int rows = dimensions->rows;
    int cols = dimensions->cols;
    i = wrap_idx(i, rows);
    j = wrap_idx(j, cols);
    
    return cols * i + j;
}


Ising *create_Ising(int rows, int cols, double coupling, Spin_fn *spinf) { /**
    Create a Ising 1D model object with custom spin selector.
    */
    
    Particle *particles = malloc(rows * cols * sizeof(*particles));
    
    for (int i=0; i<rows*cols; i++) {
        particles[i].spin = (*spinf)();
    }
    
    Ising *ising = malloc(sizeof(*ising));
    ising -> particles = particles;
    
    ising -> dimensions = malloc(sizeof(Dimensions));
        ising -> dimensions -> rows = rows;
        ising -> dimensions -> cols = cols;
    
    ising -> coupling = coupling;
    
    return ising;
}

void destroy_Ising(Ising *ising) { /**
    Free the resources occupied by the Ising object.
    */
    free(ising -> particles);
    free(ising -> dimensions);
}

Particle *at_Ising(Ising *ising, int i, int j) { /**
    Get the particle at the position i, j of the system.
    */
    Particle *particles = ising -> particles;
    Dimensions *dims = ising -> dimensions;
    
    return &( particles[idx2D(i,j, dims)] );
}

int spin_at_Ising(Ising *ising, int i, int j) { /**
    Get the spin of the particle at i,j.
    */
    return at_Ising(ising, i, j)->spin;
}

double energy_at_Ising(Ising *ising, int i, int j) { /**
    Get the interaction energy of the particle at the site with it's neighbors.
    */
    Particle *particles = ising -> particles;
    Dimensions *dims = ising -> dimensions;
    double coupling = ising -> coupling;
    
    return  coupling * (
        spin_at_Ising(ising, i,j) * (
              spin_at_Ising(ising, i,j-1)
            + spin_at_Ising(ising, i,j+1)
            + spin_at_Ising(ising, i-1,j)
            + spin_at_Ising(ising, i+1,j)
        )
    );
}

double energy_delta_Ising(Ising *ising, int i, int j) { /**
    Calculate the energy change resulting from a flip in the ith spin.
    */
    double previous_energy = energy_at_Ising(ising, i,j);
    double new_energy = -1 * previous_energy;
    return new_energy - previous_energy;
}

void swap_spin_Ising(Ising *ising, int i, int j) { /**
    Swap the spin of the ith particle.
    */
    Particle *particle = at_Ising(ising, i, j);
    particle -> spin *= -1;
}

void montecarlo_sample_Ising(Ising *ising, double temperature) { /**
    Take the next sample using Monte Carlo.
    */
    
    Particle *particles = ising -> particles;
    Dimensions *dims = ising -> dimensions;
    int rows = dims -> rows;
    int cols = dims -> cols;
    
    // 1 - Choose a random particle.
    int i = random_index(rows);
    int j = random_index(cols);
    
    // 2 - Choose whether to accept or reject the change
    double dE = energy_delta_Ising(ising, i, j);
    
    int accepted = (
        (dE < 0) || random_test(boltzmannf(dE, temperature))
    );
    
    // 3 - Change accordingly
    
    if (accepted)
        swap_spin_Ising(ising, i, j);
}

// <-- Measurement

double energy_Ising(Ising *ising) { /**
    Calculate the energy of the Ising system.
    */
    Dimensions *dims = ising -> dimensions;
    Particle *particles = ising -> particles;
    int rows = dims -> rows;
    int cols = dims -> cols;
    
    double energy = 0;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            energy += energy_at_Ising(ising, i, j);
        }
    }
    energy = energy/2; // Avoid double counting
    return energy;
}

void print_spins_Ising(Ising *ising) {/**
    Print the spin state of the model.
    */
    Dimensions *dims = ising -> dimensions;
    Particle *particles = ising -> particles;
    int rows = dims -> rows;
    int cols = dims -> cols;
    
    printf("[");
            
            int spin;
            for (int i=0; i < rows-1; i++) {
                printf("[");
                
                    for (int j=0; j < cols-1; j++) {
                        spin = at_Ising(ising, i,j) -> spin;
                        printf("%d,", spin);
                    }
                    spin = at_Ising(ising, i,cols-1) -> spin;
                        printf("%d", spin);
                    
                printf("],");
            }
            
            printf("[");
                for (int j=0; j < cols-1; j++) {
                    spin = at_Ising(ising, rows-1,j) -> spin;
                    printf("%d,", spin);
                }
                spin = at_Ising(ising, rows-1,cols-1) -> spin;
                            printf("%d", spin);
            printf("]");
            
    printf("]");
}

void print_state_Ising(Ising *ising) { /**
    Print the state of the Ising model object in JSON.
    */
    
    printf("{");
    
        printf("\"spins\": ");
            print_spins_Ising(ising);
            
        printf(", ");
        
        printf("\"energy\": ");
            printf("%f", energy_Ising(ising));
            
    printf("}\n");
}
