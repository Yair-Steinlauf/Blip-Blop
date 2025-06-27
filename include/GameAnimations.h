#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include "Constance.h"

/*==================================================
  Enums – סט/כיוון בצורה בטוחה
==================================================*/
enum class AnimationSet {
    Blip, Blop, Boss, BossBull,
    ForkEnemy, PresentEnemy,
    RifleGunBull, RifleGunChar, RifleGunCharBlop,
    ShotgunBull, ShotgunChar, ShotgunCharBlop,
    StandardBullet, StandardEnemy, playerHPFrames
};

enum class Direction {
    Nan, Right, Left,
    UpRight, UpLeft,
    DownRight, DownLeft,
    UpHeadRight, UpHeadLeft,
    DownHeadRight, DownHeadLeft,
    Health0, Health1, Health2, Health3, Health4, Health5
};
static Direction posToDirection(sfPos delta) {
    const float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159f;

    // ירי ימינה רגיל
    if (angle > -22.5f && angle <= 22.5f)
        return (Direction::Right);

    // ירי ימינה למעלה (זווית חדה)
    if (angle > -67.5f && angle <= -22.5f)
        return(Direction::UpRight);

    // ירי ימינה אלכסון למעלה (כמעט מעל)
    if (angle <= -67.5f && angle > -112.5f)
        return(Direction::UpHeadRight);

    // ירי ימינה למטה (זווית חדה)
    if (angle > 22.5f && angle <= 67.5f)
        return(Direction::DownRight);

    // ירי ימינה אלכסון למטה (כמעט מתחת)
    if (angle > 67.5f && angle <= 112.5f)
        return(Direction::DownHeadRight);

    // ירי שמאלה רגיל
    if (angle > 157.5f || angle <= -157.5f)
        return(Direction::Left);

    // ירי שמאלה למעלה (זווית חדה)
    if (angle > -157.5f && angle <= -112.5f)
        return(Direction::UpLeft);

    // ירי שמאלה אלכסון למעלה (כמעט מעל)
    if (angle <= -112.5f && angle > -157.5f)
        return(Direction::UpHeadLeft);

    // ירי שמאלה למטה (זווית חדה)
    if (angle > 112.5f && angle <= 157.5f)
        return(Direction::DownLeft);

    // ירי שמאלה אלכסון למטה (כמעט מתחת)
    if (angle > 67.5f && angle <= 112.5f)
        return(Direction::DownHeadLeft);

    return Direction::Nan;

}

static sfPos directionToPos(Direction dir) {
    switch (dir) {
    case Direction::Right:
        return sfPos(1.0f, 0.0f);

    case Direction::Left:
        return sfPos(-1.0f, 0.0f);

    case Direction::UpRight:
        return sfPos(0.707f, -0.707f);  // 45° למעלה ימינה

    case Direction::UpLeft:
        return sfPos(-0.707f, -0.707f);  // 45° למעלה שמאלה

    case Direction::DownRight:
        return sfPos(0.707f, 0.707f);  // 45° למטה ימינה

    case Direction::DownLeft:
        return sfPos(-0.707f, 0.707f);  // 45° למטה שמאלה

    case Direction::UpHeadRight:
        return sfPos(0.383f, -0.924f);  // ~22.5° (כמעט למעלה, קצת ימינה)

    case Direction::UpHeadLeft:
        return sfPos(-0.383f, -0.924f);  // ~22.5° (כמעט למעלה, קצת שמאלה)

    case Direction::DownHeadRight:
        return sfPos(0.383f, 0.924f);  // ~22.5° (כמעט למטה, קצת ימינה)

    case Direction::DownHeadLeft:
        return sfPos(-0.383f, 0.924f);  // ~22.5° (כמעט למטה, קצת שמאלה)

    case Direction::Nan:
    default:
        return sfPos(0.0f, 0.0f);  // אין כיוון
    }
}
/*==================================================
  GameAnimations – Singleton + Frame maps
==================================================*/
class GameAnimations
{
public:
    using FrameMap = std::map<std::string, std::vector<sf::IntRect>>;

    /*----- גישה יחידה -----*/
    static GameAnimations& getInstance() { static GameAnimations i; return i; }

    /*----- טעינה – לקרוא פעם אחת בהתחלה -----*/
    static void initializeFrames();               /* מוגדר בהמשך */

