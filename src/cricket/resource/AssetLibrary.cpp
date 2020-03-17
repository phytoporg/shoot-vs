#include "AssetLibrary.h"

namespace cricket
{
    AssetLibrary::AssetLibrary(const std::string& assetRoot)
        : m_assetRoot(assetRoot)
    {}

    const std::string& AssetLibrary::GetRoot() const
    {
        return m_assetRoot;
    }
}

