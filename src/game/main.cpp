#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cricket/game/World.h>
#include <cricket/resource/AssetLibrary.h>

#include <cricket/input/KeyboardEventState.h>
#include <cricket/input/InputDeviceEnumerator.h>
#include <cricket/input/InputDeviceCollector.h>

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

    //
    // Initialize input devices.
    //
    cricket::KeyboardEventState eventState;
    cricket::InputDeviceEnumerator deviceEnumerator(eventState);

    auto inputDevices = deviceEnumerator.GetAvailableDevices();
    if (inputDevices.empty()) 
    {
        std::cerr << "Couldn't find any input devices." << std::endl;
        return -1;
    }

    //
    // Hard-code the device map for now (player 1 gets keyboard)
    //

    cricket::InputDevicePtr spKeyboardDevice;
    for (const auto& spDevice : inputDevices)
    {
        if (spDevice->GetDeviceClass() == cricket::InputDeviceClass::Keyboard)
        {
            spKeyboardDevice = spDevice;
            break;
        }
    }

    if (!spKeyboardDevice)
    {
        std::cerr << "Couldn't find keyboard device." << std::endl;
        return -1;
    }
    
    cricket::InputDeviceCollector::DeviceMap deviceMap { spKeyboardDevice };
    auto spInputCollector = 
        cricket::InputDeviceCollector::CreateAndInitialize(deviceMap);
    if (!spInputCollector)
    {
        std::cerr << "Failed to create input collector." << std::endl;
        return -1;
    }

    sf::Clock clock;
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

        {
            cricket::ActionState p1State;
            if (spInputCollector->GetActionStateForPlayer(
                cricket::ActionPlayer1, &p1State
                ))
            {
                if (p1State.Quit) { window.close(); break; }

                spGameSimulation->EnqueueAction(
                    p1State, cricket::ActionPlayer1
                    );
            }
        }

        {
            cricket::ActionState p2State;
            if (spInputCollector->GetActionStateForPlayer(
                cricket::ActionPlayer2, &p2State
                ))
            {
                if (p2State.Quit) { window.close(); break; }

                spGameSimulation->EnqueueAction(
                    p2State, cricket::ActionPlayer1
                    );
            }
        }

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

