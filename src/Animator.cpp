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
    std::cout << "idx = " << m_index << "  set=" << int(m_set)
        << " dir=" << int(m_dir) << '\n';

    if (m_paused || m_finished)
        return;

    m_accumulator += dt;

    while (m_accumulator >= m_frameTime)
    {
        m_accumulator -= m_frameTime;
        ++m_index;                       // עוברים למסגרת הבאה

        try
        {
            applyRect();                 // תופס גם את Frame-0 וגם מעבר גבול
        }
        catch (const std::out_of_range&)
        {
            if (m_loop)                  // בלולאה: חוזרים להתחלה
            {
                m_index = 0;
                applyRect();             // בטוח קיים (idx==0)
            }
            else                         // חד-פעמי: עוצרים על המסגרת האחרונה
            {
                m_finished = true;
                --m_index;               // משאירים אינדקס תקף
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