    /*----- Getters -----*/
    const sf::IntRect& getFrame(AnimationSet set,
        Direction    dir,
        std::size_t  idx = 0) const;

private:
    GameAnimations() = default;                   /* ctor פרטי */

    static const char* dirToStr(Direction);
    static FrameMap& setMap(AnimationSet);

    /*----- Frame maps – inline-static (C++17) -----*/
    static inline FrameMap  blipFrames,
        blopFrames,
        bossFrames,
        bossbullFrames,
        forkenemydataFrames,
        presentenemydataFrames,
        riflegunbullFrames,
        rifleguncharFrames,
        rifleguncharblopFrames,
        shotgunbullFrames,
        shotguncharFrames,
        shotguncharblopFrames,
        standardbulletFrames,
        standardenemydataFrames,
        playerHPdataFrames;
};

/*==================================================
           ===   IMPLEMENTATION  ===
==================================================*/
inline const char* GameAnimations::dirToStr(Direction d)
{
    switch (d) {
    case Direction::Right:          return "Right";
    case Direction::Left:           return "Left";
    case Direction::UpRight:        return "UpRight";
    case Direction::UpLeft:         return "UpLeft";
    case Direction::DownRight:      return "DownRight";
    case Direction::DownLeft:       return "DownLeft";
    case Direction::UpHeadRight:    return "UpHeadRight";
    case Direction::UpHeadLeft:     return "UpHeadLeft";
    case Direction::DownHeadRight:  return "DownHeadRight";
    case Direction::DownHeadLeft:   return "DownHeadLeft";
    case Direction::Health0:        return "Health0";
    case Direction::Health1:        return "Health1";
    case Direction::Health2:        return "Health2";
    case Direction::Health3:        return "Health3";
    case Direction::Health4:        return "Health4";
    case Direction::Health5:        return "Health5";
    }
    return "";
}

inline GameAnimations::FrameMap& GameAnimations::setMap(AnimationSet s)
{
    switch (s) {
    case AnimationSet::Blip:             return blipFrames;
    case AnimationSet::Blop:             return blopFrames;
    case AnimationSet::Boss:             return bossFrames;
    case AnimationSet::BossBull:         return bossbullFrames;
    case AnimationSet::ForkEnemy:        return forkenemydataFrames;
    case AnimationSet::PresentEnemy:     return presentenemydataFrames;
    case AnimationSet::RifleGunBull:     return riflegunbullFrames;
    case AnimationSet::RifleGunChar:     return rifleguncharFrames;
    case AnimationSet::RifleGunCharBlop: return rifleguncharblopFrames;
    case AnimationSet::ShotgunBull:      return shotgunbullFrames;
    case AnimationSet::ShotgunChar:      return shotguncharFrames;
    case AnimationSet::ShotgunCharBlop:  return shotguncharblopFrames;
    case AnimationSet::StandardBullet:   return standardbulletFrames;
    case AnimationSet::StandardEnemy:    return standardenemydataFrames;
    case AnimationSet::playerHPFrames:   return playerHPdataFrames;
    }
    throw std::out_of_range("GameAnimations: unknown set");
}

inline const sf::IntRect&
GameAnimations::getFrame(AnimationSet set, Direction dir, std::size_t idx) const
{
    const auto& m = setMap(set);
    const std::string key{ dirToStr(dir) };
    auto it = m.find(key);
    if (it == m.end() || idx >= it->second.size())
        throw std::out_of_range("GameAnimations: bad dir/index");
    return it->second[idx];
}

