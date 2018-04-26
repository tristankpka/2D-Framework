#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <list>

#include <SFML/Audio.hpp>

#include <FRK2D/ResourceHolder.hpp>

class SoundPlayer : private sf::NonCopyable
{
    public:
                                SoundPlayer();

        void                    play(SoundEffects::ID effect);
        void                    removeStoppedSounds();
    private:
        SoundBufferHolder       m_soundBuffers;
        std::list<sf::Sound>    m_sounds;
};

#endif // SOUNDPLAYER_H