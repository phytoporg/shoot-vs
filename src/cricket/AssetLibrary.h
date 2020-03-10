//
// Loads and keeps track of assets, resources.
//

#pragma once

#include <string>

namespace cricket
{
    class AssetLibrary
    {
        public:
            //
            // For now this is just a filesystem reference. Ideally this grows
            // into a means of managing resources, refcounts, etc.
            //
            AssetLibrary(const std::string& assetsRoot);

            const std::string& GetRoot() const;

        private:
            std::string m_assetRoot;
    };
}

