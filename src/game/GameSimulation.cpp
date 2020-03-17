#include "GameSimulation.h"

#include <cricket/game/World.h>
#include <cricket/resource/AssetLibrary.h>

#include "Ship.h"

#include <cassert>

namespace 
{
    bool 
    HandleAction(
        const cricket::PlayerActionState action,
        sf::Vector2i* pAccumulatorVectors,
        cricket::GameObjectPtr p1Ship
        )
    {
        sf::Vector2i* pVelocity;
        if (action.Player == cricket::ActionPlayer1)
        {
            pVelocity = &pAccumulatorVectors[0];
        }
        else if (action.Player == cricket::ActionPlayer2)
        {
            // Not supported yet TODO
            //pVelocity = &pAccumulatorVectors[1];
            return false;
        }
        else
        {
            return false;
        }

        if (action.State.MoveDown)
        {
            *pVelocity += sf::Vector2i(0, 1);
        }

        if(action.State.MoveUp)
        {
            *pVelocity += sf::Vector2i(0, -1);
        }

        if(action.State.MoveLeft)
        {
            *pVelocity += sf::Vector2i(-1, 0);
        }

        if(action.State.MoveRight)
        {
            *pVelocity += sf::Vector2i(1, 0);
        }

        p1Ship->SetVelocity(*pVelocity);
        return true;
    }
}

namespace ShootVs
{
    const double   GameSimulation::TargetFPS{60.0};
    const uint32_t GameSimulation::FrameDelay{3};

    GameSimulationPtr GameSimulation::CreateAndInitialize(
        cricket::AssetLibrary& assetLibrary)
    {
        GameSimulationPtr spGameSimulation;

        auto spP1Ship = Ship::CreateObject(assetLibrary, 0);
        if (!spP1Ship)
        {
            return spGameSimulation;
        }
        spP1Ship->SetPosition(sf::Vector2i(100, 100));
        spP1Ship->SetVelocity(sf::Vector2i(0, 0));

        cricket::WorldPtr spWorld(new cricket::World);
        if (!spWorld)
        {
            return spGameSimulation;
        }
        spWorld->AddObject(spP1Ship);

        spGameSimulation.reset(new GameSimulation(
            assetLibrary, spWorld));
        spGameSimulation->m_spP1Ship = spP1Ship;

        return spGameSimulation;
    }

    GameSimulation::GameSimulation(
        cricket::AssetLibrary& assetLibrary,
        cricket::WorldPtr spWorld)
        : m_assetLibrary(assetLibrary), 
          m_spWorld(spWorld),
          m_frameNumber(0)
    {}

    void GameSimulation::EnqueueAction(
        cricket::ActionState state, 
        cricket::ActionPlayer player)
    {
        m_actionQueue.Enqueue(player, state, m_frameNumber + FrameDelay);
    }

    void GameSimulation::AdvanceFrames(int32_t numFrames)
    {
        const uint32_t StartingFrame{m_frameNumber};
        for (int32_t i = 0; i < numFrames; ++i)
        {
            const uint32_t LoopFrame{StartingFrame + static_cast<uint32_t>(i)};

            uint32_t earliestFrame;
            if (!m_actionQueue.PeekEarliestFrame(&earliestFrame)) 
            { 
                m_frameNumber++;
                break; 
            }

            if (earliestFrame > LoopFrame) { m_frameNumber++; continue; }

            assert(earliestFrame >= LoopFrame);

            std::vector<cricket::PlayerActionState> actionsForThisFrame;
            if (!m_actionQueue.GetAndRemoveActionsOnFrame(
                    LoopFrame, &actionsForThisFrame))
            {
                //
                // TODO: properly handle this case.
                // 
                assert(false);
            }

            sf::Vector2i shipVelocityAccumulators[2];
            for (const auto& Action : actionsForThisFrame)
            {
                if (!HandleAction(Action, shipVelocityAccumulators, m_spP1Ship))
                {
                    //
                    // TODO: properly handle this case.
                    //
                    assert(false);
                }
            }

            m_spWorld->Update(sf::seconds(1.0 / TargetFPS));
            m_frameNumber++;
        }
    }

    void GameSimulation::Draw(sf::RenderWindow& window)
    {
        m_spWorld->Draw(window);
    }

    uint32_t GameSimulation::GetFrame() const
    {
        return m_frameNumber;
    }
}

