#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>

namespace knockOut {

    enum TextureID {
        Background1,
        Background2,
        Background3,
        BaldBull,
        PlayerTexture
    };

    enum FontID {
        MainFont
    };

    template<typename Resource, typename ID>
    class ResourceManager {
    public:

        void load(ID id, const std::string& filename) {
            std::unique_ptr<Resource> resource(new Resource());
            resource->loadFromFile(filename);
    
            _resourceMap.emplace(id, std::move(resource)).second;
        }
        Resource& get(ID id) {
            auto found = _resourceMap.find(id);
            return *found->second;
        }

    private:
        std::map<ID, std::unique_ptr<Resource>> _resourceMap;
    };
};