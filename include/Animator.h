#pragma once
#include "GameAnimations.h"
#include <SFML/Graphics.hpp>
#include <functional>

class Animator {
public:
    explicit Animator(sf::Sprite& sprite,
        AnimationSet   set = AnimationSet::Blip,
        Direction      dir = Direction::Right,
        float          frameTime = 0.10f,   
        bool           loop = true);


    void play(AnimationSet set, Direction dir, bool loop = true);
    void setPaused(bool pause) { m_paused = pause; }
    void setDirection(Direction dir);
    void setFrameTime(float seconds) { m_frameTime = seconds; }
    void setLoop(bool loop) { m_loop = loop; }
    void reset();        


    AnimationSet currentSet()   const { return m_set; }
    Direction    currentDir()   const { return m_dir; }
    std::size_t  currentIndex() const { return m_index; }
    bool         isPaused()     const { return m_paused; }
    bool         isFinished()   const { return m_finished; }

 
    void update(float dt);

private:
    void applyRect(); 

    sf::Sprite& m_sprite;
    AnimationSet    m_set;
    Direction       m_dir;
    float           m_frameTime; 
    float           m_accumulator;
    std::size_t     m_index;      
    bool            m_loop;
    bool            m_paused;
    bool            m_finished;
};
