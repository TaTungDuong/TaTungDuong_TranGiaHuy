#pragma once
#include <stdio.h>
#include <vector>

#define TILEMAP_WIDTH 46
#define TILEMAP_HEIGHT 145

class Tilemap
{
public:
	Tilemap();
	std::vector<int> ground;
	std::vector<int> wall;

	int number_of_ground_tiles;
	int number_of_wall_tiles;
};