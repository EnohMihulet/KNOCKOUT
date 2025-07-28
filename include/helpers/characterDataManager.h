#pragma once

#include <unordered_map>
#include <vector>

namespace knockOut {

    const int CHARACTER_NUMBER = 2;
    const int CHARACTER_STATE_NUMBER = 22;

    enum class CharacterType {
        Player,
        BaldBull,
        GlassJoe
    };

    enum CharacterState {
        idle, lJab, rJab, lHook, rHook, upperCut,
        bodyBlock, headBlock, lDodge, rDodge, bDodge,
        lHit, rHit, bodyHit, headHit,
        lKnockDown, rKnockDown, lGetUp, rGetUp,
        taunt, duck, celebrate, 
    };

    struct MoveDef {CharacterState state; int row, startCol; std::vector<int> frameTimes; };

    class CharacterDataManager {
    public:

        CharacterDataManager() {};

        void loadTable();
        std::unordered_map<CharacterType, std::vector<MoveDef>> _characterMoveDefs;
    };
}