#include "Animator.h"
#include <iostream>

Animator::Animator(sf::Sprite& sprite,
    AnimationSet set,
    Direction    dir,
    float        frameTime,
    bool         loop)
    : m_sprite(sprite),
    m_set(set),
    m_dir(dir),
    m_frameTime(frameTime),
    m_accumulator(0.f),
    m_index(0),
    m_loop(loop),
    m_paused(false),
    m_finished(false)
{
    applyRect();
}

/*------------------------------------------------*/
void Animator::play(AnimationSet set, Direction dir, bool loop)
{
    m_set = set;
    m_dir = dir;
    m_loop = loop;
    m_index = 0;
    m_accumulator = 0.f;
    m_paused = false;
    m_finished = false;
    applyRect();
}

/*------------------------------------------------*/
void Animator::setDirection(Direction dir)
{
    if (dir != m_dir) {
        m_dir = dir;
        m_index = 0;
        applyRect();
    }
}

/*------------------------------------------------*/
void Animator::reset()
{
    m_index = 0;
    m_accumulator = 0.f;
    m_finished = false;
    applyRect();
}

/*------------------------------------------------*/
void Animator::update(float dt)
{        

    if (m_paused || m_finished)
        return;

    m_accumulator += dt;

    while (m_accumulator >= m_frameTime)
    {
        m_accumulator -= m_frameTime;
        ++m_index;

        try
        {
            applyRect();
        }
        catch (const std::out_of_range&)
        {
            if (m_loop)
            {
                m_index = 0;
                applyRect();
            }
            else
            {
                m_finished = true;
                --m_index;
            }
        }
    }
}

/*------------------------------------------------*/
void Animator::applyRect()
{
    const sf::IntRect& rect =
        GameAnimations::getInstance()
        .getFrame(m_set, m_dir, m_index);
    m_sprite.setTextureRect(rect);
}
