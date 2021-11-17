#include <fstream>
#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp>
#include "json.hpp"
#include "TileMap.h"

using namespace sf;
using namespace std;

int curTile = 0;

int main()
{
    using nlohmann::json;
    json j;

    ifstream inMap("mapLevel1.json");//read in mapData.json
    inMap >> j;
    int newTiles[128] = {}; //array of tiles
    int index = 0;
    //take data from json and add to array
    for (auto i : j["map"]) {
        newTiles[index] = i;
        index++;
    }

    RenderWindow window(VideoMode(1280, 720), "Tilemap");
    window.setVerticalSyncEnabled(true); //I want this to limit the framerates and not cook my cpu!!

    // define the level with an array of tile indices

    TileMap map;
    if (!map.load("tileset.png", sf::Vector2u(32, 32), newTiles, 16, 8))
        return -1;


    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.display();

    //Change tiles with keyboard
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        curTile = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        curTile = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        curTile = 2;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        curTile = 3;
    }

    //Painting
    if (sf::Mouse::isButtonPressed(Mouse::Left) && curTile > -1) {
        sf::Vector2i position = Mouse::getPosition(window); //get the position relative to window
        //if position is on map
        if (position.x > 45 && position.x < 559 && position.y <263 && position.y>-1) {
            int newx = (position.x - 45) / 32; 
            int newy = position.y / 32; 
            newTiles[newx + newy * 16] = curTile; //get position in array
        }
        //redraw the tiles
        if (!map.load("tileset.png", sf::Vector2u(32, 32), newTiles, 16, 8))
            return -1;
		}
    }

    //save on close
    std::ofstream outJson("mapData.json");
    json jmap = {
        {"map", newTiles}
    };

    outJson << jmap << std::endl;
    outJson.close();
    return 0;


};