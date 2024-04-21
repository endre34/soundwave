/*
 *  Project: SzalontaGrafika2024
 *   Author: Endre
 */

#include <cmath>

#include "utils.hpp"


double round_to_precision(double value, int decimal_places)
{
    double multiplier = std::pow(10.0, decimal_places);
    return std::round(value * multiplier) / multiplier;
}

int to_millis(double meters)
{
	return meters * 1000.0;
}

double to_meters(int millis)
{
	return millis / 1000.0;
}
