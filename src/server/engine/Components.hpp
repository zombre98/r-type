/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** rtype
*/

#pragma once

#include <memory>
#include <chrono>
#include <bitset>

namespace ecs {

    struct Component {
	    bool updated{true};
    };

    struct Player : public Component {
        Player() = delete;
        explicit Player(std::size_t _id) : id{_id} {};
        ~Player() = default;
        std::size_t id;
    };

    struct Velocity : public Component {
        Velocity() = delete;

	    Velocity(int w, int v) :
		    x(w),
		    y(v) {
        };
        ~Velocity() = default;
	    int x;
	    int y;
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

	    explicit LifePoint(int basicLifePoint) :
		    lifePoint(basicLifePoint) {
	    }
        ~LifePoint() = default;
        int lifePoint;
    };

    struct Score : public Component {
        Score() = delete;

	    explicit Score(int sc) :
		    score(sc) {
	    }
        ~Score() = default;
        int score;
    };

    struct Input : public Component {
	    enum Action : std::size_t {
		    Left,
		    Right,
		    Up,
		    Down,
		    Shoot,
		    Count
	    };

	    Input() = default;

	    explicit Input(Action a) {
		    input.set(a, true);
	    };
	    ~Input() = default;
	    std::bitset<Count> input;
    };

    struct Damage : public Component {
        Damage() = delete;

	    explicit Damage(int d) :
		    damage(d) {
	    }
        ~Damage() = default;
        int damage;
    };

	struct EnemyType : public Component {
		enum class Enemy : std::size_t {
			CLASSIC,
			SHIP,
                        SINUS,
		};

		EnemyType() = delete;
		EnemyType(Enemy t) : type(t) {}
		~EnemyType() = default;
		Enemy type;
	};

    struct ShotType : public Component {
        enum class Shot : std::size_t {
            ALLY,
            ENEMY,
            SHIPENEMY,
            SINUSENEMY
        };

        ShotType() = delete;

	    explicit ShotType(Shot t) :
		    type(t) {
	    }
        ~ShotType() = default;
        Shot type;
    };

    struct Hitbox : public Component {
        Hitbox() = delete;
        Hitbox(int w, int h): width(w), height(h) {}
        ~Hitbox() = default;
        int width;
        int height;
    };
}
