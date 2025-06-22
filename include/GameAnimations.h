#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

// Auto-generated animation frames from game code
enum class AnimationSet {
    Blip, Blop, Boss, BossBull,
    ForkEnemy, PresentEnemy,
    RifleGunBull, RifleGunChar, RifleGunCharBlop,
    ShotgunBull, ShotgunChar, ShotgunCharBlop,
    StandardBullet, StandardEnemy
};
enum class Direction {
    Right, Left,
    UpRight, UpLeft,
    DownRight, DownLeft,
    UpHeadRight, UpHeadLeft,
    DownHeadRight, DownHeadLeft
};

class GameAnimations {
private:
    using FrameMap = std::map<std::string, std::vector<sf::IntRect>>;

    /* ctor פרטי – Singleton */
    GameAnimations() = default;

    /* המרה Enum→string (המפתחות נשארו בדיוק כפי שהיו במקור) */
    static const char* dirToStr(Direction d) {
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
        }
        return "";
    }

    /* מחזירה את ה-map של ה-set המבוקש */
    static const FrameMap& getSet(AnimationSet s) {
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
        }
        throw std::out_of_range("GameAnimations: unknown AnimationSet");
    }

public:
    /*------------ Singleton getter ------------*/
    static GameAnimations& getInstance() {
        static GameAnimations inst;
        return inst;
    }

    /*------------ טעינת כל הפריימים – חובה לקרוא פעם אחת בתחילת התכנית ------------*/
    static void initializeFrames();   // ההגדרה עצמה מופיעה מיד אחרי המחלקה

    /*------------ Getter גנרי על-פי Enum ------------*/
    const sf::IntRect& getFrame(AnimationSet set,
        Direction      dir,
        std::size_t    idx = 0) const
    {
        const auto& m = getSet(set);
        const char* key = dirToStr(dir);

        auto it = m.find(key);
        if (it == m.end() || idx >= it->second.size())
            throw std::out_of_range("GameAnimations: bad dir/index");
        return it->second[idx];
    }

    /* אופציונלי – Getter ע״פ מחרוזת (לשימוש קוד קיים) */
    const sf::IntRect& getFrame(AnimationSet      set,
        const std::string& dirStr,
        std::size_t        idx = 0) const
    {
        const auto& m = getSet(set);
        auto it = m.find(dirStr);
        if (it == m.end() || idx >= it->second.size())
            throw std::out_of_range("GameAnimations: bad dir/index");
        return it->second[idx];
    }

    static inline FrameMap blipFrames,
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
        standardenemydataFrames;
};

