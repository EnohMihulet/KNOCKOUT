#include "../../include/helpers/characterDataManager.h"

namespace knockOut {

    void CharacterDataManager::loadTable() {
        _characterMoveDefs[CharacterType::Player] = {
        {CharacterState::idle, 0, 0, {10, 10}},
        {CharacterState::rJab, 0, 2, {4,4, 7}},
        {CharacterState::bodyBlock, 0, 5, {30}},
        {CharacterState::headBlock, 0, 6, {30}},
        {CharacterState::rDodge, 0, 7, {30}},        
        {CharacterState::lDodge, 0, 8, {30}},
        {CharacterState::lHook, 1, 0, {10, 20}},
        {CharacterState::rHook, 1, 2, {10, 20}},
        {CharacterState::upperCut, 1, 4, {10, 25, 15}},
        {CharacterState::rHit, 1, 7, {40}},
        {CharacterState::lHit, 1, 8, {40}}
        };

        _characterMoveDefs[CharacterType::BaldBull] = {
        {CharacterState::idle, 0, 0, {15, 10, 15, 10}},
        {CharacterState::bodyBlock, 1, 0, {30}},
        {CharacterState::rJab, 1, 1, {15}},
        {CharacterState::rHook, 1, 2, {25}},
        {CharacterState::upperCut, 2, 0, {15, 40}},
        {CharacterState::celebrate, 4, 2, {25, 25}}
        };

        _characterMoveDefs[CharacterType::GlassJoe] = {
        {CharacterState::idle, 0, 0, {5, 10, 20, 15, 20, 15}},
        {CharacterState::taunt, 0, 6, {15, 20}},
        {CharacterState::rJab, 1, 0, {10, 10, 20}},
        {CharacterState::upperCut, 1, 3, {15, 15, 30}},
        {CharacterState::bDodge, 1, 6, {5, 30}},
        {CharacterState::lDodge, 2, 0, {15, 15, 20}},
        {CharacterState::rHook, 2, 3, {15, 15, 20}},
        {CharacterState::headBlock, 3, 0, {30}},
        {CharacterState::bodyBlock, 3, 1, {30}},
        {CharacterState::duck, 3, 2, {30}},
        {CharacterState::rDodge, 3, 3, {15, 20}},
        {CharacterState::lDodge, 3, 5, {15, 20}},
        {CharacterState::rHit, 4, 0, {25}},
        {CharacterState::bodyHit, 4, 1, {25}},
        {CharacterState::lHit, 4, 2, {25}},
        {CharacterState::lKnockDown, 5, 0, {20, 20, 30}},
        {CharacterState::rKnockDown, 6, 0, {20, 20, 30}},
        {CharacterState::lGetUp, 5, 3, {20, 30}},
        {CharacterState::rGetUp, 6, 3, {20, 30}}
        };
    }
}