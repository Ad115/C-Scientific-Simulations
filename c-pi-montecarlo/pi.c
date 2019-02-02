#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0


struct Particle_struct {
    double x;
    double y;
};
typedef struct Particle_struct Particle;


void print_state(Particle *particle, double pi) { /**
    Print the current state in web friendly notation.
    */
    printf("{\"coords\": [%f, %f], \"pi\": %f}\n", particle->x, particle->y, pi);
}

void shoot(Particle *particle) { /**
    Pick a new position.
    */
    particle->x = 1 - 2*drand48();
    particle->y = 1 - 2*drand48();
}

int on_circle_q(Particle *particle) { /**
    Does the particle falls on the unit circle?
    */
    double x = particle->x;
    double y = particle->y;
    double r = sqrt( x*x + y*y );
    
    return r<1 ? TRUE : FALSE;
}

void seed_random() {srand48(time(0));}



// --- Main routine --- //


int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <no. of particles> \n", argv[0]);
        return 0;
    }
    int frames = atoi(argv[1]);    
    
    seed_random();
    
    double pi;
    double total = 0;
    double on_circle = 0;
    Particle particle;
    
    for (int i=0; i<frames; i++) {
        shoot(&particle);
        total++;
        
        if (on_circle_q(&particle)) {
            on_circle++;
        }
        
        pi = 4 * on_circle / total;
        
        print_state(&particle, pi);
    }
}
