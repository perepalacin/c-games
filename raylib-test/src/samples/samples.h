#ifndef SAMPLES_H
#define SAMPLES_H

#include "stdio.h"
#include "stdlib.h"
#include "../entities/particle.h"

Particle *InitParticles(void);
void DeinitParticles(Particle *);
void UpdateParticles(Particle *);
#endif