#include "MusicManager.h"
#include "DataLoader.h"
#include "Constance.h"
#include <iostream>

MusicManager& MusicManager::getInstance() {
    static MusicManager instance;
    return instance;
}

void MusicManager::startBackgroundMusic() {
    try {
        m_currentMusic = &DataLoader::getInstance().getMusic(ObjectType::BackgroundMusic);
        if (m_musicEnabled && m_currentMusic->getStatus() != sf::Music::Playing) {
            m_currentMusic->play();
            std::cout << "Background music started" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to start background music: " << e.what() << std::endl;
    }
}

void MusicManager::stopBackgroundMusic() {
    if (m_currentMusic && m_currentMusic->getStatus() == sf::Music::Playing) {
        m_currentMusic->stop();
        std::cout << "Background music stopped" << std::endl;
    }
}

void MusicManager::toggleMusic() {
    m_musicEnabled = !m_musicEnabled;

    if (m_musicEnabled) {
        startBackgroundMusic();
        std::cout << "Music turned ON" << std::endl;
    }
    else {
        stopBackgroundMusic();
        std::cout << "Music turned OFF" << std::endl;
    }
}

bool MusicManager::isMusicOn() const {
    return m_musicEnabled;
}

void MusicManager::setVolume(float volume) {
    if (m_currentMusic) {
        m_currentMusic->setVolume(volume);
    }
}