// Static frame maps
static std::map<std::string, std::vector<sf::IntRect>> blipFrames;
static std::map<std::string, std::vector<sf::IntRect>> blopFrames;
static std::map<std::string, std::vector<sf::IntRect>> bossFrames;
static std::map<std::string, std::vector<sf::IntRect>> bossbullFrames;
static std::map<std::string, std::vector<sf::IntRect>> forkenemydataFrames;
static std::map<std::string, std::vector<sf::IntRect>> presentenemydataFrames;
static std::map<std::string, std::vector<sf::IntRect>> riflegunbullFrames;
static std::map<std::string, std::vector<sf::IntRect>> rifleguncharFrames;
static std::map<std::string, std::vector<sf::IntRect>> rifleguncharblopFrames;
static std::map<std::string, std::vector<sf::IntRect>> shotgunbullFrames;
static std::map<std::string, std::vector<sf::IntRect>> shotguncharFrames;
static std::map<std::string, std::vector<sf::IntRect>> shotguncharblopFrames;
static std::map<std::string, std::vector<sf::IntRect>> standardbulletFrames;
static std::map<std::string, std::vector<sf::IntRect>> standardenemydataFrames;

    inline void initializeFrames() {

        // Blip Animation - 10 frames
        blipFrames.clear();
        blipFrames["Right"].push_back(sf::IntRect(15, 7, 65, 28));
        blipFrames["Left"].push_back(sf::IntRect(6, 40, 65, 28));
        blipFrames["UpRight"].push_back(sf::IntRect(20, 76, 55, 55));
        blipFrames["UpLeft"].push_back(sf::IntRect(20, 133, 55, 55));
        blipFrames["DownRight"].push_back(sf::IntRect(21, 194, 54, 46));
        blipFrames["DownLeft"].push_back(sf::IntRect(18, 247, 55, 46));
        blipFrames["DownHeadLeft"].push_back(sf::IntRect(25, 368, 47, 66));
        blipFrames["DownHeadRight"].push_back(sf::IntRect(23, 299, 48, 65));
        blipFrames["UpHeadLeft"].push_back(sf::IntRect(24, 438, 48, 65));
        blipFrames["UpHeadRight"].push_back(sf::IntRect(22, 509, 47, 66));

        // Blop Animation - 10 frames
        blopFrames.clear();
        blopFrames["Right"].push_back(sf::IntRect(263, 2, 63, 36));
        blopFrames["Left"].push_back(sf::IntRect(248, 38, 65, 35));
        blopFrames["UpRight"].push_back(sf::IntRect(258, 75, 50, 54));
        blopFrames["UpLeft"].push_back(sf::IntRect(253, 131, 50, 55));
        blopFrames["DownRight"].push_back(sf::IntRect(257, 188, 55, 50));
        blopFrames["DownLeft"].push_back(sf::IntRect(254, 238, 55, 60));
        blopFrames["DownHeadLeft"].push_back(sf::IntRect(261, 357, 42, 60));
        blopFrames["DownHeadRight"].push_back(sf::IntRect(257, 290, 46, 60));
        blopFrames["UpHeadLeft"].push_back(sf::IntRect(258, 460, 44, 55));
        blopFrames["UpHeadRight"].push_back(sf::IntRect(259, 525, 45, 55));

        // Boss Animation - 30 frames
        bossFrames.clear();
        bossFrames["Right"].push_back(sf::IntRect(12, 1, 28, 54));
        bossFrames["Right"].push_back(sf::IntRect(10, 56, 23, 56));
        bossFrames["Right"].push_back(sf::IntRect(11, 112, 25, 56));
        bossFrames["Right"].push_back(sf::IntRect(8, 168, 32, 54));
        bossFrames["Left"].push_back(sf::IntRect(10, 224, 28, 54));
        bossFrames["Left"].push_back(sf::IntRect(17, 279, 23, 56));
        bossFrames["Left"].push_back(sf::IntRect(14, 335, 25, 56));
        bossFrames["Left"].push_back(sf::IntRect(10, 391, 32, 54));
        bossFrames["DownRight"].push_back(sf::IntRect(72, 206, 33, 50));
        bossFrames["DownRight"].push_back(sf::IntRect(69, 257, 34, 48));
        bossFrames["DownRight"].push_back(sf::IntRect(62, 307, 44, 48));
        bossFrames["DownRight"].push_back(sf::IntRect(56, 356, 49, 48));
        bossFrames["DownLeft"].push_back(sf::IntRect(56, 2, 33, 50));
        bossFrames["DownLeft"].push_back(sf::IntRect(58, 53, 34, 48));
        bossFrames["DownLeft"].push_back(sf::IntRect(55, 103, 44, 48));
        bossFrames["DownLeft"].push_back(sf::IntRect(56, 152, 49, 48));
        bossFrames["DownHeadLeft"].push_back(sf::IntRect(399, 2, 28, 54));
        bossFrames["DownHeadLeft"].push_back(sf::IntRect(401, 112, 32, 46));
        bossFrames["DownHeadLeft"].push_back(sf::IntRect(399, 214, 32, 46));
        bossFrames["DownHeadLeft"].push_back(sf::IntRect(395, 311, 36, 46));
        bossFrames["DownHeadLeft"].push_back(sf::IntRect(392, 411, 39, 45));
        bossFrames["DownHeadLeft"].push_back(sf::IntRect(385, 459, 46, 46));
        bossFrames["DownHeadLeft"].push_back(sf::IntRect(372, 624, 59, 24));
        bossFrames["DownHeadRight"].push_back(sf::IntRect(302, 2, 28, 54));
        bossFrames["DownHeadRight"].push_back(sf::IntRect(297, 112, 32, 46));
        bossFrames["DownHeadRight"].push_back(sf::IntRect(296, 214, 32, 46));
        bossFrames["DownHeadRight"].push_back(sf::IntRect(298, 311, 36, 46));
        bossFrames["DownHeadRight"].push_back(sf::IntRect(298, 411, 39, 45));
        bossFrames["DownHeadRight"].push_back(sf::IntRect(298, 459, 46, 46));
        bossFrames["DownHeadRight"].push_back(sf::IntRect(298, 624, 59, 24));

        // BossBull Animation - 4 frames
        bossbullFrames.clear();
        bossbullFrames["Right"].push_back(sf::IntRect(55, 407, 44, 35));
        bossbullFrames["Right"].push_back(sf::IntRect(55, 445, 57, 30));
        bossbullFrames["Left"].push_back(sf::IntRect(68, 480, 44, 35));
        bossbullFrames["Left"].push_back(sf::IntRect(54, 518, 57, 30));

        // ForkEnemyData Animation - 16 frames
        forkenemydataFrames.clear();
        forkenemydataFrames["Right"].push_back(sf::IntRect(726, 4, 54, 44));
        forkenemydataFrames["Right"].push_back(sf::IntRect(725, 48, 51, 45));
        forkenemydataFrames["Right"].push_back(sf::IntRect(723, 95, 52, 42));
        forkenemydataFrames["Right"].push_back(sf::IntRect(725, 138, 52, 44));
        forkenemydataFrames["Left"].push_back(sf::IntRect(720, 190, 54, 44));
        forkenemydataFrames["Left"].push_back(sf::IntRect(724, 234, 51, 45));
        forkenemydataFrames["Left"].push_back(sf::IntRect(725, 281, 52, 42));
        forkenemydataFrames["Left"].push_back(sf::IntRect(723, 324, 52, 44));
        forkenemydataFrames["DownLeft"].push_back(sf::IntRect(719, 376, 83, 35));
        forkenemydataFrames["DownLeft"].push_back(sf::IntRect(720, 413, 53, 32));
        forkenemydataFrames["DownLeft"].push_back(sf::IntRect(721, 448, 53, 32));
        forkenemydataFrames["DownLeft"].push_back(sf::IntRect(719, 481, 54, 32));
        forkenemydataFrames["DownRight"].push_back(sf::IntRect(717, 516, 83, 35));
        forkenemydataFrames["DownRight"].push_back(sf::IntRect(746, 553, 53, 32));
        forkenemydataFrames["DownRight"].push_back(sf::IntRect(745, 588, 53, 32));
        forkenemydataFrames["DownRight"].push_back(sf::IntRect(746, 621, 54, 32));

        // PresentEnemyData Animation - 15 frames
        presentenemydataFrames.clear();
        presentenemydataFrames["Right"].push_back(sf::IntRect(811, 5, 55, 50));
        presentenemydataFrames["Right"].push_back(sf::IntRect(811, 56, 55, 50));
        presentenemydataFrames["Right"].push_back(sf::IntRect(812, 107, 54, 50));
        presentenemydataFrames["Right"].push_back(sf::IntRect(813, 156, 53, 51));
        presentenemydataFrames["Right"].push_back(sf::IntRect(813, 207, 54, 51));
        presentenemydataFrames["Left"].push_back(sf::IntRect(816, 260, 55, 50));
        presentenemydataFrames["Left"].push_back(sf::IntRect(816, 312, 55, 50));
        presentenemydataFrames["Left"].push_back(sf::IntRect(816, 362, 54, 50));
        presentenemydataFrames["Left"].push_back(sf::IntRect(816, 411, 53, 51));
        presentenemydataFrames["Left"].push_back(sf::IntRect(815, 461, 54, 51));
        presentenemydataFrames["Stay"].push_back(sf::IntRect(810, 515, 96, 61));
        presentenemydataFrames["Stay"].push_back(sf::IntRect(810, 515, 96, 61));
        presentenemydataFrames["Stay"].push_back(sf::IntRect(814, 579, 89, 73));
        presentenemydataFrames["Stay"].push_back(sf::IntRect(817, 654, 92, 79));
        presentenemydataFrames["Stay"].push_back(sf::IntRect(817, 654, 92, 79));

        // RifleGunBull Animation - 10 frames
        riflegunbullFrames.clear();
        riflegunbullFrames["Left"].push_back(sf::IntRect(475, 253, 26, 9));
        riflegunbullFrames["Right"].push_back(sf::IntRect(478, 280, 26, 9));
        riflegunbullFrames["DownLeft"].push_back(sf::IntRect(479, 400, 21, 20));
        riflegunbullFrames["UpRight"].push_back(sf::IntRect(476, 330, 20, 20));
        riflegunbullFrames["DownRight"].push_back(sf::IntRect(479, 359, 20, 22));
        riflegunbullFrames["UpLeft"].push_back(sf::IntRect(481, 300, 20, 21));
        riflegunbullFrames["UpHeadLeft"].push_back(sf::IntRect(486, 426, 10, 28));
        riflegunbullFrames["DownHeadRight"].push_back(sf::IntRect(486, 459, 10, 26));
        riflegunbullFrames["UpHeadRight"].push_back(sf::IntRect(486, 426, 10, 28));
        riflegunbullFrames["DownHeadLeft"].push_back(sf::IntRect(486, 459, 10, 26));

        // RifleGunChar Animation - 10 frames
        rifleguncharFrames.clear();
        rifleguncharFrames["Left"].push_back(sf::IntRect(177, 41, 61, 27));
        rifleguncharFrames["Right"].push_back(sf::IntRect(185, 8, 61, 27));
        rifleguncharFrames["DownLeft"].push_back(sf::IntRect(186, 244, 48, 40));
        rifleguncharFrames["UpRight"].push_back(sf::IntRect(183, 74, 53, 41));
        rifleguncharFrames["DownRight"].push_back(sf::IntRect(184, 191, 48, 40));
        rifleguncharFrames["UpLeft"].push_back(sf::IntRect(182, 134, 53, 41));
        rifleguncharFrames["UpHeadRight"].push_back(sf::IntRect(187, 516, 44, 55));
        rifleguncharFrames["DownHeadRight"].push_back(sf::IntRect(185, 295, 45, 54));
        rifleguncharFrames["UpHeadLeft"].push_back(sf::IntRect(190, 450, 44, 55));
        rifleguncharFrames["DownHeadLeft"].push_back(sf::IntRect(186, 362, 46, 54));

        // RifleGunCharBlop Animation - 10 frames
        rifleguncharblopFrames.clear();
        rifleguncharblopFrames["Right"].push_back(sf::IntRect(417, 2, 55, 37));
        rifleguncharblopFrames["Left"].push_back(sf::IntRect(404, 39, 55, 39));
        rifleguncharblopFrames["UpRight"].push_back(sf::IntRect(418, 82, 49, 43));
        rifleguncharblopFrames["UpLeft"].push_back(sf::IntRect(413, 145, 49, 43));
        rifleguncharblopFrames["DownRight"].push_back(sf::IntRect(419, 189, 48, 48));
        rifleguncharblopFrames["DownLeft"].push_back(sf::IntRect(415, 239, 48, 48));
        rifleguncharblopFrames["DownHeadRight"].push_back(sf::IntRect(419, 362, 44, 67));
        rifleguncharblopFrames["DownHeadLeft"].push_back(sf::IntRect(416, 291, 44, 67));
        rifleguncharblopFrames["UpHeadLeft"].push_back(sf::IntRect(417, 449, 41, 59));
        rifleguncharblopFrames["UpHeadRight"].push_back(sf::IntRect(415, 516, 42, 59));

        // ShotGunBull Animation - 10 frames
        shotgunbullFrames.clear();
        shotgunbullFrames["Left"].push_back(sf::IntRect(465, 500, 47, 31));
        shotgunbullFrames["Right"].push_back(sf::IntRect(468, 540, 47, 30));
        shotgunbullFrames["DownLeft"].push_back(sf::IntRect(472, 707, 51, 39));
        shotgunbullFrames["UpRight"].push_back(sf::IntRect(471, 620, 43, 40));
        shotgunbullFrames["DownRight"].push_back(sf::IntRect(472, 663, 39, 42));
        shotgunbullFrames["UpLeft"].push_back(sf::IntRect(470, 574, 39, 42));
        shotgunbullFrames["UpHeadLeft"].push_back(sf::IntRect(475, 752, 30, 47));
        shotgunbullFrames["DownHeadRight"].push_back(sf::IntRect(478, 803, 28, 47));
        shotgunbullFrames["UpHeadRight"].push_back(sf::IntRect(475, 752, 30, 47));
        shotgunbullFrames["DownHeadLeft"].push_back(sf::IntRect(478, 803, 28, 47));

        // ShotGunChar Animation - 10 frames
        shotguncharFrames.clear();
        shotguncharFrames["Left"].push_back(sf::IntRect(86, 38, 69, 28));
        shotguncharFrames["Right"].push_back(sf::IntRect(100, 7, 68, 27));
        shotguncharFrames["DownLeft"].push_back(sf::IntRect(101, 239, 55, 49));
        shotguncharFrames["UpRight"].push_back(sf::IntRect(98, 67, 59, 53));
        shotguncharFrames["DownRight"].push_back(sf::IntRect(104, 184, 55, 49));
        shotguncharFrames["UpLeft"].push_back(sf::IntRect(97, 125, 59, 55));
        shotguncharFrames["UpHeadRight"].push_back(sf::IntRect(110, 506, 46, 65));
        shotguncharFrames["DownHeadRight"].push_back(sf::IntRect(102, 292, 45, 65));
        shotguncharFrames["UpHeadLeft"].push_back(sf::IntRect(113, 439, 46, 65));
        shotguncharFrames["DownHeadLeft"].push_back(sf::IntRect(109, 359, 45, 65));

        // ShotGunCharBlop Animation - 10 frames
        shotguncharblopFrames.clear();
        shotguncharblopFrames["Right"].push_back(sf::IntRect(342, 1, 68, 37));
        shotguncharblopFrames["Left"].push_back(sf::IntRect(318, 38, 68, 37));
        shotguncharblopFrames["UpRight"].push_back(sf::IntRect(342, 75, 55, 53));
        shotguncharblopFrames["UpLeft"].push_back(sf::IntRect(332, 137, 55, 53));
        shotguncharblopFrames["DownRight"].push_back(sf::IntRect(341, 190, 53, 49));
        shotguncharblopFrames["DownLeft"].push_back(sf::IntRect(340, 239, 53, 49));
        shotguncharblopFrames["DownHeadRight"].push_back(sf::IntRect(347, 361, 43, 73));
        shotguncharblopFrames["DownHeadLeft"].push_back(sf::IntRect(346, 288, 44, 73));
        shotguncharblopFrames["UpHeadLeft"].push_back(sf::IntRect(343, 443, 46, 67));
        shotguncharblopFrames["UpHeadRight"].push_back(sf::IntRect(342, 510, 46, 67));

        // StandardBullet Animation - 10 frames
        standardbulletFrames.clear();
        standardbulletFrames["Left"].push_back(sf::IntRect(474, 15, 19, 7));
        standardbulletFrames["Right"].push_back(sf::IntRect(475, 43, 19, 7));
        standardbulletFrames["DownLeft"].push_back(sf::IntRect(480, 162, 15, 15));
        standardbulletFrames["UpLeft"].push_back(sf::IntRect(480, 68, 15, 15));
        standardbulletFrames["DownRight"].push_back(sf::IntRect(481, 129, 15, 15));
        standardbulletFrames["UpRight"].push_back(sf::IntRect(481, 94, 16, 16));
        standardbulletFrames["UpHeadLeft"].push_back(sf::IntRect(483, 189, 8, 20));
        standardbulletFrames["UpHeadRight"].push_back(sf::IntRect(483, 189, 8, 20));
        standardbulletFrames["DownHeadLeft"].push_back(sf::IntRect(484, 220, 8, 20));
        standardbulletFrames["DownHeadRight"].push_back(sf::IntRect(484, 220, 8, 20));

        // standardEnemyData Animation - 27 frames
        standardenemydataFrames.clear();
        standardenemydataFrames["Right"].push_back(sf::IntRect(519, 0, 26, 38));
        standardenemydataFrames["Right"].push_back(sf::IntRect(520, 39, 23, 38));
        standardenemydataFrames["Right"].push_back(sf::IntRect(520, 77, 23, 39));
        standardenemydataFrames["Right"].push_back(sf::IntRect(521, 116, 22, 38));
        standardenemydataFrames["Right"].push_back(sf::IntRect(519, 154, 25, 38));
        standardenemydataFrames["Left"].push_back(sf::IntRect(519, 194, 26, 38));
        standardenemydataFrames["Left"].push_back(sf::IntRect(521, 233, 23, 38));
        standardenemydataFrames["Left"].push_back(sf::IntRect(520, 272, 22, 39));
        standardenemydataFrames["Left"].push_back(sf::IntRect(521, 311, 22, 38));
        standardenemydataFrames["Left"].push_back(sf::IntRect(520, 351, 25, 38));
        standardenemydataFrames["UpHeadRight"].push_back(sf::IntRect(518, 392, 30, 38));
        standardenemydataFrames["UpHeadRight"].push_back(sf::IntRect(518, 392, 30, 38));
        standardenemydataFrames["UpHeadRight"].push_back(sf::IntRect(518, 392, 30, 38));
        standardenemydataFrames["UpHeadRight"].push_back(sf::IntRect(518, 392, 30, 38));
        standardenemydataFrames["UpHeadRight"].push_back(sf::IntRect(518, 392, 30, 38));
        standardenemydataFrames["UpHeadLeft"].push_back(sf::IntRect(518, 430, 29, 38));
        standardenemydataFrames["UpHeadLeft"].push_back(sf::IntRect(518, 430, 29, 38));
        standardenemydataFrames["UpHeadLeft"].push_back(sf::IntRect(518, 430, 29, 38));
        standardenemydataFrames["UpHeadLeft"].push_back(sf::IntRect(518, 430, 29, 38));
        standardenemydataFrames["UpHeadLeft"].push_back(sf::IntRect(518, 430, 29, 38));
        standardenemydataFrames["Stay"].push_back(sf::IntRect(565, 470, 24, 39));
        standardenemydataFrames["Stay"].push_back(sf::IntRect(563, 509, 26, 41));
        standardenemydataFrames["Stay"].push_back(sf::IntRect(563, 551, 34, 47));
        standardenemydataFrames["Stay"].push_back(sf::IntRect(556, 606, 50, 54));
        standardenemydataFrames["Stay"].push_back(sf::IntRect(539, 663, 90, 79));
        standardenemydataFrames["Stay"].push_back(sf::IntRect(527, 745, 123, 79));
        standardenemydataFrames["Stay"].push_back(sf::IntRect(514, 828, 142, 79));

    }

//// Static member definitions
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::blipFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::blopFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::bossFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::bossbullFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::forkenemydataFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::presentenemydataFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::riflegunbullFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::rifleguncharFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::rifleguncharblopFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::shotgunbullFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::shotguncharFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::shotguncharblopFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::standardbulletFrames;
//std::map<std::string, std::vector<sf::IntRect>> GameAnimations::standardenemydataFrames;
