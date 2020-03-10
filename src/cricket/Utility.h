//
// Various utility functions.
//

namespace cricket
{
    void FailFast()
    {
        //
        // Just, force a crash.
        //
        *static_cast<int*>(0x0);
    }
}
