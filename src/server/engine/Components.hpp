/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** rtype
*/

#pragma once

#include <memory>
#include <chrono>

namespace ecs {

    struct Component {
    };

    struct Player : public Component {
        Player() = delete;
        explicit Player(std::size_t _id) : id{_id} {};
        ~Player() = default;
        std::size_t id;
    };

    struct Velocity : public Component {
        Velocity() = delete;
        Velocity(float w, float v) : x(w), y(v) {
        };
        ~Velocity() = default;
        float x;
        float y;
    };

    struct Orientation : public Component {
        Orientation() = delete;
        explicit Orientation(float ori) : orientation(ori) {
        };
        ~Orientation() = default;
        float orientation;
    };

    struct Position : public Component {
        Position(int d, int v) : x(d), y(v) {
        };
        ~Position() = default;
        int x;
        int y;
    };

    struct LifePoint : public Component {
        LifePoint() = delete;
        LifePoint(int basicLifePoint) : lifePoint(basicLifePoint) {}
        ~LifePoint() = default;
        int lifePoint;
    };

    struct Score : public Component {
        Score() = delete;
        Score(int sc) : score(sc) {}
        ~Score() = default;
        int score;
    };

    struct Input : public Component {
        Input() = default;
        ~Input() = default;
        bool up, down, left, right, shoot;
    };

}
