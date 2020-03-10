#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cricket/World.h>
#include <cricket/AssetLibrary.h>

#include "Ship.h"

#include <iostream>
#include <experimental/filesystem>

struct KeyState
{
    bool DownPressed;
    bool UpPressed;
    bool LeftPressed;
    bool RightPressed;
};

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
    
    // 
    // Initialize world.
    //  
    auto spShip = cricket::Ship::CreateObject(*spAssetLibrary, 0);
    if (!spShip)
    {
        std::cerr << "Could not create main ship! Bailing." << std::endl;
        return -1;
    }
    spShip->SetPosition(sf::Vector2i(100, 100));
    spShip->SetVelocity(sf::Vector2i(0, 0));

    cricket::World world;
    world.AddObject(spShip);

    KeyState keyState = {};

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}
            else if(event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    keyState.UpPressed = true;
                }

                if (event.key.code == sf::Keyboard::S)
                {
                    keyState.DownPressed = true;
                }

                if (event.key.code == sf::Keyboard::A)
                {
                    keyState.LeftPressed = true;
                }

                if (event.key.code == sf::Keyboard::D)
                {
                    keyState.RightPressed = true;
                }
            }
            else if(event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Q ||
                    event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }

                if (event.key.code == sf::Keyboard::W)
                {
                    keyState.UpPressed = false;
                }

                if (event.key.code == sf::Keyboard::S)
                {
                    keyState.DownPressed = false;
                }

                if (event.key.code == sf::Keyboard::A)
                {
                    keyState.LeftPressed = false;
                }

                if (event.key.code == sf::Keyboard::D)
                {
                    keyState.RightPressed = false;
                }
            } else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(
                    0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
                spShip->SetPosition(sf::Vector2i(100, 100));
            }
        }

        sf::Vector2i velocitySum(0, 0);
        if (keyState.UpPressed)    { velocitySum += sf::Vector2i(0, -1); }
        if (keyState.DownPressed)  { velocitySum += sf::Vector2i(0,  1); }
        if (keyState.LeftPressed)  { velocitySum += sf::Vector2i(-1, 0); }
        if (keyState.RightPressed) { velocitySum += sf::Vector2i( 1, 0); }
        spShip->SetVelocity(velocitySum);

        window.clear();
        world.Update(clock.getElapsedTime());
        world.Draw(window);
        clock.restart();
        window.display();
    }

    return 0;
}

