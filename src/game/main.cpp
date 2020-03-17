#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cricket/World.h>
#include <cricket/input/KeyboardEventState.h>
#include <cricket/resource/AssetLibrary.h>

#include "Ship.h"
#include "GameSimulation.h"

#include <iostream>
#include <experimental/filesystem>

//
// Usage: <program> (asset library root path)
//
int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ShootsVS");

    //
    // Verify asset library params.
    //
    std::unique_ptr<cricket::AssetLibrary> spAssetLibrary;
    if (argc > 1)
    {
        namespace fs = std::experimental::filesystem;
        if (!fs::exists(argv[1]) || !fs::is_directory(argv[1]))
        {
            std::cerr << "Invalid asset library path: " 
                      << argv[1]
                      << std::endl;
            return -1;
        }

        spAssetLibrary = std::make_unique<cricket::AssetLibrary>(argv[1]);
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " (asset library root)"  
                  << std::endl;
        return -1;
    }
    
    ShootVs::GameSimulationPtr spGameSimulation = 
        ShootVs::GameSimulation::CreateAndInitialize(*spAssetLibrary);

    sf::Clock clock;
    cricket::KeyboardEventState eventState;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
            } else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(
                    0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));

                //
                // TODO: HRM. Gotta fix this.
                //
                // spShip->SetPosition(sf::Vector2i(100, 100));
            }

            eventState.ProcessEvent(event);
        }

        const auto& P1State = eventState.GetActionState();
        if (P1State.Quit) { window.close(); break; }

        spGameSimulation->EnqueueAction(P1State, cricket::ActionPlayer1);

        //
        // TODO: Add proper timing logic per frame.
        //
        window.clear();
        spGameSimulation->AdvanceFrames(1);
        spGameSimulation->Draw(window);

        //
        // Enforce the desired FPS
        //
        sf::Time elapsed{clock.getElapsedTime()};
        const sf::Time DesiredFrameDuration(
            sf::seconds(1.0 / ShootVs::GameSimulation::TargetFPS));
        if (DesiredFrameDuration > elapsed)
        {
            sf::sleep(DesiredFrameDuration - elapsed);
        }
        clock.restart();

        window.display();
    }

    return 0;
}

