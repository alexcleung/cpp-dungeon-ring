/*
RNG
*/
#ifndef RNG
#define RNG

#include <random>

std::random_device rd;

double runif(double min=0, double max=1) {
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);

	return dis(gen);
}

#endif