/*==================================================
  initializeFrames() –- כל ה-push_back  (מלא!)
==================================================*/
inline void GameAnimations::initializeFrames()
{
    /*--------------------------------------------------
      Blip (10)
    --------------------------------------------------*/
    blipFrames.clear();
    blipFrames["Right"].push_back({ 15,  7, 65, 28 });
    blipFrames["Left"].push_back({ 6, 40, 65, 28 });
    blipFrames["UpRight"].push_back({ 20, 76, 55, 55 });
    blipFrames["UpLeft"].push_back({ 20,133, 55, 55 });
    blipFrames["DownRight"].push_back({ 21,194, 54, 46 });
    blipFrames["DownLeft"].push_back({ 18,247, 55, 46 });
    blipFrames["DownHeadLeft"].push_back({ 25,368, 47, 66 });
    blipFrames["DownHeadRight"].push_back({ 23,299, 48, 65 });
    blipFrames["UpHeadLeft"].push_back({ 24,438, 48, 65 });
    blipFrames["UpHeadRight"].push_back({ 22,509, 47, 66 });

    /*--------------------------------------------------
      Blop (10)
    --------------------------------------------------*/
    blopFrames.clear();
    blopFrames["Right"].push_back({ 263,  2, 63, 36 });
    blopFrames["Left"].push_back({ 248, 38, 65, 35 });
    blopFrames["UpRight"].push_back({ 258, 75, 50, 54 });
    blopFrames["UpLeft"].push_back({ 253,131, 50, 55 });
    blopFrames["DownRight"].push_back({ 257,188, 55, 50 });
    blopFrames["DownLeft"].push_back({ 254,238, 55, 60 });
    blopFrames["DownHeadLeft"].push_back({ 261,357, 42, 60 });
    blopFrames["DownHeadRight"].push_back({ 257,290, 46, 60 });
    blopFrames["UpHeadLeft"].push_back({ 258,460, 44, 55 });
    blopFrames["UpHeadRight"].push_back({ 259,525, 45, 55 });

    /*--------------------------------------------------
      Boss (30)
    --------------------------------------------------*/
    bossFrames.clear();
    bossFrames["Right"].push_back({ 12,  1, 28, 54 });
    bossFrames["Right"].push_back({ 10, 56, 23, 56 });
    bossFrames["Right"].push_back({ 11,112, 25, 56 });
    bossFrames["Right"].push_back({ 8,168, 32, 54 });
    bossFrames["Left"].push_back({ 10,224, 28, 54 });
    bossFrames["Left"].push_back({ 17,279, 23, 56 });
    bossFrames["Left"].push_back({ 14,335, 25, 56 });
    bossFrames["Left"].push_back({ 10,391, 32, 54 });
    bossFrames["DownRight"].push_back({ 72,206, 33, 50 });
    bossFrames["DownRight"].push_back({ 69,257, 34, 48 });
    bossFrames["DownRight"].push_back({ 62,307, 44, 48 });
    bossFrames["DownRight"].push_back({ 56,356, 49, 48 });
    bossFrames["DownLeft"].push_back({ 56,  2, 33, 50 });
    bossFrames["DownLeft"].push_back({ 58, 53, 34, 48 });
    bossFrames["DownLeft"].push_back({ 55,103, 44, 48 });
    bossFrames["DownLeft"].push_back({ 56,152, 49, 48 });
    bossFrames["DownHeadLeft"].push_back({ 399,  2, 28, 54 });
    bossFrames["DownHeadLeft"].push_back({ 401,112, 32, 46 });
    bossFrames["DownHeadLeft"].push_back({ 399,214, 32, 46 });
    bossFrames["DownHeadLeft"].push_back({ 395,311, 36, 46 });
    bossFrames["DownHeadLeft"].push_back({ 392,411, 39, 45 });
    bossFrames["DownHeadLeft"].push_back({ 385,459, 46, 46 });
    bossFrames["DownHeadLeft"].push_back({ 372,624, 59, 24 });
    bossFrames["DownHeadRight"].push_back({ 302,  2, 28, 54 });
    bossFrames["DownHeadRight"].push_back({ 297,112, 32, 46 });
    bossFrames["DownHeadRight"].push_back({ 296,214, 32, 46 });
    bossFrames["DownHeadRight"].push_back({ 298,311, 36, 46 });
    bossFrames["DownHeadRight"].push_back({ 298,411, 39, 45 });
    bossFrames["DownHeadRight"].push_back({ 298,459, 46, 46 });
    bossFrames["DownHeadRight"].push_back({ 298,624, 59, 24 });

    /*--------------------------------------------------
      BossBull (4)
    --------------------------------------------------*/
    bossbullFrames.clear();
    bossbullFrames["Right"].push_back({ 55,407, 44,35 });
    bossbullFrames["Right"].push_back({ 55,445, 57,30 });
    bossbullFrames["Left"].push_back({ 68,480, 44,35 });
    bossbullFrames["Left"].push_back({ 54,518, 57,30 });

    /*--------------------------------------------------
      ForkEnemy (16)
    --------------------------------------------------*/
    forkenemydataFrames.clear();
    forkenemydataFrames["Right"].push_back({ 726,  4, 54,44 });
    forkenemydataFrames["Right"].push_back({ 725, 48, 51,45 });
    forkenemydataFrames["Right"].push_back({ 723, 95, 52,42 });
    forkenemydataFrames["Right"].push_back({ 725,138, 52,44 });
    forkenemydataFrames["Left"].push_back({ 720,190, 54,44 });
    forkenemydataFrames["Left"].push_back({ 724,234, 51,45 });
    forkenemydataFrames["Left"].push_back({ 725,281, 52,42 });
    forkenemydataFrames["Left"].push_back({ 723,324, 52,44 });
    forkenemydataFrames["DownLeft"].push_back({ 719,376, 83,35 });
    forkenemydataFrames["DownLeft"].push_back({ 720,413, 53,32 });
    forkenemydataFrames["DownLeft"].push_back({ 721,448, 53,32 });
    forkenemydataFrames["DownLeft"].push_back({ 719,481, 54,32 });
    forkenemydataFrames["DownRight"].push_back({ 717,516, 83,35 });
    forkenemydataFrames["DownRight"].push_back({ 746,553, 53,32 });
    forkenemydataFrames["DownRight"].push_back({ 745,588, 53,32 });
    forkenemydataFrames["DownRight"].push_back({ 746,621, 54,32 });

    /*--------------------------------------------------
      PresentEnemy (15)
    --------------------------------------------------*/
    presentenemydataFrames.clear();
    presentenemydataFrames["Right"].push_back({ 811,  5, 55,50 });
    presentenemydataFrames["Right"].push_back({ 811, 56, 55,50 });
    presentenemydataFrames["Right"].push_back({ 812,107, 54,50 });
    presentenemydataFrames["Right"].push_back({ 813,156, 53,51 });
    presentenemydataFrames["Right"].push_back({ 813,207, 54,51 });
    presentenemydataFrames["Left"].push_back({ 816,260, 55,50 });
    presentenemydataFrames["Left"].push_back({ 816,312, 55,50 });
    presentenemydataFrames["Left"].push_back({ 816,362, 54,50 });
    presentenemydataFrames["Left"].push_back({ 816,411, 53,51 });
    presentenemydataFrames["Left"].push_back({ 815,461, 54,51 });
    presentenemydataFrames["Stay"].push_back({ 810,515, 96,61 });
    presentenemydataFrames["Stay"].push_back({ 810,515, 96,61 });
    presentenemydataFrames["Stay"].push_back({ 814,579, 89,73 });
    presentenemydataFrames["Stay"].push_back({ 817,654, 92,79 });
    presentenemydataFrames["Stay"].push_back({ 817,654, 92,79 });

    /*--------------------------------------------------
      RifleGunBull (10)
    --------------------------------------------------*/
    riflegunbullFrames.clear();
    riflegunbullFrames["Left"].push_back({ 475,253,26, 9 });
    riflegunbullFrames["Right"].push_back({ 478,280,26, 9 });
    riflegunbullFrames["DownLeft"].push_back({ 479,400,21,20 });
    riflegunbullFrames["UpRight"].push_back({ 476,330,20,20 });
    riflegunbullFrames["DownRight"].push_back({ 479,359,20,22 });
    riflegunbullFrames["UpLeft"].push_back({ 481,300,20,21 });
    riflegunbullFrames["UpHeadLeft"].push_back({ 486,426,10,28 });
    riflegunbullFrames["DownHeadRight"].push_back({ 486,459,10,26 });
    riflegunbullFrames["UpHeadRight"].push_back({ 486,426,10,28 });
    riflegunbullFrames["DownHeadLeft"].push_back({ 486,459,10,26 });

    /*--------------------------------------------------
      RifleGunChar (10)
    --------------------------------------------------*/
    rifleguncharFrames.clear();
    rifleguncharFrames["Left"].push_back({ 177, 41,61,27 });
    rifleguncharFrames["Right"].push_back({ 185,  8,61,27 });
    rifleguncharFrames["DownLeft"].push_back({ 186,244,48,40 });
    rifleguncharFrames["UpRight"].push_back({ 183, 74,53,41 });
    rifleguncharFrames["DownRight"].push_back({ 184,191,48,40 });
    rifleguncharFrames["UpLeft"].push_back({ 182,134,53,41 });
    rifleguncharFrames["UpHeadRight"].push_back({ 187,516,44,55 });
    rifleguncharFrames["DownHeadRight"].push_back({ 185,295,45,54 });
    rifleguncharFrames["UpHeadLeft"].push_back({ 190,450,44,55 });
    rifleguncharFrames["DownHeadLeft"].push_back({ 186,362,46,54 });

    /*--------------------------------------------------
      RifleGunCharBlop (10)
    --------------------------------------------------*/
    rifleguncharblopFrames.clear();
    rifleguncharblopFrames["Right"].push_back({ 417,  2,55,37 });
    rifleguncharblopFrames["Left"].push_back({ 404, 39,55,39 });
    rifleguncharblopFrames["UpRight"].push_back({ 418, 82,49,43 });
    rifleguncharblopFrames["UpLeft"].push_back({ 413,145,49,43 });
    rifleguncharblopFrames["DownRight"].push_back({ 419,189,48,48 });
    rifleguncharblopFrames["DownLeft"].push_back({ 415,239,48,48 });
    rifleguncharblopFrames["DownHeadRight"].push_back({ 419,362,44,67 });
    rifleguncharblopFrames["DownHeadLeft"].push_back({ 416,291,44,67 });
    rifleguncharblopFrames["UpHeadLeft"].push_back({ 417,449,41,59 });
    rifleguncharblopFrames["UpHeadRight"].push_back({ 415,516,42,59 });

    /*--------------------------------------------------
      ShotgunBull (10)
    --------------------------------------------------*/
    shotgunbullFrames.clear();
    shotgunbullFrames["Left"].push_back({ 465,500,47,31 });
    shotgunbullFrames["Right"].push_back({ 468,540,47,30 });
    shotgunbullFrames["DownLeft"].push_back({ 472,707,51,39 });
    shotgunbullFrames["UpRight"].push_back({ 471,620,43,40 });
    shotgunbullFrames["DownRight"].push_back({ 472,663,39,42 });
    shotgunbullFrames["UpLeft"].push_back({ 470,574,39,42 });
    shotgunbullFrames["UpHeadLeft"].push_back({ 475,752,30,47 });
    shotgunbullFrames["DownHeadRight"].push_back({ 478,803,28,47 });
    shotgunbullFrames["UpHeadRight"].push_back({ 475,752,30,47 });
    shotgunbullFrames["DownHeadLeft"].push_back({ 478,803,28,47 });

    /*--------------------------------------------------
      ShotgunChar (10)
    --------------------------------------------------*/
    shotguncharFrames.clear();
    shotguncharFrames["Left"].push_back({ 86, 38,69,28 });
    shotguncharFrames["Right"].push_back({ 100,  7,68,27 });
    shotguncharFrames["DownLeft"].push_back({ 101,239,55,49 });
    shotguncharFrames["UpRight"].push_back({ 98, 67,59,53 });
    shotguncharFrames["DownRight"].push_back({ 104,184,55,49 });
    shotguncharFrames["UpLeft"].push_back({ 97,125,59,55 });
    shotguncharFrames["UpHeadRight"].push_back({ 110,506,46,65 });
    shotguncharFrames["DownHeadRight"].push_back({ 102,292,45,65 });
    shotguncharFrames["UpHeadLeft"].push_back({ 113,439,46,65 });
    shotguncharFrames["DownHeadLeft"].push_back({ 109,359,45,65 });

    /*--------------------------------------------------
      ShotgunCharBlop (10)
    --------------------------------------------------*/
    shotguncharblopFrames.clear();
    shotguncharblopFrames["Right"].push_back({ 342,  1,68,37 });
    shotguncharblopFrames["Left"].push_back({ 318, 38,68,37 });
    shotguncharblopFrames["UpRight"].push_back({ 342, 75,55,53 });
    shotguncharblopFrames["UpLeft"].push_back({ 332,137,55,53 });
    shotguncharblopFrames["DownRight"].push_back({ 341,190,53,49 });
    shotguncharblopFrames["DownLeft"].push_back({ 340,239,53,49 });
    shotguncharblopFrames["DownHeadRight"].push_back({ 347,361,43,73 });
    shotguncharblopFrames["DownHeadLeft"].push_back({ 346,288,44,73 });
    shotguncharblopFrames["UpHeadLeft"].push_back({ 343,443,46,67 });
    shotguncharblopFrames["UpHeadRight"].push_back({ 342,510,46,67 });

    /*--------------------------------------------------
      StandardBullet (10)
    --------------------------------------------------*/
    standardbulletFrames.clear();
    standardbulletFrames["Left"].push_back({ 474, 15,19, 7 });
    standardbulletFrames["Right"].push_back({ 475, 43,19, 7 });
    standardbulletFrames["DownLeft"].push_back({ 480,162,15,15 });
    standardbulletFrames["UpLeft"].push_back({ 480, 68,15,15 });
    standardbulletFrames["DownRight"].push_back({ 481,129,15,15 });
    standardbulletFrames["UpRight"].push_back({ 481, 94,16,16 });
    standardbulletFrames["UpHeadLeft"].push_back({ 483,189, 8,20 });
    standardbulletFrames["UpHeadRight"].push_back({ 483,189, 8,20 });
    standardbulletFrames["DownHeadLeft"].push_back({ 484,220, 8,20 });
    standardbulletFrames["DownHeadRight"].push_back({ 484,220, 8,20 });

    /*--------------------------------------------------
      StandardEnemy (27)
    --------------------------------------------------*/
    standardenemydataFrames.clear();
    standardenemydataFrames["Right"].push_back({ 519,  0,26,38 });
    standardenemydataFrames["Right"].push_back({ 520, 39,23,38 });
    standardenemydataFrames["Right"].push_back({ 520, 77,23,39 });
    standardenemydataFrames["Right"].push_back({ 521,116,22,38 });
    standardenemydataFrames["Right"].push_back({ 519,154,25,38 });
    standardenemydataFrames["Left"].push_back({ 519,194,26,38 });
    standardenemydataFrames["Left"].push_back({ 521,233,23,38 });
    standardenemydataFrames["Left"].push_back({ 520,272,22,39 });
    standardenemydataFrames["Left"].push_back({ 521,311,22,38 });
    standardenemydataFrames["Left"].push_back({ 520,351,25,38 });
    standardenemydataFrames["UpHeadRight"].push_back({ 518,392,30,38 });
    standardenemydataFrames["UpHeadRight"].push_back({ 518,392,30,38 });
    standardenemydataFrames["UpHeadRight"].push_back({ 518,392,30,38 });
    standardenemydataFrames["UpHeadRight"].push_back({ 518,392,30,38 });
    standardenemydataFrames["UpHeadRight"].push_back({ 518,392,30,38 });
    standardenemydataFrames["UpHeadLeft"].push_back({ 518,430,29,38 });
    standardenemydataFrames["UpHeadLeft"].push_back({ 518,430,29,38 });
    standardenemydataFrames["UpHeadLeft"].push_back({ 518,430,29,38 });
    standardenemydataFrames["UpHeadLeft"].push_back({ 518,430,29,38 });
    standardenemydataFrames["UpHeadLeft"].push_back({ 518,430,29,38 });
    standardenemydataFrames["Stay"].push_back({ 565,470,24,39 });
    standardenemydataFrames["Stay"].push_back({ 563,509,26,41 });
    standardenemydataFrames["Stay"].push_back({ 563,551,34,47 });
    standardenemydataFrames["Stay"].push_back({ 556,606,50,54 });
    standardenemydataFrames["Stay"].push_back({ 539,663,90,79 });
    standardenemydataFrames["Stay"].push_back({ 527,745,123,79 });
    standardenemydataFrames["Stay"].push_back({ 514,828,142,79 });

    /*--------------------------------------------------
    playerHPFrames (5)
    --------------------------------------------------*/
    playerHPdataFrames["Health5"].push_back({ 2,   816, 64, 64 });
    playerHPdataFrames["Health4"].push_back({ 67,  816, 64, 64 });
    playerHPdataFrames["Health3"].push_back({ 129, 816, 64, 64 });
    playerHPdataFrames["Health2"].push_back({ 192, 816, 64, 64 });
    playerHPdataFrames["Health1"].push_back({ 255, 816, 62, 64 });
    playerHPdataFrames["Health0"].push_back({ 316, 816, 64, 64 });

}
