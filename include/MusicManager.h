#pragma once
#include <SFML/Audio.hpp>

class MusicManager {
public:
    static MusicManager& getInstance();

    void startBackgroundMusic();
    void stopBackgroundMusic();
    void toggleMusic();
    bool isMusicOn() const;
    void setVolume(float volume);

private:
    MusicManager() = default;
    bool m_musicEnabled = true;
    sf::Music* m_currentMusic = nullptr;
};