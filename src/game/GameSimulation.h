//
// Game state wrapper for advancing, rollback and serialization.
//

#pragma once

#include <cricket/game/World.h>
#include <cricket/input/ActionState.h>
#include <cricket/input/ActionPlayer.h>
#include <cricket/input/ActionQueue.h>

#include "Ship.h"

// 
// Forward decls
// 
namespace cricket
{
    class AssetLibrary;
}

namespace ShootVs
{
    class GameSimulation;
    using GameSimulationPtr = std::shared_ptr<GameSimulation>;

    class GameSimulation
    {
    public:
        static GameSimulationPtr
            CreateAndInitialize(cricket::AssetLibrary& assetLibrary);

        void EnqueueAction(
            cricket::ActionState state, 
            cricket::ActionPlayer player);

        //
        // Advances state.
        //
        // Once rollback is supported, numFrames is permitted to be negative.
        //
        void AdvanceFrames(int32_t numFrames);

        //
        // Render state to the window.
        //
        void Draw(sf::RenderWindow& window);

        //
        // Returns the current frame number in the game simulation.
        //
        uint32_t GetFrame() const;

    private:
        GameSimulation(
            cricket::AssetLibrary& assetLibrary,
            cricket::WorldPtr spWorld);

        uint32_t               m_frameNumber;
        cricket::WorldPtr      m_spWorld;

        cricket::AssetLibrary& m_assetLibrary;
        cricket::ActionQueue   m_actionQueue;

        cricket::GameObjectPtr m_spP1Ship;

    public:
        static const double   TargetFPS;
        static const uint32_t FrameDelay;
    };
}

