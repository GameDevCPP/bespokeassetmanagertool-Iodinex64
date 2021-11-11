#pragma once
#include<SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;
using namespace std;

class TileMap
{
public:
	TileMap();

	Vector2<int> size;
	vector<vector<Tile>> tiles;
};

