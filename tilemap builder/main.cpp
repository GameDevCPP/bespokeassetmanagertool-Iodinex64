#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp>

#include "TileMap.h"

using namespace sf;

int main()
{
    //new json object to store map data
    nlohmann::json j;
    std::ofstream outJson("MapLevel1.json");
    std::ifstream inJson("MapLevel1.json");
    // create the window
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");
    window.setVerticalSyncEnabled(true); //I want this to limit the framerates and not cook my cpu!!

    // define the level with an array of tile indices


//Change to using JSON
//save the data to map.json
//load back into new json object called j2;
//use that to populate level/map info.
    j["level"] = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };
    j["tileset"] = "tileset.png";
    j["TileSize"] = { 32,32 };
    j["MapDims"] = { 16,8 };

    //save our json file
    outJson << j << std::endl;

    //I'm goint to load in my json data file. Let's pretend a highly skilled level designer spent hours on this level ;)
    nlohmann::json jsonMap;

    inJson >> jsonMap;

    //did it load correctly or is it rubbish - let's take a look. This is a simple form of debugging.
    std::cout << jsonMap["level"] << std::endl;
    //copy map data to suitable structure
    std::vector<int> levelVector = jsonMap["level"];
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(jsonMap["tileset"], sf::Vector2u(32, 32), &levelVector[0], 16, 8)) //neat trick to pass a vector as a const array! See https://stackoverflow.com/questions/2923272/how-to-convert-vector-to-array
        return -1; //if problem we bail out of here!


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
    }

    return 0;
};