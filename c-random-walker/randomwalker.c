#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Particle_struct {
    double x;
    double y;
};

typedef struct Particle_struct Particle;

Particle *create_particles(int n) {
    
    Particle *particles = malloc(n * sizeof(*particles));
    
    for (int i=0; i<n; i++) {
        particles[i].x = 0;
        particles[i].y = 0;
    }
    
    return particles;
}

void random_walk(Particle *particles, int n) {
    for (int i=0; i<n; i++) {
        particles[i].x += 1 - 2*drand48();
        particles[i].y += 1 - 2*drand48();
    }
}

void print_particles(Particle *particles, int n) {
    printf("[");
    for (int i=0; i<n-1; i++) {
        printf("[%f, %f],", particles[i].x, particles[i].y);
    }
    printf("[%f, %f]]\n", particles[n-1].x, particles[n-1].y);
}


int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        printf("Usage: %s <no. of particles> <simulation steps>\n", argv[0]);
        return 0;
    }
    int n = atoi(argv[1]);
    int frames = atoi(argv[2]);
    
    srand48(time(0));
    
    Particle *particles = create_particles(n);
    
    for (int i=0; i<frames; i++) {
        random_walk(particles, n);
        print_particles(particles, n);
    }
    
    free(particles);
}
