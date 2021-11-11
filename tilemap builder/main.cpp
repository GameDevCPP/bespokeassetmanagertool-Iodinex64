#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp>

using namespace sf;
using namespace std;
using namespace tgui;
//----------------------------WARNING-----------------------------//
//-----------This template won't work unless you add the----------//
//-contents of SFML/bin and TGUI/bin to the root of this project!-//

int main()
{
    RenderWindow window{ {1280, 720}, "TGUI window with SFML" };
    GuiSFML gui{ window };

    gui.mainLoop();
}