#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <tmx/MapLoader.hpp>
#include "TiledMap.hpp"

namespace sf
{
    class Texture;
    class Font;
    class SoundBuffer;
}
class SettingsParser;

namespace Textures
{
    enum ID
    {
        TitleScreen,
        Hero,
        HeroLeft,
        HeroUp,
        HeroDown,
        Enemy
    };
}

namespace Fonts
{
    enum ID
    {
        Main,
        Debug,
    };
}


namespace SoundEffects
{
    enum ID
    {
      Default
    };
}

namespace Settings
{
    enum ID
    {
        Default,
    };
}

namespace TiledMaps
{
    enum ID
    {
        Default,
    };
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void                                                load(Identifier id, const std::string& filename);

        template <typename Parameter>
        void                                                load(Identifier id, const std::string& filename, const Parameter& secondParam);

        Resource&                                           get(Identifier id);
        const Resource&                                     get(Identifier id) const;

    private:
        void                                                insertResource(Identifier id, std::unique_ptr<Resource> resource);

    private:
        std::map<Identifier, std::unique_ptr<Resource>>     mResourceMap;
};

typedef ResourceHolder<SettingsParser, Settings::ID>        SettingsHolder;
typedef ResourceHolder<sf::Texture, Textures::ID>           TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>                 FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffects::ID>   SoundBufferHolder;
typedef ResourceHolder<TiledMap, TiledMaps::ID>             TiledMapHolder;

#include "ResourceHolder.inl"
#endif // RESOURCEHOLDER_H