#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Tile
{
public:
	Tile();
	String name;
	Texture image;
	int size;
};