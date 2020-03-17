//
// Action state for a particular player.
//

#pragma once

namespace cricket
{
    struct ActionState
    {
        bool MoveDown;
        bool MoveUp;
        bool MoveLeft;
        bool MoveRight;
        bool Quit;
    };
}

